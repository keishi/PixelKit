/*
 *  FaceVertexMesh.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/16/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef FaceVertexMesh_h
#define FaceVertexMesh_h

#include <vector>

#include "Surface.h"
#include "TriangleFace.h"

namespace PixelKit {
    class FaceVertexMesh : public Surface {
    public:
        FaceVertexMesh()
        {
            m_boundingBox = kBoundingBoxNull;
        }
        
        void loadObj(const char *filename);
        
        bool hit(const Ray& ray, HitInfo *hitInfo);
        void drawGL();
        void applyTransformation(const Matrix4x4& t);
        
    private:
        std::vector<VertexRef> m_vertexList;
        std::vector<TriangleFaceRef> m_faceList;
        std::vector<MaterialRef> m_materialList;
    };
}

#endif
