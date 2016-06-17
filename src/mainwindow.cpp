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
    scene->setSceneRect(10,4,800,530);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());

    QImage bg;
    bg.load(":/bg_sky");
    scene->setBackgroundBrush(bg);

    // Create ground
    itemList.push_back(new Land(9.0,1.3,QPixmap(":/ground.png").scaled(1270,72),world,scene));

    //邊界
    itemList.push_back(new Land(32.0,14.0,QPixmap(":/-.png").scaled(12,1837),world,scene));//右
    itemList.push_back(new Land(-3.3,14.0,QPixmap(":/-.png").scaled(12,1837),world,scene));//左
    itemList.push_back(new Land(15.7,18.5,QPixmap(":/--.png").scaled(1870,12),world,scene));//上

    //障礙物
    //itemList.push_back(new Barrier(12.7,5,&timer,QPixmap(":/barr_tree.png").scaled(39,156),world,scene));
    //itemList.push_back(new Barrier(17.4,5,&timer,QPixmap(":/barr_tree.png").scaled(39,156),world,scene));
    //itemList.push_back(new Barrier(15.0,3,&timer,QPixmap(":/barr_base.png").scaled(194,39),world,scene));
    //itemList.push_back(new Barrier(15.0,8,&timer,QPixmap(":/barr_base.png").scaled(194,39),world,scene));

    itemList.push_back(new Barrier(15,5,&timer,QPixmap(":/barr_l.png").scaled(20,137),world,scene));
    itemList.push_back(new Barrier(19,5,&timer,QPixmap(":/barr_l.png").scaled(20,137),world,scene));
    itemList.push_back(new Barrier(23,5,&timer,QPixmap(":/barr_l.png").scaled(20,137),world,scene));
    itemList.push_back(new Barrier(27,5,&timer,QPixmap(":/barr_l.png").scaled(20,137),world,scene));
    itemList.push_back(new Barrier(25.0,3,&timer,QPixmap(":/barr_--.png").scaled(137,20),world,scene));
    itemList.push_back(new Barrier(25.0,8,&timer,QPixmap(":/barr_--.png").scaled(137,20),world,scene));

    //彈弓
    slingshot = new Other;
    QPixmap slingshot_p;
    slingshot_p.load(":/slingshot.png");
    slingshot->setPixmap(slingshot_p);
    slingshot->setPos(60,330);
    scene->addItem(slingshot);

    //敵人
    pig = new Enemy(25.0,5,&timer,QPixmap(":/pig.png").scaled(78,77),world,scene);
    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
    stopCheck.start(1);
    useAbility = true;
    genType = 0;
    //stopCheck = new QTimer(this);
//    connect(&stopCheck , SIGNAL(timeout()) , this , SLOT(takeBirdAway()));
//    stopCheck.start(1);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress && useAbility == true)
    {
        stopCheck.stop();
        //cout << "Press !" << endl ;
        QMouseEvent *mclick = static_cast<QMouseEvent *>(event);
        ropeStart = qtToBox2d(mclick->x(),mclick->y(),23,23);
        //cout<<"start:"<<ropeStart.x()<<" "<<ropeStart.y()<<endl;
        genType = (genType) % BIRD_NUM;
        world->SetGravity(b2Vec2(0.0f, 0.0f));//點擊時把重力設成0
        bird_1 = genBird(2.94,6.43,&timer,genType,world,scene);
        //line->setLine(60,320,click->x(),click->y());
        list.push_back(bird_1);
        useAbility = false;
        return true;
    }
    if(event->type() == QEvent::MouseButtonPress && useAbility == false)
    {
        bird_1->ability();

        //useAbility = true;
    }
    if(event->type() == QEvent::MouseMove)
    {

//        QMouseEvent *click = static_cast<QMouseEvent *>(event);
//        QLineF line1(6,3,8,4);
//        //cout << "Move !" << endl ;
//        //line->setLine(60,320,click->x(),click->y());
//        QPen pen;
//        pen.setWidth(10);
//        pen.setColor(Qt::black);
//        line->setPen(pen);
//        line->setLine(line1);
//        line->setVisible(true);

        return true;
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        //cout << "Release !" << endl ;
        world->SetGravity(b2Vec2(0.0f, -9.8f));//釋放時把重力設成-9.8
        QMouseEvent *mclick = static_cast<QMouseEvent *>(event);
        ropeEnd = qtToBox2d(mclick->x(),mclick->y(),23,23);
        //cout<<"end:"<<ropeEnd.x()<<" "<<ropeEnd.y()<<endl;
        ropeLength = ropeEnd - ropeStart;
        //cout<<"length:"<<-1*ropeLength.x()<<" "<<ropeLength.y()<<endl;
        bird_1->setLinearVelocity(b2Vec2(-4*ropeLength.x(),-4*ropeLength.y()));

        itemList.push_back(bird_1);

        connect(&stopCheck , SIGNAL(timeout()) , this , SLOT(takeBirdAway()));
        stopCheck.start();
        //cout<<bird_1->getLinearVelocity().x<<" "<<bird_1->getLinearVelocity().y<<endl;
        return true;
    }
    return false;
}
QPointF MainWindow::qtToBox2d(float x,float y,float w,float h)
{//把 qt 的座標轉換成 box2D 的
    QPointF tmp;
    tmp.setX((x-95+w)*W_WORLD/W_WINDOW);
    tmp.setY(((-1*(y+10)/H_WINDOW)+1)*H_WORLD+h*H_WORLD/H_WINDOW);
    return tmp;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    timer.stop();
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
void MainWindow::takeBirdAway()
{
    foreach (Bird *i, list) {
        if(i->getLinearVelocity() == b2Vec2(0.0f,0.0f))
        {
            i->removeBird(scene);
            list.removeOne(i);
            delete i;
            useAbility = true;
            genType++;
        }
    }
}

