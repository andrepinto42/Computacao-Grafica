//
// Created by pinto on 31/03/22.
//

#ifndef CLASS1_T_SCALE_H
#define CLASS1_T_SCALE_H


#include "Transform.h"

class T_Scale: public Transform {
public:
    T_Scale(float x, float y, float z);
    float x,y,z;
};


#endif //CLASS1_T_SCALE_H
