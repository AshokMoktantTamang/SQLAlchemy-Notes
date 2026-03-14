#include "contactus.h"
#include "ui_contactus.h"
#include"landingpage.h"
#include<QDesktopServices>
#include<QUrl>
Contactus::Contactus(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Contactus)
{
    ui->setupUi(this);
}

Contactus::~Contactus()
{
    delete ui;
}

void Contactus::on_actionexit_triggered()
{
    QApplication::quit();
}


void Contactus::on_actionHome_triggered()
{
    hide();
    landingPage *land3 = new landingPage(this);
    land3->show();
}


void Contactus::on_pushButton_clicked()
{
    QString link="mailto:studentresourceshub00@gmail.com?";
    QDesktopServices::openUrl(QUrl(link));
}

