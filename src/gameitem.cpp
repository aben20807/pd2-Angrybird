#include "gameitem.h"

#include <iostream>

GameItem::GameItem(b2World *world):
    g_body(NULL),g_world(world)
{
}

GameItem::~GameItem()
{
    g_world->DestroyBody(g_body);
}

QSizeF GameItem::g_windowsize = QSizeF();
QSizeF GameItem::g_worldsize = QSizeF();

void GameItem::setGlobalSize(QSizeF worldsize, QSizeF windowsize)
{
    g_worldsize = worldsize;
    g_windowsize = windowsize;
}

void GameItem::paint()
{//box2D 轉 Qt
    b2Vec2 pos = g_body->GetPosition();
    //cout << g_body->GetAngle() << std::endl;
    QPointF mappedPoint;
    //mappedPoint.setX(((pos.x-g_size.width()/2) * g_windowsize.width())/g_worldsize.width());
    //mappedPoint.setY((1.0f - (pos.y+g_size.height()/2)/g_worldsize.height()) * g_windowsize.height());
    mappedPoint.setX(((pos.x-g_size.width()/2) * W_WINDOW)/W_WORLD);
    mappedPoint.setY((1.0f - (pos.y+g_size.height()/2)/H_WORLD) * H_WINDOW);
    //cout<<g_size.width()<<endl<<g_size.height()<<endl;
    //cout<<pos.x<<endl<<pos.y<<endl;
    //cout<<g_worldsize.width()<<endl<<g_worldsize.height()<<endl;
    //cout<<g_windowsize.width()<<endl<<g_windowsize.height()<<endl;
    //cout<<W_WORLD<<endl<<H_WORLD<<endl<<W_WINDOW<<endl<<H_WINDOW<<endl;
    g_pixmap.setPos(mappedPoint);
    g_pixmap.resetTransform();
    g_pixmap.setRotation(-(g_body->GetAngle()*180/3.14159));
}
