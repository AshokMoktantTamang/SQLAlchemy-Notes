#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QPixmap>
#include"termsncond.h"
#include<QInputDialog>
QString username;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QPixmap pix(":/resources/Img/aababa.png");
    int w = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));


   if(!databaseopen())
        ui->label_status->setText("Failed to open database!!");
    else
        ui->label_status->setText("CONNECTED!......");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    if(ui->checkBox->isChecked()==1){
     username= ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();


    if(!databaseopen())
    {
        qDebug()<<"Failed to Open Database!";
        return ;
    }
    databaseopen();
    QSqlQuery qry;
    qry.prepare("select * from lognreg where username='"+username+"'and password='"+password+"'");
    if(qry.exec())
    {
        int count=0;
        while(qry.next())
        {
            count++;
        }
        if(count==1)
        {
            databaseclose();
            hide();
            obj2 = new landingPage(this);
            obj2->show();
        }
        else
        {
            QMessageBox::warning(this,"Incorrect","Username and password is not correct..");
        }
    }

    }
    else
    {
        QMessageBox::warning(this,"Check","Please Accept the Terms and Conditions to proceed");
    }
}




void MainWindow::on_pushButton_regiss_clicked()
{
    hide();
    obj1 = new Register(this);
    obj1->show();
}




void MainWindow::on_pushButton_terms_clicked()
{
    hide();
    termsncond *term= new termsncond(this);
    term->show();
}


void MainWindow::on_pushButton_clicked()
{
    bool ok;
    QString username = QInputDialog::getText(
        this,
        tr("Forgot Password"),
        tr("Enter your username:"),
        QLineEdit::Normal,
        QString(),
        &ok
        );



    if (ok && !username.isEmpty()) {

        QSqlQuery query;
        query.prepare("SELECT password FROM lognreg WHERE username ='"+username+"'");

        if (query.exec()) {
            if (query.next()) {

                QString password = query.value(0).toString();


                QMessageBox::information(
                    this,
                    tr("Your Password"),
                    tr("Your password is: %1").arg(password)
                );
            } else {

                QMessageBox::warning(
                    this,
                    tr("Error"),
                    tr("Username not found.")
                );
            }
        } else {

            QMessageBox::critical(
                this,
                tr("Error"),
                tr("Failed to query the database: %1").arg(query.lastError().text())
            );
        }

}
}
