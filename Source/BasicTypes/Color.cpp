/*
 *  Color.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/6/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "Color.h"

namespace PixelKit {
    
    std::ostream& operator<<(std::ostream& out, const Color& a)
    {
        out << "Color(";
        out << a.red;
        out << ",";
        out << a.green;
        out << ",";
        out << a.blue;
        out << ")";
        return out;
    }
    
}