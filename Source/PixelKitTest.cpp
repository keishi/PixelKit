/*
 *  PixelKitTest.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/14/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "CuTest.h"
#include "TestImage.h"
#include "TestVector3.h"
#include "TestRefPtr.h"
#include "TestScene.h"
#include "TestBoundingBox.h"

int main(void) {
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();
    
    CuSuiteAddSuite(suite, getImageTestSuite());
    CuSuiteAddSuite(suite, getVector3TestSuite());
    CuSuiteAddSuite(suite, getRefPtrTestSuite());
    CuSuiteAddSuite(suite, getSceneTestSuite());
    CuSuiteAddSuite(suite, getBoundingBoxTestSuite());
    
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}
