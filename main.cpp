////OpenGL Empty Project

#include <stdio.h>     // - Just for some ASCII messages
#include <fstream>
#include <string>
 using std::string;
#include <iostream>
#include <math.h>
#include "gl/glut.h"   // - An interface and windows 

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#  define GLUT_WHEEL_UP    3
#  define GLUT_WHEEL_DOWN  4
#  define GLUT_WHEEL_LEFT  5
#  define GLUT_WHEEL_RIGHT  6

#  define GLUT_WHEEL_UP    3
#  define GLUT_WHEEL_DOWN  4
#  define GLUT_WHEEL_LEFT  5
#  define GLUT_WHEEL_RIGHT  6

 // angle of rotation for the camera direction
 float angle = 0.0;
 // actual vector representing the camera's direction
 float lx = 0.0f, lz = -1.0f;
 // XZ position of the camera
 float x = 0.0f, y = 1.0f, z = 5.0f;

 double rotate_by_key = 0;
 double rotate_x = 0.5;

 // Mouse
 bool mouseleftpressed = false;   // True if mouse LEFT button is down.
                               // Saved by mouse.
 int mousex, mousey;           // Mouse x,y coords, in GLUT format (pixels from upper-left corner).
                               // Only guaranteed to be valid if a mouse button is down.
                               // Saved by mouse, motion.
 double zoom = 0.5;

using namespace std;

const int N = 2000;

void clearWindow()
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    // Documentation
    glColor3d(0.0, 0.0, 0.0);  // Black text
    ("Sto debugging"/*"Esc   Quit"*/, 0.15, 0.25);
}

void keyPress(int key, int x, int y)
{

    if (key == 27)
        exit(0);
    if (key == GLUT_KEY_UP)
        rotate_x += .05;
    if (key == GLUT_KEY_DOWN)
        rotate_x -= .05;

    glutPostRedisplay();

    
}

//used for testing
void drawSnowMan() {

    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw Body
    glTranslatef(0.0f, 0.75f, 0.0f);
    glutSolidSphere(0.75f, 20, 20);

    // Draw Head
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f, 20, 20);

    // Draw Eyes
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f, 10, 10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();

    // Draw Nose
    glColor3f(1.0f, 0.5f, 0.5f);
    glutSolidCone(0.08f, 0.5f, 10, 2);
}

void processSpecialKeys(int key, int xx, int yy) {

    float tfraction = 0.1f;
    float rfraction = 0.01f;

    switch (key) {
    case GLUT_KEY_LEFT:
        angle -= rfraction;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case GLUT_KEY_RIGHT:
        angle += rfraction;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    //case GLUT_KEY_UP:
    case GLUT_KEY_UP: 
        x += lx * tfraction;
        z += lz * tfraction;
        break;
    case GLUT_KEY_DOWN:
        x -= lx * tfraction;
        z -= lz * tfraction;
        break;
    }
    glutPostRedisplay();
}

void mouseWheel(int direction, int x, int y)
{

    if (direction == -1)
    {
        zoom -= 0.5;

    }
    else if (direction == +1)
    {
        zoom += 0.5;
    }

    return;

    glutPostRedisplay();
}

// The GLUT mouse function
void Mouse(int button, int state, int x, int y)
{
    // Save the left button state
    if (button == GLUT_LEFT_BUTTON)
    {
        //std::cout<<"test"<<state<<std::endl;
        mouseleftpressed = (state == GLUT_UP);
        //if (mouseleftpressed)
        glutPostRedisplay();  // Left button has changed; redisplay!
    }

    // Save the mouse position
    mousex = x;
    mousey = y;

    if (button == GLUT_WHEEL_DOWN)
    {
        mouseWheel(-1, x, y);
    }
    if (button == GLUT_WHEEL_UP)
    {
        mouseWheel(+1, x, y);
    }

}

void getUniqueNumbers(string txtLines[], int* returnArr) {

    int numberPos[4], numcount = 0;
    bool foundNum = 0;

    cout << "\n in function" << "\n\n";

    for (int i = 0; i < txtLines[0].length(); i++) {
        cout << " bruh ";
        cout << foundNum << " " << txtLines[0][i] << " " << numcount << " ";
        if (foundNum == 0 && isdigit(txtLines[0][i])) {
            cout << i << " " << "\n";
            numberPos[numcount++] = i;
            foundNum = 1;
        }
        if (foundNum == 1 && (!isdigit(txtLines[0][i]))) {
            cout << i << " " << "\n";
            numberPos[numcount++] = i;
            foundNum = 0;
        }

        if (i == txtLines[0].length() - 1) {
            numberPos[numcount++] = i + 1;
        }

        cout << "\n";
    }

    for (int i = 0; i < 4; i++) {
        cout << numberPos[i] << " ";
    }

    for (int i = 0; i < 4; i++) {
        returnArr[i] = numberPos[i];
    }


    cout << "\n\n\n\n";
}

void shape() {

    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
       // Top face (y = 1.0f)
       // Define vertices in counter-clockwise (CCW) order with normal pointing out
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    // Bottom face (y = -1.0f)
    glColor3f(1.0f, 0.5f, 0.0f);     // Orange
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Front face  (z = 1.0f)
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Back face (z = -1.0f)
    glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    // Left face (x = -1.0f)
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Right face (x = 1.0f)
    glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();  // End of drawing color-cube

    // Render a pyramid consists of 4 triangles
    //glLoadIdentity();                  // Reset the model-view matrix
    glTranslatef(-1.5f, 0.0f, -6.0f);  // Move left and into the screen

    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
       // Front
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Right
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Back
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(1.0f, -1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Left
    glColor3f(1.0f, 0.0f, 0.0f);       // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);       // Blue
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);       // Green
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();   // Done drawing the pyramid

    GLfloat VertNumbering[N] = {2 ,3 ,4 ,5, 6, 7, 8, 9, 10 ,11, 0, 1};
    GLfloat beginVerts[N][3] = 
    {
      { 0.333333, 0.942809, 0.57735},
      { - 1, 0, 0.57735},
      {-0.333333, -0.942809, 0.57735},
      {1, 0, -0.57735},
      {0.666667, -0.942809, 0},
      {-0.666667, 0.942809, 0},
      {0.333333, 0.942809, -0.57735},
      {-1, 0, -0.57735},
      {-0.333333, -0.942809, -0.57735},
      {0, 0, -1.1547},
      {0, 0, 1.1547},
      {1, 0, 0.57735}
    };

    for (int i = 0; i < 12; i++) {
        cout << VertNumbering[i] << " ";
        cout << beginVerts[i][0] << " ";
        cout << beginVerts[i][1] << " ";
        cout << beginVerts[i][2] << "\n";
    }

    for (int j = 0; j < 12; j++) {
        for (int i = 0; i < 11; i++) {
            int temp;
            GLfloat tmp[][3] = { 0, 0, 0 };

            if (VertNumbering[i] > VertNumbering[i + 1]) {
                temp = VertNumbering[i];
                tmp[0][0] = beginVerts[i][0];
                tmp[0][1] = beginVerts[i][1];
                tmp[0][2] = beginVerts[i][2];

                VertNumbering[i] = VertNumbering[i + 1];
                beginVerts[i][0] = beginVerts[i + 1][0];
                beginVerts[i][1] = beginVerts[i + 1][1];
                beginVerts[i][2] = beginVerts[i + 1][2];

                VertNumbering[i + 1] = temp;
                beginVerts[i + 1][0] = tmp[0][0];
                beginVerts[i + 1][1] = tmp[0][1];
                beginVerts[i + 1][2] = tmp[0][2];
            }
        }
    }

    cout << "\n";
    for (int i = 0; i < 12; i++) {
        cout << VertNumbering[i] << " ";
        cout << beginVerts[i][0] << " ";
        cout << beginVerts[i][1] << " ";
        cout << beginVerts[i][2] << "\n";
    }

    glTranslatef(-1.5f, 0.0f, -6.0f);

    glBegin(GL_POINTS);
    glVertex3f(0.333333, 0.942809, 0.57735);
    glVertex3f(-1, 0, 0.57735);
    glVertex3f(-0.333333, - 0.942809, 0.57735);
    glVertex3f(1, 0, - 0.57735);
    glVertex3f(0.666667, - 0.942809, 0);
    glVertex3f(-0.666667, 0.942809, 0);
    glVertex3f(0.333333, 0.942809, - 0.57735);
    glVertex3f(-1, 0, - 0.57735);
    glVertex3f(-0.333333, - 0.942809, - 0.57735);
    glVertex3f(0, 0, - 1.1547);
    glVertex3f(0, 0, 1.1547);
    glVertex3f(1, 0, 0.57735);
    glEnd();
    
    char QuadsLettering[N] = {'A', 'B', 'C', 'D', 'E', 'F','G', 'H', 'I', 'J', 'K', 'L', 'M', 'N'};
    
    char beginQuads[N][4] = {
        {'2', '1', '0', '-'},
        {'0', '3', '4', '-'},
        {'1', '6', '5', '-'},
        {'2', '8', '7', '-'},
        {'3', '7', '9', '-'},
        {'4', '10', '6', '-'},
        {'5', '11', '8', '-'},
        {'9', '11', '10', '-'},
        {'0', '2', '7', '3'},
        {'0', '4', '6', '1'},
        {'1', '5', '8', '2'},
        {'3', '9', '10', '4'},
        {'5', '6', '10', '11'},
        {'7', '8', '11', '9'},
    };


    int rowCount = 0;
    for (int j = 0; j < 4; j++) {
        if (isdigit(beginQuads[0][j]))
            rowCount++;
    }

    GLfloat *tmpArr = (GLfloat*)malloc(100 * sizeof(GLfloat) * rowCount);

    for (int j = 0; j < rowCount; j++) {
        tmpArr[j] = beginQuads[0][j];
    }


//A:	2 1 0;
//B:	0 3 4;
//C:	1 6 5;
//D:	2 8 7;
//E:	3 7 9;
//F:	4 10 6;
//G:	5 11 8;
//H:	9 11 10;
//I:	0 2 7 3;
//J:	0 4 6 1;
//K:	1 5 8 2;
//L:	3 9 10 4;
//M:	5 6 10 11;
//N:	7 8 11 9;
}

void Render()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
                                    // and the depth buffer
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(1.5f, 0.0f, -7.0f);  // Move right and into the screen
        
    glScalef(zoom, zoom, 1.0f);
    
    // Set the camera
    gluLookAt(x, y, z,
        x + lx, y, z + lz,
        0.0f, 1.0f, 0.0f);

    // Draw ground
    //glColor3f(0.9f, 0.9f, 0.9f);
    //glBegin(GL_QUADS);
    //glVertex3f(-100.0f, 0.0f, -100.0f);
    //glVertex3f(-100.0f, 0.0f, 100.0f);
    //glVertex3f(100.0f, 0.0f, 100.0f);
    //glVertex3f(100.0f, 0.0f, -100.0f);
    //glEnd();

    //// Draw 36 SnowMen
    //for (int i = -3; i < 3; i++)
    //    for (int j = -3; j < 3; j++) {
    //        glPushMatrix();
    //        glTranslatef(i * 10.0, 0, j * 10.0);
    //        drawSnowMan();
    //        glPopMatrix();
    //    }

    shape();

     // Render a pyramid consists of 4 triangles
    glLoadIdentity();                  // Reset the model-view matrix

      glFlush();
    //	glutSwapBuffers();             // All drawing commands applied to the 
                                       // hidden buffer, so now, bring forward
                                     // the hidden buffer and hide the visible one    


}

void Resize(int w, int h)
{
    // define the visible area of the window ( in pixels )
    if (h == 0) h = 1;
    GLfloat ratio = (GLfloat)w / (GLfloat)h;

    glViewport(0, 0, w, h);

    // Setup viewing volume

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //         L	   R 	  B 	T	 N	   F
   // glOrtho(-100.0, 100.0, -100.0, 100.0, 100.0, -100.0);

    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    //glMatrixMode(GL_MODELVIEW); // not sure if needed 

}

void Idle()
{

}

void Setup()  // DON'T TOUCH IT 
{
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glClearDepth(1.0f);                   // Set background depth to farthest
    
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections


}

/////////////// Main Program ///////////////////////////

int main(int argc, char* argv[])
{


    string line, txtLines[N];
    ifstream myfile("solid1.txt");
    int filelinesCount = 0;

    if (myfile.is_open()) {
        while (getline(myfile, line) && !line.empty())
        {
            line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
            cout << line << '\n';
            txtLines[filelinesCount++] = line;
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    int numberPos[4];

    getUniqueNumbers(txtLines, numberPos);
    
    string widthStr = txtLines[0].substr(numberPos[0], numberPos[1] - numberPos[0]);
    string heightStr = txtLines[0].substr(numberPos[2], numberPos[3] - numberPos[2]);
    
    int width = stoi(widthStr);
    int height = stoi(heightStr);


    for (int j = 1; j < filelinesCount; j++) {
        //remove spaces
        //if it starts with size save sizes 
        //if this save there 
        //if triangle save there 
    }



  // initialize GLUT library state
    glutInit(&argc, argv);

    // Set up the display using the GLUT functions to 
    // get rid of the window setup details:
    // - Use true RGB colour mode ( and transparency )
    // - Enable double buffering for faster window update
    // - Allocate a Depth-Buffer in the system memory or 
    //   in the video memory if 3D acceleration available	
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    //glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);


    // Define the main window size and initial position 
    // ( upper left corner, boundaries included )
    glutInitWindowSize(width, height);
    //glutInitWindowPosition(500, 500);
    glutInitWindowPosition(50, 50);

    // Create and label the main window
    glutCreateWindow("3D objects");

    // Configure various properties of the OpenGL rendering context
    Setup();

    // Callbacks for the GL and GLUT events:

    // The rendering function 
    glutDisplayFunc(Render);
    glutReshapeFunc(Resize);

    glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(Mouse);
    //glutMouseWheelFunc(mouseWheel);

    glutIdleFunc(Idle);


    //Enter main event handling loop
    glutMainLoop();
    
    return 0;

}
