/*
Lucas Lyon
CSCI 4229 Computer Graphics
HW2: Lorenz Attractor

Using code from:
1. https://stackoverflow.com/questions/12507054/lorenz-attractor-in-opengl
2. https://github.com/mikepack/lorenz
3. https://nathanselikoff.com/training/tutorial-strange-attractors-in-c-and-opengl
*/




#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int numPts = 50000;
int iter = 0;
int iterInc = 20;
/* View Rotations */
static GLfloat view_rotx = 25.0, view_roty = 50.0, view_rotz = 35.0;
/*  Lorenz Parameters  */
double s  = 10;
double b  = 2.6666;
double r  = 28;

//const int font=(int)GLUT_BITMAP_9_BY_15;
// points for the lorenz Attractor
float point_array[50000][3];

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


   }
}

void init() {

	// set the background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// set the foreground (pen) color
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	//setup viewport
	glViewport(0, 0, 700, 700);

	//setup camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2.0f, 2.0f, -2.0f, 2.0f);

	// set up the modelview matrix (the objects)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}

static void reshape(int width, int height) {
  GLfloat h = (GLfloat) height / (GLfloat) width;
  glViewport(0, 0, (GLint) width, (GLint) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-5.0, 5.0, -h*2, h*2, 1.0, 300.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -60.0);
}

void renderBitmapString(float x, float y,const char *string){
    const char *c;
    glWindowPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(  GLUT_BITMAP_HELVETICA_12  , *c);
    }
}

void mydisplay() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// clear the screen
  glPushMatrix();

  glRotatef(view_rotx, 1.0, 0.0, 0.0);
  glRotatef(view_roty, 0.0, 1.0, 0.0);
  glRotatef(view_rotz, 0.0, 0.0, 1.0);

	// draw some points
  glBegin(GL_LINE_STRIP);

  int i = 0;
  while( i < iter && i < numPts)
  {
  	glColor3f(point_array[i][0],point_array[i][1],point_array[i][2]);
    int ii = i++;
  	glVertex3f(point_array[ii][0],point_array[ii][1],point_array[ii][2]);
  }
  glEnd();

  if( iter < numPts ) {
		if( iter + iterInc > numPts ) iter = numPts;
		else iter+=iterInc;
	}


  /*
  char arrS[sizeof(s)];
  memcpy(arrS, &s, sizeof(s));
  renderBitmapString(0,0, arrS);

  char arrB[sizeof(b)];
  memcpy(arrB, &b, sizeof(b));
  renderBitmapString(0,50, arrB);

  char arrR[sizeof(r)];
  memcpy(arrR, &r, sizeof(r));
  renderBitmapString(0,100, arrR);

  */

  renderBitmapString(10, 100, "1: increase s");
  renderBitmapString(100, 100, "2: decrease s");
  renderBitmapString(10, 85, "3: increase b");
  renderBitmapString(100, 85, "4: decrease b");
  renderBitmapString(10, 70, "5: increase r");
  renderBitmapString(100, 70, "6: decrease r");
  renderBitmapString(10, 55, "A: increase x");
  renderBitmapString(100, 55, "S: decrease x");
  renderBitmapString(10, 40, "Q: increase y");
  renderBitmapString(100, 40, "W: decrease y");
  renderBitmapString(10, 25, "Z: increase z");
  renderBitmapString(100, 25, "X: decrease z");
  renderBitmapString(100, 10, "Esc: exit");
  renderBitmapString(10, 10, "R: reset");





  glFlush();

	// swap the buffers
	glutSwapBuffers();
  glPopMatrix();
}

static void idle(void) {
	iter+=iterInc;
	glutPostRedisplay();
}

void mykey(unsigned char k, int x, int y) {

  switch (k) {
    case 27:
      exit(0);
      break;
    case 'a':
      view_rotx -= 2.5;
      break;
    case 's':
      view_rotx += 2.5;
      break;
    case 'z':
      view_rotz -= 2.5;
      break;
    case 'x':
      view_rotz += 2.5;
      break;
    case 'q':
      view_roty -= 2.5;
      break;
    case 'w':
      view_roty += 2.5;
      break;

      case '1':
        s += 1;
        pointGen();
        mydisplay();
        break;

    case '2':
      s -= 1;
      pointGen();
      mydisplay();
      break;

    case '3':
      r += 1;
      pointGen();
      mydisplay();
      break;

    case '4':
      r -= 1;
      pointGen();
      mydisplay();
      break;

    case '5':
      b += 1;
      pointGen();
      mydisplay();
      break;

    case '6':
      b -= 1;
      pointGen();
      mydisplay();
      break;


    case 'r':
      s = 10;
      b = 2.6666;
      r = 28;
      pointGen();
      mydisplay();
    default:
    return;
  }
  glutPostRedisplay();


	// exit the program when the Esc key is pressed


}

int main (int argc, char **argv) {

  //generate the Lorenz points
  pointGen();

	// initialize GLUT
	glutInit(&argc,argv);

	// set up our display mode for color and double buffering
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowSize(700, 700);
	glutCreateWindow("Lorenz Attractor");

	// register our callback functions
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(mykey);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);


	// call our initialization function
	init();


	// start the program
	glutMainLoop();

    return 0;
}
