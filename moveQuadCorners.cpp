//#include <stdio.h>
//#include "GL/glut.h"
//
//typedef struct
//{
//    GLfloat x;
//    GLfloat y;
//}vertice_t;
//
//
//GLuint width = 500;
//GLuint height = 500;
//
//vertice_t quad[4];
//
//int bMoving = 0;
//
//int corner = 0;
//
//
//void InitQuad()
//{
//    quad[0].x = -0.5f;
//    quad[0].y = -0.5f;
//
//    quad[1].x = -0.5f;
//    quad[1].y = 0.5f;
//
//
//    quad[2].x = 0.5f;
//    quad[2].y = 0.5f;
//
//
//    quad[3].x = 0.5f;
//    quad[3].y = -0.5f;
//}
//
//void Screen2GLpos(int x, int y, GLfloat* xpos, GLfloat* ypos)
//{
//    *xpos = ((GLfloat)(x)-(GLfloat)(width / 2)) / (GLfloat)(width / 2);
//    *ypos = ((GLfloat)(-y) + (GLfloat)(height / 2)) / (GLfloat)(height / 2);
//    printf("Transform Screen position (%d,%d) to OpenGL position  (%.3f,%.3f)", x, y, *xpos, *ypos);
//}
//
//int BestCorner(float x, float y)
//{
//    int i, idx = -1;
//    float dist2, bestdist2 = 1000000;
//
//    for (i = 0; i < 4; i++)
//    {
//        dist2 = (x - quad[i].x) * (x - quad[i].x) + (y - quad[i].y) * (y - quad[i].y);
//        if (dist2 < bestdist2)
//        {
//            bestdist2 = dist2;
//            idx = i;
//        }
//    }
//
//    return idx;
//}
//
//void OnInit()
//{
//    InitQuad();
//
//    glClearColor(0.0, 0.0, 0.0, 1.0);
//    glColor3f(0.0, 1.0, 1.0);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
//}
//
//
//void OnDisplay()
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//    glBegin(GL_POLYGON);
//    glVertex2f(quad[0].x, quad[0].y);
//    glVertex2f(quad[1].x, quad[1].y);
//    glVertex2f(quad[2].x, quad[2].y);
//    glVertex2f(quad[3].x, quad[3].y);
//    glEnd();
//    glFlush();
//}
//
//
//
//void OnMouseClick(int button, int state, int x, int y)
//{
//    float xmousef, ymousef;
//    int corner;
//
//    if (button == GLUT_LEFT_BUTTON)
//    {
//        if (state == GLUT_DOWN)
//        {
//            printf("button=%d state=%d x=%d y=%d", button, state, x, y);
//            Screen2GLpos(x, y, &xmousef, &ymousef);
//            corner = BestCorner(xmousef, ymousef);
//            quad[corner].x = xmousef;
//            quad[corner].y = ymousef;
//            glutPostRedisplay();
//            bMoving = 1;
//        }
//        else
//        {
//            bMoving = 0;
//        }
//    }
//}
//
//void OnMouseMove(int x, int y)
//{
//    GLfloat xmousef, ymousef;
//
//    if (bMoving)
//    {
//        printf("OnMouseMove :  x=%d y=%d", x, y);
//        Screen2GLpos(x, y, &xmousef, &ymousef);
//        corner = BestCorner(xmousef, ymousef);
//        quad[corner].x = xmousef;
//        quad[corner].y = ymousef;
//        glutPostRedisplay();
//    }
//}
//
//
//
//static void OnKey(unsigned char key, int x, int y)
//{
//    switch (key)
//    {
//    case 27:
//        exit(0);
//    }
//}
//
//static void OnResize(int w, int h)
//{
//    int i;
//
//    printf("Onresize(%d,%d)", w, h);
//
//    width = w;
//    height = h;
//
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//
//    glutPostRedisplay();
//}
//
//
//int main(int argc, char** argv)
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//    glutInitWindowSize(width, height);
//    glutInitWindowPosition(0, 0);
//    glutCreateWindow("simple");
//
//
//    OnInit();
//    glutDisplayFunc(OnDisplay);
//    glutKeyboardFunc(OnKey);
//    glutMouseFunc(OnMouseClick);
//    glutMotionFunc(OnMouseMove);
//    glutReshapeFunc(OnResize);
//
//
//    glutMainLoop();
//
//    return 0;
//}