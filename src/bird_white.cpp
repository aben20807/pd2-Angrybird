#include "bird_white.h"

Bird_white::Bird_white(float x, float y, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Bird(x,y,timer,pixmap,world,scene){}
int Bird_white::ability()
{
    return 2;
}
