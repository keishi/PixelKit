/*
 *  Sphere.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/15/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef Sphere_h
#define Sphere_h

#include "Surface.h"

namespace PixelKit {
    class Sphere : public Surface {
    public:
        Sphere(Vector3& center, float radius);
        
        const Vector3& center() const { return m_center; }
        float radius() const { return m_radius; }
        const MaterialRef material() const { return m_material; }
        
        void setMaterial(MaterialRef material) { m_material = material; }
        
        bool hit(const Ray& ray, HitInfo *hitInfo);
        void drawGL();
        void applyTransformation(const Matrix4x4& t);
        
    private:
        Vector3 m_center;
        float m_radius;
        float m_radiusSq;
        float m_radiusInv;
        MaterialRef m_material;
    };
    
    typedef Sphere* SphereRef;
}

#endif
