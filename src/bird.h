#ifndef BIRD_H
#define BIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
using namespace std;

#define BIRD_DENSITY 10.0f//密度
#define BIRD_FRICTION 0.2f//摩擦力
#define BIRD_RESTITUTION 0.5f//回復力

class Bird : public GameItem
{
public:
    Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
};

#endif // BIRD_H
