/*
 *  TestScene.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/15/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "TestScene.h"
#include "Scene.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"
#include "PointLight.h"
#include "FaceVertexMesh.h"
#include "ImageTexture.h"
#include "CheckeredTexture.h"
#include "Timer.h"


using namespace PixelKit;

void testSceneRasterize(CuTest *tc)
{
    SceneRef scene = new Scene();
    MaterialRef redMaterial = new Material();
    redMaterial->setColor(kColorRed);
    Vector3 sphereCenter(0.0, 0.0, 2.0);
    SphereRef sphere = new Sphere(sphereCenter, 0.5f);
    sphere->setMaterial(redMaterial);
    scene->addSurface(sphere);
    CameraRef camera = new Camera();
    camera->setWidth(64);
    camera->setHeight(64);
    ImageRef image = scene->rasterize(camera);
    ImageRef referenceImage = new Image();
    referenceImage->loadBMPFile("ref-testSceneRasterize.bmp");
    if (!(image->equalToImage(referenceImage))) {
        image->writeBMPFile("testSceneRasterize.bmp");
        CuAssertTrue(tc, false);
    }
    
}

void testSceneRasterizeTriangle(CuTest *tc)
{
    SceneRef scene = new Scene();
    MaterialRef redMaterial = new Material();
    redMaterial->setColor(kColorRed);
    Vector3 v0(-1.0, -1.0, 2.0);
    Vector3 v1(1.0, -1.0, 2.0);
    Vector3 v2(0.0, 1.0, 2.0);
    TriangleRef triangle = new Triangle(v0, v1, v2);
    triangle->setMaterial(redMaterial);
    scene->addSurface(triangle);
    CameraRef camera = new Camera();
    camera->setWidth(64);
    camera->setHeight(64);
    ImageRef image = scene->rasterize(camera);
    ImageRef referenceImage = new Image();
    referenceImage->loadBMPFile("ref-testSceneRasterizeTriangle.bmp");
    if (!(image->equalToImage(referenceImage))) {
        image->writeBMPFile("testSceneRasterizeTriangle.bmp");
        CuAssertTrue(tc, false);
    }
}

void testSceneRasterizeMesh(CuTest *tc)
{
    SceneRef scene = new Scene();
    MaterialRef redMaterial = new Material();
    redMaterial->setColor(kColorRed);
    
    FaceVertexMesh* mesh = new FaceVertexMesh();
    mesh->loadObj("teapot.obj");
    
    Matrix4x4 t = kMatrix4x4Identity;
    t.translate(0.0f, 0.0f, 2.0f);
    
    mesh->applyTransformation(t);
    
    scene->addSurface(mesh);
    
    CameraRef camera = new Camera();
    camera->setWidth(64);
    camera->setHeight(64);
    
    ImageRef image = scene->rasterize(camera);
    ImageRef referenceImage = new Image();
    referenceImage->loadBMPFile("ref-testSceneRasterizeMesh.bmp");
    if (!(image->equalToImage(referenceImage))) {
        image->writeBMPFile("testSceneRasterizeMesh.bmp");
        CuAssertTrue(tc, false);
    }
}

void testSceneRaytrace(CuTest *tc)
{
    SceneRef scene = new Scene();
    
    MaterialRef redMaterial = new Material();
    redMaterial->setColor(kColorRed);
    redMaterial->setSpecular(Color(0.2));
    redMaterial->setShininess(2.0);
    
    Vector3 sphereCenter(0.0, 0.0, 2.0);
    SphereRef sphere = new Sphere(sphereCenter, 0.5f);
    sphere->setMaterial(redMaterial);
    scene->addSurface(sphere);
    
    Vector3 lightPos(0.0, 0.5, 1.0);
    PointLightRef light = new PointLight();
    light->setPosition(lightPos);
    light->setColor(kColorWhite);
    scene->addLight(light);
    
    CameraRef camera = new Camera();
    camera->setWidth(64);
    camera->setHeight(64);
    
    ImageRef image = scene->raytrace(camera, RenderMaterialAmbience | RenderDiffuseLighting | RenderSpecularLighting);
    ImageRef referenceImage = new Image();
    referenceImage->loadBMPFile("ref-testSceneRaytrace.bmp");
    if (!(image->equalToImage(referenceImage))) {
        image->writeBMPFile("testSceneRaytrace.bmp");
        CuAssertTrue(tc, false);
    }
}

void testSceneRaytraceMesh(CuTest *tc)
{
    SceneRef scene = new Scene();
    
    MaterialRef redMaterial = new Material();
    redMaterial->setColor(kColorRed);
    redMaterial->setSpecular(Color(0.2));
    redMaterial->setShininess(2.0);
    
    FaceVertexMesh* mesh = new FaceVertexMesh();
    mesh->loadObj("teapot.obj");
    
    Matrix4x4 t = kMatrix4x4Identity;
    t.rotate(0.0, DEG2RAD(30.0), 0.0);
    t.translate(0.0f, 0.0f, 2.0f);
    
    mesh->applyTransformation(t);
    
    scene->addSurface(mesh);
    
    Vector3 lightPos(0.0, 0.5, 2.0);
    PointLightRef light = new PointLight();
    light->setPosition(lightPos);
    light->setColor(kColorWhite);
    scene->addLight(light);
    
    CameraRef camera = new Camera();
    camera->setWidth(64);
    camera->setHeight(64);
    
    ImageRef image = scene->raytrace(camera, RenderMaterialAmbience | RenderDiffuseLighting | RenderSpecularLighting);
    ImageRef referenceImage = new Image();
    referenceImage->loadBMPFile("ref-testSceneRaytraceMesh.bmp");
    if (!(image->equalToImage(referenceImage))) {
        image->writeBMPFile("testSceneRaytraceMesh.bmp");
        CuAssertTrue(tc, false);
    }
}

void testSceneRaytraceTexture(CuTest *tc)
{
    SceneRef scene = new Scene();
    
    ImageTextureRef earthTexture = new ImageTexture();
    earthTexture->loadBMPFile("earth.bmp");
    
    MaterialRef earthMaterial = new Material();
    earthMaterial->setSpecular(Color(0.2));
    earthMaterial->setShininess(2.0);
    earthMaterial->setTexture(earthTexture);
    
    CheckeredTextureRef checkeredTexture = new CheckeredTexture();
    
    MaterialRef checkeredMaterial = new Material();
    checkeredMaterial->setTexture(checkeredTexture);
    
    Vector3 sphereCenter(0.0, 0.0, 2.0);
    SphereRef sphere = new Sphere(sphereCenter, 0.5f);
    sphere->setMaterial(earthMaterial);
    scene->addSurface(sphere);
    
    Vector3 planeNormal(0.0, 1.0, 0.0);
    PlaneRef plane = new Plane(planeNormal, 1.0);
    plane->setMaterial(checkeredMaterial);
    scene->addSurface(plane);
    
    Vector3 lightPos(0.0, 0.5, 1.0);
    PointLightRef light = new PointLight();
    light->setPosition(lightPos);
    light->setColor(kColorWhite);
    scene->addLight(light);
    
    CameraRef camera = new Camera();
    camera->setWidth(64);
    camera->setHeight(64);
    
    ImageRef image = scene->raytrace(camera, RenderMaterialAmbience | RenderDiffuseLighting | RenderSpecularLighting);
    ImageRef referenceImage = new Image();
    referenceImage->loadBMPFile("ref-testSceneRaytraceTexture.bmp");
    if (!(image->equalToImage(referenceImage))) {
        image->writeBMPFile("testSceneRaytraceTexture.bmp");
        CuAssertTrue(tc, false);
    }
}

void testSceneRaytraceShadow(CuTest *tc)
{
    SceneRef scene = new Scene();
    MaterialRef redMaterial = new Material();
    redMaterial->setColor(kColorRed);
    
    Vector3 v0(-1.0, -1.0, 3.0);
    Vector3 v1(0.0, -1.0, 0.5);
    Vector3 v2(1.0, -1.0, 3.0);
    TriangleRef triangle = new Triangle(v0, v1, v2);
    triangle->setMaterial(redMaterial);
    scene->addSurface(triangle);
    
    Vector3 sphereCenter(0.0, 0.0, 1.5);
    SphereRef sphere = new Sphere(sphereCenter, 0.2f);
    sphere->setMaterial(redMaterial);
    scene->addSurface(sphere);
    
    Vector3 lightPos(0.0, 1.0, 1.0);
    PointLightRef light = new PointLight();
    light->setPosition(lightPos);
    light->setColor(kColorWhite);
    scene->addLight(light);
    
    CameraRef camera = new Camera();
    camera->setWidth(64);
    camera->setHeight(64);
    
    ImageRef image = scene->raytrace(camera, RenderShadow | RenderMaterialAmbience | RenderDiffuseLighting | RenderSpecularLighting);
    ImageRef referenceImage = new Image();
    referenceImage->loadBMPFile("ref-testSceneRaytraceShadow.bmp");
    if (!(image->equalToImage(referenceImage))) {
        image->writeBMPFile("testSceneRaytraceShadow.bmp");
        CuAssertTrue(tc, false);
    }
}

void testSceneRaytraceReflection(CuTest *tc)
{
    SceneRef scene = new Scene();
    
    MaterialRef mirrorMaterial = new Material();
    mirrorMaterial->setColor(kColorGray);
    mirrorMaterial->setReflectivity(0.8);
    
    MaterialRef redMaterial = new Material();
    redMaterial->setColor(kColorRed);
    
    Vector3 v0(-1.0, -0.5, 3.0);
    Vector3 v1(0.0, -0.5, 0.5);
    Vector3 v2(1.0, -0.5, 3.0);
    TriangleRef triangle = new Triangle(v0, v1, v2);
    triangle->setMaterial(mirrorMaterial);
    scene->addSurface(triangle);
    
    Vector3 sphereCenter(0.0, -0.3, 1.5);
    SphereRef sphere = new Sphere(sphereCenter, 0.2f);
    sphere->setMaterial(redMaterial);
    scene->addSurface(sphere);
    
    Vector3 lightPos(0.0, 1.0, 1.0);
    PointLightRef light = new PointLight();
    light->setPosition(lightPos);
    light->setColor(kColorWhite);
    scene->addLight(light);
    
    CameraRef camera = new Camera();
    camera->setWidth(64);
    camera->setHeight(64);
    
    ImageRef image = scene->raytrace(camera, RenderReflection | RenderShadow | RenderMaterialAmbience | RenderDiffuseLighting | RenderSpecularLighting);
    ImageRef referenceImage = new Image();
    referenceImage->loadBMPFile("ref-testSceneRaytraceReflection.bmp");
    if (!(image->equalToImage(referenceImage))) {
        image->writeBMPFile("testSceneRaytraceReflection.bmp");
        CuAssertTrue(tc, false);
    }
}

void testSceneRaytraceParallel(CuTest *tc)
{
    SceneRef scene = new Scene();
    
    ImageTextureRef earthTexture = new ImageTexture();
    earthTexture->loadBMPFile("earth.bmp");
    
    MaterialRef earthMaterial = new Material();
    earthMaterial->setSpecular(Color(0.2));
    earthMaterial->setShininess(2.0);
    earthMaterial->setReflectivity(0.3);
    earthMaterial->setTexture(earthTexture);
    
    CheckeredTextureRef checkeredTexture = new CheckeredTexture();
    
    MaterialRef checkeredMaterial = new Material();
    checkeredMaterial->setTexture(checkeredTexture);
    checkeredMaterial->setReflectivity(0.3);
    
    Vector3 sphereCenter(0.0, 0.0, 2.0);
    SphereRef sphere = new Sphere(sphereCenter, 0.5f);
    sphere->setMaterial(earthMaterial);
    scene->addSurface(sphere);
    
    Vector3 planeNormal(0.0, 1.0, 0.0);
    PlaneRef plane = new Plane(planeNormal, 1.0);
    plane->setMaterial(checkeredMaterial);
    scene->addSurface(plane);
    
    Vector3 lightPos(0.0, 0.5, 1.0);
    PointLightRef light = new PointLight();
    light->setPosition(lightPos);
    light->setColor(kColorWhite);
    scene->addLight(light);
    
    CameraRef camera = new Camera();
    camera->setWidth(128);
    camera->setHeight(128);
    
    ImageRef image = scene->parallelRaytrace(camera, RenderReflection | RenderShadow | RenderMaterialAmbience | RenderDiffuseLighting | RenderSpecularLighting);
    
    ImageRef referenceImage = new Image();
    referenceImage->loadBMPFile("ref-testSceneRaytraceParallel.bmp");
    if (!(image->equalToImage(referenceImage))) {
        image->writeBMPFile("testSceneRaytraceParallel.bmp");
        CuAssertTrue(tc, false);
    }
}

void testSceneRaytraceRefraction(CuTest *tc)
{
    SceneRef scene = new Scene();
    
    ImageTextureRef earthTexture = new ImageTexture();
    earthTexture->loadBMPFile("earth.bmp");
    
    MaterialRef earthMaterial = new Material();
    earthMaterial->setSpecular(Color(0.2));
    earthMaterial->setShininess(2.0);
    earthMaterial->setTransparency(1.0);
    earthMaterial->setRefractiveIndex(1.33);
    earthMaterial->setColor(kColorBlue);
    
    CheckeredTextureRef checkeredTexture = new CheckeredTexture();
    
    MaterialRef checkeredMaterial = new Material();
    checkeredMaterial->setTexture(checkeredTexture);
    checkeredMaterial->setReflectivity(0.3);
    
    Vector3 sphereCenter(0.0, 0.0, 2.0);
    SphereRef sphere = new Sphere(sphereCenter, 0.5f);
    sphere->setMaterial(earthMaterial);
    scene->addSurface(sphere);
    
    Vector3 planeNormal(0.0, 1.0, 0.0);
    PlaneRef plane = new Plane(planeNormal, 1.0);
    plane->setMaterial(checkeredMaterial);
    scene->addSurface(plane);
    
    Vector3 lightPos(0.0, 0.5, 1.0);
    PointLightRef light = new PointLight();
    light->setPosition(lightPos);
    light->setColor(kColorWhite);
    scene->addLight(light);
    
    CameraRef camera = new Camera();
    camera->setWidth(512);
    camera->setHeight(512);
    
    ImageRef image = scene->parallelRaytrace(camera, RenderTransparency | RenderShadow | RenderMaterialAmbience | RenderDiffuseLighting | RenderSpecularLighting);
    
    ImageRef referenceImage = new Image();
    referenceImage->loadBMPFile("ref-testSceneRaytraceParallel.bmp");
    if (!(image->equalToImage(referenceImage))) {
        image->writeBMPFile("testSceneRaytraceRefraction.bmp");
        CuAssertTrue(tc, false);
    }
}

CuSuite* getSceneTestSuite()
{
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testSceneRasterize);
    SUITE_ADD_TEST(suite, testSceneRasterizeTriangle);
    SUITE_ADD_TEST(suite, testSceneRasterizeMesh);
    SUITE_ADD_TEST(suite, testSceneRaytrace);
    SUITE_ADD_TEST(suite, testSceneRaytraceMesh);
    SUITE_ADD_TEST(suite, testSceneRaytraceTexture);
    SUITE_ADD_TEST(suite, testSceneRaytraceShadow);
    SUITE_ADD_TEST(suite, testSceneRaytraceReflection);
    SUITE_ADD_TEST(suite, testSceneRaytraceParallel);
    SUITE_ADD_TEST(suite, testSceneRaytraceRefraction);
    return suite;
}