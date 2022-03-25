

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
#endif


float camX = 00, camY = 30, camZ = 40;
int startX, startY, tracking = 0;

int alpha = 0, beta =45, r = 50;

void drawTerrain();
void DrawStripeHeight(float startXpos,float startZ,float lengthDivision,int numberDivisions,float* arrayHeights,int currentRow);

void DrawStripe(float startXpos,float startZ,float lengthDivision,int numberDivisions);

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
	gluPerspective(45,ratio,1,1000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

float *arrayGrid;
int imageWidth;
int imageHeight;
GLuint buffers[1];



void renderScene(void) {

	float pos[4] = {-1.0, 1.0, 1.0, 0.0};

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX, camY, camZ, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	drawTerrain();


// End of frame
	glutSwapBuffers();
}



void processKeys(unsigned char key, int xx, int yy) {

// put code to process regular keys in here
}



void processMouseButtons(int button, int state, int xx, int yy) {
	
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			
			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
}


void processMouseMotion(int xx, int yy) {

	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * 							     sin(betaAux * 3.14 / 180.0);
}


void init() {

// 	Load the height map "terreno.jpg"
    unsigned int t;
    unsigned char *imageData;
    ilGenImages(1,&t);
    ilBindImage(t);

    // terreno.jpg is the image containing our height map
    ilLoadImage((ILstring)"terreno.jpg");

    // convert the image to single channel per pixel
    // with values ranging between 0 and 255
    ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);

    // important: check imageWidth and imageHeight values
    // both should be equal to 256
    // if not there was an error loading the image
    // most likely the image could not be found
    imageWidth = ilGetInteger(IL_IMAGE_WIDTH);
    imageHeight = ilGetInteger(IL_IMAGE_HEIGHT);

    int numberPixels = imageWidth*imageHeight;
    // imageData is a LINEAR array with the pixel values
    imageData = ilGetData();

    printf("width = %d height = %d\n", imageWidth, imageHeight);

    // 	Build the vertex arrays
    const float maxHeight = 20.f;

    arrayGrid = (float*) malloc(sizeof(float) * numberPixels);

    for (int i = 0; i < numberPixels; ++i) {
        //Maybe here do some math so the vertices dont look so distance from one another
        arrayGrid[i] =  imageData[i];
        printf("%f ",arrayGrid[i]);
    }


    //Build the VBO
    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,numberPixels, arrayGrid, GL_STATIC_DRAW);

    // 	OpenGL settings
    glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
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

    // init GLEW
    glewInit();
    glEnableClientState(GL_VERTEX_ARRAY);

    //Iniciar a ferramenta de carregar imagens
    ilInit();

    init();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 0;
}


void drawTerrain() {

    // colocar aqui o código de desnho do terreno usando VBOs com TRIANGLE_STRIPS
//    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
//    glVertexPointer(3, GL_FLOAT, 0, 0);
//    for (int i = 0; i < imageHeight - 1 ; i++) {
//        glDrawArrays(GL_TRIANGLE_STRIP, (imageWidth) * 2 * i, (imageWidth) * 2);
//    }

    float lengthDivision = 1.f;
    float startX = 0.f;
    float startZ = 0.f;
    int numberDivisions = 10;

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
//    for (int i = 0; i < numberDivisions; ++i) {
//        DrawStripe(startX+i, startZ, lengthDivision,numberDivisions);
//    }


    for (int i = 0; i < imageHeight-1; ++i) {
        DrawStripeHeight(startX+i, startZ, lengthDivision,imageWidth,arrayGrid,i);
    }
}

void DrawStripe(float startX,float startZ,float lengthDivision,int numberDivisions){

    float endX = startX -lengthDivision;

    glBegin(GL_TRIANGLE_STRIP);
    //Draw a Stripe
    for (int i = 0; i < numberDivisions*2 ; ++i) {
        glColor3f(0.f,7/7.f,0.f);

        float z =((i%2) == 0) ? startX : endX;
        float x = floor(i/2.f) * -lengthDivision + startZ;

        glVertex3d(x,0.0f,z);
//        printf("x=%f z=%f \n",x,z);
    }
    glEnd();
}

//Carefull that the arrayHeights has capacity enough to suport the stripe Start
void DrawStripeHeight(float startX,float startZ,float lengthDivision,int numberDivisions,float* arrayHeights,int currentLine){

    float endX = startX -lengthDivision;

    glBegin(GL_TRIANGLE_STRIP);
    //Draw a Stripe
    for (int i = 0; i < numberDivisions ; ++i) {
        glColor3f(0.f,7/7.f,0.f);
        bool isPair = (i%2) == 0;

        float z = isPair ? startX : endX;
        float x = floor(i/2.f) * -lengthDivision + startZ;
        float y;
        if (isPair)
            y= arrayHeights[numberDivisions * currentLine+i];
        else
            y = arrayHeights[numberDivisions * (currentLine+1) +i];

        glVertex3d(x,y,z);
        printf("y = %f \n",y);
    }
    glEnd();
}