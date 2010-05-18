/*
 *  TestImage.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/14/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "TestImage.h"
#include "Image.h"
#include "RefPtr.h"

using namespace PixelKit;

void testImageWriteBMPFile(CuTest *tc)
{
    RefPtr<Image> image = new Image(64, 64);
    RefPtr<Image> referenceImage = new Image();
    for (int y = 0; y < image->height(); y++) {
        for (int x = 0; x < image->width(); x++) {
            int m = ((x / 16) + ((y / 16) % 4)) % 4;
            Color color = (m == 0 ? kColorWhite : 
                           m == 1 ? kColorBlack :
                           m == 2 ? kColorRed : 
                           m == 3 ? kColorGreen : kColorBlue);
            image->setPixelColor(x, y, color);
        }
    }
    image->writeBMPFile("testImageWriteBMPFile.bmp");
    image->loadBMPFile("testImageWriteBMPFile.bmp");
    referenceImage->loadBMPFile("ref-testImageWriteBMPFile.bmp");
    CuAssertTrue(tc, image->equalToImage(referenceImage));
}

CuSuite* getImageTestSuite()
{
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testImageWriteBMPFile);
    return suite;
}
