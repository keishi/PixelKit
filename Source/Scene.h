/*
 *  Scene.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/15/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef Scene_h
#define Scene_h

#include <vector>

#include "SurfaceGroup.h"
#include "Image.h"
#include "Camera.h"
#include "Light.h"
#include "Rect.h"

namespace PixelKit {
    class Scene {
    public:
        Scene()
        {
            m_rootGroup = new SurfaceGroup();
        }
        
        SurfaceGroupRef rootGroup() const { return m_rootGroup; }
        
        void addSurface(SurfaceRef s);
        void addLight(LightRef l);
        
        bool traceRay(Ray& ray, RenderOption option, float refractiveIndex, int level, Color* acc, HitInfo* hitInfo);
        
        void renderGL(CameraRef camera);
        ImageRef rasterize(CameraRef camera);
        ImageRef raytrace(CameraRef camera, RenderOption option);
        void raytrace(CameraRef camera, Rect rect, RenderOption option, ImageRef image);
        ImageRef parallelRaytrace(CameraRef camera, RenderOption option);
        
    private:
        std::vector<LightRef> m_lights;
        SurfaceGroupRef m_rootGroup;
    };
    
    typedef Scene* SceneRef;
}

#endif
