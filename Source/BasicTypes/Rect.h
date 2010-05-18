/*
 *  Rect.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/17/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef Rect_h
#define Rect_h

#include "Vector2.h"

namespace PixelKit {
    class Rect {
    public:
        Rect()
        : origin(0.0f, 0.0f)
        , size(0.0f, 0.0f)
        {
        }
        Rect(float x, float y, float width, float height)
        : origin(x, y)
        , size(width, height)
        {
        }
        
        float maxX() { return size.width > 0 ? origin.x + size.width : origin.x - size.width; }
        float maxY() { return size.height > 0 ? origin.y + size.height : origin.y - size.height; }
        
        Rect integral()
        {
            return Rect(floor(origin.x), floor(origin.y), ceil(size.width), ceil(size.height));
        }
        
        Vector2 origin;
        Vector2 size;
    };
}

#endif
