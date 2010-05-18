/*
 *  common.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/14/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#define MIN(a,b)  ( ((a)<(b)) ? (a) : (b) )
#define MAX(a,b)  ( ((a)>(b)) ? (a) : (b) )

#define DEG2RAD(d) ( (d) / 180.0f * PI )
#define RAD2DEG(r) ( (r) / PI * 180.0f )

#define ASSERT(x) ( assert(x) )

const float EPSILON = 0.001f;
const float PI = 3.14159265358979323846f;
