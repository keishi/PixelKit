/*
 *  CheckeredTexture.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/17/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "CheckeredTexture.h"

namespace PixelKit {
    Color CheckeredTexture::texelAt(Vector2 uv)
    {
        int x = uv.x < 0 ? ceil(-uv.x * 8.0) : floor(uv.x * 8.0);
        int y = uv.y < 0 ? ceil(-uv.y * 8.0) : floor(uv.y * 8.0);
        int modX = x % 2;
        int modY = y % 2;
        return modX ^ modY ? m_color0 : m_color1;
    }
}