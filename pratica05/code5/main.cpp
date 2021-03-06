#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include "CameraHelper.h"

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;

void DrawPlaneBase();

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	CameraHelper::SetUpCamera();
    DrawPlaneBase();

    // End of frame

    glColor3f(1.f,0.f,0.f);
	// put code to draw scene in here
	glutWireTeapot(2.f);
	
	glutSwapBuffers();
}

void DrawPlaneBase() {
    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex3f(100.0f, 0, -100.0f);
    glVertex3f(-100.0f, 0, -100.0f);
    glVertex3f(-100.0f, 0, 100.0f);

    glVertex3f(100.0f, 0, -100.0f);
    glVertex3f(-100.0f, 0, 100.0f);
    glVertex3f(100.0f, 0, 100.0f);
    glEnd();
}

void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here
    printf("%c\n",c);
    switch (c) {
//        case 'a':
//            lookX -= 0.5f;
//            break;
//        case 'd':
//            lookX += 0.5f;
//            break;
//        case 's':
//            lookY -= 0.5f;
//            break;
//        case 'w':
//            lookY += 0.5f;
//            break;
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


void processSpecialKeys(int key, int xx, int yy) {
//
//	switch (key) {
//
//	case GLUT_KEY_RIGHT:
//		alfa -= 0.1;
//        break;
//
//	case GLUT_KEY_LEFT:
//		alfa += 0.1;
//        break;
//
//	case GLUT_KEY_UP:
//        if (beta > .5f)
//            break;
//		beta += 0.1f;
//		break;
//
//	case GLUT_KEY_DOWN:
//        if (beta <= 0.1f)
//            break;
//		beta -= 0.1f;
//		break;
//
//	case GLUT_KEY_PAGE_DOWN:
//        radius -= 1.0f;
//		break;
//
//	case GLUT_KEY_PAGE_UP:
//        radius += 1.0f;
//        break;
//	}
//	spherical2Cartesian();
//	glutPostRedisplay();

}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin");
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	printInfo();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
