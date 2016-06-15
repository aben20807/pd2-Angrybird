#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
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
#include "other.h"
#include "enemy.h"


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
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    QPointF ropeStart;
    QPointF ropeEnd;
    QPointF ropeLength;
    QGraphicsSceneMouseEvent *click;
    Bird *birdie2;
    Other *slingshot;
    QGraphicsLineItem *line;
};

#endif // MAINWINDOW_H
