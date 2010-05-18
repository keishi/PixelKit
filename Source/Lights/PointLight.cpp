/*
 *  PointLight.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/16/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "PointLight.h"

#include "Ray.h"
#include "Scene.h"

namespace PixelKit {
    Color PointLight::luminanceOfMaterialAt(const HitInfo& hitInfo, SceneRef scene, RenderOption option)
    {
        Color color = kColorBlack;
        
        Vector3 hitPosition = hitInfo.position;
        Vector3 hitNormal = hitInfo.normal;
        MaterialRef hitMaterial = hitInfo.material;
        
        Vector3 lightRayV = m_position - hitPosition;
        Vector3 lightRayDirection = lightRayV.normalized();
        float lightDistance = lightRayV.norm();
        float lightProjection = lightRayDirection.dot(hitNormal);
        lightProjection = 1.0 / (lightDistance * lightDistance) * lightProjection;
        Ray lightRay(hitPosition, lightRayDirection);
        
        HitInfo occlusionInfo;
        if (option & RenderShadow) {
            if (scene->rootGroup()->hit(lightRay, &occlusionInfo)) {
                if (occlusionInfo.distance < lightDistance) {
                    return color;
                }
            }
        }
        
        Color materialColor;
        if (hitMaterial->texture()) {
            materialColor = hitMaterial->texture()->texelAt(hitInfo.uv);
        } else {
            materialColor = hitMaterial->color();
        }
        
        if (option & RenderDiffuseLighting) {
            float shade = lightRay.direction().dot(hitNormal) / attenuationAtDistance(lightDistance);
            if (shade < 0) {
                shade = 0.0;
            }
            color += materialColor * m_color * hitMaterial->diffuse() * shade;
        }
        
        if (option & RenderSpecularLighting && hitMaterial->shininess() > 0.0f) {
            float viewProjection = hitInfo.ray.direction().dot(hitNormal);
            Vector3 blinnDirection = lightRay.direction() - hitInfo.ray.direction();
            float temp = blinnDirection.normSq();
            if (temp != 0.0) {
                float blinn = (1.0 / sqrtf(temp)) * (lightProjection > viewProjection ? lightProjection - viewProjection : 0.0);
                blinn = pow(blinn, hitMaterial->shininess());
                color += m_color * hitMaterial->specular() * blinn;
            }
        }
        return color;
    }
    
    void PointLight::drawGL()
    {
        glLightfv(GL_LIGHT0, GL_POSITION, &m_position.x);
        GLfloat lightColor[] = {m_color.red, m_color.green, m_color.blue, 1.0};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
        glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, &m_attenuationConstant);
    }
}