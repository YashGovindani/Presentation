#ifndef ROLL_H
#define ROLL_H

#include "slide.h"
#include <QList>

class Roll
{
private:
    QList<Slide*> slides;
    Slide *currentSlide;
    int currentSlideIndex;
public:
    Roll();
    ~Roll();
};

#endif // ROLL_H
