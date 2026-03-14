#include "profile.h"
#include "ui_profile.h"
#include"landingpage.h"
#include"mainwindow.h"
#include<QMessageBox>

profile::profile(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::profile)
{
    ui->setupUi(this);
    MainWindow prof;
    if(!prof.databaseopen())
        ui->label_prof_status->setText("Failed to open database!!");
    else
    {ui->label_prof_status->setText("CONNECTED!......");
    }
    prof.databaseopen();
    QSqlQuery qry;
     qry.prepare("select * from lognreg where username='"+username+"'");
    if(qry.exec())


    {
        if (qry.next())
        {
            ui->label_username->setText(qry.value("username").toString());
            ui->label_password->setText(qry.value("password").toString());
            ui->label_name->setText(qry.value("name").toString());
            ui->label_phno->setText(qry.value("phno").toString());
        }
        else
        {
            ui->label_username->setText(qry.value("NO Records Found!").toString());
            ui->label_password->setText(qry.value("NO Records Found!").toString());
            ui->label_name->setText(qry.value("NO Records Found!").toString());
            ui->label_phno->setText(qry.value("NO Records Found!").toString());
        }
    }
    else
    {
        qDebug() << "Query execution failed: " << qry.lastError().text();
    }
    prof.databaseclose();



}

profile::~profile()
{
    delete ui;
}

void profile::on_actionExit_triggered()
{
    QApplication::quit();
}
void profile::on_actionHome_triggered()
{
    hide();
    landingPage *land = new landingPage(this);
    land->show();
}


void profile::on_pushButton_clicked()
{
    MainWindow del;
    del.databaseopen();
    QSqlQuery qry;
    qry.prepare("DELETE FROM lognreg WHERE username ='"+username+"' ");
    if(qry.exec())
    {
        QMessageBox::warning(this,"ACCOUNT DELETED","YOUR ACCOUNT HAS BEEN SUCCESSFULLY DELETED!!");
        hide();
        MainWindow *open = new MainWindow(this);
        open->show();
        del.databaseclose();

    }
    else
    {
        qDebug() << "Query execution failed: " << qry.lastError().text();
    }

}


void profile::on_pushButton_2_clicked()
{
    hide();
    update = new updateinfo(this);
    update->show();
}

