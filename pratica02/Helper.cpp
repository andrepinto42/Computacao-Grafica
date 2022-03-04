//
// Created by pinto on 04/03/22.
//

#include "Helper.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>


float Helper::polar2CartX(float radius,float angle)
{
    return radius * sin(angle * M_PI / 180.f);
}

float Helper::polar2CartZ(float radius, float angle)
{
    return radius * cos(angle *  M_PI / 180.f);
}

void Helper::drawCilinder(float radius , float height, int slices)
{
    float step = 360.f / (float) slices;
    for (float i = 0; i < 360.f; i+=step) {
        drawBaseCilinderTriangle(0, radius, i, i + step);
        drawBaseCilinderTriangle(height, radius, i, i + step);
        drawSideCilinderTriangle(height,radius,i,i+step);
    }
}

void Helper::drawBaseCilinderTriangle(float base, float radius, float angle1, float angle2)
{
    glBegin(GL_TRIANGLES);
    // Bottom face (y = 0.0f)
    // Define vertices in counter-clockwise (CCW) order with normal pointing out
    glVertex3f( 0.0f, base, 0.0f);
    glColor3f(0.0f, angle1, angle2);     // Green
    glVertex3f(polar2CartX(radius,angle1), base, polar2CartZ(radius, angle1));
    glColor3f(angle1, angle2, angle1);     // Green
    glVertex3f(polar2CartX(radius,angle2), base, polar2CartZ(radius, angle2));
    glEnd();

}

void Helper::drawSideCilinderTriangle(float height, float radius, float angle1, float angle2)
{
    glBegin(GL_QUADS);

    glColor3f(0.0f, angle1, angle2);     // Green
    glVertex3f(polar2CartX(radius,angle1), 0.0f, polar2CartZ(radius, angle1));
    glVertex3f(polar2CartX(radius,angle2), 0.0f, polar2CartZ(radius, angle2));
    glVertex3f(polar2CartX(radius,angle2), height, polar2CartZ(radius, angle2));
    glVertex3f(polar2CartX(radius,angle1), height, polar2CartZ(radius, angle1));

    glEnd();
}


