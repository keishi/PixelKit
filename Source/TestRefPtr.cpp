/*
 *  TestRefPtr.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/15/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "TestRefPtr.h"
#include "RefPtr.h"

using namespace PixelKit;

static int allocated_object_count = 0;

class A {
private:
	char a;
public:
	A(char _a):a(_a){ allocated_object_count++; }
	~A(){ allocated_object_count--; }
};

RefPtr<A> getA()
{
	RefPtr<A> a;
	a = new A('C');
    
	return a;
}

void testRefPtr(CuTest *tc)
{
    allocated_object_count = 0;
    RefPtr<A> a = new A('A');
	RefPtr<A> b = new A('B');
	a = b;
    a = getA();
	b = a;
    CuAssertIntEquals(tc, 0, allocated_object_count);
}
CuSuite* getRefPtrTestSuite()
{
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testRefPtr);
    return suite;
}

