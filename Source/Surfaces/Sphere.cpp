/*
 *  Sphere.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/15/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "Sphere.h"

#define isnan(x) ((x) != (x))

namespace PixelKit {
    Sphere::Sphere(Vector3& center, float radius)
    : m_center(center)
    , m_radius(radius)
    , m_radiusSq(radius * radius)
    , m_radiusInv(1.0f / radius)
    {
        Vector3 r = Vector3(m_radius);
        Vector3 minPos = m_center - r;
        Vector3 maxPos = m_center + r;
        m_boundingBox = BoundingBox(minPos, maxPos);
    }
    
    bool Sphere::hit(const Ray& ray, HitInfo *hitInfo)
    {
        if (!m_boundingBox.doesHit(ray)) {
            return false;
        }
        
        Vector3 dist = m_center - ray.origin();
        float b = ray.direction().dot(dist);
        float discriminant = m_radiusSq - dist.normSq() + b * b;
        if (discriminant < 0.0) {
            return false;
        }
        
        // two possible intersections
        float t;
        float t0 = b - sqrt(discriminant);
        float t1 = b + sqrt(discriminant);
        if (t0 > 0.0001) {
            t = t0;
        } else if (t1 > 0.0001) {
            t = t1;
        } else {
            return false;
        }

        
        Vector3 hitPosition = ray.pointAtDistance(t);
        Vector3 hitNormal = (hitPosition - m_center) * m_radiusInv;
        hitInfo->distance = t;
        hitInfo->normal = hitNormal;
        hitInfo->material = m_material;
        hitInfo->position = hitPosition;
        hitInfo->surface = this;
        hitInfo->ray = ray;
        Vector3 ve(1.0f, 0.0f, 0.0f);
        Vector3 vn(0.0f, 1.0f, 0.0f);
        Vector3 vc = vn.cross(ve);
        float phi = acosf(-vn.dot(hitNormal));
        float theta = acosf(ve.dot(hitNormal) / sinf(phi)) * (1.0f / PI);
        float u = (vc.dot(hitNormal) >= 0.0f) ? 1.0f - theta : theta;
        float v = phi / PI;
        hitInfo->uv = Vector2(u, v);
        
        return true;
    }
    
    void Sphere::drawGL()
    {
        // TODO: Implement;
    }
    void Sphere::applyTransformation(const Matrix4x4& t)
    {
        m_center = t * m_center;
        m_radius = m_radius * t.m41();
        m_radiusSq = m_radius * m_radius;
        m_radiusInv = 1.0f / m_radius;
    }
    
    std::ostream& operator<<(std::ostream& out, const Sphere& a)
    {
        out << "Sphere(center:";
        out << a.center();
        out << ", radius:";
        out << a.radius();
        out << ")";
        return out;
    }
}