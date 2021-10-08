//
// Created by 吴子庶 on 2021/9/25.
//

#ifndef STUDY_BOX_H
#define STUDY_BOX_H

#include "Shape.h"

namespace shape {

    class Box : public shape::Shape<Box> {
    public:
        Box(double length, double width, double height);

        Box(const Box &box);

        virtual ~Box();

        double getLength() const;

        double getWidth() const;

        double getHeight() const;

        double getVolume() const;

        friend void print(Box &box);

    private:
        double length;
        double width;
        double height;

        double *ptr;
    };

}


#endif //STUDY_BOX_H
