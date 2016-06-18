#ifndef BIRD_BLUE_H
#define BIRD_BLUE_H

#include "bird.h"

class Bird_blue : public Bird
{
public:
    Bird_blue(float x, float y, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual int ability();
};

#endif // BIRD_BLUE_H
