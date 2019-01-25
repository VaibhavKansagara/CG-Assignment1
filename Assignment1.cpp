#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
#define pb push_back

#define cout(a) cout<<a<<endl

using namespace std;
float scale = 1.0, x = 0.0, y = 0.0;
static GLfloat spin = 0.0,left_spin = -45.0;
const GLint WIDTH = 800, HEIGHT = 600;
double xpos,ypos;
bool left_press = false;

class Point{
public:
    Point(){}

    Point(GLfloat _x,GLfloat _y,GLfloat _z = 0.0):x(_x),y(_y),z(_z){}

    ~Point(){}

    GLfloat getX() const {
        return x;
    }
    GLfloat getY() const {
        return y;
    }
    GLfloat getZ() const {
        return z;
    }

    void set_coord(GLfloat _x,GLfloat _y,GLfloat _z = 0.0) {
        x = _x;
        y = _y;
        z = _z;
    }

    GLfloat get_distance(const Point &other) const {
        return sqrt(pow(this->x-other.x,2)+pow(this->y-other.y,2)+pow(this->z-other.z,2));
    }

    void normalize(GLfloat norm){
        x = x/norm;
        y = y/norm;
        z = z/norm;
    }

    friend istream & operator >> (istream &in, Point &p){
        in >> p.x >> p.y >> p.z;
        return in;
    }

    friend ostream & operator << (ostream &out, const Point &p){
        out << "Point:" << p.x << " "<< p.y << " "<< p.z << endl;
        return out;
    }

    Point operator + (Point const& obj){
        return Point(this->x + obj.getX(),this->y + obj.getY());
    }
private:
    GLfloat x,y,z;
};


class Color {
public:
    Color(){}
    Color(GLfloat r, GLfloat g, GLfloat b):red(r),green(g),blue(b){}
    ~Color(){}
    void set_red(GLfloat r){
        red = r;
    }
    void set_green(GLfloat g){
        green = g;
    }
    void set_blue(GLfloat b){
        blue = b;
    }
    GLfloat get_red() const{
        return red;
    }
    GLfloat get_green() const{
        return green;
    }
    GLfloat get_blue() const{
        return blue;
    }

    void set_color(GLfloat r, GLfloat g, GLfloat b) {
        red = r;
        green = g;
        blue = b;
    }

    friend ostream & operator << (ostream &out, const Color &c){
        out << "Color:" << c.red << " "<< c.green << " "<< c.blue << endl;
        return out;
    }
private:
    GLfloat red, green, blue;
};

class Rectangle{
public:
    Rectangle(){}

    Rectangle (Point LB,Point RT){
        this->LeftBottom = LB;
        LeftTop = Point(LB.getX(),RT.getY());
        RightBottom = Point(RT.getX(),LB.getY());
        this->RightTop = RT;
        color = Color(0.0f,0.0f,0.0f);
    }

    Rectangle (Point LB,Point RT,Color c){
        this->LeftBottom = LB;
        LeftTop = Point(LB.getX(),RT.getY());
        RightBottom = Point(RT.getX(),LB.getY());
        this->RightTop = RT;
        color = c;
    }

    Rectangle (Point LeftBottom,Point LeftTop,Point RightBottom,Point RightTop){
        this->LeftBottom = LeftBottom;
        this->LeftTop = LeftTop;
        this->RightBottom = RightBottom;
        this->RightTop = RightTop;
        color = Color(0.0,0.0,0.0);
    }

    Rectangle (Point LeftBottom,Point LeftTop,Point RightBottom,Point RightTop,Color c){
        this->LeftBottom = LeftBottom;
        this->LeftTop = LeftTop;
        this->RightBottom = RightBottom;
        this->RightTop = RightTop;
        color = c;
    }

    ~Rectangle(){}

    Point getLeftBottom () const {
        return LeftBottom; 
    }
 
    Point getLeftTop () const {
        return LeftTop;
    }
 
    Point getRightBottom () const {
        return RightBottom;
    }

    Point getRightTop () const {
        return RightTop;
    }
 
    GLfloat getWidth () const {
        return LeftBottom.get_distance(RightBottom);
    }
 
    GLfloat getHeight () const {
        return LeftBottom.get_distance(LeftTop);
    }
 
    GLfloat getAreaSize () const {
        return getWidth()*getHeight();
    }

    Color getColor() const {
        return color;
    }

    void normalize(GLfloat norm){
        LeftBottom.normalize(norm);
        LeftTop.normalize(norm);
        RightBottom.normalize(norm);
        RightTop.normalize(norm);
    }

    bool is_inside() {
        if(LeftBottom.getX() <= xpos && RightTop.getX() >= xpos
            && LeftBottom.getY() <= ypos && RightTop.getY() >= ypos)
            return true;
        return false;
    }

    void rotate() {
        glPushMatrix();
        glLoadIdentity();//load identity matrix
        glScalef(scale, scale, scale);
        glTranslatef(x, y, 0);//move forward 4 units

        //next 3 lines are trickier.
        //first translate the coordinates to left bottom to make left-bottom the origin point.
        //and then rotate otherwise it will rotate w.r.t origin and not left-bottom point.
        glTranslatef(LeftBottom.getX(),LeftBottom.getY(),0.0f);
        glRotatef(left_spin,0.0f,0.0f,1.0f);
        // //And move it back.
        glTranslatef(-LeftBottom.getX(),-LeftBottom.getY(),0.0f);

        //fill red color.
        glColor3f(1.0f,0.0f,0.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_QUADS);
            glVertex3f(LeftBottom.getX(),LeftBottom.getY(),LeftBottom.getZ());
            glVertex3f(LeftTop.getX(),LeftTop.getY(),LeftTop.getZ());
            glVertex3f(RightTop.getX(),RightTop.getY(),RightTop.getZ());
            glVertex3f(RightBottom.getX(),RightBottom.getY(),RightBottom.getZ());
        glEnd();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glPopMatrix();
    }

    void Draw(){
        glPushMatrix();
        glBegin(GL_QUADS);
            glVertex3f(LeftBottom.getX(),LeftBottom.getY(),LeftBottom.getZ());
            glVertex3f(LeftTop.getX(),LeftTop.getY(),LeftTop.getZ());
            glVertex3f(RightTop.getX(),RightTop.getY(),RightTop.getZ());
            glVertex3f(RightBottom.getX(),RightBottom.getY(),RightBottom.getZ());
        glEnd();
        glPopMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(0.0f,0.0f,0.0f);
        glPushMatrix();
        glBegin(GL_QUADS);
            glVertex3f(LeftBottom.getX(),LeftBottom.getY(),LeftBottom.getZ());
            glVertex3f(LeftTop.getX(),LeftTop.getY(),LeftTop.getZ());
            glVertex3f(RightTop.getX(),RightTop.getY(),RightTop.getZ());
            glVertex3f(RightBottom.getX(),RightBottom.getY(),RightBottom.getZ());
        glEnd();
        glPopMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    friend ostream & operator << (ostream &out, const Rectangle &c){
        out << c.LeftBottom << c.RightBottom << c.LeftTop 
            << c.RightTop<< c.getColor() << endl;
        return out;
    }
private:
    Point LeftBottom,LeftTop,RightBottom,RightTop;
    Color color;
};

class Mesh{
public:
    Mesh(){}

    Mesh(const Mesh& other){
        Rectangles = other.Rectangles;
    }

    Mesh(vector<Rectangle> vt){
        Rectangles = vt;
    }

    Mesh(Rectangle &rectangle){
        //generate the rectangles.
        GLint height = rectangle.getHeight();
        GLint width = rectangle.getWidth();
        GLfloat norm = sqrt(height*height + width*width);
        GLint sz=0;//keeps track of the size of the rectangle.
        for(int i = 0;i < height;i++){
            Rectangle rstart(Point(0.0,i*1.0),Point(1.0,(i+1)*1.0),Color(1.0,0.5,0.0));
            Rectangles.pb(rstart);
            sz++;
            for(int j = 1;j < width;j++){
                Rectangle temp(Rectangles[sz-1].getRightBottom(),
                            Rectangles[sz-1].getRightBottom() + Point(1.0,1.0),Color(1.0,0.5,0.0));
                Rectangles.pb(temp);
                sz++;
            }
        }
        //now insert one large rectangle with default color black.
        Rectangles.pb(Rectangle(Point(0.0,height*1.0),Point(width*1.0,(height+1)*1.0)));
        //normalize the coordinates of the mesh between 0.0 and 1.0 .
        normalize(norm);
    }

    ~Mesh(){}

    GLint getSize(){
        return Rectangles.size();
    }

    //get idx'th rectangle.
    Rectangle get_rectangle(int idx) const {
        return Rectangles[idx];
    }

    void normalize(GLfloat norm){
        GLint sz = getSize();
        for(GLint i = 0;i < sz;i++){
            Rectangles[i].normalize(norm);
        }
    }

    void Draw(){
        GLint sz = getSize();
        for(GLint i = 0;i < sz;i++){
            Color curr_color = Rectangles[i].getColor();
            glColor3f(curr_color.get_red(),curr_color.get_green(),curr_color.get_blue());
            Rectangles[i].Draw();
        }
    }

    friend ostream & operator << (ostream &out, Mesh &mesh){
        for(int i = 0;i < mesh.getSize();i++){
            out << mesh.Rectangles[i] << endl << endl;
        }
        return out;
    }
private:
    vector<Rectangle> Rectangles;
};

Mesh createCalculator()
{   
    Point up_right,bottom_left;
    cin >> bottom_left >> up_right;
    Rectangle rec = Rectangle(bottom_left,up_right);
    Mesh mesh(rec);
    return mesh;
}

void drawCalculator(Mesh &mesh)
{   
    glLoadIdentity();//load identity matrix
    glTranslatef(x, y, 0);//move forward 4 units
    glScalef(scale, scale, scale);
    glRotatef(spin, 0.0f, 0.0f, 1.0f);
	mesh.Draw();
    if(left_press == true){
        for(int i = 0;i < mesh.getSize();i++){
            if(mesh.get_rectangle(i).is_inside() == true){
                mesh.get_rectangle(i).rotate();
                break; //not necessary.
            }
        }
    }
}

void handleKeys(GLFWwindow* window, GLint key, GLint code, GLint action, GLint mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	
	if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
	{
		scale += 0.05;
	}

	if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
	{
		scale -= 0.05;
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		x -= 0.05;
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		x += 0.05;
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		y += 0.05;
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		y -= 0.05;
	}

    if(key == GLFW_KEY_R  && action == GLFW_PRESS){
        //anticlockwise spin.
        spin = spin + 2.0;
        if (spin > 360.0)
            spin = spin - 360.0;
    }
}

void handleMouse(GLFWwindow *window,GLint button,GLint action,GLint mode){
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
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

        left_press = true;
        if(left_spin >= -45.0 && left_spin<= 45.0){ left_spin +=2.0; }
        else { left_spin = 0.0; }
    }

    if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS){
        
    }
    
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){

    }
}

int main(){
    Mesh mesh = createCalculator();
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
        glfwSetMouseButtonCallback(mainWindow,handleMouse);
		// Clear window
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		// Clear colour buffer before next frame
		glClear(GL_COLOR_BUFFER_BIT);

		drawCalculator(mesh);

		glfwSwapBuffers(mainWindow);
	}
	return 0;
}