//
// Created by pinto on 31/03/22.
//

#ifndef CLASS1_T_TRANSLATE_H
#define CLASS1_T_TRANSLATE_H


#include "Transform.h"

class T_Translate : public Transform{
public:
    float x,y,z;
    T_Translate(float x,float y,float z);
};


#endif //CLASS1_T_TRANSLATE_H
