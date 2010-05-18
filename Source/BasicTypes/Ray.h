/*
 *  Ray.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/6/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef Ray_h
#define Ray_h

#include "Vector3.h"

namespace PixelKit {
    class Ray {
    public:
        Ray() { }
        Ray(Vector3& origin, Vector3& direction);
        
        const Vector3& origin() const { return m_origin; }
        const Vector3& direction() const { return m_direction; }
        
        Vector3 pointAtDistance(float distance) const { return m_origin + m_direction * distance; }
        
    private:
        Vector3 m_origin;
        Vector3 m_direction;
    };
    
    std::ostream& operator<<(std::ostream& out, const Ray& a);
}

#endif
