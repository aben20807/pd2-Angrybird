#include "genbird.h"

#define BIRD_NUM 4

#define BIRD 0
#define BIRD_BLUE 1
#define BIRD_WHITE 2
#define BIRD_YELLOW 3

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
    case BIRD_WHITE:
        ptr = new Bird_white(x,y,timer,QPixmap(":/bird_w.png").scaled(58,68),world,scene);
        break;
    case BIRD_YELLOW:
        ptr = new Bird_yellow(x,y,timer,QPixmap(":/bird_y.png").scaled(60,58),world,scene);
        break;
    default:
        break;
    }
    return ptr;
}
