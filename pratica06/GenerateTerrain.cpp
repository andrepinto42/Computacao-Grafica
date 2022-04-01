//
// Created by pinto on 29/03/22.
//
#include "Axes.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glew.h>
#include <GL/glut.h>

#include <IL/il.h>
#include <vector>

#include <math.h>
#include<stdlib.h>
#include<stdio.h>
#include "GenerateTerrain.h"
#endif

std::vector<float> arrayPointsTerrain;

void drawTerrain();

void DrawStripe(float startXpos, float startZ, float lengthDivision, int numberDivisions);

void DrawStripeHeight(float startXpos, float startZ, float lengthDivision, int numberDivisions, float* arrayHeights, int currentRow);

void DrawStripeHeightArray(float startX, float startZ, float lengthDivision, int numberDivisions, float* arrayHeights, int currentLine);


const bool ENABLE_VBO = true;
float *arrayGrid;
int imageWidth;
int imageHeight;
GLuint buffers[1];

void GenerateTerrain::init() {
    // init GLEW
    glewInit();
    glEnableClientState(GL_VERTEX_ARRAY);

    //Iniciar a ferramenta de carregar imagens
    ilInit();

    // 	Load the height map "terreno.jpg"
    unsigned int t;
    unsigned char *imageData;
    ilGenImages(1,&t);
    ilBindImage(t);

    // terreno.jpg is the image containing our height map
    ilLoadImage((ILstring)"terreno.jpg");

    // convert the image to single channel per pixel
    // with values ranging between 0 and 255
    ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);

    // important: check imageWidth and imageHeight values
    // both should be equal to 256
    // if not there was an error loading the image
    // most likely the image could not be found
    imageWidth = ilGetInteger(IL_IMAGE_WIDTH);
    imageHeight = ilGetInteger(IL_IMAGE_HEIGHT);

    int numberPixels = imageWidth*imageHeight;
    // imageData is a LINEAR array with the pixel values
    imageData = ilGetData();

    printf("width = %d height = %d\n", imageWidth, imageHeight);

    // 	Build the vertex arrays
    const float maxHeight = 20.f;

    arrayGrid = (float*) malloc(sizeof(float) * numberPixels);

    for (int i = 0; i < numberPixels; ++i) {
        //Maybe here do some math so the vertices dont look so distance from one another
        arrayGrid[i] =  imageData[i];
        printf("%f ",arrayGrid[i]);
    }

    if (ENABLE_VBO)
        Fill_VBO_ArrayTerrain();


    // 	OpenGL settings
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
}

void GenerateTerrain::Fill_VBO_ArrayTerrain() {
    float lengthDivision = 1.f;
    float startX = 0.f;
    float startZ = 0.f;
    for (int i = 0; i < imageHeight-1; ++i) {
        DrawStripeHeightArray(startX+i, startZ, lengthDivision,imageWidth,arrayGrid,i);
    }

    //Build the VBO
    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arrayPointsTerrain.size(), arrayPointsTerrain.data(), GL_STATIC_DRAW);
}

//TODO
void GenerateTerrain::drawTerrain(){

    if (ENABLE_VBO)
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        //Desenhar terreno usando VBOs com TRIANGLE_STRIPS
        glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        //Iterar imageHeight-1 pois não é necessário desenhar a ultima strip de terreno
        for (int i = 0; i < imageHeight - 1 ; i++) {
            glColor3f( float ((imageHeight - 1) -i) / (float)(imageHeight-1),(float)i / (float)(imageHeight-1),0.f );
            glDrawArrays(GL_TRIANGLE_STRIP, (imageWidth) * 2 * i, (imageWidth) * 2);
        }
    }

    else{

        float lengthDivision = 1.f;
        float startX = 0.f;
        float startZ = 0.f;

        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        for (int i = 0; i < imageHeight-1; ++i) {
            DrawStripeHeight(startX+i, startZ, lengthDivision,imageWidth,arrayGrid,i);
        }
    }

}

void DrawStripe(float startX, float startZ, float lengthDivision, int numberDivisions){

    float endX = startX -lengthDivision;

    glBegin(GL_TRIANGLE_STRIP);
    //Draw a Stripe
    for (int i = 0; i < numberDivisions*2 ; ++i) {
        glColor3f(0.f,7/7.f,0.f);

        float z =((i%2) == 0) ? startX : endX;
        float x = floor(i/2.f) * -lengthDivision + startZ;

        glVertex3d(x,0.0f,z);
//        printf("x=%f z=%f \n",x,z);
    }
    glEnd();
}

//Carefull that the arrayHeights has capacity enough to suport the stripe Start
void DrawStripeHeight(float startX,float startZ,float lengthDivision,int numberDivisions,float* arrayHeights,int currentLine){

    float endX = startX -lengthDivision;

    glBegin(GL_TRIANGLE_STRIP);

    //Draw a Stripe
    for (int i = 0; i < numberDivisions *2; ++i) {
        glColor3f(1.f,i/ ((float) numberDivisions * 2.f),0.f);
        bool isPair = (i%2) == 0;

        float x = floor(i/2.f) * -lengthDivision + startZ;
        float z = isPair ? startX : endX;
        float y;
        if (isPair)
            y = arrayHeights[numberDivisions * (currentLine+1) +i/2];
        else
            y= arrayHeights[numberDivisions * currentLine + i/2];

        glVertex3d(x,y,z);

//        if(active)
//        {
//            printf("x = %f, y = %f, z = %f\n",x,y,z);
//            if (isPair)
//                printf("index = %d ,height = %f ",numberDivisions * currentLine + i/2,arrayHeights[numberDivisions * currentLine + i/2]);
//            else
//                printf("index = %d ,height = %f ",numberDivisions * (currentLine+1) + i/2,arrayHeights[numberDivisions * (currentLine+1) + i/2]);
//            printf("i = %d\n\n",i);
//        }
    }
    glEnd();
}

//Carefull that the arrayHeights has capacity enough to suport the stripe Start
void DrawStripeHeightArray(float startX,float startZ,float lengthDivision,int numberDivisions,float* arrayHeights,int currentLine){
    float endX = startX -lengthDivision;
    //Draw a Stripe
    for (int i = 0; i < numberDivisions *2; ++i) {
        glColor3f(1.f,i/ ((float) numberDivisions * 2.f),0.f);
        bool isPair = (i%2) == 0;

        float x = floor(i/2.f) * -lengthDivision + startZ;
        float z = isPair ? startX : endX;
        float y;
        if (isPair)
            y = arrayHeights[numberDivisions * (currentLine+1) +i/2];
        else
            y= arrayHeights[numberDivisions * currentLine + i/2];

        if(currentLine == 0)
        {

        printf("x = %f, y = %f, z = %f\n",x,y,z);
        if (isPair)
            printf("index = %d ,height = %f ",numberDivisions * currentLine + i/2,arrayHeights[numberDivisions * currentLine + i/2]);
        else
            printf("index = %d ,height = %f ",numberDivisions * (currentLine+1) + i/2,arrayHeights[numberDivisions * (currentLine+1) + i/2]);
        printf("i = %d\n\n",i);
        }

        arrayPointsTerrain.push_back(x);
        arrayPointsTerrain.push_back(y);
        arrayPointsTerrain.push_back(z);
    }
}
