#include "termsncond.h"
#include "ui_termsncond.h"
#include"mainwindow.h"
termsncond::termsncond(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::termsncond)
{
    ui->setupUi(this);
}

termsncond::~termsncond()
{
    delete ui;
}

void termsncond::on_pushButton_clicked()
{
    hide();
    MainWindow *obj122= new MainWindow;
    obj122->show();
}

