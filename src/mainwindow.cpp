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
    isUseAbility = true;
    isPreDisappear = true;
    genType = 0;
    //stopCheck = new QTimer(this);
//    connect(&stopCheck , SIGNAL(timeout()) , this , SLOT(takeBirdAway()));
//    stopCheck.start(1);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress && isPreDisappear == true)
    {
        stopCheck.stop();
        //cout << "Press !" << endl ;
        QMouseEvent *mclick = static_cast<QMouseEvent *>(event);
        ropeStart = qtToBox2d(mclick->x(),mclick->y(),23,23);
        //cout<<"start:"<<ropeStart.x()<<" "<<ropeStart.y()<<endl;
        genType = (genType) % BIRD_NUM;
        world->SetGravity(b2Vec2(0.0f, 0.0f));//點擊時把重力設成0
        bird_1 = genBird(2.94f,6.43f,&timer,genType,world,scene);
        //bird_1 = genBird(2.94f,6.43f,&timer,1,world,scene);//測試單一鳥種用
        //line->setLine(60,320,click->x(),click->y());
        list.push_back(bird_1);
        isUseAbility = false;
        isSetVelocity = false;
        return true;
    }
    if(event->type() == QEvent::MouseButtonPress && isUseAbility == false)
    {
        int callAbility = bird_1->ability();
        //cout<<bird_1->getPosition().x<<" "<<bird_1->getPosition().y<<endl;
        switch (callAbility) {
        case BIRD://紅鳥能力
            break;
        case BIRD_BLUE://藍鳥能力
            bird_2 = new Bird_blue(bird_1->getPosition().x,bird_1->getPosition().y,&timer,QPixmap(":/bird_b.png").scaled(42,41),world,scene);
            bird_3 = new Bird_blue(bird_1->getPosition().x,bird_1->getPosition().y,&timer,QPixmap(":/bird_b.png").scaled(42,41),world,scene);
            bird_4 = new Bird_blue(bird_1->getPosition().x,bird_1->getPosition().y,&timer,QPixmap(":/bird_b.png").scaled(42,41),world,scene);
            bird_2->setLinearVelocity(b2Vec2(bird_1->getLinearVelocity().x,bird_1->getLinearVelocity().y-1.0f));
            bird_3->setLinearVelocity(b2Vec2(bird_1->getLinearVelocity().x,bird_1->getLinearVelocity().y+1.0f));
            bird_4->setLinearVelocity(b2Vec2(bird_1->getLinearVelocity().x,bird_1->getLinearVelocity().y+2.0f));
            list.push_back(bird_2);
            list.push_back(bird_3);
            list.push_back(bird_4);
            break;
        case BIRD_WHITE://白鳥能力
            bird_2 = new Bird_white(bird_1->getPosition().x,bird_1->getPosition().y-0.5,&timer,QPixmap(":/egg.png").scaled(47,60),world,scene);
            bird_2->setLinearVelocity(b2Vec2(0.0f,-2.0f));
            bird_1->setLinearVelocity(b2Vec2(bird_1->getLinearVelocity().x,bird_1->getLinearVelocity().y+2.0f));
            list.push_back(bird_2);
            break;
        case BIRD_YELLOW://黃鳥能力
            bird_1->setLinearVelocity(b2Vec2(bird_1->getLinearVelocity().x*4,bird_1->getLinearVelocity().y));
            break;
        default:
            break;
        }
        //cout<<"ability()"<<endl;
        isUseAbility = true;//能力只可使用一次
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
        if(isUseAbility == false && isSetVelocity == false)
        {
            world->SetGravity(b2Vec2(0.0f, -9.8f));//釋放時把重力設成-9.8
            QMouseEvent *mclick = static_cast<QMouseEvent *>(event);
            ropeEnd = qtToBox2d(mclick->x(),mclick->y(),23,23);
            //cout<<"end:"<<ropeEnd.x()<<" "<<ropeEnd.y()<<endl;
            ropeLength = ropeEnd - ropeStart;
            //cout<<"length:"<<-1*ropeLength.x()<<" "<<ropeLength.y()<<endl;
            bird_1->setLinearVelocity(b2Vec2(-4*ropeLength.x(),-4*ropeLength.y()));

            itemList.push_back(bird_1);
            isSetVelocity = true;//速度只可設定一次
            isPreDisappear = false;
            genType++;
        }
        connect(&stopCheck , SIGNAL(timeout()) , this , SLOT(takeBirdAway()));
        stopCheck.start();
        cout<<bird_1->getLinearVelocity().x<<" "<<bird_1->getLinearVelocity().y<<endl;
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
            isUseAbility = true;
            isPreDisappear = true;
        }
    }
}

