/*
 *  Camera.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/15/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef Camera_h
#define Camera_h

#include "Ray.h"

namespace PixelKit {
    class Camera {
    public:
        Camera()
        : m_aspect(1.0)
        , m_eye(0.0f, 0.0f, 0.0f)
        , m_lookat(1.0f, 0.0f, 0.0f)
        , m_xDirection(1.0f, 0.0f, 0.0f)
        , m_yDirection(0.0f, 1.0f, 0.0f)
        , m_zDirection(0.0f, 0.0f, 1.0f)
        , m_FOV(DEG2RAD(60.0f))
        {
        }
        
        unsigned int width() const { return m_width; }
        void setWidth(unsigned int width) { m_width = width; }
        
        unsigned int height() const { return m_height; }
        void setHeight(unsigned int height) { m_height = height; }
        
        float aspect() const { return m_aspect; }
        void setAspect(float ratio) { m_aspect = ratio; }
        
        const Vector3& eye() const { return m_eye; }
        void setEye(const Vector3& pos) 
        {
            m_eye = pos;
            m_zDirection = (m_lookat - m_eye).normalized();
            m_xDirection = m_yDirection.cross(m_zDirection).normalize();
        }
        
        const Vector3& lookat() const { return m_lookat; }
        void setLookat(const Vector3& v)
        {
            m_lookat = v;
            m_zDirection = (m_lookat - m_eye).normalized();
            m_xDirection = m_yDirection.cross(m_zDirection).normalize();
        }
        
        const Vector3& up() const { return m_yDirection; }
        void setUp(const Vector3& v) 
        {
            m_yDirection = v.normalized();
            m_xDirection = m_yDirection.cross(m_zDirection).normalize();
        }
        
        float FOV() const { return m_FOV; }
        void setFOV(float angle) { m_FOV = angle; }
        
        Ray viewRay(float x, float y);
        
    private:
        unsigned int m_width;
        unsigned int m_height;
        float m_aspect;
        Vector3 m_eye;
        Vector3 m_lookat;
        Vector3 m_xDirection;
        Vector3 m_yDirection;
        Vector3 m_zDirection;
        float m_FOV; // Angle in the y direction that is visible.
    };
    
    typedef Camera* CameraRef;
}

#endif
