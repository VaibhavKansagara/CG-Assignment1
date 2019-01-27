#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../include/Calculator.h"

#define pb push_back

#define cout(a) cout<<a<<endl

using namespace std;

float scale = 1.0, x = 0.0, y = 0.0;
GLfloat spin = 0.0;
const GLint WIDTH = 800, HEIGHT = 600;
double xpos,ypos,diffxpos,diffypos;
bool left_press = false,right_press =false,press_and_release = false;
string arr[20] = {"0",".","=","1","2","3","+","4","5","6","-","7","8","9","*","C","+/-","%","/","black screen"};

/*
explanation of all global variables
scale - amount by which the whole calculator is scaled by.
spin - amount by which the whole calculator is rotated by.
xpos and ypos - the current world coordinates of the cursor.
diffxpos and diffypos - the displacement of the pick-point rectangle.
left_press - whether the left mouse button is pressed or not.
right_press - whether the left mouse button is pressed or not.
press_and_release - whether the right mouse button was first pressed and then released.
*/

void determine_coords(GLFWwindow* window){
    glfwGetCursorPos(window, &xpos, &ypos);

    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ=0;
    GLdouble posX, posY, posZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);


    winX = (float)xpos;
    winY = (float)viewport[3] - (float)ypos;

    glReadPixels(xpos, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY,
                &posZ);
    xpos = posX;
    ypos = posY;
}

Calculator createCalculator()
{   
    Point up_right(0,0,0),bottom_left(4,5,0);
    Rectangle rec = Rectangle(bottom_left,up_right,"big rectangle");
    Calculator mesh(rec);
    return mesh;
}

void drawCalculator(Calculator &mesh)
{   
    glLoadIdentity();//load identity matrix
    glTranslatef(x, y, 0);//move forward 4 units
    glScalef(scale, scale, scale);
    glRotatef(spin, 0.0f, 0.0f, 1.0f);
	mesh.Draw();
    if(left_press == true) {
        for(int i = 0;i < mesh.getSize();i++){
            if(mesh.get_rectangle(i).is_inside() == true){
                mesh.set_red_rotate(i,true);
                left_press = false;
            }
        }
    }
    else if(right_press == true) {
        for(int i = 0;i < mesh.getSize();i++){
            if(mesh.get_rectangle(i).is_inside() == true){
                mesh.set_right_press(i,true);
            }
        }
    }
}

void handleKeys(GLFWwindow* window, GLint key, GLint code, GLint action, GLint mode)
{
	if (key == GLFW_KEY_ESCAPE && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	
	if (key == GLFW_KEY_EQUAL && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		scale += 0.05;
	}

	if (key == GLFW_KEY_MINUS && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		scale -= 0.05;
	}

	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		x -= 0.05;
	}

	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		x += 0.05;
	}

	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		y += 0.05;
	}

	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		y -= 0.05;
	}

    if(key == GLFW_KEY_R  && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        //anticlockwise spin.
        spin = spin + 2.0;
        if (spin > 360.0)
            spin = spin - 360.0;
    }
}

void handleMouseButton(GLFWwindow *window,GLint button,GLint action,GLint mode){
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        determine_coords(window);
        left_press = true;
    }
    
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        determine_coords(window);
        right_press = true;
    }

    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE && right_press == true){
        diffxpos = xpos;
        diffypos = ypos;
        determine_coords(window);
        diffxpos = xpos - diffxpos;
        diffypos = ypos - diffypos;
        right_press = false;
        press_and_release = true;
    }
}

Calculator mesh = createCalculator();

void CursorLocation(GLFWwindow *window, double xpos, double ypos){
    if(right_press != true && left_press != true)
        determine_coords(window);
    mesh.printtext();
}

int main(){
    // Initializing GLFW
	if(!glfwInit())
	{
		cout("GLFW initialization failed.");
		glfwTerminate();
		return 1;
	}
	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Calculator", NULL, NULL);
	if(!mainWindow)
	{
		cout("GLFW window creation failed.");
		glfwTerminate();
		return 1;
	}
	// Get buffer size information
	GLint bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if(glewInit() != GLEW_OK)
	{
		cout("GLEW initialization failed.");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}
	// Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	// Loop until window is closed
	while(!glfwWindowShouldClose(mainWindow))
	{
		// Get and handle user input
		glfwPollEvents();
		glfwSetKeyCallback(mainWindow, handleKeys);
		glfwSetMouseButtonCallback(mainWindow,handleMouseButton);
		glfwSetCursorPosCallback(mainWindow, CursorLocation);
		// Clear window
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		// Clear colour buffer before next frame
		glClear(GL_COLOR_BUFFER_BIT);

		drawCalculator(mesh);

		glfwSwapBuffers(mainWindow);
	}
	return 0;
}
