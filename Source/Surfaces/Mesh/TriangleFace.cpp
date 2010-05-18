/*
 *  TriangleFace.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/16/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "TriangleFace.h"

namespace PixelKit {
    const float kSmallValue = -0.000001;
    
    TriangleFace::TriangleFace(VertexRef v0, VertexRef v1, VertexRef v2)
    : m_v0(v0)
    , m_v1(v1)
    , m_v2(v2)
    , m_isDoubleSided(false)
    {
        updateBoudingBox();
    }
    
    void TriangleFace::updateBoudingBox()
    {
        Vector3 v02 = *m_v2 - *m_v0;
        Vector3 v01 = *m_v1 - *m_v0;
        m_normal = v02.cross(v01).normalize();
        
        Vector3 min = Vector3(MIN(MIN(m_v0->x, m_v1->x), m_v2->x),
                              MIN(MIN(m_v0->y, m_v1->y), m_v2->y),
                              MIN(MIN(m_v0->z, m_v1->z), m_v2->z));
        Vector3 max = Vector3(MAX(MAX(m_v0->x, m_v1->x), m_v2->x),
                              MAX(MAX(m_v0->y, m_v1->y), m_v2->y),
                              MAX(MAX(m_v0->z, m_v1->z), m_v2->z));
        
        m_boundingBox = BoundingBox(min, max);
    }
    
    bool TriangleFace::hit(const Ray& ray, HitInfo *hitInfo)
    {
        if (!m_boundingBox.doesHit(ray)) {
            return false;
        }
        
        float vn = ray.direction().dot(m_normal);
        bool isRightSide = vn < 0;
        if (fabs(vn) < kSmallValue)
            return false;
        if (isRightSide && !m_isDoubleSided) {
            return false;
        }
        Vector3 v0r = ray.origin() - (*m_v0);
        float xpn = m_normal.dot(v0r);
        float distance = -xpn / vn;
        if (distance < 0)
            return false;
        Vector3 hitPosition = ray.pointAtDistance(distance);
        
        Vector3 v0h = hitPosition - (*m_v0);
        Vector3 v01 = (*m_v1) - (*m_v0);
        Vector3 cross0 = v0h.cross(v01);
        if (cross0.dot(m_normal) < kSmallValue) {
            return false;
        }
        Vector3 v1h = hitPosition - (*m_v1);
        Vector3 v12 = (*m_v2) - (*m_v1);
        Vector3 cross1 = v1h.cross(v12);
        if (cross1.dot(m_normal) < kSmallValue) {
            return false;
        }
        Vector3 v2h = hitPosition - (*m_v2);
        Vector3 v20 = (*m_v0) - (*m_v2);
        Vector3 cross2 = v2h.cross(v20);
        if (cross2.dot(m_normal) < kSmallValue) {
            return false;
        }
        
        hitInfo->distance = distance;
        hitInfo->material = m_material;
        hitInfo->normal = m_normal;
        hitInfo->position = hitPosition;
        hitInfo->ray = ray;
        hitInfo->surface = this;
        return true;
    }
    
    void TriangleFace::drawGL()
    {
        GLfloat diffuseColor[] = {m_material->color().red, m_material->color().green, m_material->color().blue, 1.0};
        
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseColor);
        
        glBegin(GL_TRIANGLES);
        glNormal3fv(&m_normal.x);
        glVertex3fv(&m_v0->x);
        glVertex3fv(&m_v1->x);
        glVertex3fv(&m_v2->x);
        glEnd();
    }
    
    void TriangleFace::applyTransformation(const Matrix4x4& t)
    {
        // Transformation is done applied to the mesh. This just updates the bounding box.
        
        Vector3 min = Vector3(MIN(MIN(m_v0->x, m_v1->x), m_v2->x),
                              MIN(MIN(m_v0->y, m_v1->y), m_v2->y),
                              MIN(MIN(m_v0->z, m_v1->z), m_v2->z));
        Vector3 max = Vector3(MAX(MAX(m_v0->x, m_v1->x), m_v2->x),
                              MAX(MAX(m_v0->y, m_v1->y), m_v2->y),
                              MAX(MAX(m_v0->z, m_v1->z), m_v2->z));
        
        m_boundingBox = BoundingBox(min, max);
    }
}