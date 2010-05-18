/*
 *  Triangle.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/7/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef Triangle_h
#define Triangle_h

#include "Surface.h"

namespace PixelKit {
    class Triangle : public Surface {
    public:
        Triangle(Vector3& v0, Vector3& v1, Vector3& v2);
        
        const Material* material() const { return m_material; }
        bool isDoubleSided() const { return m_isDoubleSided; }
        
        void setMaterial(Material* material) { m_material = material; }
        void setIsDoubleSided(bool b) { m_isDoubleSided = b; }
        
        bool hit(const Ray& ray, HitInfo *hitInfo);
        void drawGL();
        void applyTransformation(const Matrix4x4& t);
        
    private:
        Vector3 m_v0;
        Vector3 m_v1;
        Vector3 m_v2;
        Vector3 m_normal;
        Material* m_material;
        bool m_isDoubleSided;
    };
    
    typedef Triangle* TriangleRef;
}

#endif
