#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(10,0,800,530);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());

    // Create ground
    itemList.push_back(new Land(13.6,0.9,32,3,QPixmap(":/ground.png").scaled(width(),height()/8.0),world,scene));
    //邊界
    itemList.push_back(new Barrier(30.7,9.2,2,18,QPixmap(":/-.png").scaled(width()/10,height()),world,scene));//右
    itemList.push_back(new Barrier(-5.0,9.2,2,18,QPixmap(":/-.png").scaled(width()/10,height()),world,scene));//左
    itemList.push_back(new Barrier(13.6,19.5,32,1,QPixmap(":/--.png").scaled(width(),height()/10),world,scene));//上

    // Create bird (You can edit here)
    Bird *birdie = new Bird(0.0f,10.0f,0.27f,&timer,QPixmap(":/bird.png").scaled(height()/10.0,height()/10.0),world,scene);
    // Setting the Velocity
    birdie->setLinearVelocity(b2Vec2(5,5));
    itemList.push_back(birdie);

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
    {
        /* TODO : add your code here */
        //cout << "Press !" << endl ;
    }
    if(event->type() == QEvent::MouseMove)
    {
        /* TODO : add your code here */
        //cout << "Move !" << endl ;
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        /* TODO : add your code here */
        //cout << "Release !" << endl ;
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}
