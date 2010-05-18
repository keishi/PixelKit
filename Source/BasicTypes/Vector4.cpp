/*
 *  Vector4.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/7/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "Vector4.h"

namespace PixelKit {
    std::ostream& operator<<(std::ostream& out, const Vector4& a)
    {
        out << "<";
        out << a.x;
        out << ",";
        out << a.y;
        out << ",";
        out << a.z;
        out << ",";
        out << a.w;
        out << ">";
        return out;
    }
}