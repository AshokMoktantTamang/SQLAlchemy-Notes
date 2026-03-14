#ifndef CONTACTUS_H
#define CONTACTUS_H

#include <QMainWindow>

namespace Ui {
class Contactus;
}

class Contactus : public QMainWindow
{
    Q_OBJECT

public:
    explicit Contactus(QWidget *parent = nullptr);
    ~Contactus();

private slots:
    void on_actionexit_triggered();

    void on_actionHome_triggered();

    void on_pushButton_clicked();

private:
    Ui::Contactus *ui;
};

#endif // CONTACTUS_H
