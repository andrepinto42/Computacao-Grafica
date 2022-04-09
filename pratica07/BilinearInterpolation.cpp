//
// Created by pinto on 09/04/22.
//
#include "GenerateTerrain.h"
#include "BilinearInterpolation.h"
#include <math.h>

float *arrayGrid;
int imageWidth;

void GenerateTerrain::SetUpVariavels(float *arr1,int imageWidth1)
{
    arrayGrid = arr1;
    imageWidth = imageWidth1;
}

float GenerateTerrain::GetHeight(int x, int z){
    return arrayGrid[z * imageWidth - x];
}

float GenerateTerrain::GetHeightBilinearInterpolation(float x,float z){
    int nearX = floor(x);
    int nearZ = floor(z);
    int nextX = nearX +1;
    int nextZ = nearZ +1;

    float Xfractional =  x-nearX;
    float Zfractional =  z-nearZ;

    //Descobrir a coordenada Z entre 2 pontos e também entre os dois pontos que são adjacentes
    //Interpolação bilienar
    float height_x1_z = GetHeight(nearX,nearZ) * (1-Zfractional) + GetHeight(nearX,nextZ) * Zfractional;
    float height_x2_z = GetHeight(nextX,nearZ) * (1-Zfractional) + GetHeight(nextX,nextZ) * Zfractional;

    //Tendo 2 pontos então podemos interpolar linearmente entre eles para descobrir o verdadeiro valor da altura
    float height_XZ = height_x1_z * (1-Xfractional) + height_x2_z * Xfractional;

    return height_XZ;
}
