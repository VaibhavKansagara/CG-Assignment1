#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

static GLfloat spin = 0.0;

void init(void) 
{
    //clears the screen with this color.
   glClearColor (0.0, 0.0, 0.0, 0.0);
   //two options GL_FLAT or GL_SMOOTH.
   //in flat mode the pixels are interpolated.
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   //push the matrix for applying changes like rotation or transformation.
   //the current matrix is projection.
   //it replicates and pushes the already present matrix.
   glPushMatrix();
   //angle,x,y,z - the axis about which you want to rotate.
   glRotatef(spin, 0.0, 0.0, 1.0);
   glColor3f(0.0, 1.0, 0.0);
   /*
    glBegin(GL_POLYGON);
        glVertex3f (0.25, 0.25, 0.0);
        glVertex3f (0.75, 0.25, 0.0);
        glVertex3f (0.75, 0.75, 0.0);
        glVertex3f (0.25, 0.75, 0.0);
    glEnd();
    glRectf is exactly equivalent to above code.
    */
   glRectf(-25.0, -25.0, 25.0, 25.0);
   //here glflush could be used for faster rendering.
   //it basically forces the execution of commands as soon as possible.

   //restore the original state.
   glPopMatrix();
   glutSwapBuffers();
}

void spinDisplay(void)
{
   spin = spin + 2.0;
   if (spin > 360.0)
      spin = spin - 360.0;
    //self explanatory-set's the flag that on next iteration the registered display function is called.
   glutPostRedisplay();
}

void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void mouse(int button, int state, int x, int y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplay);
            //this is a way of security that postredisplay funciton is called once all the rendering calls
            //are complete.
         break;
      case GLUT_MIDDLE_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
         break;
      default:
         break;
   }
}

/* 
 *  Request double buffer display mode.
 *  Register mouse input callback functions
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (250, 250); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutMouseFunc(mouse);
   glutMainLoop();
   return 0;
}
