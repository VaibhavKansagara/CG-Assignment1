#include "../include/Rectangle.h"

using namespace std;
extern double xpos,ypos;
extern bool press_and_release;
extern double diffxpos,diffypos;
extern GLfloat left_spin;

Rectangle::Rectangle(){}

Rectangle::Rectangle (Point LB,Point RT,string text){
    this->LeftBottom = LB;
    LeftTop = Point(LB.getX(),RT.getY());
    RightBottom = Point(RT.getX(),LB.getY());
    this->RightTop = RT;
    color = Color(0.0f,0.0f,0.0f);
    this->text = text;
    left_spin = -45.0;
}

Rectangle::Rectangle (Point LB,Point RT,Color c,string text){
    this->LeftBottom = LB;
    LeftTop = Point(LB.getX(),RT.getY());
    RightBottom = Point(RT.getX(),LB.getY());
    this->RightTop = RT;
    color = c;
    this->text = text;
    left_spin = -45.0;
}

Rectangle::Rectangle (Point LeftBottom,Point LeftTop,Point RightBottom,Point RightTop,string text){
    this->LeftBottom = LeftBottom;
    this->LeftTop = LeftTop;
    this->RightBottom = RightBottom;
    this->RightTop = RightTop;
    this->text = text;
    color = Color(0.0,0.0,0.0);
    left_spin = -45.0;
}

Rectangle::Rectangle (Point LeftBottom,Point LeftTop,Point RightBottom,Point RightTop,Color c,string text){
    this->LeftBottom = LeftBottom;
    this->LeftTop = LeftTop;
    this->RightBottom = RightBottom;
    this->RightTop = RightTop;
    this->text = text;
    color = c;
    left_spin = -45.0;
}

Rectangle::~Rectangle(){}

Point Rectangle::getLeftBottom () const {
    return LeftBottom; 
}

Point Rectangle::getLeftTop () const {
    return LeftTop;
}

Point Rectangle::getRightBottom () const {
    return RightBottom;
}

Point Rectangle::getRightTop () const {
    return RightTop;
}

GLfloat Rectangle::getWidth () const {
    return LeftBottom.get_distance(RightBottom);
}

GLfloat Rectangle::getHeight () const {
    return LeftBottom.get_distance(LeftTop);
}

GLfloat Rectangle::getAreaSize () const {
    return getWidth()*getHeight();
}

Color Rectangle::getColor() const {
    return color;
}

string Rectangle::get_text() const {
    return text;
}

bool Rectangle::get_red_rotate() const{
    return red_rotate;
}

GLfloat Rectangle::get_left_spin() const {
    return left_spin;
}

void Rectangle::set_red_rotate(bool value) {
    red_rotate = value;
}

void Rectangle::set_right_press(bool value) {
    point_pick = value;
}

void Rectangle::set_left_spin(GLfloat value) {
    left_spin = value;
}

void Rectangle::normalize(GLfloat norm){
    LeftBottom.normalize(norm);
    LeftTop.normalize(norm);
    RightBottom.normalize(norm);
    RightTop.normalize(norm);
}

bool Rectangle::is_inside() {
    if(LeftBottom.getX() <= xpos && RightTop.getX() >= xpos
        && LeftBottom.getY() <= ypos && RightTop.getY() >= ypos)
        return true;
    return false;
}

void Rectangle::printtext() const {
    cout<<"text on the mouse: "<<text<<endl;
}

void Rectangle::Draw(){
    glPushMatrix();
    if(press_and_release == true && point_pick == true) {
        LeftBottom.setXY(LeftBottom.getX() + diffxpos, LeftBottom.getY() + diffypos);
        LeftTop.setXY(LeftTop.getX() + diffxpos, LeftTop.getY() + diffypos);
        RightTop.setXY(RightTop.getX() + diffxpos, RightTop.getY() + diffypos);
        RightBottom.setXY(RightBottom.getX() + diffxpos, RightBottom.getY() + diffypos);
        point_pick = false;
        press_and_release = false;
    }
    glBegin(GL_QUADS);
        glVertex3f(LeftBottom.getX(),LeftBottom.getY(),LeftBottom.getZ());
        glVertex3f(LeftTop.getX(),LeftTop.getY(),LeftTop.getZ());
        glVertex3f(RightTop.getX(),RightTop.getY(),RightTop.getZ());
        glVertex3f(RightBottom.getX(),RightBottom.getY(),RightBottom.getZ());
    glEnd();
    glPopMatrix();

    glPushMatrix();
    if(red_rotate == true){
        glTranslatef(LeftBottom.getX(),LeftBottom.getY(),0.0f);
        glRotatef(left_spin, 0.0f, 0.0f, 1.0f);
        glTranslatef(-LeftBottom.getX(),-LeftBottom.getY(),0.0f);
        glColor3f(1.0f,0.0f,0.0f);
        if(cross_45){
            left_spin -= 2.0;
            if(left_spin < 0){
                left_spin = -45.0;
                red_rotate = false;
                cross_45 = false;
            }
        }
        else if(!cross_45){
            left_spin += 2.0;
            if(left_spin > 45.0)
                cross_45 = true;
        }
    }
    else{
        glColor3f(0.0f,0.0f,0.0f);
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
        glVertex3f(LeftBottom.getX(),LeftBottom.getY(),LeftBottom.getZ());
        glVertex3f(LeftTop.getX(),LeftTop.getY(),LeftTop.getZ());
        glVertex3f(RightTop.getX(),RightTop.getY(),RightTop.getZ());
        glVertex3f(RightBottom.getX(),RightBottom.getY(),RightBottom.getZ());
    glEnd();
    glPopMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

ostream & operator << (ostream &out, const Rectangle &c){
    out << c.LeftBottom << c.RightBottom << c.LeftTop 
        << c.RightTop<< c.getColor() << endl;
    return out;
}
