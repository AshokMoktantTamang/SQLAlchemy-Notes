#ifndef PROFILE_H
#define PROFILE_H

#include <QMainWindow>
#include<QtSql>
#include<QDebug>
#include<QFileInfo>
#include"updateinfo.h"


namespace Ui {
class profile;
}

class profile : public QMainWindow
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = nullptr);
    ~profile();

private slots:
    void on_actionExit_triggered();



    void on_actionHome_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::profile *ui;
    updateinfo *update;
};

#endif // PROFILE_H
