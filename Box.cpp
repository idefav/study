//
// Created by 吴子庶 on 2021/9/25.
//

#include <iostream>
#include "Box.h"

using namespace std;
using namespace shape;

Box::Box(double length, double width, double height) : length(length), width(width), height(height) {

}

double Box::getLength() const {
    return length;
}

double Box::getWidth() const {
    return width;
}

double Box::getHeight() const {
    return height;
}

Box::~Box() {
    this->length = 0;
    this->height = 0;
    this->width = 0;
    delete ptr;
}

double Box::getVolume() const {
    return this->width * this->height * this->length;
}

Box::Box(const Box &box) {
    *ptr = *box.ptr;
}

void shape::print(Box &box) {
    cout << "Length: " << box.getLength() << endl;
    cout << "Width: " << box.getWidth() << endl;
    cout << "Height: " << box.getHeight() << endl;
}


