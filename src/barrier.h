#ifndef BARRIER_H
#define BARRIER_H

#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include "gameitem.h"

#define BARR_DENSITY 0.05f//密度
#define BARR_FRICTION 2.0f//摩擦力
#define BARR_RESTITUTION 0.5f//回復力

class Barrier : public GameItem
{
public:
    Barrier(float x, float y, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // BARRIER_H
