#ifndef Rectangle_H_
#define Rectangle_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
#include "Point.h"
#include "Color.h"

using namespace std;

class Rectangle{
public:
    Rectangle();

    Rectangle (Point LB,Point RT,string text);

    Rectangle (Point LB,Point RT,Color c,string text);

    Rectangle (Point LeftBottom,Point LeftTop,Point RightBottom,Point RightTop,string text);

    Rectangle (Point LeftBottom,Point LeftTop,Point RightBottom,Point RightTop,Color c,string text);

    ~Rectangle();

    Point getLeftBottom () const;
 
    Point getLeftTop () const;
 
    Point getRightBottom () const;

    Point getRightTop () const;
 
    GLfloat getWidth () const;

    GLfloat getHeight () const;
 
    GLfloat getAreaSize () const;

    Color getColor() const;

    string get_text() const;

    bool get_red_rotate() const;

    GLfloat get_left_spin() const;

    void set_red_rotate(bool value);

    void set_right_press(bool value);

    void set_left_spin(GLfloat value);

    void normalize(GLfloat norm);

    bool is_inside();

    void printtext() const;

    void Draw();

    friend ostream & operator << (ostream &out, const Rectangle &c);
private:
    Point LeftBottom,LeftTop,RightBottom,RightTop;
    Color color;
    GLfloat left_spin;
    bool red_rotate = false, point_pick = false, cross_45 = false;
    string text;
};

#endif