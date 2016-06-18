#include "bird.h"

Bird::Bird(float x, float y, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);

    float radius = (pixmap.height())*(H_WORLD/H_WINDOW)/2;
    g_size = QSize(radius*2.0f,radius*2.0f);
    //cout<<radius<<endl;

    // Create Body
    //b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;
    bodyDef.position.Set(x,y);
    bodyDef.userData = this;
    g_body = world->CreateBody(&bodyDef);
    //b2CircleShape bodyShape;
    bodyShape.m_radius = radius;
    //b2FixtureDef fixturedef;
    fixturedef.shape = &bodyShape;
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void Bird::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}
b2Vec2 Bird::getLinearVelocity()
{
    return g_body->GetLinearVelocity();
}
b2Vec2 Bird::getPosition()
{
    return g_body->GetPosition();
}

void Bird::removeBird(QGraphicsScene *scene)
{
    scene->removeItem(&g_pixmap);
}
int Bird::ability()
{
    return 0;
}
