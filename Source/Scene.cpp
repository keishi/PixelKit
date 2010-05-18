/*
 *  Scene.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/15/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "Scene.h"
#include <pthread.h>

namespace PixelKit {
    void Scene::addSurface(SurfaceRef s)
    {
        m_rootGroup->addSurface(s);
    }
    void Scene::addLight(LightRef l)
    {
        m_lights.push_back(l);
    }
    void Scene::renderGL(CameraRef camera)
    {
        glDrawBuffer(GL_BACK);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // set up the screen with our camera parameters
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluPerspective(RAD2DEG(camera->FOV()), camera->aspect(), 0.1, 1000.0);
        
        
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
        gluLookAt(camera->eye().x, camera->eye().y, camera->eye().z, 
                  camera->lookat().x, camera->lookat().y, camera->lookat().z, 
                  camera->up().x, camera->up().y, camera->up().z);
        glEnable( GL_DEPTH_TEST );
        
        glCullFace(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        for (unsigned int i = 0; i < m_lights.size(); i++) {
            LightRef light = m_lights[i];
            light->drawGL();
        }
        
        m_rootGroup->drawGL();
        
        glDisable(GL_DEPTH_TEST);
        
        glutSwapBuffers();
    }
    ImageRef Scene::rasterize(CameraRef camera)
    {
        ImageRef image = new Image(camera->width(), camera->height());
        for (unsigned int y = 0; y < camera->height(); y++) {
            for (unsigned int x = 0; x < camera->width(); x++) {
                float xPos = (float)x / (float) camera->width() - 0.5f;
                float yPos = (float)y / (float) camera->height() - 0.5f;
                Ray viewRay = camera->viewRay(xPos, yPos);
                HitInfo hitInfo;
                if (m_rootGroup->hit(viewRay, &hitInfo)) {
                    image->setPixelColor(x, y, hitInfo.material->color());
                }
            }
        }
        return image;
    }
    
    const int kMaxTraceLevel = 10;
    bool Scene::traceRay(Ray& ray, RenderOption option, float refractiveIndex, int level, Color* acc, HitInfo* hitInfo)
    {
        if (level > kMaxTraceLevel) {
            return false;
        }
        *acc = kColorBlack;
        
        if (m_rootGroup->hit(ray, hitInfo)) {
            Vector3 hitPosition = hitInfo->position;
            Vector3 hitNormal = hitInfo->normal;
            MaterialRef hitMaterial = hitInfo->material;
            
            if (option & RenderMaterialAmbience) {
                Color materialColor;
                if (hitMaterial->texture()) {
                    materialColor = hitMaterial->texture()->texelAt(hitInfo->uv);
                } else {
                    materialColor = hitMaterial->color();
                }

                *acc += hitMaterial->ambient() * materialColor * (1.0f - hitMaterial->transparency());
            }
            
            for (unsigned int i = 0; i < m_lights.size(); i++) {
                LightRef light = m_lights[i];
                *acc += light->luminanceOfMaterialAt(*hitInfo, this, option) * (1.0f - hitMaterial->transparency());
                
                if (option & RenderReflection) {
                    if (hitMaterial->reflectivity() > 0.0f && level < kMaxTraceLevel) {
                        float reflection = 2.0 * ray.direction().dot(hitNormal);
                        Vector3 reflectionDirection = (ray.direction() - (hitNormal * reflection)).normalize();
                        Ray reflectedRay(hitPosition, reflectionDirection);
                        
                        HitInfo reflectionInfo;
                        Color reflectedColor = kColorBlack;
                        if (traceRay(reflectedRay, option, refractiveIndex, level + 1, &reflectedColor, &reflectionInfo)) {
                            reflectedColor = reflectedColor * hitMaterial->reflectivity();
                            *acc += reflectedColor * (1.0f - hitMaterial->transparency());
                        }
                    }
                }
                
                if (option & RenderTransparency) {
                    if (hitMaterial->transparency() > 0.0f && level < kMaxTraceLevel) {
                        float n = refractiveIndex / hitMaterial->refractiveIndex();
                        float cosA = -ray.direction().dot(hitNormal);
                        float cosB = sqrtf(1.0f - n * n * (1 - cosA * cosA));
                        if (cosB > 0.0f) {
                            Vector3 refracDirection = (n * ray.direction()) + (n * cosA - cosB) * hitNormal;
                            
                            Vector3 refracRayOrigin = hitPosition + refracDirection * EPSILON;
                            Ray refracRay(refracRayOrigin, refracDirection);
                            
                            HitInfo refracInfo;
                            Color refracColor = kColorBlack;
                            if (traceRay(refracRay, option, refractiveIndex, level + 1, &refracColor, &refracInfo)) {
                                refracColor = refracColor * hitMaterial->transparency();
                                Color absorbance = hitMaterial->color() * 0.15f * -refracInfo.distance;
                                Color transparency = Color(expf(absorbance.red), expf(absorbance.green), expf(absorbance.blue));
                                refracColor = refracColor * transparency;
                                *acc += refracColor;
                            }
                        }
                    }
                }
            }
        }
        
        
        return true;
    }
    
    ImageRef Scene::raytrace(CameraRef camera, RenderOption option)
    {
        Rect rect(0.0f, 0.0f, camera->width(), camera->height());
        ImageRef image = new Image(rect.size.width, rect.size.height);
        raytrace(camera, Rect(0.0f, 0.0f, camera->width(), camera->height()), option, image);
        return image;
    }
    
    void Scene::raytrace(CameraRef camera, Rect rect, RenderOption option, ImageRef image)
    {
        ASSERT(image->width() == rect.size.width && image->height() == rect.size.height);
        for (unsigned int y = 0; y < rect.size.height; y++) {
            for (unsigned int x = 0; x < rect.size.width; x++) {
                float xPos = (float)(x + rect.origin.x) / (float) camera->width() - 0.5f;
                float yPos = (float)(y + rect.origin.y) / (float) camera->height() - 0.5f;
                Ray viewRay = camera->viewRay(xPos, yPos);
                HitInfo hitInfo;
                Color color;
                
                if (traceRay(viewRay, option, 1.0f, 0, &color, &hitInfo)) {
                    image->setPixelColor(x, y, color);
                } else {
                    // set Background ccolor
                    //image->setPixelColor(x, y, hitInfo.material->color());
                }
                
            }
        }
    }
    
    typedef struct {
        SceneRef scene;
        CameraRef camera;
        Rect rect;
        RenderOption option;
        ImageRef image;
    } RaytraceThreadParam;
    void* raytraceThread(void* arg)
    {
        RaytraceThreadParam* param = (RaytraceThreadParam*)arg;
        param->scene->raytrace(param->camera, param->rect, param->option, param->image);
        return NULL;
    }
    
    RaytraceThreadParam p1, p2;
    
    ImageRef Scene::parallelRaytrace(CameraRef camera, RenderOption option)
    {
        Rect leftRect(0.0f, 0.0f, camera->width(), floor(camera->height() / 2.0f));
        Rect rightRect(0.0f, leftRect.maxY(), camera->width(), camera->height() - leftRect.size.height);
        
        p1.scene = this;
        p1.camera = camera;
        p1.rect = leftRect;
        p1.option = option;
        p1.image = new Image(leftRect.size.width, leftRect.size.height);
        
        p2.scene = this;
        p2.camera = camera;
        p2.rect = rightRect;
        p2.option = option;
        p2.image = new Image(rightRect.size.width, rightRect.size.height);
        
        pthread_t thread1, thread2;
        int  iret1, iret2;
        std::cout << this;
        iret1 = pthread_create(&thread1, NULL, raytraceThread, &p1);
        iret2 = pthread_create(&thread2, NULL, raytraceThread, &p2);
        
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        
        ImageRef image = new Image(camera->width(), camera->height());
        image->drawImageAtPoint(p1.image, p1.rect.origin);
        image->drawImageAtPoint(p2.image, p2.rect.origin);
        
        delete p1.image;
        delete p2.image;
        
        return image;
    }
}