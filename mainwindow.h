#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtSql>
#include<QDebug>
#include<QFileInfo>
#include "register.h"
#include "landingpage.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb1;


    bool databaseopen() {
        mydb1=QSqlDatabase::addDatabase("QSQLITE");
        mydb1.setDatabaseName("C:/Project Qt/StudentResourceHubDB/StudentResourceHubDB.db");
        if(!mydb1.open()){
             qDebug()<<("Failed to open database!!");
            return false;}
        else
            qDebug()<<("CONNECTED!......");
        return true;
    }
    void databaseclose(){
        mydb1.close();
        mydb1.removeDatabase(QSqlDatabase::defaultConnection);

    }




public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pushButton_login_clicked();



    void on_pushButton_regiss_clicked();


    void on_pushButton_terms_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Register *obj1;
    landingPage *obj2;

};
extern QString username;
#endif // MAINWINDOW_H
