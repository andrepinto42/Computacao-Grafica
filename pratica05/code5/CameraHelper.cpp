//
// Created by pinto on 29/03/22.
//

#include "CameraHelper.h"
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <stdio.h>

#endif


float camX=3.f, camY=3.f, camZ=3.f;
float lookX=0.f,lookY=1.f,lookZ=0.f;

float speed = 2.f;

Vector3::Vector3(float x,float y,float z) {
    this->x = x;
    this->y = y;
    this->z= z;
}

Vector3* CameraHelper::GetDirection(float x1,float y1,float z1,float x2,float y2,float z2){
    return GetDirection(Vector3(x1,y1,z1), Vector3(x2,y2,z2));
}

Vector3* CameraHelper::GetDirection(Vector3 position,Vector3 lookPosition){
    //Calcular a direçao que a camera está a olhar
    float directionX = position.x - lookPosition.x;
    float directionY = position.y - lookPosition.y;
    float directionZ = position.z - lookPosition.z;

    //Descobrir o vetor da direção que tem comprimento 1
    float magnitude = sqrt(directionX*directionX + directionY*directionY + directionZ*directionZ);
    directionX /= magnitude;
    directionY /= magnitude;
    directionZ /= magnitude;

    return new Vector3(directionX,directionY,directionZ);
}
void CameraHelper::MoveCamera(Vector3 position,Vector3 lookPosition,float *camX,float *camY,float *camZ,float speed) {
    auto direction =GetDirection(position,lookPosition);
    //Adicionar o vetor direção à camara
    *camX += direction->x * speed;
    *camY += direction->y * speed;
    *camZ += direction->z * speed;
    free(direction);
}
void CameraHelper::MoveCameraForward() {
    auto direction =GetDirection(
            lookX,lookY,lookZ,
            camX,camY,camZ);

    AddVectorCamera(direction);

}

void CameraHelper::MoveCameraRight() {
    auto direction =GetDirection(
            camX,camY,camZ,
            lookX,lookY,lookZ);


    float x = direction->x;
    float z = direction->z;


    float angleZXRight = tanh(z/x) - (M_PI/2.f);

    x = cos(angleZXRight);
    z = sin(angleZXRight);

    float y;

    if (direction->y != 0)
        y = ( (-direction->x * x) - direction->z * z) / direction->y;
    //Caso esteja a lidar com o plano em que o y = 0
    else y = 0;
    
    free(direction);

    direction = new Vector3(x,y,z);


    AddVectorCamera(direction);
}


void CameraHelper::MoveCameraLeft() {
    auto direction =GetDirection(
            camX,camY,camZ,
            lookX,lookY,lookZ);


    float x = direction->x;
    float z = direction->z;


    float angleZXRight = tanh(z/x) + (M_PI/2.f);

    x = cos(angleZXRight);
    z = sin(angleZXRight);

    float y = ( (-direction->x * x) - direction->z * z) / direction->y;

    free(direction);

    direction = new Vector3(x,y,z);


    AddVectorCamera(direction);
}

void CameraHelper::MoveCameraBackwards() {
    auto direction =GetDirection(
            camX,camY,camZ,
            lookX,lookY,lookZ);

    AddVectorCamera(direction);
}

void CameraHelper::AddVectorCamera(Vector3* direction) {
    //Adicionar o vetor direção à camara
    camX += direction->x * speed;
    camY += direction->y * speed;
    camZ += direction->z * speed;

    lookX += direction->x * speed;
    lookY += direction->y * speed;
    lookZ += direction->z * speed;
    free(direction);
}



void CameraHelper::SetUpCamera() {
    gluLookAt(camX, camY, camZ,
              lookX, lookY, lookZ,
              0.f, 1.f, 0.f);
    printf("x=%f,y=%f,z=%f\n",camX,camY,camZ);
}