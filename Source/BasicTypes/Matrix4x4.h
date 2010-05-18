/*
 *  Matrix4x4.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/7/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef Matrix4x4_h
#define Matrix4x4_h

#include "Vector4.h"

namespace PixelKit {
    class Matrix4x4 {
    public:
        Matrix4x4()
        : m_m11(0.0f), m_m21(0.0f), m_m31(0.0f), m_m41(0.0f)
        , m_m12(0.0f), m_m22(0.0f), m_m32(0.0f), m_m42(0.0f)
        , m_m13(0.0f), m_m23(0.0f), m_m33(0.0f), m_m43(0.0f)
        , m_m14(0.0f), m_m24(0.0f), m_m34(0.0f), m_m44(0.0f)
        { }
        Matrix4x4(float m11, float m21, float m31, float m41, 
                  float m12, float m22, float m32, float m42,
                  float m13, float m23, float m33, float m43,
                  float m14, float m24, float m34, float m44)
        : m_m11(m11), m_m21(m21), m_m31(m31), m_m41(m41)
        , m_m12(m12), m_m22(m22), m_m32(m32), m_m42(m42)
        , m_m13(m13), m_m23(m23), m_m33(m33), m_m43(m43)
        , m_m14(m14), m_m24(m24), m_m34(m34), m_m44(m44)
        { }
        Matrix4x4(const Vector4& u, const Vector4& v, const Vector4& s, const Vector4& t)
        : m_m11(u.x), m_m21(v.x), m_m31(s.x), m_m41(t.x)
        , m_m12(u.y), m_m22(v.y), m_m32(s.y), m_m42(t.y)
        , m_m13(u.z), m_m23(v.z), m_m33(s.z), m_m43(t.z)
        , m_m14(u.w), m_m24(v.w), m_m34(s.w), m_m44(t.w)
        { }
        
        float m11() const { return m_m11; }
        float m21() const { return m_m21; }
        float m31() const { return m_m31; }
        float m41() const { return m_m41; }
        float m12() const { return m_m12; }
        float m22() const { return m_m22; }
        float m32() const { return m_m32; }
        float m42() const { return m_m42; }
        float m13() const { return m_m13; }
        float m23() const { return m_m23; }
        float m33() const { return m_m33; }
        float m43() const { return m_m43; }
        float m14() const { return m_m14; }
        float m24() const { return m_m24; }
        float m34() const { return m_m34; }
        float m44() const { return m_m44; }
        
        void setM11(const float v) { m_m11 = v; }
        void setM21(const float v) { m_m21 = v; }
        void setM31(const float v) { m_m31 = v; }
        void setM41(const float v) { m_m41 = v; }
        void setM12(const float v) { m_m12 = v; }
        void setM22(const float v) { m_m22 = v; }
        void setM32(const float v) { m_m32 = v; }
        void setM42(const float v) { m_m42 = v; }
        void setM13(const float v) { m_m13 = v; }
        void setM23(const float v) { m_m23 = v; }
        void setM33(const float v) { m_m33 = v; }
        void setM43(const float v) { m_m43 = v; }
        void setM14(const float v) { m_m14 = v; }
        void setM24(const float v) { m_m24 = v; }
        void setM34(const float v) { m_m34 = v; }
        void setM44(const float v) { m_m44 = v; }
        void set(float m11, float m21, float m31, float m41, 
                 float m12, float m22, float m32, float m42,
                 float m13, float m23, float m33, float m43,
                 float m14, float m24, float m34, float m44)
        {
            m_m11 = m11; m_m21 = m21; m_m31 = m31; m_m41 = m41;
            m_m12 = m12; m_m22 = m22; m_m32 = m32; m_m42 = m42;
            m_m13 = m13; m_m23 = m23; m_m33 = m33; m_m43 = m43;
            m_m14 = m14; m_m24 = m24; m_m34 = m34; m_m44 = m44;
        }
        
        void setToIndentity()
        {
            m_m11 = 1.0f; m_m21 = 0.0f; m_m31 = 0.0f; m_m41 = 0.0f;
            m_m12 = 0.0f; m_m22 = 1.0f; m_m32 = 0.0f; m_m42 = 0.0f;
            m_m13 = 0.0f; m_m23 = 0.0f; m_m33 = 1.0f; m_m43 = 0.0f;
            m_m14 = 0.0f; m_m24 = 0.0f; m_m34 = 0.0f; m_m44 = 1.0f;
        }
        
        bool isIdentity()
        {
            return m_m11 == 1.0f && m_m21 == 0.0f && m_m31 == 0.0f && m_m41 == 0.0f && 
                   m_m12 == 0.0f && m_m22 == 1.0f && m_m32 == 0.0f && m_m42 == 0.0f && 
                   m_m13 == 0.0f && m_m23 == 0.0f && m_m33 == 1.0f && m_m43 == 0.0f && 
                   m_m14 == 0.0f && m_m24 == 0.0f && m_m34 == 0.0f && m_m44 == 1.0f;
        }
        
        Matrix4x4& translate(float tx, float ty, float tz);
        Matrix4x4& translate(const Vector3& t);
        Matrix4x4& scale(float sx, float sy, float sz);
        Matrix4x4& scale(const Vector3& s);
        Matrix4x4& rotate(float rx, float ry, float rz);
        Matrix4x4& rotate(const Vector3& r);
        
        void transpose()
        {
            float temp;
            temp = m_m12; m_m12 = m_m21; m_m21 = temp;
            temp = m_m13; m_m13 = m_m31; m_m31 = temp;
            temp = m_m14; m_m14 = m_m41; m_m41 = temp;
            temp = m_m23; m_m23 = m_m32; m_m32 = temp;
            temp = m_m24; m_m24 = m_m42; m_m42 = temp;
            temp = m_m34; m_m34 = m_m43; m_m43 = temp;
        }
        
    private:
        float m_m11, m_m21, m_m31, m_m41;
        float m_m12, m_m22, m_m32, m_m42;
        float m_m13, m_m23, m_m33, m_m43;
        float m_m14, m_m24, m_m34, m_m44;
    };
    
    inline Matrix4x4& operator+=(Matrix4x4& a, const Matrix4x4& b)
    {
        a.setM11(a.m11() + b.m11());
        a.setM21(a.m21() + b.m21());
        a.setM31(a.m31() + b.m31());
        a.setM41(a.m41() + b.m41());
        a.setM12(a.m12() + b.m12());
        a.setM22(a.m22() + b.m22());
        a.setM32(a.m32() + b.m32());
        a.setM42(a.m42() + b.m42());
        a.setM13(a.m13() + b.m13());
        a.setM23(a.m23() + b.m23());
        a.setM33(a.m33() + b.m33());
        a.setM43(a.m43() + b.m43());
        a.setM13(a.m14() + b.m14());
        a.setM23(a.m24() + b.m24());
        a.setM33(a.m34() + b.m34());
        a.setM43(a.m44() + b.m44());
        
        return a;
    }
    
    inline Matrix4x4& operator-=(Matrix4x4& a, const Matrix4x4& b)
    {
        a.setM11(a.m11() - b.m11());
        a.setM21(a.m21() - b.m21());
        a.setM31(a.m31() - b.m31());
        a.setM41(a.m41() - b.m41());
        a.setM12(a.m12() - b.m12());
        a.setM22(a.m22() - b.m22());
        a.setM32(a.m32() - b.m32());
        a.setM42(a.m42() - b.m42());
        a.setM13(a.m13() - b.m13());
        a.setM23(a.m23() - b.m23());
        a.setM33(a.m33() - b.m33());
        a.setM43(a.m43() - b.m43());
        a.setM13(a.m14() - b.m14());
        a.setM23(a.m24() - b.m24());
        a.setM33(a.m34() - b.m34());
        a.setM43(a.m44() - b.m44());
        
        return a;
    }
    
    inline Matrix4x4& operator*=(Matrix4x4& a, float m)
    {
        a.setM11(a.m11() * m);
        a.setM21(a.m21() * m);
        a.setM31(a.m31() * m);
        a.setM41(a.m41() * m);
        a.setM12(a.m12() * m);
        a.setM22(a.m22() * m);
        a.setM32(a.m32() * m);
        a.setM42(a.m42() * m);
        a.setM13(a.m13() * m);
        a.setM23(a.m23() * m);
        a.setM33(a.m33() * m);
        a.setM43(a.m43() * m);
        a.setM13(a.m14() * m);
        a.setM23(a.m24() * m);
        a.setM33(a.m34() * m);
        a.setM43(a.m44() * m);
        
        return a;
    }
    
    inline Matrix4x4& operator*=(Matrix4x4& a, const Matrix4x4& b)
    {
        float t1, t2, t3, t4;
        
        t1 = a.m11() * b.m11() + a.m12() * b.m21() + a.m13() * b.m31() + a.m14() * b.m41();
        t2 = a.m11() * b.m12() + a.m12() * b.m22() + a.m13() * b.m32() + a.m14() * b.m42();
        t3 = a.m11() * b.m13() + a.m12() * b.m23() + a.m13() * b.m33() + a.m14() * b.m43();
        t4 = a.m11() * b.m14() + a.m12() * b.m24() + a.m13() * b.m34() + a.m14() * b.m44();
        a.setM11(t1);
        a.setM12(t2);
        a.setM13(t3);
        a.setM14(t4);
        
        t1 = a.m21() * b.m11() + a.m22() * b.m21() + a.m23() * b.m31() + a.m24() * b.m41();
        t2 = a.m21() * b.m12() + a.m22() * b.m22() + a.m23() * b.m32() + a.m24() * b.m42();
        t3 = a.m21() * b.m13() + a.m22() * b.m23() + a.m23() * b.m33() + a.m24() * b.m43();
        t4 = a.m21() * b.m14() + a.m22() * b.m24() + a.m23() * b.m34() + a.m24() * b.m44();
        a.setM21(t1);
        a.setM22(t2);
        a.setM23(t3);
        a.setM24(t4);
        
        t1 = a.m31() * b.m11() + a.m32() * b.m21() + a.m33() * b.m31() + a.m34() * b.m41();
        t2 = a.m31() * b.m12() + a.m32() * b.m22() + a.m33() * b.m32() + a.m34() * b.m42();
        t3 = a.m31() * b.m13() + a.m32() * b.m23() + a.m33() * b.m33() + a.m34() * b.m43();
        t4 = a.m31() * b.m14() + a.m32() * b.m24() + a.m33() * b.m34() + a.m34() * b.m44();
        a.setM31(t1);
        a.setM32(t2);
        a.setM33(t3);
        a.setM34(t4);
        
        t1 = a.m41() * b.m11() + a.m42() * b.m21() + a.m43() * b.m31() + a.m44() * b.m41();
        t2 = a.m41() * b.m12() + a.m42() * b.m22() + a.m43() * b.m32() + a.m44() * b.m42();
        t3 = a.m41() * b.m13() + a.m42() * b.m23() + a.m43() * b.m33() + a.m44() * b.m43();
        t4 = a.m41() * b.m14() + a.m42() * b.m24() + a.m43() * b.m34() + a.m44() * b.m44();
        a.setM41(t1);
        a.setM42(t2);
        a.setM43(t3);
        a.setM44(t4);
        
        return a;
    }

    inline Matrix4x4 operator+(const Matrix4x4& a, const Matrix4x4& b)
    {
        return Matrix4x4(a.m11() + b.m11(),
                         a.m21() + b.m21(),
                         a.m31() + b.m31(),
                         a.m41() + b.m41(),
                         a.m12() + b.m12(),
                         a.m22() + b.m22(),
                         a.m32() + b.m32(),
                         a.m42() + b.m42(),
                         a.m13() + b.m13(),
                         a.m23() + b.m23(),
                         a.m33() + b.m33(),
                         a.m43() + b.m43(),
                         a.m14() + b.m14(),
                         a.m24() + b.m24(),
                         a.m34() + b.m34(),
                         a.m44() + b.m44());
    }
    
    inline Matrix4x4 operator-(const Matrix4x4& a)
    {
        return Matrix4x4(-a.m11(),
                         -a.m21(),
                         -a.m31(),
                         -a.m41(),
                         -a.m12(),
                         -a.m22(),
                         -a.m32(),
                         -a.m42(),
                         -a.m13(),
                         -a.m23(),
                         -a.m33(),
                         -a.m43(),
                         -a.m14(),
                         -a.m24(),
                         -a.m34(),
                         -a.m44());
    }
    
    inline Matrix4x4 operator-(const Matrix4x4& a, const Matrix4x4& b)
    {
        return Matrix4x4(a.m11() - b.m11(),
                         a.m21() - b.m21(),
                         a.m31() - b.m31(),
                         a.m41() - b.m41(),
                         a.m12() - b.m12(),
                         a.m22() - b.m22(),
                         a.m32() - b.m32(),
                         a.m42() - b.m42(),
                         a.m13() - b.m13(),
                         a.m23() - b.m23(),
                         a.m33() - b.m33(),
                         a.m43() - b.m43(),
                         a.m14() - b.m14(),
                         a.m24() - b.m24(),
                         a.m34() - b.m34(),
                         a.m44() - b.m44());
    }
    
    
    inline Matrix4x4 operator*(const Matrix4x4& a, float m)
    {
        return Matrix4x4(a.m11() * m,
                         a.m21() * m,
                         a.m31() * m,
                         a.m41() * m,
                         a.m12() * m,
                         a.m22() * m,
                         a.m32() * m,
                         a.m42() * m,
                         a.m13() * m,
                         a.m23() * m,
                         a.m33() * m,
                         a.m43() * m,
                         a.m14() * m,
                         a.m24() * m,
                         a.m34() * m,
                         a.m44() * m);
    }
    
    inline Matrix4x4 operator*(float m, const Matrix4x4& a)
    {
        return Matrix4x4(a.m11() * m,
                         a.m21() * m,
                         a.m31() * m,
                         a.m41() * m,
                         a.m12() * m,
                         a.m22() * m,
                         a.m32() * m,
                         a.m42() * m,
                         a.m13() * m,
                         a.m23() * m,
                         a.m33() * m,
                         a.m43() * m,
                         a.m14() * m,
                         a.m24() * m,
                         a.m34() * m,
                         a.m44() * m);
    }
    
    inline Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b)
    {
        Matrix4x4 v;
        float t1, t2, t3, t4;
        
        t1 = a.m11() * b.m11() + a.m12() * b.m21() + a.m13() * b.m31() + a.m14() * b.m41();
        t2 = a.m11() * b.m12() + a.m12() * b.m22() + a.m13() * b.m32() + a.m14() * b.m42();
        t3 = a.m11() * b.m13() + a.m12() * b.m23() + a.m13() * b.m33() + a.m14() * b.m43();
        t4 = a.m11() * b.m14() + a.m12() * b.m24() + a.m13() * b.m34() + a.m14() * b.m44();
        v.setM11(t1);
        v.setM12(t2);
        v.setM13(t3);
        v.setM14(t4);
        
        t1 = a.m21() * b.m11() + a.m22() * b.m21() + a.m23() * b.m31() + a.m24() * b.m41();
        t2 = a.m21() * b.m12() + a.m22() * b.m22() + a.m23() * b.m32() + a.m24() * b.m42();
        t3 = a.m21() * b.m13() + a.m22() * b.m23() + a.m23() * b.m33() + a.m24() * b.m43();
        t4 = a.m21() * b.m14() + a.m22() * b.m24() + a.m23() * b.m34() + a.m24() * b.m44();
        v.setM21(t1);
        v.setM22(t2);
        v.setM23(t3);
        v.setM24(t4);
        
        t1 = a.m31() * b.m11() + a.m32() * b.m21() + a.m33() * b.m31() + a.m34() * b.m41();
        t2 = a.m31() * b.m12() + a.m32() * b.m22() + a.m33() * b.m32() + a.m34() * b.m42();
        t3 = a.m31() * b.m13() + a.m32() * b.m23() + a.m33() * b.m33() + a.m34() * b.m43();
        t4 = a.m31() * b.m14() + a.m32() * b.m24() + a.m33() * b.m34() + a.m34() * b.m44();
        v.setM31(t1);
        v.setM32(t2);
        v.setM33(t3);
        v.setM34(t4);
        
        t1 = a.m41() * b.m11() + a.m42() * b.m21() + a.m43() * b.m31() + a.m44() * b.m41();
        t2 = a.m41() * b.m12() + a.m42() * b.m22() + a.m43() * b.m32() + a.m44() * b.m42();
        t3 = a.m41() * b.m13() + a.m42() * b.m23() + a.m43() * b.m33() + a.m44() * b.m43();
        t4 = a.m41() * b.m14() + a.m42() * b.m24() + a.m43() * b.m34() + a.m44() * b.m44();
        v.setM41(t1);
        v.setM42(t2);
        v.setM43(t3);
        v.setM44(t4);
        
        return v;
    }
    
    inline Vector4 operator*(const Matrix4x4& a, const Vector4& v)
    {
        return Vector4(a.m11() * v.x + a.m21() * v.y + a.m31() * v.z + a.m41() * v.w,
                       a.m12() * v.x + a.m22() * v.y + a.m32() * v.z + a.m42() * v.w,
                       a.m13() * v.x + a.m23() * v.y + a.m33() * v.z + a.m43() * v.w,
                       a.m14() * v.x + a.m24() * v.y + a.m34() * v.z + a.m44() * v.w); 
    }
    
    inline Vector3 operator*(const Matrix4x4& a, const Vector3& v)
    {
        return Vector3(a.m11() * v.x + a.m21() * v.y + a.m31() * v.z + a.m41(),
                       a.m12() * v.x + a.m22() * v.y + a.m32() * v.z + a.m42(),
                       a.m13() * v.x + a.m23() * v.y + a.m33() * v.z + a.m43()); 
    }
    
    inline Matrix4x4 operator/(const Matrix4x4& a, float m)
    {
        float mInv = 1.0f / m;
        return Matrix4x4(a.m11() * mInv,
                         a.m21() * mInv,
                         a.m31() * mInv,
                         a.m41() * mInv,
                         a.m12() * mInv,
                         a.m22() * mInv,
                         a.m32() * mInv,
                         a.m42() * mInv,
                         a.m13() * mInv,
                         a.m23() * mInv,
                         a.m33() * mInv,
                         a.m43() * mInv,
                         a.m14() * mInv,
                         a.m24() * mInv,
                         a.m34() * mInv,
                         a.m44() * mInv);
    }
    
    inline Matrix4x4 operator/(float m, const Matrix4x4& a)
    {
        return Matrix4x4(m / a.m11(),
                         m / a.m21(),
                         m / a.m31(),
                         m / a.m41(),
                         m / a.m12(),
                         m / a.m22(),
                         m / a.m32(),
                         m / a.m42(),
                         m / a.m13(),
                         m / a.m23(),
                         m / a.m33(),
                         m / a.m43(),
                         m / a.m14(),
                         m / a.m24(),
                         m / a.m34(),
                         m / a.m44());
    }
    
    std::ostream& operator<<(std::ostream& out, const Matrix4x4& a);
    
    const Matrix4x4 kMatrix4x4Identity = Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f, 
                                                   0.0f, 1.0f, 0.0f, 0.0f,
                                                   0.0f, 0.0f, 1.0f, 0.0f,
                                                   0.0f, 0.0f, 0.0f, 1.0f);
}

#endif