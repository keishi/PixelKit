/*
 *  PointLight.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/16/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef PointLight_h
#define PointLight_h

#include "Light.h"
#include "Vector3.h"

namespace PixelKit {
    class PointLight : public Light {
    public:
        PointLight()
        : m_position()
        , m_attenuationConstant(1.0f)
        , m_attenuationLinear(0.0f)
        , m_attenuationQuadratic(0.0f)
        {
        }
        
        const Vector3& position() const { return m_position; }
        void setPosition(const Vector3& pos) { m_position = pos; }
        
        void setAttenuation(float constant, float linear, float quadratic)
        {
            m_attenuationConstant = constant;
            m_attenuationLinear = linear;
            m_attenuationQuadratic = quadratic;
        }
        
        float attenuationAtDistance(float distance) 
        {
            return m_attenuationConstant + m_attenuationLinear * distance + m_attenuationQuadratic * distance * distance;
        }
        
        virtual Color luminanceOfMaterialAt(const HitInfo& hitInfo, SceneRef scene, RenderOption option);
        virtual void drawGL();
        
    private:
        Vector3 m_position;
        float m_attenuationConstant;
        float m_attenuationLinear;
        float m_attenuationQuadratic;
    };
    
    typedef PointLight* PointLightRef;
}

#endif
