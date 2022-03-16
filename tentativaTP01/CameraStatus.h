//
// Created by pinto on 07/03/22.
//

#ifndef PARSER_CPP_CAMERASTATUS_H
#define PARSER_CPP_CAMERASTATUS_H


class CameraStatus {
public:
    float posX;
    float posY;
    float posZ;

    float lookX;
    float lookY;
    float lookZ;

    float upX;
    float upY;
    float upZ;

    float fov;
    float near;
    float far;

    CameraStatus(float posX, float posY, float posZ, float lookX, float lookY, float lookZ, float upX, float upY,
                 float upZ, float fov, float near, float far);
    CameraStatus();
};


#endif //PARSER_CPP_CAMERASTATUS_H
