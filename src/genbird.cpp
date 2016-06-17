#include "genbird.h"

#define BIRD 0
#define BIRD_BLUE 1
Bird *genBird(int bird_type)
{
    Bird *ptr;
    switch (bird_type) {
    case BIRD:
        //ptr = new Bird(b2World *world);
        break;
    case BIRD_BLUE:
        //ptr = new Bird_blue(b2World *world);
        break;
    default:
        break;
    }
    return ptr;
}
