/*
 *  gim: Program for demonstrating the usage of the OpenGI library
 *  Copyright (C) 2009-2011  Christian Rau
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *  If you modify this software, you should include a notice giving the
 *  name of the person performing the modification, the date of modification,
 *  and the reason for such modification.
 *
 *  Contact: Christian Rau
 *
 *     rauy@users.sourceforge.net
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif // _WIN32

#include <math.h>
#include <time.h>

#include <GI/gi.h>

#if __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE    0x812F
#endif // !GL_CLAMP_TO_EDGE

#ifndef GL_RGBA32F
#define GL_RGBA32F          0x8814
#endif // !GL_RGBA32F


#define M_TWO_PI            (2.0 * M_PI)

#define VEC3_ADD(d,v,w)     (d)[0]=(v)[0]+(w)[0]; (d)[1]=(v)[1]+(w)[1]; (d)[2]=(v)[2]+(w)[2]

#define VEC3_SUB(d,v,w)     (d)[0]=(v)[0]-(w)[0]; (d)[1]=(v)[1]-(w)[1]; (d)[2]=(v)[2]-(w)[2]

#define VEC3_CROSS(d,v,w)   (d)[0]=(v)[1]*(w)[2] - (v)[2]*(w)[1]; \
                            (d)[1]=(v)[2]*(w)[0] - (v)[0]*(w)[2]; \
                            (d)[2]=(v)[0]*(w)[1] - (v)[1]*(w)[0]

#define VEC3_NORMALIZE(v)   { float n = sqrtf((v)[0]*(v)[0]+(v)[1]*(v)[1]+(v)[2]*(v)[2]); \
                            if(fabsf(n) > 1E-6f) { float m = 1.0f / n; (v)[0] *= m; (v)[1] *= m; (v)[2] *= m; } }

// ==== Configurale ====

// Options:
// GI_SHAPE_PRESERVING
// GI_DISCRETE_HARMONIC
// GI_MEAN_VALUE
// GI_DISCRETE_AUTHALIC
#define INITIAL_PARAMETERIZATION_MODE       GI_MEAN_VALUE

// Options:
// GI_FROM_ATTRIB
// GI_TUTTE_BARYCENTRIC
// GI_SHAPE_PRESERVING
// GI_DISCRETE_HARMONIC
// GI_MEAN_VALUE
// GI_DISCRETE_AUTHALIC
// GI_INTRINSIC
// GI_STRETCH_MINIMIZING
// GI_GIM
// Originally used `GI_STRETCH_MINIMIZING`
#define PARAMETERIZER_MODE                  GI_GIM

#define USE_MATERIAL                        true

#define NORMAL_IMAGE_WITH_SCALE             2.0f

#define GEOMETRY_IMAGE_SQUARE_WIDTH         0.4f

// ==== Not configurable ====

#define GEOMETRY_IMAGE_SQUARE_HALF_WITH     (GEOMETRY_IMAGE_SQUARE_WIDTH * 0.5f)

enum
{
    VERTEX_POSITION_INDEX = 0,
    NORMAL_INDEX = 1,
    CHECKERBOARD_INDEX = 2,

    MODEL_VERTEX_COMPONENT_COUNT = 3,

    CHECKER_BOARD_WDITH = 256,

    WINDOW_WIDTH = 640,
    WINDOW_HEIGHT = 640
};

static unsigned uiMesh;        // mesh object
static unsigned uiGIM[3];    // image objects
static unsigned uiPattern;    // checkerboard texture
static unsigned uiList;        // OpenGL display list
static float fAngleX = 0.0f, fAngleY = 0.0f, fZ = 5.0f;
static int iLastX, iLastY, iButton, iWidth, iHeight;
static int iWireframe = 0, iDrawMesh = 1, iParam = 0, iFPS = 0;

// geometry image (to be shown) vertex coordinates
static const float s_geometryImageVertexCoords[] = {
    // up-left
    -GEOMETRY_IMAGE_SQUARE_HALF_WITH, GEOMETRY_IMAGE_SQUARE_HALF_WITH, 0.0f,
    // bottom-left
    -GEOMETRY_IMAGE_SQUARE_HALF_WITH, -GEOMETRY_IMAGE_SQUARE_HALF_WITH, 0.0f,
    // up-right
    GEOMETRY_IMAGE_SQUARE_HALF_WITH, GEOMETRY_IMAGE_SQUARE_HALF_WITH, 0.0f,
    // bottom-right
    GEOMETRY_IMAGE_SQUARE_HALF_WITH, -GEOMETRY_IMAGE_SQUARE_HALF_WITH, 0.0f
};

static const float s_geometryImageTextureCoords[] = {
    // up-left
    0.0f, 0.0f,
    // bottom-left
    0.0f, 1.0f,
    // up-right
    1.0f, 0.0f,
    // up-right
    1.0f, 1.0f
};

struct ModelBufferInfo
{
    int vertexCount;
    int indexCount;
    int normalCount;
    int vertexElemCount;
    int indexElemCount;
    int normalElemCount;

    float* vertexBuffer;
    unsigned* indexBuffer;
};

// ==== read PLY2 file and store the data into the buffers ====
static struct ModelBufferInfo CreateModelDataFromPLY2File(const char* fileName)
{
    FILE* pFile = fopen(fileName, "r");
    if (pFile == NULL)
    {
        fprintf(stderr, "cannot open file!\n");
        exit(-1);
    }
    // read vertex data
    int iNumVertices = 0, iNumIndices = 0;
    int ret = fscanf(pFile, "%d\n%d\n", &iNumVertices, &iNumIndices);

    struct ModelBufferInfo result = { iNumVertices, iNumIndices };

    iNumVertices *= MODEL_VERTEX_COMPONENT_COUNT;
    iNumIndices *= MODEL_VERTEX_COMPONENT_COUNT;

    result.vertexElemCount = iNumVertices;
    result.indexElemCount = iNumIndices;

    float* pVertices = calloc(iNumVertices, sizeof(float));
    unsigned* pIndices = calloc(iNumIndices, sizeof(unsigned int));
    if (pVertices == NULL || pIndices == NULL) exit(-1);

    // read vertex data
    for (int i = 0; i < iNumVertices; ++i) {
        ret += fscanf(pFile, "%f\n", pVertices + i);
    }

    // read index data
    for (int i = 0; i < iNumIndices; i += 3)
    {
        int f = 0;
        ret += fscanf(pFile, "%d\n", &f);
        for (int j = 0; j < f; ++j) {
            ret += fscanf(pFile, "%d\n", pIndices + i + j);
        }
    }

    result.vertexBuffer = pVertices;
    result.indexBuffer = pIndices;

    fclose(pFile);

    if (ret == 0)
    {
        fprintf(stderr, "reading file failed!\n");
        exit(-1);
    }

    return result;
}

static void ReleaseModelDataBuffers(struct ModelBufferInfo* modelBufferInfo)
{
    if (modelBufferInfo == NULL) return;

    if (modelBufferInfo->vertexBuffer != NULL)
    {
        free(modelBufferInfo->vertexBuffer);
        modelBufferInfo->vertexBuffer = NULL;
    }
    if (modelBufferInfo->indexBuffer != NULL)
    {
        free(modelBufferInfo->indexBuffer);
        modelBufferInfo->indexBuffer = NULL;
    }
}

// ==== create OpenGI mesh ====
static unsigned create_mesh(struct ModelBufferInfo *pModelBufferInfo)
{
    assert(pModelBufferInfo != NULL);

    const int iNumVertices = pModelBufferInfo->vertexElemCount;
    const int iNumIndices = pModelBufferInfo->indexElemCount;

    float v1[3], v2[3], n[3];

    float* pVertices = pModelBufferInfo->vertexBuffer;
    const unsigned* pIndices = pModelBufferInfo->indexBuffer;
    float* pNormals = calloc(iNumVertices, sizeof(float));
    if (pNormals == NULL) exit(-1);

    // process index data and average face normals
    for (int i = 0; i < iNumIndices; i += 3)
    {
        const unsigned i0 = 3 * pIndices[i];
        const unsigned i1 = 3 * pIndices[i + 1];
        const unsigned i2 = 3 * pIndices[i + 2];
        VEC3_SUB(v1, pVertices + i1, pVertices + i0);
        VEC3_SUB(v2, pVertices + i2, pVertices + i0);
        VEC3_CROSS(n, v1, v2);
        VEC3_ADD(pNormals + i0, pNormals + i0, n);
        VEC3_ADD(pNormals + i1, pNormals + i1, n);
        VEC3_ADD(pNormals + i2, pNormals + i2, n);
    }

    // normalize vertex normals
    for (int i = 0; i < iNumVertices; i += 3) {
        VEC3_NORMALIZE(pNormals + i);
    }

    // set attribute arrays
    giBindAttrib(GI_POSITION_ATTRIB, VERTEX_POSITION_INDEX);
    giBindAttrib(GI_PARAM_ATTRIB, CHECKERBOARD_INDEX);
    giAttribPointer(VERTEX_POSITION_INDEX, 3, GI_FALSE, 0, pVertices);
    giAttribPointer(NORMAL_INDEX, 3, GI_TRUE, 0, pNormals);
    giEnableAttribArray(VERTEX_POSITION_INDEX);
    giEnableAttribArray(NORMAL_INDEX);

    // create mesh
    const unsigned uiMesh = giGenMesh();
    giBindMesh(uiMesh);
    giGetError();
    giIndexedMesh(0, iNumVertices - 1, iNumIndices, pIndices);

    // clean up
    free(pNormals);

    if (giGetError() != GI_NO_ERROR) {
        return 0;
    }

    return uiMesh;
}

// ==== cut mesh ====
static int cut_mesh(unsigned int mesh)
{
    giBindMesh(mesh);
    // cut the mesh into a topological disc
    giCutterParameteri(GI_CUTTER, GI_INITIAL_GIM);
    giCut();

    //check success
    GIboolean bCut = GI_FALSE;
    giGetMeshbv(GI_HAS_CUT, &bCut);
    return (bCut == GI_FALSE) ? -1 : 0;
}

// ==== parameterize mesh ====
static int parameterize_mesh(unsigned mesh, int res)
{
    // configure parameterization and parameterize mesh
    giBindMesh(mesh);
    giParameterizerParameteri(GI_PARAMETERIZER, PARAMETERIZER_MODE);
    giParameterizerParameteri(GI_INITIAL_PARAMETERIZATION, INITIAL_PARAMETERIZATION_MODE);
    giParameterizerParameterf(GI_STRETCH_WEIGHT, 1.0f);
    giParameterizerParameteri(GI_PARAM_RESOLUTION, res);
    giParameterize();

    // check success
    GIboolean bParams = GI_FALSE;
    giGetMeshbv(GI_HAS_PARAMS, &bParams);
    return bParams == GI_FALSE ? -1 : 0;
}

static GLuint s_uiTex[2] = { 0 };

// ==== create geometry, normal and texture image ====
static int create_gim(unsigned int* gim, int res)
{
    const double radius = 1.0;
    const int iNRes = (int)(res * NORMAL_IMAGE_WITH_SCALE);

    // create textures to store geometry and normal data
    glGenTextures(2, s_uiTex);
    glBindTexture(GL_TEXTURE_2D, s_uiTex[VERTEX_POSITION_INDEX]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, res, res, 0, GL_RGBA, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, s_uiTex[NORMAL_INDEX]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iNRes, iNRes, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    // create images and specify data
    giGenImages(3, gim);
    giBindImage(gim[VERTEX_POSITION_INDEX]);
    giImageGLTextureData(res, res, 4, GL_FLOAT, s_uiTex[0]);
    giBindImage(gim[NORMAL_INDEX]);
    giImageGLTextureData(iNRes, iNRes, 3, GI_UNSIGNED_BYTE, s_uiTex[1]);
    giBindImage(gim[CHECKERBOARD_INDEX]);
    giImageGLTextureData(CHECKER_BOARD_WDITH, CHECKER_BOARD_WDITH, 1, GI_UNSIGNED_BYTE, uiPattern);

    // sample into position and normal images
    giAttribImage(VERTEX_POSITION_INDEX, gim[VERTEX_POSITION_INDEX]);
    giAttribImage(NORMAL_INDEX, gim[NORMAL_INDEX]);
    giBindImage(gim[CHECKERBOARD_INDEX]);
    giAttribImage(CHECKERBOARD_INDEX, 0);
    giSamplerParameteri(GI_SAMPLER, GI_SAMPLER_SOFTWARE);
    giAttribSamplerParameteri(VERTEX_POSITION_INDEX, GI_SAMPLING_MODE, GI_SAMPLE_DEFAULT);
    giAttribSamplerParameteri(NORMAL_INDEX, GI_SAMPLING_MODE, GI_SAMPLE_NORMALIZED);
    giSample();

    // check success
    int iAttribCount = 0;
    giGetIntegerv(GI_SAMPLED_ATTRIB_COUNT, &iAttribCount);
    if (iAttribCount != 2)
    {
        giDeleteImages(3, gim);
        return -1;
    }
    return 0;
}

// ==== The followings are GLUT interface implementations ====

static void display(void);
static void reshape(int w, int h);
static void keyboard(unsigned char key, int w, int h);
static void mouse(int button, int state, int x, int y);
static void motion(int x, int y);
static void GICALLBACK errorCB(unsigned int error, void* data);

// initialize OpenGL
static void initGL(void)
{
    const float specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

    // ==== set OpenGL state ====
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glPolygonOffset(-1.0f, -1.0f);
    if (USE_MATERIAL)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 96.0f);
    }
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    uiList = glGenLists(1);

    uint8_t* checkerboardData = calloc(CHECKER_BOARD_WDITH * CHECKER_BOARD_WDITH, sizeof(*checkerboardData));
    if (checkerboardData == NULL) exit(-1);

    // ==== make texture for param visiualization ====
    for (int i = 0; i < CHECKER_BOARD_WDITH; ++i)
    {
        for (int j = 0; j < CHECKER_BOARD_WDITH; ++j) {
            checkerboardData[i * CHECKER_BOARD_WDITH + j] = (uint8_t)(255U * (((i >> 3) + (j >> 3)) & 1U));
        }
    }
    glGenTextures(1, &uiPattern);
    glBindTexture(GL_TEXTURE_2D, uiPattern);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 256, 256, 0,
        GL_LUMINANCE, GL_UNSIGNED_BYTE, checkerboardData);

    free(checkerboardData);
}

// ==== the `main` function for simple geometry image creation and reconstruction ====
int main(int argc, char* argv[])
{
    int f = 0, iRes = 0;

    for (int i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], "--help"))
        {
            printf("usage: gim [--help] -r <RES> <FILE>\n"
                "  <RES>  resolution of geometry image\n  <FILE> PLY2 file\n"
                "keys for controlling the application:\n"
                "  C   change culling mode\n  G   toggle use of geometry shader\n"
                "  M   switch between geometry image and input mesh\n"
                "  P   show parameterization\n  T   toggle use of vertex texturing\n"
                "  V   view all\n  W   show wireframe overlay\n  ESC exit\n");
            return 0;
        }
        if (strcmp(argv[i], "-r") == 0) {
            iRes = atoi(argv[++i]);
        }
        else {
            f = i;
        }
    }
    if (argc < 4)
    {
        printf("usage: gim [--help] -r <RES> <FILE>\n"
            "  <RES>  resolution of geometry image\n  <FILE> PLY2 file\n");
        return -1;
    }
    if (f == 0)
    {
        fprintf(stderr, "no file specified\n");
        return -1;
    }
    if (iRes < 2 || iRes > 1024)
    {
        fprintf(stderr, "resolution not in [2,1024]\n");
        return -1;
    }

    // init GLUT and GL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Geometry Images");
    initGL();

    // ==== init GI, read mesh and create geometry image ====
    GIcontext pContext = giCreateContext();
    giMakeCurrent(pContext);
    giErrorCallback(errorCB, NULL);

    puts("reading model file...");
    const char *modelFilePath = argv[f];
    struct ModelBufferInfo modelBufferInfo = CreateModelDataFromPLY2File(argv[f]);

    puts("creating mesh...");
    uiMesh = create_mesh(&modelBufferInfo);

    ReleaseModelDataBuffers(&modelBufferInfo);

    if (uiMesh == 0)
    {
        fprintf(stderr, "mesh creation failed!\n");
        return -1;
    }
    puts("cutting...");
    if (cut_mesh(uiMesh) == -1)
    {
        fprintf(stderr, "cutting failed!\n");
        return -1;
    }
    puts("parameterizing...");
    if (parameterize_mesh(uiMesh, 17) == -1)
    {
        fprintf(stderr, "parameterization failed!\n");
        return -1;
    }
    puts("sampling...");
    if (create_gim(uiGIM, iRes) == -1)
    {
        fprintf(stderr, "geometry image creation failed!\n");
        return -1;
    }
    giGLAttribRenderParameteri(CHECKERBOARD_INDEX, GI_TEXTURE_COORD_DOMAIN, GI_UNIT_SQUARE);

    // draw mesh into display list
    giGLAttribRenderParameteri(VERTEX_POSITION_INDEX, GI_GL_RENDER_SEMANTIC, GI_GL_VERTEX);
    giGLAttribRenderParameteri(NORMAL_INDEX, GI_GL_RENDER_SEMANTIC, GI_GL_NORMAL);
    giGLAttribRenderParameteri(CHECKERBOARD_INDEX, GI_GL_RENDER_SEMANTIC, GI_GL_TEXTURE_COORD);
    giGLAttribRenderParameteri(CHECKERBOARD_INDEX, GI_GL_RENDER_CHANNEL, 0);

    glNewList(uiList, GL_COMPILE);
    giGLDrawMesh();
    glEndList();

    float fRadius = 0.0f;
    giGetMeshfv(GI_RADIUS, &fRadius);
    fZ = fRadius * 1.9f;

    // run GLUT
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(display);
    glutMainLoop();

    // clean up
    giDeleteMesh(uiMesh);

    GIint iTex[3] = { 0 };
    for (int i = 0; i < 3; ++i)
    {
        giBindImage(uiGIM[i]);
        giGetImageiv(GI_GL_IMAGE_TEXTURE, iTex + i);
    }
    giDeleteImages(3, uiGIM);
    giDestroyContext(pContext);
    glDeleteTextures(3, (GLuint*)iTex);
    return 0;
}

static int s_iFrame = 0, s_iTime = 0, s_iTimebase = 0;

// ==== render geometry image ====
static void display(void)
{
    // clear screen and set camera
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -fZ);
    glRotatef(fAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(fAngleY, 0.0f, 1.0f, 0.0f);

    // set pattern texture
    if (iParam && iDrawMesh)
    {
        glBindTexture(GL_TEXTURE_2D, uiPattern);
        glEnable(GL_TEXTURE_2D);
    }
    else if (!iDrawMesh) {
        giAttribImage(2, iParam ? uiGIM[2] : 0);
    }

    // let OpenGI render the Mesh or the Geometry Image
    if (iDrawMesh) {
        glCallList(uiList);
    }
    else {
        giGLDrawGIM();
    }
    if (iWireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_POLYGON_OFFSET_LINE);
        glDisable(GL_LIGHTING);
        glColor3f(0.5f, 0.5f, 0.5f);
        if (iDrawMesh) {
            glCallList(uiList);
        }
        else
        {
            giAttribImage(1, 0);
            giGLDrawGIM();
            giAttribImage(1, uiGIM[1]);
        }
        glEnable(GL_LIGHTING);
        glDisable(GL_POLYGON_OFFSET_LINE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // restore state
    if (iParam && iDrawMesh) {
        glDisable(GL_TEXTURE_2D);
    }

    // ==== Draw geometry image texture ====
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();

    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    // Enable client vertex array function
    glEnableClientState(GL_VERTEX_ARRAY);
    // Enable client texture coord array function
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, s_geometryImageVertexCoords);
    glTexCoordPointer(2, GL_FLOAT, 0, s_geometryImageTextureCoords);

    // setup viewport
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_WIDTH);

    // setup projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 5.0);

    // setup model view for the geometry image
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-0.75f, -0.5f, -3.0f);

    glBindTexture(GL_TEXTURE_2D, s_uiTex[VERTEX_POSITION_INDEX]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // setup model view for the normal image
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.75f, -0.5f, -3.0f);

    glBindTexture(GL_TEXTURE_2D, s_uiTex[NORMAL_INDEX]);
    glTexCoordPointer(2, GL_FLOAT, 0, s_geometryImageTextureCoords);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glPopMatrix();
    glPopAttrib();

    // compute and display FPS
    ++s_iFrame;
    s_iTime = glutGet(GLUT_ELAPSED_TIME);
    if (s_iTime - s_iTimebase > 1000)
    {
        if (iFPS)
        {
            float fFPS = s_iFrame * 1000.0f / (s_iTime - s_iTimebase);
            printf("FPS: %.2f\n", fFPS);
        }
        s_iTimebase = s_iTime;
        s_iFrame = 0;
    }
    glutSwapBuffers();
}

// ==== react on resizing of window ====
static void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w / (double)h, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    iWidth = w;
    iHeight = h;
}

// cull face status
static unsigned int s_uiCullFace = 0;

// ==== keyboard event ====
static void keyboard(unsigned char key, int w, int h)
{
    const float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    const float amb[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
    const float diff[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GIboolean b;
    float fRadius;
    switch (key)
    {
        // change culling mode
    case 'c':
        if (s_uiCullFace == GL_BACK) {
            s_uiCullFace = GL_FRONT;
        }
        else if (s_uiCullFace == GL_FRONT) {
            s_uiCullFace = 0;
        }
        else {
            s_uiCullFace = GL_BACK;
        }
        if (s_uiCullFace)
        {
            glCullFace(s_uiCullFace);
            glEnable(GL_CULL_FACE);
        }
        else {
            glDisable(GL_CULL_FACE);
        }
        printf("culling %s\n", s_uiCullFace ?
            (s_uiCullFace == GL_FRONT ? "frontfaces" : "backfaces") : "disabled");
        break;

        // toggle display of FPS
    case 'f':
        iFPS = !iFPS;
        break;

        // toggle use of geometry shader
    case 'g':
        giGetBooleanv(GI_GL_USE_GEOMETRY_SHADER, &b);
        giGLRenderParameterb(GI_GL_USE_GEOMETRY_SHADER, !b);
        printf("geometry shader %s\n", b ? "disabled" : "enabled");
        break;

        // switch between mesh and remesh
    case 'm':
        iDrawMesh = !iDrawMesh;
        printf("drawing %s\n", iDrawMesh ? "mesh" : "geometry image");
        break;

        // visualize parameterization
    case 'p':
        iParam = !iParam;
        if (!USE_MATERIAL) break;
        if (iParam)
        {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
        }
        else
        {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
        }
        break;

        // toggle use of vertex texturing
    case 't':
        giGetBooleanv(GI_GL_USE_VERTEX_TEXTURE, &b);
        giGLRenderParameterb(GI_GL_USE_VERTEX_TEXTURE, !b);
        printf("vertex texturing %s\n", b ? "disabled" : "enabled");
        break;

        // view all
    case 'v':
        giBindMesh(uiMesh);
        giGetMeshfv(GI_RADIUS, &fRadius);
        fZ = fRadius * 1.9f;
        break;

        // wireframe overlay
    case 'w':
        iWireframe = !iWireframe;
        break;

        // exit
    case 27:
        exit(0);
    }
}

// ==== mouse click ====
static void mouse(int button, int state, int x, int y)
{
    iLastX = x;
    iLastY = y;
    iButton = button;
}

// ==== mouse move ====
void motion(int x, int y)
{
    if (iButton == GLUT_LEFT_BUTTON)
    {
        fAngleX = fmodf(fAngleX + 360.0f * (float)(y - iLastY) / iHeight, 360.0f);
        fAngleY = fmodf(fAngleY + 360.0f * (float)(x - iLastX) / iWidth, 360.0f);
        iLastX = x;
        iLastY = y;
    }
    else if (iButton == GLUT_RIGHT_BUTTON)
    {
        fZ *= 1.0f - 2.0f * (float)(iLastY - y) / iHeight;
        iLastY = y;
    }
}

// ==== OpenGI error callback ====
void GICALLBACK errorCB(unsigned int error, void* data)
{
    // actually default callback in debug but we want it in release, too
    fprintf(stderr, "OpenGI error: %s!\n", giErrorString(error));
}

