//
// Created by pinto on 07/03/22.
//

#include "CameraStatus.h"

CameraStatus::CameraStatus(float posX, float posY, float posZ, float lookX, float lookY, float lookZ, float upX,
                           float upY, float upZ, float fov, float near, float far) :
        posX(posX), posY(posY), posZ(posZ),
        lookX(lookX), lookY(lookY),
        lookZ(lookZ), upX(upX), upY(upY),
        upZ(upZ), fov(fov), near(near),
        far(far)
        {

        }

CameraStatus::CameraStatus():
    posX(0.f), posY(0.f), posZ(0.f),
    lookX(0.f), lookY(0.f),lookZ(0.f),
    upX(0.f), upY(1.f), upZ(0.f),
    fov(60), near(1),far(1000)
{
}
