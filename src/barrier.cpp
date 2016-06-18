#include "barrier.h"

Barrier::Barrier(float x, float y, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    float w = (pixmap.width())*(W_WORLD/W_WINDOW);
    float h = (pixmap.height())*(H_WORLD/H_WINDOW);
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(w,h);

    // Create Body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;
    bodyDef.position.Set(x,y);
    bodyDef.userData = this;
    g_body = world->CreateBody(&bodyDef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w/2.3f,h/2.0f);
    //g_body->CreateFixture(&bodyBox,9.0f);
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyBox;
    fixturedef.density = BARR_DENSITY;
    fixturedef.friction = BARR_FRICTION;
    fixturedef.restitution = BARR_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->SetLinearVelocity(b2Vec2(0,0));
    g_body->CreateFixture(&fixturedef);

    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
    paint();
}
void Barrier::removeBarr(QGraphicsScene *scene)
{
    scene->removeItem(&g_pixmap);
}
