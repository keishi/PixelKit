/*
 *  Vector4.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/7/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef Vector4_h
#define Vector4_h

#include "Vector3.h"

namespace PixelKit {
    class Vector4 {
    public:
        Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
        Vector4(float vx, float vy, float vz, float vw) : x(vx), y(vy), z(vz), w(vw) { }
        Vector4(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) { }
        Vector4(const Vector3& v) : x(v.x), y(v.y), z(v.z), w(0.0f) { }
        
        void set(Vector4 &v) { x = v.x; y = v.y; z = v.z; w = v.w; }
        
        inline float operator[](int i) const;
        Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }
        Vector4& operator=(const Vector4& a)
        {
            x = a.x;
            y = a.y;
            z = a.z;
            w = a.w;
            return *this;
        }
        
        float dot(Vector4 &v) const { return x * v.x + y * v.y + z * v.z + w * v.w; }
        
        float norm() const { return sqrtf(x * x + y * y + z * z + w * w); }
        float normSq() const { return (x * x + y * y + z * z + w * w); }
        Vector4& normalize() 
        {
            float normInv = 1.0f / norm();
            x = x * normInv;
            y = y * normInv;
            z = z * normInv;
            w = w * normInv;
            return *this;
        }
        
        union {
            struct { float x, y, z, w; };
            struct { float cell[4]; };
        };
    };
    
    inline Vector4& operator+=(Vector4& a, const Vector4& b)
    {
        a.x = a.x + b.x;
        a.y = a.y + b.y;
        a.z = a.z + b.z;
        a.w = a.w + b.w;
        return a;
    }
    
    inline Vector4& operator-=(Vector4& a, const Vector4& b)
    {
        a.x = a.x - b.x;
        a.y = a.y - b.y;
        a.z = a.z - b.z;
        a.w = a.w - b.w;
        return a;
    }
    
    inline Vector4& operator*=(Vector4& a, const Vector4& b)
    {
        a.x = a.x * b.x;
        a.y = a.y * b.y;
        a.z = a.z * b.z;
        a.w = a.w * b.w;
        return a;
    }
    
    inline Vector4& operator*=(Vector4& a, const float m)
    {
        a.x = a.x * m;
        a.y = a.y * m;
        a.z = a.z * m;
        a.w = a.w * m;
        return a;
    }
    
    inline Vector4& operator/=(Vector4& a, const Vector4& b)
    {
        a.x = a.x / b.x;
        a.y = a.y / b.y;
        a.z = a.z / b.z;
        a.w = a.w / b.w;
        return a;
    }
    
    inline Vector4& operator/=(Vector4& a, const float m)
    {
        float mInv = 1.0f / m;
        return (a *= mInv);
    }
    
    inline float Vector4::operator[](int i) const
    {
        switch (i) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            case 3:
                return w;
        }
        return 0.0f;
    }
    
    struct v4
    {    
        float x, y, z, w;        
    };
    
    inline Vector4 operator+(const Vector4& a, const Vector4& b)
    {
        return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
    }
    
    inline Vector4 operator-(const Vector4& a, const Vector4& b)
    {
        return Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
    }
    
    inline Vector4 operator*(const Vector4& a, const Vector4& b)
    {
        return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
    }
    
    inline Vector4 operator*(const Vector4& a, const float m)
    {
        return Vector4(a.x * m, a.y * m, a.z * m, a.w * m);
    }
    
    inline Vector4 operator*(const float m, const Vector4& a)
    {
        return Vector4(a.x * m, a.y * m, a.z * m, a.w * m);
    }
    
    inline Vector4 operator/(const Vector4& a, const float m)
    {
        float mInv = 1.0f / m;
        return (a * mInv);
    }
    
    inline Vector4 operator/(const float m, const Vector4& a)
    {
        return Vector4(m / a.x, m / a.y, m / a.z, m / a.w);
    }
    
    inline int operator==(const Vector4& a, const Vector4& b)
    {
        return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
    }
    
    std::ostream& operator<<(std::ostream& out, const Vector4& a);
}

#endif
