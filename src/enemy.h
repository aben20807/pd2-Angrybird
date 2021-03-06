#ifndef ENEMY_H
#define ENEMY_H

#include "bird.h"

class Enemy : public Bird
{
public:
    Enemy(float x, float y, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void removePig(QGraphicsScene *scene);
    int blood;
};

#endif // ENEMY_H
