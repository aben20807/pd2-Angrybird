#ifndef BARRIER_H
#define BARRIER_H

#include <gameitem.h>
#include <QGraphicsScene>

class Barrier : public GameItem
{
public:
    Barrier(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // BARRIER_H
