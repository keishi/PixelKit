/*
 *  Surface.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/15/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef Surface_h
#define Surface_h

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

#include "Matrix4x4.h"
#include "BoundingBox.h"
#include "Material.h"
#include "Vector2.h"

namespace PixelKit {
    class Surface;
    
    typedef Surface* SurfaceRef;
    typedef struct {
        Vector3 position;
        Vector3 normal;
        MaterialRef material;
        float distance;
        SurfaceRef surface;
        Ray ray;
        Vector2 uv;
    } HitInfo;
    
    class Surface {
    public:
        Surface()
        : m_boundingBox(kBoundingBoxInfinite)
        {
        }
        
        const BoundingBox& boundingBox() const { return m_boundingBox; }
        
        virtual bool hit(const Ray& ray, HitInfo* hitInfo) = 0;
        virtual void drawGL() = 0;
        virtual void applyTransformation(const Matrix4x4& t) = 0;
        
    protected:
        BoundingBox m_boundingBox;
    };
}

#endif
