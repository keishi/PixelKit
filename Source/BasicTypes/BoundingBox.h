/*
 *  BoundingBox.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/9/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef BoundingBox_h
#define BoundingBox_h

#include "Ray.h"

namespace PixelKit {
    class BoundingBox {
    public:
        BoundingBox(const Vector3& min, const Vector3& max) : m_minPosition(min), m_maxPosition(max) { }
        
        float xLength() const { return m_maxPosition.x - m_minPosition.x; }
        float yLength() const { return m_maxPosition.y - m_minPosition.y; }
        float zLength() const { return m_maxPosition.z - m_minPosition.z; }
        
        const Vector3& minPosition() const { return m_minPosition; }
        const Vector3& maxPosition() const { return m_maxPosition; }
        
        inline bool isNull() const;
        inline bool isEmpty() const;
        inline bool isInfinite() const;
        
        bool doesHit(const Ray& ray) const
        {
            if (isInfinite())
                return true;
            if (isNull())
                return false;
            
            float t_min, t_max;
            if (ray.direction().x >= 0.0f) {
                t_min = (m_minPosition.x - ray.origin().x) / ray.direction().x;
                t_max = (m_maxPosition.x - ray.origin().x) / ray.direction().x;
            } else {
                t_min = (m_maxPosition.x - ray.origin().x) / ray.direction().x;
                t_max = (m_minPosition.x - ray.origin().x) / ray.direction().x;
            }
            float t_y_min, t_y_max;
            if (ray.direction().y >= 0.0f) {
                t_y_min = (m_minPosition.y - ray.origin().y) / ray.direction().y;
                t_y_max = (m_maxPosition.y - ray.origin().y) / ray.direction().y;
            } else {
                t_y_min = (m_maxPosition.y - ray.origin().y) / ray.direction().y;
                t_y_max = (m_minPosition.y - ray.origin().y) / ray.direction().y;
            }
            //if (t_min > t_y_max || t_y_min > t_max)
            //    return false;
            
            if (t_y_min > t_min)
                t_min = t_y_min;
            
            if (t_y_max < t_max)
                t_max = t_y_max;
            
            float t_z_min, t_z_max;
            if (ray.direction().z >= 0.0f) {
                t_z_min = (m_minPosition.z - ray.origin().z) / ray.direction().z;
                t_z_max = (m_maxPosition.z - ray.origin().z) / ray.direction().z;
            } else {
                t_z_min = (m_maxPosition.z - ray.origin().z) / ray.direction().z;
                t_z_max = (m_minPosition.z - ray.origin().z) / ray.direction().z;
            }
            //if (t_min > t_z_max || t_z_min > t_max)
            //    return false;
            
            if (t_z_min > t_min)
                t_min = t_z_min;
            
            if (t_z_max < t_max)
                t_max = t_z_max;
            
            return (t_min < 100.0f && t_max > 0.0f);

            return !((ray.direction().x > 0.0 && ray.origin().x > m_maxPosition.x) ||
                     (ray.direction().x < 0.0 && ray.origin().x < m_minPosition.x) ||
                     (ray.direction().y > 0.0 && ray.origin().y > m_maxPosition.y) ||
                     (ray.direction().y < 0.0 && ray.origin().y < m_minPosition.y) ||
                     (ray.direction().z > 0.0 && ray.origin().z > m_maxPosition.z) ||
                     (ray.direction().z < 0.0 && ray.origin().z < m_minPosition.z));
        }
        BoundingBox unionBox(const BoundingBox& box) const;
        bool intersectsBox(const BoundingBox& box) const
        {
            if (isNull() || box.isNull())
                return false;
            if (isInfinite() || box.isInfinite())
                return true;
            if (box.minPosition().x > m_maxPosition.x || box.maxPosition().x < m_minPosition.x)
                return false;
            if (box.minPosition().y > m_maxPosition.y || box.maxPosition().y < m_minPosition.y)
                return false;
            if (box.minPosition().z > m_maxPosition.z || box.maxPosition().z < m_minPosition.z)
                return false;
            return true;
        }
        
    private:
        Vector3 m_minPosition;
        Vector3 m_maxPosition;
    };
    
    inline int operator==(const BoundingBox& a, const BoundingBox& b)
    {
        return (a.minPosition() == b.minPosition() && a.maxPosition() == b.maxPosition());
    }
    
    std::ostream& operator<<(std::ostream& out, const BoundingBox& a);
    
    const BoundingBox kBoundingBoxInfinite = BoundingBox(Vector3(-INFINITY, -INFINITY, -INFINITY), Vector3(INFINITY, INFINITY, INFINITY));
    const BoundingBox kBoundingBoxNull = BoundingBox(Vector3(NAN, NAN, NAN), Vector3(NAN, NAN, NAN));
    const BoundingBox kBoundingBoxZero = BoundingBox(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
    
    inline bool BoundingBox::isNull() const { return *this == kBoundingBoxNull; }
    inline bool BoundingBox::isEmpty() const { return isNull() || xLength() == 0.0f || yLength() == 0.0f || zLength() == 0.0f; }
    inline bool BoundingBox::isInfinite() const { return *this == kBoundingBoxInfinite; }
}

#endif
