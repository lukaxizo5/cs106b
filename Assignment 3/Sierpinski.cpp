/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
using namespace std;

/* Function Prototypes */
void drawTriangle(GWindow window, GPoint a, GPoint b, GPoint c);
void Sierpinski(GWindow window, GPoint a, GPoint b, GPoint c, int order);

int main() {
    GWindow window(600, 400);
    double length;
    int order;
    cout << "Edge length: ";
    cin >> length;
    cout << "Fractal Order: ";
    cin >> order;
    //calculate coordinates of a triangle
    double x = window.getWidth() / 2.0;
    double y = window.getHeight() / 2.0;
    double h = length * sqrt(3.0) / 2.0;
    double ax = x - length / 2.0;
    double ay = y + h / 3.0;
    double bx = x;
    double by = y - 2.0 / 3.0 * h;
    double cx = x + length / 2.0;
    double cy = y + h / 3.0;
    GPoint a(ax, ay);
    GPoint b(bx, by);
    GPoint c(cx, cy);
    Sierpinski(window, a, b, c, order);
    return 0;
}

void Sierpinski(GWindow window, GPoint a, GPoint b, GPoint c, int order) {
    if (order == 0) drawTriangle(window, a, b, c);
    else {
        GPoint mid1((a.getX() + b.getX()) / 2.0, (a.getY() + b.getY()) / 2.0);
        GPoint mid2((b.getX() + c.getX()) / 2.0, (b.getY() + c.getY()) / 2.0);
        GPoint mid3((a.getX() + c.getX()) / 2.0, (a.getY() + c.getY()) / 2.0);
        Sierpinski(window, a, mid1, mid3, order - 1);
        Sierpinski(window, mid1, b, mid2, order - 1);
        Sierpinski(window, mid3, mid2, c, order - 1);
    }
}

void drawTriangle(GWindow window, GPoint a, GPoint b, GPoint c) {
    window.drawLine(a.getX(), a.getY(), b.getX(), b.getY());
    window.drawLine(a.getX(), a.getY(), c.getX(), c.getY());
    window.drawLine(b.getX(), b.getY(), c.getX(), c.getY());
}