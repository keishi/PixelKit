/*
 *  TriangleFace.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/16/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef TriangleFace_h
#define TriangleFace_h

#include "Vertex.h"
#include "Surface.h"

namespace PixelKit {
    class TriangleFace : public Surface {
    public:
        TriangleFace(VertexRef v0, VertexRef v1, VertexRef v2);
        
        void setMaterial(Material* material) { m_material = material; }
        void setIsDoubleSided(bool b) { m_isDoubleSided = b; }
        
        void updateBoudingBox();
        
        bool hit(const Ray& ray, HitInfo *hitInfo);
        void drawGL();
        void applyTransformation(const Matrix4x4& t);
        
    private:
        VertexRef m_v0;
        VertexRef m_v1;
        VertexRef m_v2;
        Vector3 m_normal;
        Material* m_material;
        bool m_isDoubleSided;
    };
    
    typedef TriangleFace* TriangleFaceRef;
}

#endif
