#include "genbird.h"

#define BIRD 0
#define BIRD_BLUE 1
Bird *genBird(float x, float y, QTimer *timer, int bird_type, b2World *world, QGraphicsScene *scene)
{
    Bird *ptr;
    switch (bird_type) {
    case BIRD:
        ptr = new Bird(x,y,timer,QPixmap(":/bird.png").scaled(46,46),world,scene);
        break;
    case BIRD_BLUE:
        ptr = new Bird_blue(x,y,timer,QPixmap(":/bird_b.png").scaled(42,41),world,scene);
        break;
    default:
        break;
    }
    return ptr;
}
