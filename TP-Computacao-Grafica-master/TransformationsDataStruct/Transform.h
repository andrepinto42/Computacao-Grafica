//
// Created by pinto on 31/03/22.
//

#ifndef CLASS1_TRANSFORM_H
#define CLASS1_TRANSFORM_H


#include <iostream>

class Transform {
public:
    Transform()= default;
    virtual void Print()=0;
};

class T_Scale : public Transform{
public:
    float x,y,z;
    T_Scale(float x,float y,float z):x(x),y(y),z(z){}
    void Print() override{
        std::cout << " I am Scale";
    }
};


class T_Translate : public Transform{
public:
    float x,y,z;
    T_Translate(float x,float y,float z):x(x),y(y),z(z){}
    void Print() override{
        std::cout << " I am Transform";
    }
};
class T_Rotate : public Transform{
public:
    float angle,x,y,z;
    T_Rotate(float angle,float x,float y,float z):angle(angle),x(x),y(y),z(z){}
    void Print() override{
        std::cout << " I am Rotate";
    }
};

#endif //CLASS1_TRANSFORM_H
