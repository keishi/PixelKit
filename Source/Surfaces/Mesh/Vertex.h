/*
 *  Vertex.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/16/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef Vertex_h
#define Vertex_h

#include "Vector3.h"

namespace PixelKit {
    class Vertex : public Vector3 {
    public:
        Vertex() : Vector3() { }
        Vertex(float v) : Vector3(v) { }
        Vertex(float vx, float vy, float vz) : Vector3(vx, vy, vz) { }
        Vertex(const Vector3& v) : Vector3(v) { }
    };
    
    typedef Vertex* VertexRef;
}

#endif
