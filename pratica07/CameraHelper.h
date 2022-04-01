//
// Created by pinto on 29/03/22.
//

#ifndef MAIN_CPP_CAMERAHELPER_H
#define MAIN_CPP_CAMERAHELPER_H

class Vector3{
public:
    Vector3(float x,float y,float z);
    float x;
    float y;
    float z;
};

class CameraHelper {
public:
    static Vector3* GetDirection(Vector3 position, Vector3 lookPosition);
    static void MoveCamera(Vector3 position, Vector3 lookPosition, float *camX, float *camY, float *camZ, float speed);

    static void SetUpCamera();

    static Vector3 *GetDirection(float x1, float y1, float z1, float x2, float y2, float z2);

    static void MoveCameraForward();

    static void MoveCameraBackwards();

    static void AddVectorCamera(Vector3* vector);

    static void MoveCameraRight();

    static void MoveCameraLeft();
};


#endif //MAIN_CPP_CAMERAHELPER_H
