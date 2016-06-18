#include "bird_yellow.h"

Bird_yellow::Bird_yellow(float x, float y, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Bird(x,y,timer,pixmap,world,scene){}
int Bird_yellow::ability()
{
    return 3;
}
