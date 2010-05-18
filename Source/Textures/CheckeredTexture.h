/*
 *  CheckeredTexture.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/17/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef CheckeredTexture_h
#define CheckeredTexture_h

#include "Texture.h"

namespace PixelKit {
    class CheckeredTexture : public Texture {
    public:
        CheckeredTexture()
        : m_color0(kColorBlack)
        , m_color1(kColorWhite)
        {
        }
        virtual Color texelAt(Vector2 uv);
    private:
        Color m_color0;
        Color m_color1;
    };
    
    typedef CheckeredTexture* CheckeredTextureRef;
}

#endif
