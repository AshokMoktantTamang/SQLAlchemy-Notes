#include "register.h"
#include "ui_register.h"
#include<QMessageBox>
#include"mainwindow.h"

Register::Register(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);

    MainWindow reg;

    if(!reg.databaseopen())
        ui->label_sec_status->setText("Failed to open database!!");
    else
        ui->label_sec_status->setText("CONNECTED!......");
}
Register::~Register()
{
    delete ui;
}



void Register::on_pushButton_register_clicked()
{
    if(ui->checkBox_terms->isChecked()==1)
    {



        MainWindow reg;
        QString password = ui->lineEdit_create_password->text();
        QString name = ui->lineEdit_name->text();
        QString phno = ui->lineEdit_phno1->text();
        QString username = ui->lineEdit_create_email->text();
        if(username.endsWith("@student.ku.edu.np") || username.endsWith("@gmail.com")  )
        {
            if(password.length() >=8 )
            {
                if(phno.length() >= 10)
                {



        if(!reg.databaseopen())
        {
            qDebug()<<"Failed to Open Database!";
            return ;
        }
        reg.databaseopen();
        QSqlQuery qry;
        qry.prepare("INSERT INTO lognreg(name,phno,username,password) VALUES ('"+name+"','"+phno+"','"+username+"','"+password+"')");
        if(qry.exec())
        {
            QMessageBox::information(this,"STATUS","Registered Successfully");
            reg.databaseclose();
            hide();
           MainWindow *open = new MainWindow(this);
            open->show();
        }
        else {
            QMessageBox::critical(this,"Check",qry.lastError().text());
        }
                }
                else
                {
                    QMessageBox::warning(this,"Warning","Phone No. not valid!");
                }
            }
        else
        {
            QMessageBox::warning(this,"Warning","Password must be atleast 8 letters long.");
        }

        }
        else
        {
            QMessageBox::warning(this,"Warning"," Not a valid email , Please try again with a valid EMail Thank you !");
        }
    }


    else {
        QMessageBox::warning(this,"Check","Please Accept the Terms and Conditions to proceed");
    }


}

void Register::on_pushButton_2_clicked()
{
    hide();
    MainWindow *back= new MainWindow(this);
    back->show();
}



