#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
int const MainWindow::EXIT_CODE_REBOOT = -123456789;
int main(int argc, char *argv[])
{
    int currentExitCode = 0;
    do{
        QApplication a(argc, argv);
        MainWindow w;
        QDesktopWidget wid;
        int screenW = 800;
        int screenH = 600;
        //視窗出現在中間
        w.setGeometry(wid.screen()->width()/2 - (screenW/2) , wid.screen()->height()/2 - (screenH/2) , screenW , screenH);
        w.setWindowTitle("Angry Bird");//標題設定
        w.setWindowIcon(QIcon(":/bird.png"));//設定icon
        w.show();

        //return a.exec();
        currentExitCode = a.exec();
    }while(currentExitCode == MainWindow::EXIT_CODE_REBOOT);
    return currentExitCode;
}
