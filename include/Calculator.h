#ifndef Calculator_H_
#define Calculator_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
#include "Rectangle.h"

using namespace std;


class Calculator{
public:
    Calculator();

    Calculator(const Calculator& other);

    Calculator(vector<Rectangle> vt);

    Calculator(Rectangle &rectangle);

    ~Calculator();

    GLint getSize() const;

    //get idx'th rectangle.
    Rectangle get_rectangle(int idx) const;

    void set_red_rotate(int idx,bool value);

    void set_right_press(int idx,bool value);

    void normalize(GLfloat norm);

    void Draw();

    void printtext() const;

    friend ostream & operator << (ostream &out, Calculator &mesh);
private:
    vector<Rectangle> Rectangles;
};

#endif