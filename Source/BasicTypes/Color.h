/*
 *  Color.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/6/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef Color_h
#define Color_h

namespace PixelKit {
    class Color {
    public:
        Color() : red(0.0f), green(0.0f), blue(0.0f) { }
        Color(float l) : red(l), green(l), blue(l) { }
        Color(float r, float g, float b) : red(r), green(g), blue(b) { }
        
        float luminance() { return 0.2126 * red + 0.7152 * green + 0.0722 * blue; }
        
        void setRGB(float r, float g, float b) { red = r; green = g; blue = b; }
        
        Color clipped() const
        {
            return Color((red > 1.0) ? 1.0 : (red < 0.0) ? 0.0 : red,
                         (green > 1.0) ? 1.0 : (green < 0.0) ? 0.0 : green,
                         (blue > 1.0) ? 1.0 : (blue < 0.0) ? 0.0 : blue);
        }
        
        Color& operator=(const Color& a)
        {
            red = a.red;
            green = a.green;
            blue = a.blue;
            return *this;
        }
        
        int operator==(const Color& a)
        {
            return red == a.red &&
                   green == a.green &&
                   blue == a.blue;
        }
        
        float red;
        float green;
        float blue;
    };
    
    inline Color& operator+=(Color& a, const Color& b)
    {
        a.red = a.red + b.red;
        a.green = a.green + b.green;
        a.blue = a.blue + b.blue;
        return a;
    }
    
    inline Color operator+(const Color& a, const Color& b)
    {
        return Color(a.red + b.red, a.green + b.green, a.blue + b.blue);
    }
    
    inline Color operator*(const Color& a, const Color& b)
    {
        return Color(a.red * b.red, a.green * b.green, a.blue * b.blue);
    }
    
    inline Color operator*(const Color& a, const float m)
    {
        return Color(a.red * m, a.green * m, a.blue * m);
    }
    
    inline Color operator*(const float m, const Color& a)
    {
        return Color(a.red * m, a.green * m, a.blue * m);
    }
    
    std::ostream& operator<<(std::ostream& out, const Color& a);
    
    const Color kColorBlack   = Color(0.0f, 0.0f, 0.0f);
    const Color kColorGray    = Color(0.5f, 0.5f, 0.5f);
    const Color kColorWhite   = Color(1.0f, 1.0f, 1.0f);
    const Color kColorRed     = Color(1.0f, 0.0f, 0.0f);
    const Color kColorGreen   = Color(0.0f, 1.0f, 0.0f);
    const Color kColorBlue    = Color(0.0f, 0.0f, 1.0f);
    const Color kColorCyan    = Color(0.0f, 1.0f, 1.0f);
    const Color kColorYellow  = Color(1.0f, 1.0f, 0.0f);
    const Color kColorMagenta = Color(1.0f, 0.0f, 1.0f);
}

#endif
