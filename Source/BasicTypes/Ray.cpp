/*
 *  Ray.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/6/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "Ray.h"

namespace PixelKit {
    
    Ray::Ray(Vector3& origin, Vector3& direction)
    {
        m_origin = origin;
        m_direction = direction.normalized();
    }
    
    std::ostream& operator<<(std::ostream& out, const Ray& a)
    {
        out << "Ray(origin:";
        out << a.origin();
        out << ", direction:";
        out << a.direction();
        out << ")";
        return out;
    }
    
}