//
// Created by pinto on 29/03/22.
//

#ifndef MAIN_CPP_GENERATETERRAIN_H
#define MAIN_CPP_GENERATETERRAIN_H
class GenerateTerrain{
public:

    static void drawTerrain();

    static void init();

    static void Fill_VBO_ArrayTerrain();
    static void DrawTeaPots();

    static float GetHeight(int x, int z);

    static void SetUpVariavels(float *arr1, int imageWidth1);

    static float GetHeightBilinearInterpolation(float x, float z);
};
#endif //MAIN_CPP_GENERATETERRAIN_H
