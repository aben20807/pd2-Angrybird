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
    scene->setSceneRect(10,3,800,530);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());

    QImage bg;
    bg.load(":/bg_sky");
    scene->setBackgroundBrush(bg);

    // Create ground
    itemList.push_back(new Land(8.9,1.3,QPixmap(":/ground.png").scaled(1270,72),world,scene));

//    itemList.push_back(new Land(W_CENTER,H_CENTER,QPixmap(":/dot").scaled(5,5),world,scene));
//    Enemy *t = new Enemy();
//    QPixmap face;
//    face.load(":/dot");
//    face = face.scaled(3,3);
//    t->setPixmap(face);
//    t->setPos(-69,530.5);
//    scene->addItem(t);

    //邊界
    itemList.push_back(new Land(32.0,14.0,QPixmap(":/-.png").scaled(12,1837),world,scene));//右
    itemList.push_back(new Land(-3.3,14.0,QPixmap(":/-.png").scaled(12,1837),world,scene));//左
    itemList.push_back(new Land(15.7,18.5,QPixmap(":/--.png").scaled(1870,12),world,scene));//上

    //障礙物
    itemList.push_back(new Barrier(12.7,5,&timer,QPixmap(":/barr_tree.png").scaled(39,156),world,scene));
    itemList.push_back(new Barrier(17.4,5,&timer,QPixmap(":/barr_tree.png").scaled(39,156),world,scene));
    itemList.push_back(new Barrier(15.0,3,&timer,QPixmap(":/barr_base.png").scaled(194,39),world,scene));
    itemList.push_back(new Barrier(15.0,8,&timer,QPixmap(":/barr_base.png").scaled(194,39),world,scene));

    // Create bird (You can edit here)
    Bird *birdie = new Bird(0.0f,10.0f,&timer,QPixmap(":/bird.png").scaled(46,46),world,scene);

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
