#ifndef TERMSNCOND_H
#define TERMSNCOND_H

#include <QMainWindow>

namespace Ui {
class termsncond;
}

class termsncond : public QMainWindow
{
    Q_OBJECT

public:
    explicit termsncond(QWidget *parent = nullptr);
    ~termsncond();

private slots:
    void on_pushButton_clicked();

private:
    Ui::termsncond *ui;
};

#endif // TERMSNCOND_H
