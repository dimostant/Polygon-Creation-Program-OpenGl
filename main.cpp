#include <stdio.h>     // - Just for some ASCII messages
#include <stdlib.h>
#include <iostream>
#include <string>
using std::string;
#include "gl/glut.h"   // - An interface and windows
#include <math.h>


//colors for submenu
#define BLACK 1
#define WHITE 2
#define RED 3
#define BLUE 4
#define GREEN 5
#define ORANGE 6
#define PURPLE 7
#define PINK 8

//options fur main menu
#define POLYGON 9
#define CLIPPING 10
#define EXTRUDE 11
#define CLEAR 12
#define EXIT 13


// Global variables
// Window/viewport
int winw, winh;               // Window width & height, in pixels, saved by reshape

//rgb code for line color submenu
float line_red = 0.0;
float line_green = 0.0;
float line_blue = 0.0;

//rgb code for fill color submenu
float fill_red = 1.0;
float fill_green = 1.0;
float fill_blue = 1.0;


// Mouse
bool mouseleftpressed = false;   // True if mouse LEFT button is down.
bool mouserightpressed = false;
// Saved by mouse.
int mousex, mousey;           // Mouse x,y coords, in GLUT format (pixels from upper-left corner).
							  // Only guaranteed to be valid if a mouse button is down.
							  // Saved by mouse, motion


//Keyboard
const int ESCKEY = 27;


//Polygon
const int N = 10000;
const int M = 10000;

GLfloat polygonVerticies[N];
int vertexInArray = 0; // every 2n is x cord , every 2n + 1 is y cord

int polygons[M]; // every polygon number of vetrexes is stored in every different M
int polygonInArray = 0;

double pt1x, pt1y, pt2x, pt2y;

bool firstpt = false;
bool polygonEnabled = false;
bool clearScreen = false;

const double pointsize = 1;// og 10


//Clipping window
float xmin = 0.3, xmax = 0.7, ymin = 0.3, ymax = 0.7;
//float xmin, xmax, ymin, ymax;
int left = 1;	//0001
int right = 2;	//0010
int bottom = 4;	//0100
int up = 8;	//1000

const int K = 10000;
GLfloat clippedPolygon[K];


GLuint width = 600;
GLuint height = 500;


void printbitmap(const string msg, double x, double y)
{
	glRasterPos2d(x, y);
	for (string::const_iterator ii = msg.begin();
		ii != msg.end();
		++ii)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *ii);
	}
}


void clearWindow()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Documentation
	glColor3d(0.0, 0.0, 0.0);  // Black text
	printbitmap("Mou vghke"/*"Simple Mouse Demo"*/, 0.1, 0.9);
	printbitmap("O kwlos"/*"Press left mouse button and move mouse"*/, 0.05, 0.55);
	printbitmap("Sto debugging"/*"Esc   Quit"*/, 0.15, 0.25);
	
	//clear written arrays
	for (int i = 0; i < vertexInArray; i++)
	{
		polygonVerticies[i] = 0;
	}

	vertexInArray = 0;

	for (int i = 0; i < polygonInArray; i++)
	{
		polygonVerticies[i] = 0;
	}

	polygonInArray = 0;
}


// The GLUT mouse function
void Mouse(int button, int state, int x, int y) 
{

	// Save the left button state
	if (button == GLUT_LEFT_BUTTON) 
	{
		mouseleftpressed = (state == GLUT_UP);
		glutPostRedisplay();  // Left button has changed; redisplay
	}

	//Save the mouse position
	mousex = x;
	mousey = y;

	if (button == GLUT_RIGHT_BUTTON) 
	{
		mouserightpressed = (state == GLUT_UP);
		glutPostRedisplay();
	}

}


// The GLUT Keyboard function
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		//case 'C': clearScreen = true;
		//	break;
		//case ESCKEY:
		//case 'X': exit(0);
		//	break;
		//
	}
	glutPostRedisplay();
}


void Polygon() 
{

	if (clearScreen)
	{
		clearWindow();
		firstpt = false;
		clearScreen = false;
	}

	if (mouseleftpressed && polygonEnabled)
	{
		// Convert mouse position to OpenGL's coordinate system
		double oglx = double(mousex) / winw;
		double ogly = 1 - double(mousey) / winh;
		glColor3f(line_red, line_green, line_blue);
		glPointSize(pointsize);


		if (!firstpt)
		{
			glBegin(GL_POINTS);
			glVertex2d(oglx, ogly);
			glEnd();
			pt1x = oglx;
			pt1y = ogly;
			polygonVerticies[vertexInArray++] = pt1x;
			polygonVerticies[vertexInArray++] = pt1y;
			firstpt = true;
			printf("first point : %f, %f \n", pt1x, pt1y);
		}
		else
		{
			pt2x = oglx;
			pt2y = ogly;
			glBegin(GL_POINTS);
			glVertex2d(pt2x, pt2y);
			glEnd();
			glBegin(GL_LINE_STRIP);
			glVertex2d(pt1x, pt1y);
			glVertex2d(pt2x, pt2y);
			glEnd();

			polygonVerticies[vertexInArray++] = pt2x;
			polygonVerticies[vertexInArray++] = pt2y;

			//move last point to first
			pt1x = pt2x;
			pt1y = pt2y;

			printf("next point : %f, %f \n , vertexInArray : %d \n", pt2x, pt2y, vertexInArray);
		}

		mouseleftpressed = false;
	}

	if (mouserightpressed)
	{
		int vertexPos = 0;
		for (int i = 0; i < polygonInArray; i++) {
			vertexPos += polygons[i];
		}

		polygons[polygonInArray] = vertexInArray - vertexPos;

		GLfloat *tmpVertArr = (GLfloat*)malloc(sizeof(GLfloat)* polygons[polygonInArray]);

		for (int i = 0; i < polygons[polygonInArray]; i++)
		{
			tmpVertArr[i] = polygonVerticies[vertexInArray - polygons[polygonInArray] + i];
			if (i == 0 || i % 2 == 0)
				printf("tmpVertArr[%d],x : %f", i, tmpVertArr[i]);
			else
				printf("tmpVertArr[%d],y : %f \n", i, tmpVertArr[i]);
		}

		glColor3f(fill_red, fill_green, fill_blue);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, tmpVertArr);
		glDrawArrays(GL_POLYGON, 0, polygons[polygonInArray] / 2);
		glDisableClientState(GL_VERTEX_ARRAY);

		//debug
		printf("first : %d, count : %d\n", vertexInArray - polygons[polygonInArray], polygons[polygonInArray] / 2);

		printf("\nVertex in array : %d \n", vertexInArray);
		printf("\nPolygons in array : %d\n", polygonInArray + 1);


		printf("all verticies : \n");
		for (int i = 0; i < vertexInArray; i++)
		{
			printf("x: %f, y: %f \n", polygonVerticies[i++], polygonVerticies[i]);
		}
		
		printf("verticies per poly : \n");
		for (int i = 0; i < polygonInArray + 1; i++)
		{
			printf("polygon : %d ,num of verticies : %d \n", i + 1, polygons[i]);
		}
		printf("\n\n\n");
		
		//reset 
		mouserightpressed = false;
		firstpt = false;
		polygonInArray++;

	}

	glFlush();
	//glutSwapBuffers();
}


void LeftClipping()
{

	int i = 0, j = 0;

	for (i = 0; i < N; i++) 
	{	
		//first case -> outside to inside -> 1 vertex & 1 edge
		if (polygonVerticies[i] < xmin && polygonVerticies[i + 2] >= xmin)
		{
			//x2 - x1 != 0
			if (polygonVerticies[i + 2] != polygonVerticies[i])
			{
				//s(slope) -> (y2-y1) / (x2-x1)
				//line through (x1,y1) and (x2,y2) (equation of line) -> ymin – y1 = m(xmin – x1)
				//(y2-y1) / (x2-x1) * (xmin-x1) + y1
				clippedPolygon[j + 1] = ((polygonVerticies[i + 3] - polygonVerticies[i + 1])) / (polygonVerticies[i + 2] - polygonVerticies[i]) * (xmin - polygonVerticies[i]) + polygonVerticies[i + 1];
			}
			else	//the line is completely straight, s = 0 -> y fixed
			{
				clippedPolygon[j + 1] = polygonVerticies[i + 1];
			}

			clippedPolygon[j] = xmin;
			j++;

			//the inside points
			clippedPolygon[j + 2] = polygonVerticies[i + 2];
			clippedPolygon[j + 3] = polygonVerticies[i + 3];
			j++;

		}

		//second case -> inside to inside
		if (polygonVerticies[i] >= xmin && polygonVerticies[i + 2] >= xmin) 
		{
			clippedPolygon[j] = polygonVerticies[i + 2];		//x2
			clippedPolygon[j + 1] = polygonVerticies[i + 3];	//y2
			j++;
		}
		
		//third case -> inside to outside -> 1 vertex
		if (polygonVerticies[i] >= xmin && polygonVerticies[i + 2] < xmin) 
		{
			//x2 - x1 != 0
			if (polygonVerticies[i + 2] != polygonVerticies[i])
			{
				clippedPolygon[j + 1] = ((polygonVerticies[i + 3] - polygonVerticies[i + 1])) / (polygonVerticies[i + 2] - polygonVerticies[i]) * (xmin - polygonVerticies[i]) + polygonVerticies[i + 1];
			}
			else	//the line is completely straight, s = 0 -> y fixed
			{
				clippedPolygon[j + 1] = polygonVerticies[i + 1];
			}

			clippedPolygon[j] = xmin;
			j++;
		}

		//for (i = 0; i < j; i++) 
		//{
		//	polygonVerticies[i] = clippedPolygon[i];
		//	polygonVerticies[j + 1] = clippedPolygon[i + 1];		
		//}

		//initialization -> because we are going to draw the previous polygon
		//polygonVerticies[i] = clippedPolygon[0];
		//polygonVerticies[j + 1] = clippedPolygon[1];
		//N = j;	
	}

}


void RightClipping()
{

	int i = 0, j = 0;

	for (i = 0; i < N; i++)
	{
		//first case -> outside to inside -> 1 vertex & 1 edge
		if (polygonVerticies[i] > xmax && polygonVerticies[i + 2] <= xmax)
		{
			//x2 - x1 != 0
			if (polygonVerticies[i + 2] != polygonVerticies[i])
			{
				//s(slope) -> (y2-y1) / (x2-x1)
				//line through (x1,y1) and (x2,y2) (equation of line) -> ymin – y1 = m(xmin – x1)
				//(y2-y1) / (x2-x1) * (xmax-x1) + y1
				clippedPolygon[j + 1] = ((polygonVerticies[i + 3] - polygonVerticies[i + 1])) / (polygonVerticies[i + 2] - polygonVerticies[i]) * (xmax - polygonVerticies[i]) + polygonVerticies[i + 1];
			}
			else	//the line is completely straight, s = 0 -> y fixed
			{
				clippedPolygon[j + 1] = polygonVerticies[i + 1];
			}

			clippedPolygon[j] = xmax;
			j++;

			//the inside points
			clippedPolygon[j + 2] = polygonVerticies[i + 2];
			clippedPolygon[j + 3] = polygonVerticies[i + 3];
			j++;

		}

		//second case -> inside to inside
		if (polygonVerticies[i] <= xmax && polygonVerticies[i + 2] <= xmax)
		{
			clippedPolygon[j] = polygonVerticies[i + 2];		//x2
			clippedPolygon[j + 1] = polygonVerticies[i + 3];	//y2
			j++;
		}

		//third case -> inside to outside -> 1 vertex
		if (polygonVerticies[i] <= xmax && polygonVerticies[i + 2] > xmax)
		{
			//x2 - x1 != 0
			if (polygonVerticies[i + 2] != polygonVerticies[i])
			{
				clippedPolygon[j + 1] = ((polygonVerticies[i + 3] - polygonVerticies[i + 1])) / (polygonVerticies[i + 2] - polygonVerticies[i]) * (xmax - polygonVerticies[i]) + polygonVerticies[i + 1];
			}
			else	//the line is completely straight, s = 0 -> y fixed
			{
				clippedPolygon[j + 1] = polygonVerticies[i + 1];
			}

			clippedPolygon[j] = xmax;
			j++;
		}

		//for (i = 0; i < j; i++) 
		//{
		//	polygonVerticies[i] = clippedPolygon[i];
		//	polygonVerticies[j + 1] = clippedPolygon[i + 1];		
		//}

		//initialization -> because we are going to draw the previous polygon
		//polygonVerticies[i] = clippedPolygon[0];
		//polygonVerticies[j + 1] = clippedPolygon[1];
		//N = j;	
	}

}


void TopClipping()
{

	int i = 0, j = 0;

	for (i = 0; i < N; i++)
	{
		//first case -> outside to inside -> 1 vertex & 1 edge
		if (polygonVerticies[i + 1] > ymax && polygonVerticies[i + 3] <= ymax)
		{
			//x2 - x1 != 0
			if (polygonVerticies[i + 3] != polygonVerticies[i + 1])
			{
				//ws pros x twra
				//(x2-x1) / (y2-y1) * (ymax-y1) + x1
				clippedPolygon[j] = ((polygonVerticies[i + 2] - polygonVerticies[i])) / (polygonVerticies[i + 3] - polygonVerticies[i + 1]) * (ymax - polygonVerticies[i + 1]) + polygonVerticies[i];
			}
			else	//the line is completely straight, s = 0 -> y fixed
			{
				clippedPolygon[j] = polygonVerticies[i];
			}

			clippedPolygon[j] = ymax;
			j++;

			//the inside points
			clippedPolygon[j] = polygonVerticies[i + 2];
			clippedPolygon[j + 1] = polygonVerticies[i + 3];
			j++;

		}

		//second case -> inside to inside
		if (polygonVerticies[i + 1] <= ymax && polygonVerticies[i + 3] <= ymax)
		{
			clippedPolygon[j] = polygonVerticies[i + 2];		
			clippedPolygon[j + 1] = polygonVerticies[i + 3];	
			j++;
		}

		//third case -> inside to outside -> 1 vertex
		if (polygonVerticies[i + 1] <= ymax && polygonVerticies[i + 3] > ymax)
		{
			//x2 - x1 != 0
			if (polygonVerticies[i + 3] != polygonVerticies[i + 1])
			{
				clippedPolygon[j] = ((polygonVerticies[i + 2] - polygonVerticies[i])) / (polygonVerticies[i + 3] - polygonVerticies[i + 1]) * (ymax - polygonVerticies[i + 1]) + polygonVerticies[i];
			}
			else	//the line is completely straight, s = 0 -> y fixed
			{
				clippedPolygon[j] = polygonVerticies[i];
			}

			clippedPolygon[j] = ymax;
			j++;
		}

		//for (i = 0; i < j; i++) 
		//{
		//	polygonVerticies[i] = clippedPolygon[i];
		//	polygonVerticies[j + 1] = clippedPolygon[i + 1];		
		//}

		//initialization -> because we are going to draw the previous polygon
		//polygonVerticies[i] = clippedPolygon[0];
		//polygonVerticies[j + 1] = clippedPolygon[1];
		//N = j;	
	}

}


void BottomClipping()
{

	int i = 0, j = 0;

	for (i = 0; i < N; i++)
	{
		//first case -> outside to inside -> 1 vertex & 1 edge
		if (polygonVerticies[i + 1] > ymin && polygonVerticies[i + 3] >= ymin)
		{
			//x2 - x1 != 0
			if (polygonVerticies[i + 3] != polygonVerticies[i + 1])
			{
				//ws pros x twra
				//(x2-x1) / (y2-y1) * (ymin-y1) + x1
				clippedPolygon[j] = ((polygonVerticies[i + 2] - polygonVerticies[i])) / (polygonVerticies[i + 3] - polygonVerticies[i + 1]) * (ymin - polygonVerticies[i + 1]) + polygonVerticies[i];
			}
			else	//the line is completely straight, s = 0 -> y fixed
			{
				clippedPolygon[j] = polygonVerticies[i];
			}

			clippedPolygon[j] = ymin;
			j++;

			//the inside points
			clippedPolygon[j] = polygonVerticies[i + 2];
			clippedPolygon[j + 1] = polygonVerticies[i + 3];
			j++;

		}

		//second case -> inside to inside
		if (polygonVerticies[i + 1] >= ymin && polygonVerticies[i + 3] >= ymin)
		{
			clippedPolygon[j] = polygonVerticies[i + 2];
			clippedPolygon[j + 1] = polygonVerticies[i + 3];
			j++;
		}

		//third case -> inside to outside -> 1 vertex
		if (polygonVerticies[i + 1] >= ymin && polygonVerticies[i + 3] < ymin)
		{
			//x2 - x1 != 0
			if (polygonVerticies[i + 3] != polygonVerticies[i + 1])
			{
				clippedPolygon[j] = ((polygonVerticies[i + 2] - polygonVerticies[i])) / (polygonVerticies[i + 3] - polygonVerticies[i + 1]) * (ymin - polygonVerticies[i + 1]) + polygonVerticies[i];
			}
			else	//the line is completely straight, s = 0 -> y fixed
			{
				clippedPolygon[j] = polygonVerticies[i];
			}

			clippedPolygon[j] = ymin;
			j++;
		}

		//for (i = 0; i < j; i++) 
		//{
		//	polygonVerticies[i] = clippedPolygon[i];
		//	polygonVerticies[j + 1] = clippedPolygon[i + 1];		
		//}

		//initialization -> because we are going to draw the previous polygon
		//polygonVerticies[i] = clippedPolygon[0];
		//polygonVerticies[j + 1] = clippedPolygon[1];
		//N = j;	
	}

}


void PolygonClipping() {

	//printf("Enter the coordinates of bottom left corner (min) of the clipping window: (x, y) \n");
	//scanf("%f %f", &xmin, &ymin);
	//printf("Enter the coordinates of top right corner (max) of the clipping window: (x, y) \n");
	//scanf("%f %f", &xmax, &ymax);

	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmax, ymin);
	glVertex2f(xmax, ymax);
	glVertex2f(xmin, ymax);
	glEnd();

	LeftClipping();
	RightClipping();
	TopClipping();
	BottomClipping();

	glFlush();

}


void LineColorSubMenu(int choice) 
{

	switch (choice) {
	case BLACK:
		line_red = 0.0;
		line_green = 0.0;
		line_blue = 0.0;
		break;
	case WHITE:
		line_red = 1.0;
		line_green = 1.0;
		line_blue = 1.0;
		break;
	case RED:
		line_red = 1.0;
		line_green = 0.0;
		line_blue = 0.0;
		break;
	case BLUE:
		line_red = 0.0;
		line_green = 0.0;
		line_blue = 1.0;
		break;
	case GREEN:
		line_red = 0.0;
		line_green = 0.5;
		line_blue = 0.0;
		break;
	case ORANGE:
		line_red = 1.0;
		line_green = 0.6;
		line_blue = 0.0;
		break;
	case PURPLE:
		line_red = 0.5;
		line_green = 0.0;
		line_blue = 0.5;
		break;
	case PINK:
		line_red = 0.9;
		line_green = 0.1;
		line_blue = 0.5;
		break;
	}

	glutPostRedisplay();

}


void FillColorSubMenu(int choice) 
{

	switch (choice) {
	case BLACK:
		fill_red = 0.0;
		fill_green = 0.0;
		fill_blue = 0.0;
		break;
	case WHITE:
		fill_red = 1.0;
		fill_green = 1.0;
		fill_blue = 1.0;
		break;
	case RED:
		fill_red = 1.0;
		fill_green = 0.0;
		fill_blue = 0.0;
		break;
	case BLUE:
		fill_red = 0.0;
		fill_green = 0.0;
		fill_blue = 1.0;
		break;
	case GREEN:
		fill_red = 0.0;
		fill_green = 0.5;
		fill_blue = 0.0;
		break;
	case ORANGE:
		fill_red = 1.0;
		fill_green = 0.6;
		fill_blue = 0.0;
		break;
	case PURPLE:
		fill_red = 0.5;
		fill_green = 0.0;
		fill_blue = 0.5;
		break;
	case PINK:
		fill_red = 0.9;
		fill_green = 0.1;
		fill_blue = 0.5;
		break;
	}

	glutPostRedisplay();

}


void MainMenuSelect(int choice) 
{

	switch (choice) {
	case POLYGON:
		polygonEnabled = true;
		Polygon();
		break;
	case CLIPPING:
		PolygonClipping();
		//LeftClipping();
		break;
		//case EXTRUDE:
		//	Polygon();
		//  polygonEnabled = true;
		//	break;
	case CLEAR:
		clearScreen = true;
		break;
	case EXIT:
		exit(0);
		break;
	}

	glutPostRedisplay();

}


void Render()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Polygon();
}


void Resize(int w, int h)
{
	//define the visible area of the window ( in pixels )
	if (h == 0) h = 1;		//To prevent divide by 0
	glViewport(0, 0, w, h);

	// Save the window size
	winw = w;
	winh = h;

	//Set up the projection & reset matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0.0, 1.0, 0.0, 1.0);

	//glMatrixMode(GL_MODELVIEW);  // Always go back to model /view mode
}


void Idle()
{

}


void Setup()  // DON'T TOUCH IT 
{
	// White background
	glClearColor(1.0, 1.0, 1.0, 0.0);
}


//-------------------- Main Program------------------------------

int main(int argc, char* argv[]) 
{

	// initialize GLUT library state
	glutInit(&argc, argv);

	// Set up the display using the GLUT functions to 
    // get rid of the window setup details:
    // - Use true RGB colour mode ( and transparency )
    // - Enable double buffering for faster window update
    // - Allocate a Depth-Buffer in the system memory or 
    //   in the video memory if 3D acceleration available
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

	// Define the main window size and initial position 
	// ( upper left corner, boundaries included )
	glutInitWindowSize(600, 500);
	glutInitWindowPosition(650, 300);

	// Create and label the main window
	glutCreateWindow("Grafika Upologistwn - Ergasia 1");

	// Configure various properties of the OpenGL rendering context
	Setup();

	// The rendering function 
	glutDisplayFunc(Render);
	glutReshapeFunc(Resize);

	//glutIdleFunc(Idle);

	//manage mouse
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	//glutMotionFunc(Motion);


	//create lineColor Sub menu
	int lineColorSubMenu = glutCreateMenu(LineColorSubMenu);
	glutAddMenuEntry("Black", BLACK);
	glutAddMenuEntry("White", WHITE);
	glutAddMenuEntry("Red", RED);
	glutAddMenuEntry("Blue", BLUE);
	glutAddMenuEntry("Green", GREEN);
	glutAddMenuEntry("Orange", ORANGE);
	glutAddMenuEntry("Purple", PURPLE);
	glutAddMenuEntry("Pink", PINK);

	//create fillColor Sub menu
	int fillColorSubMenu = glutCreateMenu(FillColorSubMenu);
	glutAddMenuEntry("Black", BLACK);
	glutAddMenuEntry("White", WHITE);
	glutAddMenuEntry("Red", RED);
	glutAddMenuEntry("Blue", BLUE);
	glutAddMenuEntry("Green", GREEN);
	glutAddMenuEntry("Orange", ORANGE);
	glutAddMenuEntry("Purple", PURPLE);
	glutAddMenuEntry("Pink", PINK);


	//create main menu
	glutCreateMenu(MainMenuSelect);
	glutAddSubMenu("LineColor", lineColorSubMenu);
	glutAddSubMenu("FillColor", fillColorSubMenu);
	glutAddMenuEntry("Polygon", POLYGON);
	glutAddMenuEntry("Clipping", CLIPPING);
	glutAddMenuEntry("Extrude", EXTRUDE);
	glutAddMenuEntry("Clear", CLEAR);
	glutAddMenuEntry("Exit", EXIT);

	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	clearWindow();
	//Enter main event handling loop
	glutMainLoop();
	return 0;

}
