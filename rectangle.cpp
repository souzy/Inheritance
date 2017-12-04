#include "rectangle.h"

extern Frame drawFrame;

void Rectangle::setSpeed(double dx, double dy) {
    this->dx = dx;
    this->dy = dy;
}

void Rectangle::update(double dt) {
    x += dx*dt;
    y += dy*dt;
}

void Rectangle::draw() const {
    if (drawFrame.isOutside(x, y)) return;
    int x0 = x;
    int x1 = x + w;
    int y0 = y;
    int y1 = y + h;
    for (int y = y0; y < y1; ++y) {
        for (int x = x0; x < x1; ++x) {
            drawFrame.setPixel(x, y, r, g, b);
        }

    }
}
