/*
 *  BoundingBox.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/9/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "BoundingBox.h"

namespace PixelKit {
    BoundingBox BoundingBox::unionBox(const BoundingBox& box) const
    {
        if (isInfinite() || box.isInfinite()) {
            return kBoundingBoxInfinite;
        }
        if (isNull()) {
            return box;
        } else if (box.isNull()) {
            return *this;
        }
        Vector3 maxPos(MAX(m_maxPosition.x, box.maxPosition().x), 
                       MAX(m_maxPosition.y, box.maxPosition().y), 
                       MAX(m_maxPosition.z, box.maxPosition().z));
        Vector3 minPos(MIN(m_minPosition.x, box.minPosition().x), 
                       MIN(m_minPosition.y, box.minPosition().y), 
                       MIN(m_minPosition.z, box.minPosition().z));
        return BoundingBox(minPos, maxPos);
    }
    
    std::ostream& operator<<(std::ostream& out, const BoundingBox& a)
    {
        out << "BoundingBox(";
        out << a.minPosition();
        out << ",";
        out << a.maxPosition();
        out << ")";
        return out;
    }
}