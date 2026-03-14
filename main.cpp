
#include "mainwindow.h"
#include <QApplication>
#include<QSplashScreen>
#include<QTimer>
#include<QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
MainWindow w;
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/resources/Img/Splash.png"));
    splash->show();

    QTimer::singleShot(1500,splash,SLOT(close()));
    QTimer::singleShot(1500,&w,SLOT(show()));
   // w.show();
    return a.exec();
}
