#ifndef GENBIRD_H
#define GENBIRD_H

#include "bird.h"
#include "bird_blue.h"
#include "bird_white.h"
#include "bird_yellow.h"

Bird *genBird(float x, float y, QTimer *timer, int bird_type, b2World *world, QGraphicsScene *scene);

#endif // GENBIRD_H
