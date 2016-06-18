#include "enemy.h"

Enemy::Enemy(float x, float y, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Bird(x,y,timer,pixmap,world,scene){}
void Enemy::removePig(QGraphicsScene *scene)
{
    if(g_pixmap.isActive())
    {
        scene->removeItem(&g_pixmap);

    }

}
