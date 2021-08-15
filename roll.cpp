#include "roll.h"

Roll::Roll()
{
    this->currentSlide = nullptr;
    this->currentSlideIndex = -1;
}

Roll::~Roll()
{
    for(Slide *slide:slides) delete slide;
}
