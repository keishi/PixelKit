/*
 *  Vector2.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/14/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "Vector2.h"

namespace PixelKit {
    
    std::ostream& operator<<(std::ostream& out, const Vector2& a)
    {
        out << "<";
        out << a.x;
        out << ",";
        out << a.y;
        out << ">";
        return out;
    }
    
}