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
#include <QApplication>//for using quit()

#include "gameitem.h"
#include "land.h"
#include "barrier.h"
#include "bird.h"
#include "bird_blue.h"
#include "other.h"
#include "enemy.h"
#include "genbird.h"
#include "btn.h"

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
    void closeEvent(QCloseEvent *);
    QPointF qtToBox2d(float, float, float w, float h);
    void gameInit();
    void bgChange(QString mode);
    void removeAllBarr();

signals:
    // Signal for closing the game
    void birdDisappear();
    void quitGame();


private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void takeBirdAway();
    void takePigAway();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QTimer timer;
    QTimer stopCheck;
    QPointF ropeStart;
    QPointF ropeEnd;
    QPointF ropeLength;
    Bird *bird_1;
    Bird *bird_2;
    Bird *bird_3;
    Bird *bird_4;
    bool isUseAbility;
    bool isSetVelocity;
    bool isPreDisappear;
    bool isGameStart;
    bool isOver;
    bool isWin;
    int genType;
    int tmpType;
    QList<GameItem *> itemList;
    QList<Barrier *> barrList;
    QList<Bird *> birdList;
    QList<Enemy *> pigList;
    Other *slingshot;
    Other *award;
    Enemy *pig;
    QString screenMode;
    Btn *btn_start;
    Btn *btn_restart;
    Btn *btn_exit;
    int btn_w;
    int btn_h;
    int finalScore;
};

#endif // MAINWINDOW_H
