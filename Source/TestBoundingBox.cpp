/*
 *  TestBoundingBox.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/17/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "TestBoundingBox.h"
#include "BoundingBox.h"
#include "Ray.h"
#include "Camera.h"
#include "Image.h"

using namespace PixelKit;

void testBoundingBoxDoesHit(CuTest *tc)
{
    BoundingBox box(Vector3(0,0,1), Vector3(1,1,1));
    
    CameraRef camera = new Camera();
    camera->setWidth(64);
    camera->setHeight(64);
    
    ImageRef image = new Image(camera->width(), camera->height());
    for (unsigned int y = 0; y < camera->height(); y++) {
        for (unsigned int x = 0; x < camera->width(); x++) {
            float xPos = (float)x / (float) camera->width() - 0.5f;
            float yPos = (float)y / (float) camera->height() - 0.5f;
            Ray viewRay = camera->viewRay(xPos, yPos);
            if (box.doesHit(viewRay)) {
                image->setPixelColor(x, y, kColorRed);
            }
        }
    }
    
    ImageRef referenceImage = new Image();
    referenceImage->loadBMPFile("ref-testBoundingBoxDoesHit.bmp");
    if (!(image->equalToImage(referenceImage))) {
        image->writeBMPFile("testBoundingBoxDoesHit.bmp");
        CuAssertTrue(tc, false);
    }
}
CuSuite* getBoundingBoxTestSuite()
{
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testBoundingBoxDoesHit);
    return suite;
}