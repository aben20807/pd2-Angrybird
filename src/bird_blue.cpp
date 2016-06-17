#include "bird_blue.h"

//Bird_blue::Bird_blue(b2World *world):Bird(world){}
Bird_blue::Bird_blue(float x, float y, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Bird(x,y,timer,pixmap,world,scene){}
