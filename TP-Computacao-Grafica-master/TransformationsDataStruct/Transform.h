//
// Created by pinto on 31/03/22.
//

#ifndef CLASS1_TRANSFORM_H
#define CLASS1_TRANSFORM_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

class Transform {
public:
//    Transform()= default;
    virtual void Print()
    {
        std::cout<< "hello ma man\n";
    }

    virtual void Apply() {

    }
};

class T_Scale : public Transform{
public:
    float x,y,z;
    T_Scale(float x,float y,float z):x(x),y(y),z(z){}
    virtual void Print(){
        std::cout << " I am Scale";
    }
    virtual void Apply()
    {
        glScalef(x,y,z);
    }
};

class T_Translate : public Transform{
public:
    float x,y,z;
    T_Translate(float x,float y,float z):x(x),y(y),z(z){}
    void Print() override{
        std::cout << " I am Transform";
    }
    virtual void Apply()
    {
        glTranslatef(x,y,z);
    }
};
class T_Rotate : public Transform{
public:
    float angle,x,y,z;
    T_Rotate(float angle,float x,float y,float z):angle(angle),x(x),y(y),z(z){}
    void Print() override{
        std::cout << " I am Rotate";
    }

    virtual void Apply()
    {
        glRotatef(angle,x,y,z);
    }
};

#endif //CLASS1_TRANSFORM_H
