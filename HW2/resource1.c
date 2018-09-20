/*
 * Simple program to demonstrate generating coordinates
 * using the Lorenz Attractor
 */

 /* Code from https://github.com/mikepack/lorenz/blob/master/lorenz.c */

#include <stdio.h>
#include <GLUT/glut.h>
#include <string.h>

int numPts = 50000;
int iter = 0;
int iterInc = 10;
/* View Rotations */
static GLfloat view_rotx = 25.0, view_roty = 50.0, view_rotz = 35.0;
static GLfloat view_posz = 60.0;
/*  Lorenz Parameters  */
double s  = 10;
double b  = 2.6666;
double r  = 28;

float point_array[50000][3];

static void pointGenerator()
{
  int i;
  /*  Coordinates  */
  double x = 1;
  double y = 1;
  double z = 1;
  /*  Time step  */
  double dt = 0.001;

  /*
   *  Integrate 50,000 steps (50 time units with dt = 0.001)
   *  Explicit Euler integration
   */
  for (i=0;i<50000;i++)
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

     printf("%5d %8.3f %8.3f %8.3f\n",i+1,x,y,z);  }
}

void display()
{
  //clear the color buffer (aka the screen)
  glClear(GL_COLOR_BUFFER_BIT);

  glRotatef(view_rotx, 1.0, 0.0, 0.0);
  glRotatef(view_roty, 0.0, 1.0, 0.0);
  glRotatef(view_rotz, 0.0, 0.0, 1.0);

  glBegin(GL_LINE_STRIP);

  for (int i = 0; i < 50000; i++)
  {
    glColor3f(point_array[i][0],point_array[i][1],point_array[i][2]);
    glVertex3f(point_array[i++][0],point_array[i++][1],point_array[i++][2]);
  }

  glEnd();

  glFlush();

  //swap the buffers
  glutSwapBuffers();


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

static void special(int k, int x, int y) {
	switch (k) {
		case GLUT_KEY_UP:
			view_rotx += 5.0;
			break;
		case GLUT_KEY_DOWN:
			view_rotx -= 5.0;
			break;
		case GLUT_KEY_LEFT:
			view_roty += 5.0;
			break;
		case GLUT_KEY_RIGHT:
			view_roty -= 5.0;
			break;
		default:
			return;
	}
  glutPostRedisplay();
}

static void key(unsigned char k, int x, int y) {
	switch (k) {
		case 'q':
			view_rotx += 5.0;
			break;
		case 'a':
			view_rotx -= 5.0;
			break;
		case 'w':
			view_roty += 5.0;
			break;
		case 's':
			view_roty -= 5.0;
			break;
		case 'e':
			view_rotz += 5.0;
			break;
		case 'd':
			view_rotz -= 5.0;
			break;
		case 'r':
			iter = 0;
			break;
		case 'f':
			iter = numPts;
			break;
		case 't':
			iterInc += 5;
			break;
		case 'g':
			if( iterInc - 5 >- 0 ) iterInc -= 5;
			break;
		case 'y':
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			view_posz -= 1;
			gluLookAt(0,0,view_posz,0.0,0.0,0.0,0.0,1.0,0.0);
			break;
		case 'h':
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			view_posz += 1;
			gluLookAt(0,0,view_posz,0.0,0.0,0.0,0.0,1.0,0.0);
			break;
		default:
			return;
	}
	glutPostRedisplay();
}

static void idle(void) {
	iter+=iterInc;
	glutPostRedisplay();
}

/*
 *  Main
 */
int main(int argc, char *argv[])
{
  //create the point array
  pointGenerator();

  glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(500, 500);

	glutCreateWindow("Lorenz Attractor");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();

return 0;
}
