//
// Created by pinto on 31/03/22.
//

#ifndef CLASS1_T_ROTATE_H
#define CLASS1_T_ROTATE_H


#include "Transform.h"

class T_Rotate : public Transform{
public:
    T_Rotate(float angle,float x, float y, float z);
    float angle,x,y,z;
};


#endif //CLASS1_T_ROTATE_H
