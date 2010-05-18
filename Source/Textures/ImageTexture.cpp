/*
 *  ImageTexture.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/17/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "ImageTexture.h"

namespace PixelKit {
    Color ImageTexture::texelAt(Vector2 uv)
    {
        float fu = (uv.x + 1000.5f) * width();
        float fv = (uv.y + 1000.0f) * height();
        int u1 = ((int)fu) % width();
        int v1 = ((int)fv) % height();
        int u2 = (u1 + 1) % width();
        int v2 = (v1 + 1) % height();
        float fracU = fu - floorf(fu);
        float fracV = fv - floorf(fv);
        float w1 = (1 - fracU) * (1 - fracV);
        float w2 = fracU * (1 - fracV);
        float w3 = (1 - fracU) * fracV;
        float w4 = fracU *  fracV;
        Color c1 = pixelColorAt(u1, v1);
        Color c2 = pixelColorAt(u2, v1);
        Color c3 = pixelColorAt(u1, v2);
        Color c4 = pixelColorAt(u2, v2);
        return c1 * w1 + c2 * w2 + c3 * w3 + c4 * w4;
    }
}