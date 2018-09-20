#include <stdio.h>
#include <GLUT/glut.h>
#include <string.h>

int numPts = 50000;
int iter = 0
int iterInc = 10;

/* view params */
static GLfloat view_rotx = 25.0, view_roty = 50.0, view_rotz = 35.0, view_posz = 60.0;

/*Lorenz params */
double s = 10, b=2.6666, r=28;

float point_array[numPts][3];

static void pointGen()
{
  int i = 0;

  /* coordinates */
  double x = 1, y=1, z=1;
  double dt = 0.001;

  /*
   *  Integrate 50,000 steps (50 time units with dt = 0.001)
   *  Explicit Euler integration
   */
  for (i=0;i<numPts;i++)
  {
     double dx = s*(y-x);
     double dy = x*(r-z)-y;
     double dz = x*y - b*z;
     x += dt*dx;
     y += dt*dy;
     z += dt*dz;

     //populate the array
     point_array[i][0] = x;
     point_array[i][1] = y;
     point_array[i][2] = z;

     printf("%5d %8.3f %8.3f %8.3f\n",i+1,x,y,z);

   }
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
}
