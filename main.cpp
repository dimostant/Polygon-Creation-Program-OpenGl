#include <stdio.h>     // - Just for some ASCII messages
#include <stdlib.h>
#include <iostream>
#include <string>
using std::string;
#include "gl/glut.h"   // - An interface and windows 

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


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

//polygon
const int ESCKEY = 27;
const int N = 1000;//0;
const int M = 1000;//0;

bool firstpt = false;
bool polygonEnabled = false;
bool clearScreen = false;

const double pointsize = 1;// og 10


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

double pt1x;
double pt1y;
double pt2x;
double pt2y;

// Mouse
bool mouseleftpressed = false;   // True if mouse LEFT button is down.
bool mouserightpressed = false;
// Saved by mouse.
int mousex, mousey;           // Mouse x,y coords, in GLUT format (pixels from upper-left corner).
							  // Only guaranteed to be valid if a mouse button is down.
							  // Saved by mouse, motion
GLfloat polygonVerticies[N];
int vertexInArray = 0; // every 2n is x cord , every 2n + 1 is y cord
int polygons[M]; // every polygon number of vetrexes is stored in every different M
int polygonInArray = 0;
GLfloat polygonsColors[M*3];
int colorInArray = 0;

GLuint width = 600;
GLuint height = 500;

bool lI = false;//(lineIntersection(pt1x, pt1y, pt2x, pt2y))



int getCreatedPolyTotalVerts() {
	int vertexPos = 0;
	for (int i = 0; i < polygonInArray; i++) {
		vertexPos += polygons[i];
	}
	return vertexPos;
}

void debugger() {

	printf("polygonVerticies[ ");
	for (int i = 0; i < N; i++)
	{
		printf(" %f, ", polygonVerticies[i]);
	}
	printf("] \n ");

	printf("polygons[");
	for (int i = 0; i < M; i++)
	{

		//if(polygons[i] != )
		printf(" %d, ", polygons[i]);
	}
	printf("] \n ");
	printf("vertexInArray : %d \n", vertexInArray);
	printf("polygonInArray : %d \n\n\n", polygonInArray);
}


void PolygonRendering()
{
	//std::cout << "in poly render\n\n";
	//std::cout << "vertexinArray : " << vertexInArray << "polygonInArray : " << polygonInArray << "\n";
	//printf("\n\nbainw\n\n");


	polygons[polygonInArray] = vertexInArray - getCreatedPolyTotalVerts();

	GLfloat* tmpVertArr = (GLfloat*)malloc(sizeof(GLfloat) * polygons[polygonInArray]);

	for (int i = 0; i < polygons[polygonInArray]; i++)
	{
		tmpVertArr[i] = polygonVerticies[vertexInArray - polygons[polygonInArray] + i];
		//debug
		/*if (i == 0 || i % 2 == 0)
			printf("tmpVertArr[%d],x : %f", i, tmpVertArr[i]);
		else
			printf("tmpVertArr[%d],y : %f \n", i, tmpVertArr[i]);*/
	}
	glColor3f(polygonsColors[colorInArray-3], polygonsColors[colorInArray -2], polygonsColors[colorInArray -1]);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, tmpVertArr);
	glDrawArrays(GL_POLYGON, 0, polygons[polygonInArray] / 2);
	glDisableClientState(GL_VERTEX_ARRAY);


	//debug
	/*printf("first : %d, count : %d\n", vertexInArray - polygons[polygonInArray], polygons[polygonInArray] / 2);
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
	printf("\n\nteleiwsa\n\n");
	printf("\n\n\n");

	std::cout << "vertexinArray : " << vertexInArray << "polygonInArray : " << polygonInArray << "\n";*/
}

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
	printbitmap("PROTOMALAKA"/*"Simple Mouse Demo"*/, 0.1, 0.9);
	printbitmap("gamiesai"/*"Press left mouse button and move mouse"*/, 0.05, 0.55);
	printbitmap(""/*"Esc   Quit"*/, 0.15, 0.25);
	
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


void rerender() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	int loops = polygonInArray ;
	vertexInArray = 0;
	colorInArray = 0;
	for (polygonInArray = 0; polygonInArray < loops; polygonInArray++)
	{
		vertexInArray += polygons[polygonInArray];
		colorInArray += 3;
		glColor3f(polygonsColors[colorInArray - 3 ], polygonsColors[colorInArray - 2], polygonsColors[colorInArray - 1]);
		PolygonRendering();	
	}
}

// The GLUT Keyboard function
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'R': rerender();
		break;
	case 'C': clearScreen = true;
		break;
	case ESCKEY:
	case 'X': exit(0);
		break;

	}
	glutPostRedisplay();
}


// The GLUT mouse function
void Mouse(int button, int state, int x, int y) 
{

	//// Save the left button state
	if (button == GLUT_LEFT_BUTTON) 
	{
		mouseleftpressed = (state == GLUT_DOWN);
		glutPostRedisplay();  // Left button has changed; redisplay
	}
	else
	{
		mouserightpressed = (state == GLUT_UP);
		glutPostRedisplay();
	}

	////Save the mouse position
	mousex = x;
	mousey = y;

}

bool onSegment(GLfloat px, GLfloat py, GLfloat qx , GLfloat qy, GLfloat rx, GLfloat ry )
{
	if (qx <= MAX(px, rx) && qx >= MIN(px, rx) &&
		qy <= MAX(py, ry) && qy >= MIN(py, ry))
		return true;

	return false;
}

int orientation(GLfloat px, GLfloat py, GLfloat qx, GLfloat qy, GLfloat rx, GLfloat ry)
{
	// See https://www.geeksforgeeks.org/orientation-3-ordered-points/
	// for details of below formula.
	int val = (qy - py) * (rx - qx) -
		(qx - px) * (ry - qy);

	if (val == 0) return 0;  // collinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool lineIntersection(GLfloat p1x, GLfloat p1y, GLfloat q1x, GLfloat q1y, GLfloat p2x, GLfloat p2y, GLfloat q2x, GLfloat q2y)
{
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1x, p1y, q1x, q1y, p2x, p2y);
	int o2 = orientation(p1x, p1y, q1x, q1y, q2x, q2y);
	int o3 = orientation(p2x, p2y, q2x, q2y, p1x, p1y);
	int o4 = orientation(p2x, p2y, q2x, q2y, q1x, q1y);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1x, p1y, p2x, p2y, q1x, q1y)) return true;

	// p1, q1 and q2 are collinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1x, p1y, q2x, q2y, q1x, q1y)) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2x, p2y, p1x, p1y, q2x, q2y)) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2x, p2y, q1x, q1y, q2x, q2y)) return true;

	return false; // Doesn't fall in any of the above cases
}


void Polygon() 
{
	int initialVertexPos = vertexInArray;

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
			//printf("first point : %f, %f \n", pt1x, pt1y);
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

			//printf("next point : %f, %f ,\n vertexInArray : %d, polygonInArray : %d \n", pt2x, pt2y, vertexInArray, polygonInArray);
			
			//printf("%d \n", vertexInArray);
	
			if (vertexInArray == 6)
			{	
				lI = polygonVerticies[vertexInArray - 6] == polygonVerticies[vertexInArray - 2] && polygonVerticies[vertexInArray - 5] == polygonVerticies[vertexInArray - 1];
				std::cout << lI << "\n";
			}
			else
			{
				int i = 0;
				printf("polygonVerticies[ ");
				for (int i = 0; i < N; i++)
				{
					printf(" %f, ", polygonVerticies[i]);
				}
				printf("] \n ");
				while (getCreatedPolyTotalVerts() <= vertexInArray - 8 - i * 2) {
					lI = lineIntersection(
	 /*changing line :*/polygonVerticies[vertexInArray - 8 - i*2 * 100], polygonVerticies[vertexInArray - 7 - i*2] * 100, polygonVerticies[vertexInArray - 6 - i*2] * 100, polygonVerticies[vertexInArray - 5 - i*2] * 100,
	 /* current line :*/polygonVerticies[vertexInArray - 4] * 100, polygonVerticies[vertexInArray - 3] * 100, polygonVerticies[vertexInArray - 2] * 100, polygonVerticies[vertexInArray - 1] * 100
					);

					printf("line 1: x1 : %f, y1 : %f, x2 : %f, y2 : %f \nline 2: x3 : %f, y3 : %f, x4 : %f, y4 : %f\n\n",  
						polygonVerticies[vertexInArray - 8 - i * 1], polygonVerticies[vertexInArray - 7 - i * 1], polygonVerticies[vertexInArray - 6 - i * 1], polygonVerticies[vertexInArray - 5 - i * 1],
						polygonVerticies[vertexInArray - 4], polygonVerticies[vertexInArray - 3], polygonVerticies[vertexInArray - 2], polygonVerticies[vertexInArray - 1]
					);

					std::cout << lI << "\n";
					if (lI == true)
						break;
					i++;
				}
			}

			if (lI == true)
			{
				rerender();
				firstpt = true;
				lI = false;				
			}
		}

		mouseleftpressed = false;
	}

	if (mouserightpressed && lI == false)
	{

		polygonsColors[colorInArray++] = fill_red;
		polygonsColors[colorInArray++] = fill_green;
		polygonsColors[colorInArray++] = fill_blue;

		PolygonRendering();

		//reset 
		mouserightpressed = false;
		firstpt = false;
		polygonInArray++;
		//delete design lines
		rerender();
	}


	glFlush();
	//glutSwapBuffers();
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
		//case CLIPPING:
		//	Polygon();
		//  polygonEnabled = true;
		//	break;
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

	/*if (lineIntersection(x1, y1, x2, y2, x3, y3, x4, y4) == 0) {
		printf("lines do not intersect");
	}
	else
	{
		printf("lines do intersect");
	}*/
	Polygon();
	//glClear(GL_COLOR_BUFFER_BIT);						   // my old project
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
														   // and the depth buffer

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//glFlush();
	//glutSwapBuffers();             // All drawing commands applied to the 
									 // hidden buffer, so now, bring forward
									 // the hidden buffer and hide the visible one           

}


void Resize(int w, int h)
{
	// Set the viewport to be the entire drawing area of the window
	glViewport(0, 0, w, h);

	// Save the window size
	winw = w;
	winh = h;

	// Set up the projection
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
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
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
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
