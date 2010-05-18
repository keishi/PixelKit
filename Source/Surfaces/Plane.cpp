/*
 *  Plane.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/17/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "Plane.h"

namespace PixelKit {
    bool Plane::hit(const Ray& ray, HitInfo *hitInfo)
    {
        float d = ray.direction().dot(m_normal);
        if (d != 0.0) {
            float dist = -(ray.origin().dot(m_normal) + m_distance) / d;
            if (dist > 0.0001) {
                Vector3 hitPosition = ray.pointAtDistance(dist);
                hitInfo->distance = dist;
                hitInfo->normal = m_normal;
                hitInfo->material = m_material;
                hitInfo->position = hitPosition;
                hitInfo->surface = this;
                hitInfo->ray = ray;
                hitInfo->uv = Vector2(m_uAxis.dot(hitPosition), m_vAxis.dot(hitPosition));
                return true;
            }
        }
        return false;
    }
    
    void Plane::drawGL()
    {
        // TODO: Implement;
    }
    void Plane::applyTransformation(const Matrix4x4& t)
    {
        // TODO: Implement;
    }
    
    std::ostream& operator<<(std::ostream& out, const Plane& a)
    {
        out << "Plane(normal:";
        out << a.normal();
        out << ", distance:";
        out << a.distance();
        out << ")";
        return out;
    }
}