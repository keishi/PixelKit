/*
 *  TestVector3.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/14/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "TestVector3.h"

void testVector3Arithmetic(CuTest *tc)
{
    
}
CuSuite* getVector3TestSuite()
{
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testVector3Arithmetic);
    return suite;
}