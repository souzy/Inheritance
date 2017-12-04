#pragma once
#include <iostream>
#include <vector>
#include "frame.h"
#include "Object.h"

class Rectangle : public Object {
public:
    virtual void update(double dt);
    virtual void draw() const;
    Rectangle(double h, double w, double x, double y, byte r, byte g, byte b): h(h), w(w), x(x), y(y), r(r), g(g), b(b) {}
    void setSpeed(double dx, double dy);
private:
    byte r, g, b;
    double h, w, x, y, dx, dy;

};