#include "land.h"

Land::Land(float x, float y, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    float w = (pixmap.width())*(W_WORLD/W_WINDOW);
    float h = (pixmap.height())*(H_WORLD/H_WINDOW);
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(w,h);
    //cout<<w<<endl<<h<<endl;
    //cout<<pixmap.width()<<endl<<pixmap.height()<<endl;
    //cout<<g_pixmap.boundingRect().width()/2<<endl<<g_pixmap.boundingRect().height()/2<<endl;

    // Create body
    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.position.Set(x,y);
    g_body = world->CreateBody(&bodyDef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w/2.1f,h/2.15f);
    g_body->CreateFixture(&bodyBox,9.0f);

    scene->addItem(&g_pixmap);
    paint();
}
