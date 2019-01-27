#include "../include/Calculator.h"

using namespace std;
extern string arr[20];

Calculator::Calculator(){}

Calculator::Calculator(const Calculator& other){
    Rectangles = other.Rectangles;
}

Calculator::Calculator(vector<Rectangle> vt){
    Rectangles = vt;
}

Calculator::Calculator(Rectangle &rectangle){
    //generate the rectangles.
    GLint height = rectangle.getHeight();
    GLint width = rectangle.getWidth();
    GLfloat norm = sqrt((height)*(height) + (width)*(width));
    GLint sz=0;//keeps track of the size of the rectangle.
    for(int i = 0;i < height;i++){
        if(i == 0){
            Rectangle rstart(Point(0.0,i*1.0),Point(2.0,(i+1)*1.0),Color(0.5,0.5,0.5),arr[sz]);
            Rectangles.push_back(rstart);    
        }
        else{
            Rectangle rstart(Point(0.0,i*1.0),Point(1.0,(i+1)*1.0),Color(0.5,0.5,0.5),arr[sz]);
            Rectangles.push_back(rstart);
        }
        sz++;
        for(int j = 1;j < width;j++){
            if(i == 0 && j == 1) continue;
            Color c;
            if(j == width-1) c = Color(1.0,0.5,0.0);
            else  c = Color(0.5,0.5,0.5);
            Rectangle temp(Rectangles[sz-1].getRightBottom(),
                        Rectangles[sz-1].getRightBottom() + Point(1.0,1.0),c,arr[sz]);
            Rectangles.push_back(temp);
            sz++;
        }
    }
    //now insert one large rectangle with default color black.
    Rectangles.push_back(Rectangle(Point(0.0,height*1.0),Point(width*1.0,(height+1)*1.0),arr[sz]));
    //normalize the coordinates of the mesh between 0.0 and 1.0 .
    normalize(norm);
}

Calculator::~Calculator(){}

GLint Calculator::getSize() const{
    return Rectangles.size();
}

//get idx'th rectangle.
Rectangle Calculator::get_rectangle(int idx) const {
    return Rectangles[idx];
}

void Calculator::set_red_rotate(int idx,bool value) {
    Rectangles[idx].set_red_rotate(value);
}

void Calculator::set_right_press(int idx,bool value) {
    Rectangles[idx].set_right_press(value);
}

void Calculator::normalize(GLfloat norm){
    GLint sz = getSize();
    for(GLint i = 0;i < sz;i++){
        Rectangles[i].normalize(norm);
    }
}

void Calculator::Draw(){
    GLint sz = getSize();
    for(GLint i = 0;i < sz;i++){
        Color curr_color = Rectangles[i].getColor();
        glColor3f(curr_color.get_red(),curr_color.get_green(),curr_color.get_blue());
        Rectangles[i].Draw();
    }
}

void Calculator::printtext() const {
    for(int i = 0;i < (this->getSize());i++){
        if(this->get_rectangle(i).is_inside() == true){
            this->get_rectangle(i).printtext();
        }
    }
}

ostream & operator << (ostream &out, Calculator &mesh){
    for(int i = 0;i < mesh.getSize();i++){
        out << mesh.Rectangles[i] << endl << endl;
    }
    return out;
}
