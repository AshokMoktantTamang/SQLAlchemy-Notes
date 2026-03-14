#ifndef LANDINGPAGE_H
#define LANDINGPAGE_H

#include <QMainWindow>
#include"profile.h"
#include"aboutus.h"
#include"contactus.h"

#include <QWebSocketServer>
#include <QWebSocket>


namespace Ui {
class landingPage;
}

class landingPage : public QMainWindow
{
    Q_OBJECT
public:


public:
    explicit landingPage(QWidget *parent = nullptr);
    ~landingPage();

private slots:
    void on_actionExit_triggered();

    void on_actionContact_Us_triggered();

    void on_actionAbout_Us_triggered();

    void on_actionProfile_triggered();


    void on_actionSupport_triggered();



    void on_pushButton_upload_note_clicked();



    void on_pushButton_upload_assign_clicked();

    void on_pushButton_upload_slides_clicked();

    void on_pushButton_upolad_past_clicked();

    void on_pushButton_upload_other_clicked();

    void on_actionLogout_triggered();
    void onNewConnection();
    void onTextMessageReceived(const QString &message);

    void on_pushButton_download_notes_clicked();

    void on_pushButton_download_assign_clicked();

    void on_pushButton_download_slides_clicked();

    void on_pushButton_download_pastqn_clicked();

    void on_pushButton_download_others_clicked();

private:
    Ui::landingPage *ui;
    profile *prof;
    Aboutus *about;
    Contactus *contact;
    QWebSocketServer *webSocketServer;
    QList<QWebSocket *> clients;
};

#endif // LANDINGPAGE_H
