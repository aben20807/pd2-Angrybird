#ifndef BIRD_YELLOW_H
#define BIRD_YELLOW_H

#include "bird.h"

class Bird_yellow : public Bird
{
public:
    Bird_yellow(float x, float y, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual int ability();
};

#endif // BIRD_YELLOW_H
