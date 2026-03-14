#include "updateinfo.h"
#include "ui_updateinfo.h"
#include"profile.h"
#include"mainwindow.h"
#include<QMessageBox>

updateinfo::updateinfo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::updateinfo)
{
    ui->setupUi(this);
}

updateinfo::~updateinfo()
{
    delete ui;
}

void updateinfo::on_actionExit_triggered()
{
    QApplication::quit();
}


void updateinfo::on_actionHome_triggered()
{
    hide();
    profile *page1= new profile(this);
    page1->show();
}


void updateinfo::on_pushButton_2_clicked()
{
    MainWindow mainup;
    QString username1 = ui->lineEdit_create_email->text();
    QString password = ui->lineEdit_create_password->text();
    QString name = ui->lineEdit_name->text();
    QString phno = ui->lineEdit_phno1->text();

    if(!mainup.databaseopen())
    {
        qDebug()<<"Failed to Open Database!";
        return ;
    }
    mainup.databaseopen();
    QSqlQuery qry;

    qry.prepare("UPDATE lognreg SET name = '"+name+"', phno = '"+phno+"', username = '"+username1+"', password = '"+password+"' WHERE username = '"+username+"'");
    if(qry.exec())
    {

        mainup.databaseclose();
         QMessageBox::information(this,"UPDATED","Your INFO is Updated Thank You!");

    }
    else {
         QMessageBox::critical(this,"Check",qry.lastError().text());
    }


}

