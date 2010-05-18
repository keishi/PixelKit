/*
 *  Image.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/6/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef Image_h
#define Image_h

#include "Vector3.h"
#include "Vector2.h"
#include "Color.h"

namespace PixelKit {
    class Image;
    
    typedef Image* ImageRef;
    
    class Image {
        typedef struct {
            unsigned char r, g, b;
        } Pixel;
    public:
        Image()
        : m_width(0)
        , m_height(0)
        , m_pixels(0)
        { }
        Image(unsigned int width, unsigned int height);
        virtual ~Image();
        
        void resize(unsigned int width, unsigned int height);
        
        const unsigned int width() const { return m_width; }
        const unsigned int height() const { return m_height; }
        const unsigned int pixelCount() const { return m_width * m_height; }
        
        void drawImageAtPoint(ImageRef image, Vector2 pos);
        
        Pixel pixelAt(int x, int y) const
        {
            return m_pixels[x + y * m_width];
        }
        Color pixelColorAt(int x, int y) const
        {
            if (x >= m_width || y >= m_height) {
                return kColorBlack;
            }
            Pixel p = pixelAt(x, y);
            return Color(p.r / 255.0f, p.g / 255.0f, p.b / 255.0f);
        }
        Color sampleColorAt(float x, float y) const
        {
            int left = (int)x;
            int top = (int)y;
            Color topColor = pixelColorAt(left, top) * (x - left) + pixelColorAt(left + 1, top) * (1.0f - x + left);
            Color bottomColor = pixelColorAt(left, top + 1) * (x - left) + pixelColorAt(left + 1, top + 1) * (1.0f - x + left);
            return topColor * (y - top) + bottomColor * (1.0f - y + top);
        }
        
        void setPixel(int x, int y, const Pixel& p) { m_pixels[x + y * m_width] = p; }
        void setPixelColor(int x, int y, const Color& c)
        {
            if (!(y >= 0 && y < m_height && y >= 0 && y < m_height)) {
                std::cout << x << "," << y;
            }
            ASSERT(x >= 0 && x < m_width);
            ASSERT(y >= 0 && y < m_height);
            Color d = c.clipped();
            Pixel p = {d.red * 255, d.green * 255, d.blue * 255};
            m_pixels[x + y * m_width] = p;
        }
        void thresholdFilter(float th);
        bool equalToImage(Image* i);
        
        void loadBMPFile(const char *filename);
        void writeBMPFile(const char *filename) const;
        
    private:
        unsigned int m_width;
        unsigned int m_height;
        Pixel *m_pixels;
    };
    
    std::ostream& operator<<(std::ostream& out, const Image& image);
}

#endif
