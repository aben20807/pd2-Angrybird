#include "enemy.h"



Enemy::Enemy(float x, float y, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Bird(x,y,timer,pixmap,world,scene){}
