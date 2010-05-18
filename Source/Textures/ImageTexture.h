/*
 *  ImageTexture.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/17/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef ImageTexture_h
#define ImageTexture_h

#include "Texture.h"
#include "Image.h"

namespace PixelKit {
    class ImageTexture : public Image, public Texture {
    public:
        virtual Color texelAt(Vector2 uv);
    };
    
    typedef ImageTexture* ImageTextureRef;
}

#endif
