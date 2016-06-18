#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <QTime>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <QLineF>
#include <QPen>
#include <iostream>
#include <QGraphicsLineItem>

#include "gameitem.h"
#include "land.h"
#include "barrier.h"
#include "bird.h"
#include "bird_blue.h"
#include "other.h"
#include "enemy.h"
#include "genbird.h"

#define BIRD_NUM 4

#define BIRD 0
#define BIRD_BLUE 1
#define BIRD_WHITE 2
#define BIRD_YELLOW 3

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    //void mousePressEvent(QGraphicsSceneMouseEvent *cclick);
    void closeEvent(QCloseEvent *);
    QPointF qtToBox2d(float, float, float w, float h);

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void takeBirdAway();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    QTimer stopCheck;
    QPointF ropeStart;
    QPointF ropeEnd;
    QPointF ropeLength;
    //QGraphicsSceneMouseEvent *click;
    Bird *bird_1;
    Bird *bird_2;
    Bird *bird_3;
    Bird *bird_4;
    bool isUseAbility;
    bool isSetVelocity;
    bool isPreDisappear;
    int genType;
    int tmpType;
    QList<Bird *> list;
    Other *slingshot;
    Enemy *pig;
    //QGraphicsLineItem *line;
};

#endif // MAINWINDOW_H
