#include "aboutus.h"
#include "ui_aboutus.h"
#include"landingpage.h"

Aboutus::Aboutus(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Aboutus)
{
    ui->setupUi(this);
}

Aboutus::~Aboutus()
{
    delete ui;
}

void Aboutus::on_actionexit_triggered()
{
    QApplication::quit();
}


void Aboutus::on_actionHome_triggered()
{
    hide();
    landingPage *land2 = new landingPage(this);
    land2->show();

}






