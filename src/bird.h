#ifndef BIRD_H
#define BIRD_H

#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#include "gameitem.h"

#define BIRD_DENSITY 10.0f//密度
//#define BIRD_FRICTION 0.0f//摩擦力
//#define BIRD_RESTITUTION 1.0f//回復力
#define BIRD_FRICTION 0.4f//摩擦力
#define BIRD_RESTITUTION 0.4f//回復力
class Bird : public GameItem
{
public:
    Bird(float x, float y, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    b2Vec2 getLinearVelocity();
    b2Vec2 getPosition();
    void removeBird(QGraphicsScene *scene);
    virtual int ability();

protected:
    b2BodyDef bodyDef;
    b2CircleShape bodyShape;
    b2FixtureDef fixturedef;
};

#endif // BIRD_H
