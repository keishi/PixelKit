/*
 *  Camera.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/15/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "Camera.h"

namespace PixelKit {
    Ray Camera::viewRay(float x, float y)
    {
        float viewPortHeight = tanf(m_FOV / 2.0f) * 2.0f;
        float viewPortWidth = viewPortHeight * m_aspect;
        Vector3 viewRayV(viewPortWidth * x, viewPortHeight * y, 1.0f);
        viewRayV = m_xDirection * viewRayV.x + m_yDirection * viewRayV.y + m_zDirection * viewRayV.z;
        Ray viewRay(m_eye, viewRayV.normalize());
        return viewRay;
    }
}