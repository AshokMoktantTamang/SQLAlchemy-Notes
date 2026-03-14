#ifndef UPDATEINFO_H
#define UPDATEINFO_H

#include <QMainWindow>

namespace Ui {
class updateinfo;
}

class updateinfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit updateinfo(QWidget *parent = nullptr);
    ~updateinfo();

private slots:
    void on_actionExit_triggered();

    void on_actionHome_triggered();

    void on_pushButton_2_clicked();

private:
    Ui::updateinfo *ui;
};

#endif // UPDATEINFO_H
