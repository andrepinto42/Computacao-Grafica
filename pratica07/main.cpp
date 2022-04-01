

#include<stdio.h>
#include<stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glew.h>
#include <GL/glut.h>
#include "Axes.h"
#include "GenerateTerrain.h"
#include "CameraHelper.h"

#endif

void DrawStripeHeightReversed(float startXpos,float startZ,float lengthDivision,int numberDivisions,float* arrayHeights,int currentRow);

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45,ratio,1,10000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	CameraHelper::SetUpCamera();

	GenerateTerrain::drawTerrain();
    Axes::DrawAxes();

    GenerateTerrain::DrawTeaPots();

    // End of frame
	glutSwapBuffers();
}



void processKeys(unsigned char key, int xx, int yy) {
    switch (key) {
        case 'w': {
            CameraHelper::MoveCameraForward();
            break;
        }
        case 's':{
            CameraHelper::MoveCameraBackwards();
            break;
        }
        case 'd':{
            CameraHelper::MoveCameraRight();
            break;
        }
        case 'a':{
            CameraHelper::MoveCameraLeft();
            break;
        }
    }

}

void processMouseButtons(int button, int state, int xx, int yy) {
}


void processMouseMotion(int xx, int yy) {
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(900,900);
	glutCreateWindow("CG@DI-UM");
		

// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

    // Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);

    GenerateTerrain::init();

    // enter GLUT's main cycle
	glutMainLoop();
	
	return 0;
}