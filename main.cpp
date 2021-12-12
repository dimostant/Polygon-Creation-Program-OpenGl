////OpenGL Empty Project
//
//#include <stdio.h>     // - Just for some ASCII messages
//#include <stdlib.h>
//#include <iostream>
//#include <string>
//using std::string;// - Just for some ASCII messages
//#include "gl/glut.h"   // - An interface and windows 
//
//#define POLYGON 1
//#define BLACK 2
//#define RED 3
//#define BLUE 4
//#define CLEAR 5
//#define EXIT 6
//
//const int ESCKEY = 27;
//const double pointsize = 1;// og 10
//const int N = 1000;
//
//bool clearScreen = false;
//bool polygonEnabled = false;
//bool mouseleftpressed = false;
//bool mouserightpressed = false;
//bool firstpt = false;
//
//int winw, winh;
//int mousex, mousey;
//int arraySlot = 0;
//
//float red = 0;// og 0
//float green = 0;
//float blue = 0;
//
//double pt1x;
//double pt1y;
//double pt2x;
//double pt2y;
//double pointsTaken[N];
//
//
//
//void Keyboard(unsigned char key, int x, int y)
//{
//    switch (key)
//    {
//    case 'C': /*std::cout << "mou gamietai"*/clearScreen = true;
//        break;
//    case ESCKEY:
//    case 'X': exit(0);
//        break;
//        
//    }
//    glutPostRedisplay();
//}
//
//// mouse
//// The GLUT mouse function
//void Mouse(int button, int state, int x, int y)
//{
//    // Save the left button state
//    if (button == GLUT_LEFT_BUTTON)
//    {
//        //std::cout<<"test"<<state<<std::endl;
//        mouseleftpressed = (state == GLUT_UP);
//        //if (mouseleftpressed)
//        glutPostRedisplay();  // Left button has changed; redisplay!
//    }
//
//    mousex = x;
//    mousey = y;
//
//    if (button == GLUT_RIGHT_BUTTON)
//    {
//        //std::cout<<"test"<<state<<std::endl;
//        mouserightpressed = (state == GLUT_UP);
//        glutPostRedisplay();  // Left button has changed; redisplay!
//    }
//
//    // Save the mouse position
//}
//
//void MenuSelect(int choice)
//{
//    switch (choice) {
//    case POLYGON:
//        polygonEnabled = true;
//        break;
//    case BLACK:
//        red = 0.0;
//        green = 0.0;
//        blue = 0.0;
//        polygonEnabled = false;
//        break;
//    case RED:
//        red = 1.0;
//        green = 0.0;
//        blue = 0.0;
//        polygonEnabled = false;
//        break;
//    case BLUE:
//        red = 0.0;
//        green = 0.0;
//        blue = 1.0;
//        polygonEnabled = false;
//        break;
//    case CLEAR:
//        clearScreen = true;
//        break;
//    case EXIT:
//        exit(0);
//        break;
//    }
//    glutPostRedisplay();
//}
//
//void printbitmap(const string msg, double x, double y)
//{
//    glRasterPos2d(x, y);
//    for (string::const_iterator ii = msg.begin();
//        ii != msg.end();
//        ++ii)
//    {
//        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *ii);
//    }
//}
//
//void clearWindow()
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // Documentation
//    glColor3d(0.0, 0.0, 0.0);  // Black text
//    printbitmap("Mou vghke"/*"Simple Mouse Demo"*/, 0.1, 0.9);
//    printbitmap("O kwlos"/*"Press left mouse button and move mouse"*/, 0.05, 0.55);
//    printbitmap("Sto debugging"/*"Esc   Quit"*/, 0.15, 0.25);
//}
//
//
//void project() {
//    if (clearScreen)
//    {
//        clearWindow();
//        firstpt = false;
//        clearScreen = false;
//    }
//
//    if (mouseleftpressed && polygonEnabled)
//    { 
// 
//        // Convert mouse position to OpenGL's coordinate system
//        double oglx = double(mousex) / winw;
//        double ogly = 1 - double(mousey) / winh;
//        glColor3f(red, green, blue);
//        glPointSize(pointsize);
//       // glBegin(GL_POLYGON);
//        
//        
//        
//        if (!firstpt)
//        {
//            glBegin(GL_POINTS);
//            glVertex2d(oglx, ogly);
//            glEnd();
//            pt1x = oglx;
//            pt1y = ogly;
//            pointsTaken[arraySlot++] = pt1x;
//            pointsTaken[arraySlot++] = pt1y;
//            firstpt = true;
//        }
//        else
//        {
//            pt2x = oglx;
//            pt2y = ogly;
//            //glRectd(pt1x, pt1y, pt2x, pt2y);
//            glBegin(GL_POINTS);
//            glVertex2d(pt2x, pt2y);
//            glEnd();
//            glBegin(GL_LINE_STRIP);
//            glVertex2d(pt1x, pt1y);
//            glVertex2d(pt2x, pt2y);
//            glEnd();
//            pointsTaken[arraySlot++] = pt2x;
//            pointsTaken[arraySlot++] = pt2y;
//            //move last point to first
//            pt1x = pt2x;
//            pt1y = pt2y;
//        }
//        mouseleftpressed = false;
//    }
//
//    if (mouserightpressed) {
//        glBegin(GL_LINE_STRIP);
//        glVertex2d(pt1x, pt1y);
//        glVertex2d(pointsTaken[0], pointsTaken[1]);
//        glEnd();
//        /*glBegin(GL_POLYGON);
//        for (int i = 0; i == arraySlot / 2; i+=2) {
//            glVertex2d(pointsTaken[i], pointsTaken[i + 1]);
//        }
//        glEnd();*/
//        //glEnd();
//        // activate and specify pointer to vertex array
//        //glenableclientstate(gl_vertex_array);
//        //glvertexpointer(3, gl_float, 0, vertices);
//
//        //// draw a cube
//        //gldrawelements(gl_triangles, 36, gl_unsigned_byte, indices);
//
//        //// deactivate vertex arrays after drawing
//        //gldisableclientstate(gl_vertex_array);
//        arraySlot = 0;
//        mouserightpressed = false;
//        firstpt = false;
//    }
//    glFlush();
//    //glutSwapBuffers();
//}
//
//void Render()
//{
//    /*int arr[] = { 1,1,2,2,10,1,10,10 };
//    arraySlot = 8;
//    glBegin(GL_POLYGON);
//    for (int i = 0; i == arraySlot / 2; i += 2) {
//        glVertex2d(arr[i], arr[i + 1]);
//    }
//    glEnd();*/
//    project();
//	//glClear(GL_COLOR_BUFFER_BIT);  // Clean up the colour of the window
//	//								// and the depth buffer
//	//glMatrixMode(GL_MODELVIEW);
//	//glLoadIdentity();
//
//	//glFlush();
////	glutSwapBuffers();             // All drawing commands applied to the 
//								   // hidden buffer, so now, bring forward
//								 // the hidden buffer and hide the visible one           
//
//}
//
////-----------------------------------------------------------
//
//
//void Resize(int w, int h)
//{
//    // Save the window size
//    winw = w;
//    winh = h;
//
//    // Set up the projection
//    glMatrixMode(GL_PROJECTION);
//    //glLoadIdentity();
//    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
//
//    //glMatrixMode(GL_MODELVIEW);  // Always go back to model/view mode
//
//    //-------------------- OLD --------------------------------------
//	
//    //// define the visible area of the window ( in pixels )
//	//if (h == 0) h = 1;
//	//glViewport(0, 0, w, h);
//
//	//// Setup viewing volume
//
//	//glMatrixMode(GL_PROJECTION);
//	//glLoadIdentity();
//
//	////         L	   R 	  B 	T	 N	   F
//	//glOrtho(-10.0, 10.0, -10.0, 10.0, 10.0, -10.0);
//
//}
//
//void Idle()
//{
//
//}
//
////-----------------------------------------------------------
//
//void Setup()  // DON'T TOUCH IT 
//{
//	// White background
//	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
//
//}
//
//
///////////////// Main Program ///////////////////////////
//
//int main(int argc, char* argv[])
//{ 
//  // initialize GLUT library state
//  glutInit(&argc, argv);
//	
//  // Set up the display using the GLUT functions to 
//  // get rid of the window setup details:
//  // - Use true RGB colour mode ( and transparency )
//  // - Enable double buffering for faster window update
//  // - Allocate a Depth-Buffer in the system memory or 
//  //   in the video memory if 3D acceleration available	
//  glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
// 
//  
//  // Define the main window size and initial position 
//  // ( upper left corner, boundaries included )
//  glutInitWindowSize(600, 500);
//  glutInitWindowPosition(650, 300);
//
//  // Create and label the main window
//  glutCreateWindow("Ntaks Kserw Gw ergasia kserw gw na oume");
//  
//  // Configure various properties of the OpenGL rendering context
//  Setup();
//  
//  // Callbacks for the GL and GLUT events:
//
//  // The rendering function 
//  glutDisplayFunc(Render);
//  glutReshapeFunc(Resize);
//  
//  //glutIdleFunc(Idle);
//
//  //manage keyboard mouse
//  glutKeyboardFunc(Keyboard);
//  glutMouseFunc(Mouse);
//  //glutMotionFunc(Motion);
//
//  //create main menu
//  glutCreateMenu(MenuSelect);
//  glutAddMenuEntry("Polygon", POLYGON);
//  glutAddMenuEntry("Black", BLACK);
//  glutAddMenuEntry("Red", RED);
//  glutAddMenuEntry("Blue", BLUE);
//  glutAddMenuEntry("Clear", CLEAR);
//  glutAddMenuEntry("Exit", EXIT);
//
//  //// attach the menu to the right button
//
//  glutAttachMenu(GLUT_RIGHT_BUTTON);
//
//  clearWindow();
//  //Enter main event handling loop
//  glutMainLoop();
//  return 0;
//
//}  


#include <stdio.h>     // - Just for some ASCII messages
#include <stdlib.h>
#include <iostream>
#include <string>
using std::string; 
#include "gl/glut.h"   // - An interface and windows 


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
const int N = 1000;

double pointsTaken[N];

int arraySlot = 0;

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

float red = 0;// og 0
float green = 0;
float blue = 0;

// Mouse
bool mouseleftpressed = false;   // True if mouse LEFT button is down.
bool mouserightpressed = false;
// Saved by mouse.
int mousex, mousey;           // Mouse x,y coords, in GLUT format (pixels from upper-left corner).
							  // Only guaranteed to be valid if a mouse button is down.
							  // Saved by mouse, motion.

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
}

void Polygon() {

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
		glColor3f(red, green, blue);
		glPointSize(pointsize);
		// glBegin(GL_POLYGON);
		        
		        
		        
		if (!firstpt)
		{
		    glBegin(GL_POINTS);
		    glVertex2d(oglx, ogly);
		    glEnd();
		    pt1x = oglx;
		    pt1y = ogly;
		    pointsTaken[arraySlot++] = pt1x;
		    pointsTaken[arraySlot++] = pt1y;
		    firstpt = true;
		}
		else
		{
		    pt2x = oglx;
		    pt2y = ogly;
		    //glRectd(pt1x, pt1y, pt2x, pt2y);
		    glBegin(GL_POINTS);
		    glVertex2d(pt2x, pt2y);
		    glEnd();
		    glBegin(GL_LINE_STRIP);
		    glVertex2d(pt1x, pt1y);
		    glVertex2d(pt2x, pt2y);
		    glEnd();
		    pointsTaken[arraySlot++] = pt2x;
		    pointsTaken[arraySlot++] = pt2y;
		    //move last point to first
		    pt1x = pt2x;
		    pt1y = pt2y;
		}
		mouseleftpressed = false;
	}
		
	if (mouserightpressed) {
		glBegin(GL_LINE_STRIP);
		glVertex2d(pt1x, pt1y);
		glVertex2d(pointsTaken[0], pointsTaken[1]);
		glEnd();

		/*glBegin(GL_POLYGON);
		for (int i = 0; i == arraySlot / 2; i+=2) {
		    glVertex2d(pointsTaken[i], pointsTaken[i + 1]);
		}
		glEnd();*/
		//glEnd();
		// activate and specify pointer to vertex array
		//glenableclientstate(gl_vertex_array);
		//glvertexpointer(3, gl_float, 0, vertices);
		
		//// draw a cube
		//gldrawelements(gl_triangles, 36, gl_unsigned_byte, indices);
		
		//// deactivate vertex arrays after drawing
		//gldisableclientstate(gl_vertex_array);
		arraySlot = 0;
		mouserightpressed = false;
		firstpt = false;
	}
	glFlush();
	//glutSwapBuffers();
}


void Render()
{

	Polygon();
	//glClear(GL_COLOR_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
														 // and the depth buffer

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();


	//glutSwapBuffers();             // All drawing commands applied to the 
								   // hidden buffer, so now, bring forward
								 // the hidden buffer and hide the visible one           

}

//-----------------------------------------------------------

// The GLUT Keyboard function
void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'C': clearScreen = true;
        break;
    case ESCKEY:
    case 'X': exit(0);
        break;
        
    }
    glutPostRedisplay();
}


// The GLUT mouse function
void Mouse(int button, int state, int x, int y) {

	// Save the left button state
	if (button == GLUT_LEFT_BUTTON) {
		mouseleftpressed = (state == GLUT_UP);
		//if (mouseleftpressed)
		glutPostRedisplay();  // Left button has changed; redisplay
	}

	//Save the mouse position
	mousex = x;
	mousey = y;

	if (button == GLUT_RIGHT_BUTTON) {
		mouserightpressed = (state == GLUT_UP);
		glutPostRedisplay();
	}

}

void MainMenuSelect(int choice) {

	switch (choice) {
	case POLYGON:
		polygonEnabled = true;
		Polygon();
		break;
		//case CLIPPING:
		//	Polygon();
		//	break;
		//case EXTRUDE:
		//	Polygon();
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


void LineColorSubMenu(int choice) {

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


void FillColorSubMenu(int choice) {

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

	//glMatrixMode(GL_MODELVIEW);  // Always go back to model/view mode
}

void Idle()
{

}

//-----------------------------------------------------------

void Setup()  // DON'T TOUCH IT 
{
	// Black background
	glClearColor(1.0, 1.0, 1.0, 0.0);

}


/////////////// Main Program ///////////////////////////

//int main(int argc, char* argv[])
//{ 
//  // initialize GLUT library state
//  glutInit(&argc, argv);
//	
//  // Set up the display using the GLUT functions to 
//  // get rid of the window setup details:
//  // - Use true RGB colour mode ( and transparency )
//  // - Enable double buffering for faster window update
//  // - Allocate a Depth-Buffer in the system memory or 
//  //   in the video memory if 3D acceleration available	
//  glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
// 
//  
//  // Define the main window size and initial position 
//  // ( upper left corner, boundaries included )
//  glutInitWindowSize(600, 500);
//  glutInitWindowPosition(650, 300);
//
//  // Create and label the main window
//  glutCreateWindow("Ntaks Kserw Gw ergasia kserw gw na oume");
//  
//  // Configure various properties of the OpenGL rendering context
//  Setup();
//  
//  // Callbacks for the GL and GLUT events:
//
//  // The rendering function 
//  glutDisplayFunc(Render);
//  glutReshapeFunc(Resize);
//  
//  //glutIdleFunc(Idle);
//
//  //manage keyboard mouse
//  glutKeyboardFunc(Keyboard);
//  glutMouseFunc(Mouse);
//  //glutMotionFunc(Motion);
//
//  //create main menu
//  glutCreateMenu(MenuSelect);
//  glutAddMenuEntry("Polygon", POLYGON);
//  glutAddMenuEntry("Black", BLACK);
//  glutAddMenuEntry("Red", RED);
//  glutAddMenuEntry("Blue", BLUE);
//  glutAddMenuEntry("Clear", CLEAR);
//  glutAddMenuEntry("Exit", EXIT);
//
//  //// attach the menu to the right button
//
//  glutAttachMenu(GLUT_RIGHT_BUTTON);
//
//  clearWindow();
//  //Enter main event handling loop
//  glutMainLoop();
//  return 0;
//
//}  

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

	glutInitWindowSize(600, 500);
	glutInitWindowPosition(650, 300);
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


	//create main menu
	int lineColorSubMenu = glutCreateMenu(LineColorSubMenu);
	glutAddMenuEntry("Black", BLACK);
	glutAddMenuEntry("White", WHITE);
	glutAddMenuEntry("Red", RED);
	glutAddMenuEntry("Blue", BLUE);
	glutAddMenuEntry("Green", GREEN);
	glutAddMenuEntry("Orange", ORANGE);
	glutAddMenuEntry("Purple", PURPLE);
	glutAddMenuEntry("Pink", PINK);

	//create main menu
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
	//Enter main event handling loop
	
	clearWindow();
	
	glutMainLoop();
	return 0;


}
	
