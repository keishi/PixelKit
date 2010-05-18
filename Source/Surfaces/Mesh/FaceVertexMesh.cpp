/*
 *  FaceVertexMesh.cpp
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/16/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#include "FaceVertexMesh.h"

namespace PixelKit {
    static void get_indices(char *word, int *vindex, int *tindex, int *nindex)
    {
        const char* nullString = " ";
        char* ptr;
        const char* tp;
        const char* np;
        
        /* by default, the texture and normal pointers are set to the null string */
        
        tp = nullString;
        np = nullString;
        
        /* replace slashes with null characters and cause tp and np to point */
        /* to character immediately following the first or second slash */
        
        for (ptr = word; *ptr != '\0'; ptr++) {
            if (*ptr == '/') {
                if (tp == nullString)
                    tp = ptr + 1;
                else
                    np = ptr + 1;
                
                *ptr = '\0';
            }
        }
        
        *vindex = atoi (word);
        *tindex = atoi (tp);
        *nindex = atoi (np);
    }
    
    void FaceVertexMesh::loadObj(const char *filename)
    {
        FILE* fp = fopen(filename, "r");
        int numVertices = 0, numUV = 0, numNormals = 0, numFaces = 0;
        char line[81];
        while ( fgets( line, 80, fp ) != NULL ) {
            if (line[0] == 'v') {
                if (line[1] == 'n')
                    numNormals++;
                else if (line[1] == 't')
                    numUV++;
                else
                    numVertices++;
            } else if (line[0] == 'f') {
                numFaces++;
            }
        }
        fseek(fp, 0, 0);
        
        MaterialRef defaultMaterial = new Material();
        defaultMaterial->setColor(kColorYellow);
        m_materialList.push_back(defaultMaterial);
        
        while ( fgets( line, 80, fp ) != NULL ) {
            switch (line[0]) {
                case 'v':
                {
                    switch (line[1]) {
                        case 'n':
                            // TODO: Do something with normals
                            break;
                        case 't':
                            // TODO: Do something with UV
                            break;
                        default:
                        {
                            float x, y, z;
                            sscanf(&line[1], "%f %f %f\n", &x, &y, &z);
                            VertexRef v = new Vertex(x, y, z);
                            m_vertexList.push_back(v);
                        }
                            break;
                    }
                }
                    break;
                case 'f':
                {
                    int i0, i1, i2;
                    int it0, it1, it2;
                    int in0, in1, in2;
                    
                    char s0[32], s1[32], s2[32];
                    sscanf( &line[1], "%s %s %s\n", s0, s1, s2);
                    
                    get_indices(s0, &i0, &it0, &in0);
                    get_indices(s1, &i1, &it1, &in1);
                    get_indices(s2, &i2, &it2, &in2);
                    
                    TriangleFaceRef face = new TriangleFace(m_vertexList[i0 - 1], m_vertexList[i1 - 1], m_vertexList[i2 - 1]);
                    face->setMaterial(m_materialList[0]);
                    
                    m_faceList.push_back(face);
                    m_boundingBox = m_boundingBox.unionBox(face->boundingBox());
                }
                    break;
                    
            }
        }
    }
    
    bool FaceVertexMesh::hit(const Ray& ray, HitInfo *hitInfo)
    {
        if (!m_boundingBox.doesHit(ray)) {
            return false;
        }
        
        float hitDistance = INFINITY;
        HitInfo intersectionInfo;
        // find nearest intersection
        for (unsigned int i = 0; i < m_faceList.size(); i++) {
            TriangleFaceRef face = m_faceList[i];
            if (face->hit(ray, &intersectionInfo)) {
                if (intersectionInfo.distance < hitDistance) {
                    hitDistance = intersectionInfo.distance;
                    *hitInfo = intersectionInfo;
                }
            }
        }
        return hitDistance != INFINITY;
    }
    
    void FaceVertexMesh::drawGL()
    {
        for (unsigned int i = 0; i < m_faceList.size(); i++) {
            m_faceList[i]->drawGL();
        }
    }
    
    void FaceVertexMesh::applyTransformation(const Matrix4x4& t)
    {
        for (unsigned int i = 0; i < m_vertexList.size(); i++) {
            VertexRef v = m_vertexList[i];
            *v = t * (*v);
        }
        m_boundingBox = kBoundingBoxNull;
        for (unsigned int i = 0; i < m_faceList.size(); i++) {
            TriangleFaceRef f = m_faceList[i];
            f->updateBoudingBox();
            m_boundingBox = m_boundingBox.unionBox(f->boundingBox());
        }
    }
}