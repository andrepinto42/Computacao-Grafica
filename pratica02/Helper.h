//
// Created by pinto on 04/03/22.
//

#ifndef MAIN_CPP_HELPER_H
#define MAIN_CPP_HELPER_H


#include <GL/gl.h>

class Helper {
public:
    static float polar2CartX(float radius, float angle);
    static float polar2CartZ(float radius, float angle);

    static void drawCilinder(float radius ,float height,int slices);

    static void drawBaseCilinderTriangle(float base, float radius, float angle1, float angle2);


    static void drawSideCilinderTriangle(float height, float radius, float angle1, float angle2);
};


#endif //MAIN_CPP_HELPER_H
