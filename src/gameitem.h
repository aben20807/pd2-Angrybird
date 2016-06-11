#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTransform>
#include <QtMath>
#include <iostream>

using namespace std;
#define W_CENTER (31.85/2-2.3)
#define H_CENTER (17.85/2+0.3)
#define W_WINDOW 887.8
#define H_WINDOW 534.5
#define W_WORLD 31.85
#define H_WORLD 17.85

class GameItem : public QObject
{
    Q_OBJECT
public:
    GameItem(b2World *world);
    ~GameItem();
    static void setGlobalSize(QSizeF worldsize, QSizeF windowsize);

public slots:
    void paint();
    //TODO virtual void collide();

protected:
    b2Body *g_body;
    QGraphicsPixmapItem g_pixmap;
    QSizeF g_size;
    b2World *g_world;
    static QSizeF g_worldsize, g_windowsize;
};

#endif // GAMEITEM_H
