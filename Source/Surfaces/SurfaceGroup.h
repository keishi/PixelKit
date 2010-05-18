/*
 *  SurfaceGroup.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/15/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef SurfaceGroup_h
#define SurfaceGroup_h

#include <vector>

#include "Surface.h"

namespace PixelKit {
    class SurfaceGroup : public Surface {
    public:
        SurfaceGroup()
        {
            m_boundingBox = kBoundingBoxNull;
        }
        
        std::vector<SurfaceRef>& surfaces() { return m_surfaces; };
        void addSurface(Surface* s)
        {
            m_surfaces.push_back(s);
            m_boundingBox = m_boundingBox.unionBox(s->boundingBox());
            m_surfaces.push_back(s);
        }
        
        bool hit(const Ray& ray, HitInfo* hitInfo);
        void drawGL();
        void applyTransformation(const Matrix4x4& t);
        
    private:
        std::vector<SurfaceRef> m_surfaces;
    };
    
    typedef SurfaceGroup* SurfaceGroupRef;
}

#endif
