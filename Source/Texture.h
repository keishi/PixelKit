/*
 *  Texture.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/17/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef Texture_h
#define Texture_h

#include "Vector2.h"
#include "Color.h"

namespace PixelKit {
    class Texture {
    public:
        virtual Color texelAt(Vector2 uv) = 0;
    };
    
    typedef Texture* TextureRef;
}

#endif
