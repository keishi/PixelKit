#include <iostream>

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "Scene.h"
#include "Sphere.h"
#include "Triangle.h"
#include "PointLight.h"
#include "FaceVertexMesh.h"

using namespace PixelKit;

SceneRef scene;
CameraRef camera;


void display(void)
{
    scene->renderGL(camera);
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    
    camera->setWidth(w);
    camera->setHeight(h);
    
    glutPostRedisplay();
}

void init()
{
    scene = new Scene();
    
    MaterialRef yellowColor = new Material();
    yellowColor->setColor(kColorYellow);
    
    FaceVertexMesh* mesh = new FaceVertexMesh();
    mesh->loadObj("teapot.obj");
    
    Matrix4x4 t = kMatrix4x4Identity;
    t.translate(0.0f, 0.0f, 2.0f);
    
    mesh->applyTransformation(t);
    
    scene->addSurface(mesh);
    /*
     Vector3 v0(-1.0, -1.0, 2.0);
     Vector3 v1(1.0, -1.0, 2.0);
     Vector3 v2(0.0, 1.0, 2.0);
     TriangleRef triangle = new Triangle(v0, v1, v2);
     triangle->setMaterial(yellowColor);
     scene->addSurface(triangle);*/
    
    Vector3 lightPos(0.0, 0.5, 2.0);
    PointLightRef light = new PointLight();
    light->setPosition(lightPos);
    light->setColor(kColorWhite);
    scene->addLight(light);
    
    camera = new Camera();
    camera->setWidth(200);
    camera->setHeight(200);
}

int main (int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    
    init();
    
    glutMainLoop();
    return 0;
}
