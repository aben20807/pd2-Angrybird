#ifndef BIRD_WHITE_H
#define BIRD_WHITE_H

#include "bird.h"

class Bird_white : public Bird
{
public:
    Bird_white(float x, float y, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void ability();
};

#endif // BIRD_WHITE_H
