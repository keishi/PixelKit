/*
 *  SurfaceGroup.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/15/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "SurfaceGroup.h"

namespace PixelKit {
    bool SurfaceGroup::hit(const Ray& ray, HitInfo* hitInfo)
    {
        if (!m_boundingBox.doesHit(ray)) {
            return false;
        }
        
        float hitDistance = INFINITY;
        HitInfo intersectionInfo;
        
        // find nearest intersection
        for (unsigned int i = 0; i < m_surfaces.size(); i++) {
            SurfaceRef s = m_surfaces[i];
            if (s->hit(ray, &intersectionInfo)) {
                if (intersectionInfo.distance < hitDistance) {
                    hitDistance = intersectionInfo.distance;
                    *hitInfo = intersectionInfo;
                }
            }
        }
        return hitDistance != INFINITY;
    }
    
    void SurfaceGroup::drawGL()
    {
        for (unsigned int i = 0; i < m_surfaces.size(); i++) {
            m_surfaces[i]->drawGL();
        }
    }
    
    void SurfaceGroup::applyTransformation(const Matrix4x4& t)
    {
        m_boundingBox = kBoundingBoxNull;
        for (unsigned int i = 0; i < m_surfaces.size(); i++) {
            Surface *s = m_surfaces[i];
            s->applyTransformation(t);
            m_boundingBox = m_boundingBox.unionBox(s->boundingBox());
        }
    }
}