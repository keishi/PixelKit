/*
 *  Vector3.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/6/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef Vector3_h
#define Vector3_h

namespace PixelKit {
    
    class Vector3 {
    public:
        Vector3() : x(0.0f), y(0.0f), z(0.0f) { }
        Vector3(float v) : x(v), y(v), z(v) { }
        Vector3(float vx, float vy, float vz) : x(vx), y(vy), z(vz) { }
        Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) { }
        
        void set(Vector3 &v) { x = v.x; y = v.y; z = v.z; }
        
        Vector3 operator-() const { return Vector3(-x, -y, -z); }
        Vector3& operator=(const Vector3& a)
        {
            x = a.x;
            y = a.y;
            z = a.z;
            return *this;
        }
        
        float dot(Vector3 &v) const { return x * v.x + y * v.y + z * v.z; }
        Vector3 cross(Vector3 &v) const
        {
            return Vector3(y * v.z - z * v.y,
                           z * v.x - x * v.z,
                           x * v.y - y * v.x);
        }
        
        float norm() const { return sqrtf(x * x + y * y + z * z); }
        float normSq() const { return (x * x + y * y + z * z); }
        Vector3& normalize() 
        {
            float normInv = 1.0f / norm();
            x = x * normInv;
            y = y * normInv;
            z = z * normInv;
            return *this;
        }
        Vector3 normalized() const
        {
            float normInv = 1.0f / norm();
            return Vector3(x * normInv, y * normInv, z * normInv);
        }
        
        union {
            struct { float x, y, z; };
            struct { float cell[3]; };
        };
    };
    
    inline Vector3& operator+=(Vector3& a, const Vector3& b)
    {
        a.x = a.x + b.x;
        a.y = a.y + b.y;
        a.z = a.z + b.z;
        return a;
    }
    
    inline Vector3& operator-=(Vector3& a, const Vector3& b)
    {
        a.x = a.x - b.x;
        a.y = a.y - b.y;
        a.z = a.z - b.z;
        return a;
    }
    
    inline Vector3& operator*=(Vector3& a, const Vector3& b)
    {
        a.x = a.x * b.x;
        a.y = a.y * b.y;
        a.z = a.z * b.z;
        return a;
    }
    
    inline Vector3& operator*=(Vector3& a, const float m)
    {
        a.x = a.x * m;
        a.y = a.y * m;
        a.z = a.z * m;
        return a;
    }
    
    inline Vector3& operator/=(Vector3& a, const Vector3& b)
    {
        a.x = a.x / b.x;
        a.y = a.y / b.y;
        a.z = a.z / b.z;
        return a;
    }
    
    inline Vector3& operator/=(Vector3& a, const float m)
    {
        float mInv = 1.0f / m;
        return (a *= mInv);
    }
    
    inline Vector3 operator+(const Vector3& a, const Vector3& b)
    {
        return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
    }
    
    inline Vector3 operator-(const Vector3& a, const Vector3& b)
    {
        return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
    }
    
    inline Vector3 operator*(const Vector3& a, const Vector3& b)
    {
        return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
    }
    
    inline Vector3 operator*(const Vector3& a, const float m)
    {
        return Vector3(a.x * m, a.y * m, a.z * m);
    }
    
    inline Vector3 operator*(const float m, const Vector3& a)
    {
        return Vector3(a.x * m, a.y * m, a.z * m);
    }
    
    inline Vector3 operator/(const Vector3& a, const float m)
    {
        float mInv = 1.0f / m;
        return (a * mInv);
    }
    
    inline Vector3 operator/(const float m, const Vector3& a)
    {
        return Vector3(m / a.x, m / a.y, m / a.z);
    }
    
    inline int operator==(const Vector3& a, const Vector3& b)
    {
        return (a.x == b.x && a.y == b.y && a.z == b.z);
    }
    
    std::ostream& operator<<(std::ostream& out, const Vector3& a);
}

#endif
