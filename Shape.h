//
// Created by 吴子庶 on 2021/9/25.
//

#ifndef STUDY_SHAPE_H
#define STUDY_SHAPE_H
namespace shape {
    template<class T>
    class Shape {
    public:
        virtual double getVolume() const = 0;

    private:

    };

}


#endif //STUDY_SHAPE_H
