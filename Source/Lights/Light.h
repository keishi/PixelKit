/*
 *  Light.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/16/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef Light_h
#define Light_h

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

#include "Color.h"
#include "Material.h"
#include "Vector3.h"
#include "Ray.h"
#include "Surface.h"

namespace PixelKit {
    class Scene;
    typedef Scene* SceneRef;
    
    enum {
        RenderMaterialAmbience  = 1 << 0,
        RenderShadow            = 1 << 1,
        RenderDiffuseLighting   = 1 << 2,
        RenderSpecularLighting  = 1 << 3,
        RenderReflection        = 1 << 4,
        RenderTransparency      = 1 << 5
    };
    typedef unsigned int RenderOption;
    
    class Light {
    public:
        const Color& color() const { return m_color; }
        void setColor(const Color& color) { m_color = color; }
        
        const float intensity() const { return m_intensity; }
        void setIntensity(const float intensity) { m_intensity = intensity; }
        
        virtual Color luminanceOfMaterialAt(const HitInfo& hitInfo, SceneRef scene, RenderOption option) = 0;
        virtual void drawGL() = 0;
        
    protected:
        Color m_color;
        float m_intensity;
    };
    
    typedef Light* LightRef;
}

#endif
