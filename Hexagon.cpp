
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

const int MAX = 29;
const float ORTH = MAX * 1.0;
int arr[MAX];

void loader(){
  for(int i = 0; i < MAX; i++)
      arr[i] = (rand() % 3) + 1;
      // if(i != MAX / 2)
      //   arr[i] = 1;
      // else
      //   arr[i] = 2;
}
// Init function for OpenGL
void init()
{
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1*ORTH, ORTH, ORTH, -1*ORTH, -1*ORTH, ORTH);
   srand(time(NULL));
   loader();
}

int game = 1;
void drawer(int * color, float x, float y, int row_num, int max) {

  if(max <= 1)
    return;

  int color_buffer = color[game++];

  if(color_buffer == 1)
    glColor3f(1.0, 0.0, 1.0);
  else if(color_buffer == 2)
    glColor3f(0.0, 0.0, 1.0);
  else if(color_buffer == 3)
    glColor3f(0.0, 1.0, 0.0);

   glBegin(GL_POLYGON);
   for(int i = 0; i < 6; ++i) {
      glVertex2d(sin(i/6.0*2*M_PI) + x,
                 cos(i/6.0*2*M_PI) + y);
   }
   glEnd();

   row_num--;

   if(row_num == 1) {
     y = y - 1.7;
     max = max - 1;
     row_num = max;
     x = 0.0 - max;
     game = 1;

     for(int i = 1; i < MAX; i++) {
       color[i - 1] = color[i - 1] + color[i];

       if(color[i - 1] == 2 || color[i - 1] == 5)
         color[i - 1] = 1;
       else if(color[i - 1] == 3 || color[i - 1] == 6)
         color[i - 1] = 3;
       else if(color[i - 1] == 4)
         color[i - 1] = 2;
     }
    }
  drawer(color, x + 2, y, row_num, max);
}

void display2()
{
     glClear(GL_COLOR_BUFFER_BIT);
     drawer(arr, (ORTH -2)*-1, ORTH - 5, MAX, MAX);
     glFlush();
}

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitWindowSize(1500, 1500);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutCreateWindow("hexagon");
   glutDisplayFunc(display2);
   init();
   glutMainLoop();
   return 0;
}
