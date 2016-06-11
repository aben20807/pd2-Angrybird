#ifndef LAND_H
#define LAND_H

#include "gameitem.h"
#include <QGraphicsScene>
//#include <iostream>
//using namespace std;
class Land : public GameItem
{
public:
    Land(float x, float y, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // LAND_H
