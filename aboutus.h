#ifndef ABOUTUS_H
#define ABOUTUS_H

#include <QMainWindow>

namespace Ui {
class Aboutus;
}

class Aboutus : public QMainWindow
{
    Q_OBJECT

public:
    explicit Aboutus(QWidget *parent = nullptr);
    ~Aboutus();

private slots:
    void on_actionexit_triggered();

    void on_actionHome_triggered();

    void on_label_3_linkActivated(const QString &link);

private:
    Ui::Aboutus *ui;
};

#endif // ABOUTUS_H
