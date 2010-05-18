/*
 *  Vector2.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/14/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef Vector2_h
#define Vector2_h

namespace PixelKit {
    class Vector2 {
    public:
        Vector2() : x(0.0f), y(0.0f) { }
        Vector2(float v) : x(v), y(v) { }
        Vector2(float vx, float vy) : x(vx), y(vy) { }
        Vector2(const Vector2& v) : x(v.x), y(v.y) { }
        
        void set(Vector2 &v) { x = v.x; y = v.y; }
        
        Vector2 operator-() const { return Vector2(-x, -y); }
        Vector2& operator=(const Vector2& a)
        {
            x = a.x;
            y = a.y;
            return *this;
        }
        
        float norm() const { return sqrtf(x * x + y * y); }
        float normSq() const { return (x * x + y * y); }
        Vector2& normalize() 
        {
            float normInv = 1.0f / norm();
            x = x * normInv;
            y = y * normInv;
            return *this;
        }
        Vector2 normalized() const
        {
            float normInv = 1.0f / norm();
            return Vector2(x * normInv, y * normInv);
        }
        
        union {
            struct { float x, y; };
            struct { float u, v; };
            struct { float width, height; };
            struct { float cell[2]; };
        };
    };
    
    inline Vector2& operator+=(Vector2& a, const Vector2& b)
    {
        a.x = a.x + b.x;
        a.y = a.y + b.y;
        return a;
    }
    
    inline Vector2& operator-=(Vector2& a, const Vector2& b)
    {
        a.x = a.x - b.x;
        a.y = a.y - b.y;
        return a;
    }
    
    inline Vector2& operator*=(Vector2& a, const Vector2& b)
    {
        a.x = a.x * b.x;
        a.y = a.y * b.y;
        return a;
    }
    
    inline Vector2& operator*=(Vector2& a, const float m)
    {
        a.x = a.x * m;
        a.y = a.y * m;
        return a;
    }
    
    inline Vector2& operator/=(Vector2& a, const Vector2& b)
    {
        a.x = a.x / b.x;
        a.y = a.y / b.y;
        return a;
    }
    
    inline Vector2& operator/=(Vector2& a, const float m)
    {
        float mInv = 1.0f / m;
        return (a *= mInv);
    }
    
    inline Vector2 operator+(const Vector2& a, const Vector2& b)
    {
        return Vector2(a.x + b.x, a.y + b.y);
    }
    
    inline Vector2 operator-(const Vector2& a, const Vector2& b)
    {
        return Vector2(a.x - b.x, a.y - b.y);
    }
    
    inline Vector2 operator*(const Vector2& a, const Vector2& b)
    {
        return Vector2(a.x * b.x, a.y * b.y);
    }
    
    inline Vector2 operator*(const Vector2& a, const float m)
    {
        return Vector2(a.x * m, a.y * m);
    }
    
    inline Vector2 operator*(const float m, const Vector2& a)
    {
        return Vector2(a.x * m, a.y * m);
    }
    
    inline Vector2 operator/(const Vector2& a, const float m)
    {
        float mInv = 1.0f / m;
        return (a * mInv);
    }
    
    inline Vector2 operator/(const float m, const Vector2& a)
    {
        return Vector2(m / a.x, m / a.y);
    }
    
    inline int operator==(const Vector2& a, const Vector2& b)
    {
        return (a.x == b.x && a.y == b.y);
    }
    
    std::ostream& operator<<(std::ostream& out, const Vector2& a);
}

#endif
