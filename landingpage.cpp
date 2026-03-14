#include "landingpage.h"
#include "ui_landingpage.h"
#include "QFileDialog"
#include<QDesktopServices>
#include<QUrl>
#include<QFileDialog>
#include<QDir>
#include<QApplication>
#include<QFile>
#include<QFileInfo>
#include<QMessageBox>
#include<QWidget>
#include<mainwindow.h>
#include<QWebSocketServer>
#include <QWebSocket>



landingPage::landingPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::landingPage)
    , webSocketServer(new QWebSocketServer(QStringLiteral("Upload Server"),
                                           QWebSocketServer::NonSecureMode, this))
{
    ui->setupUi(this);

    if (webSocketServer->listen(QHostAddress::Any, 12345)) {
        qDebug() << "WebSocket server started on port 12345";

        connect(webSocketServer, &QWebSocketServer::newConnection,
                this, &landingPage::onNewConnection);
    } else {
        qDebug() << "WebSocket server failed to start.";
    }

    QDir dir("C:/Project Qt/Study Materials/Notes");
    dir.setNameFilters(QStringList() << "*.txt" << "*.pdf" << "*.doc" <<"*.docx" <<"*.ppt" <<"*.pptx");
    foreach (QFileInfo var, dir.entryInfoList())
    {
        ui->listWidget->addItem(var.fileName());
    }

    QDir dir2("C:/Project Qt/Study Materials/Assignments");
    dir2.setNameFilters(QStringList() << "*.txt" << "*.pdf" << "*.doc" <<"*.docx" <<"*.ppt" <<"*.pptx");
    foreach (QFileInfo var, dir2.entryInfoList())
    {
        ui->listWidget_2->addItem(var.fileName());
    }

    QDir dir3("C:/Project Qt/Study Materials/Slides");
    dir3.setNameFilters(QStringList() << "*.txt" << "*.pdf" << "*.doc" <<"*.docx" <<"*.ppt" <<"*.pptx");
    foreach (QFileInfo var, dir3.entryInfoList())
    {
        ui->listWidget_slides->addItem(var.fileName());
    }

    QDir dir4("C:/Project Qt/Study Materials/Past Questions");
    dir4.setNameFilters(QStringList() << "*.txt" << "*.pdf" << "*.doc" <<"*.docx" <<"*.ppt" <<"*.pptx");
    foreach (QFileInfo var, dir4.entryInfoList())
    {
        ui->listWidget_past->addItem(var.fileName());
    }

    QDir dir5("C:/Project Qt/Study Materials/Others");
    dir5.setNameFilters(QStringList() << "*.txt" << "*.pdf" << "*.doc" <<"*.docx" <<"*.ppt" <<"*.pptx");
    foreach (QFileInfo var, dir5.entryInfoList())
    {
        ui->listWidget_others->addItem(var.fileName());
    }
}

landingPage::~landingPage()
{
    delete ui;
    webSocketServer->close();
    qDeleteAll(clients);

}

void landingPage::on_actionExit_triggered()
{
    QApplication::quit();
}


void landingPage::on_actionContact_Us_triggered()
{
    hide();
     contact = new Contactus(this);
    contact->show();
}


void landingPage::on_actionAbout_Us_triggered()
{
    hide();
    about = new Aboutus(this);
    about->show();
}





void landingPage::on_actionProfile_triggered()
{
    hide();
    prof = new profile(this);
    prof->show();
}




void landingPage::on_actionSupport_triggered()
{
    QString link="mailto:studentresourceshub00@gmail.com?subject=SUPPORT%20NEEDED";
    QDesktopServices::openUrl(QUrl(link));
}




void landingPage::on_pushButton_upload_note_clicked()
{
   QString file_name= QFileDialog::getOpenFileName(this,"Choose File","/","Text Files (*.txt);;PDF Files (*.pdf);;All Files (*.*) ;; WORD FILES (*.doc);; WORD FILES (*.docx);; PPT FILES (*.ppt) :: PPT FILES(*.pptx)");
    if(!file_name.isEmpty())
    {
         QString destinationDir = "C:/Project Qt/Study Materials/Notes";

        QFileInfo fileInfo(file_name);
        QString destinationFilePath = destinationDir + "/" + fileInfo.fileName();
        if (QFile::copy(file_name, destinationFilePath))
        {
            QMessageBox::information(this, "Success", "File uploaded successfully to: " + destinationFilePath);

            ui->listWidget->clear();
            QDir dir(destinationDir);
            dir.setNameFilters(QStringList() << "*.txt" << "*.pdf" << "*.doc" <<"*.docx" <<"*.ppt" <<"*.pptx");
            foreach (QFileInfo var, dir.entryInfoList()) {
                ui->listWidget->addItem(var.fileName());
            }

        }
        else
        {
            QMessageBox::warning(this, "Error", "Failed to upload the file.");
        }
    }
    else
    {
        QMessageBox::information(this, "No File Selected", "No file was selected for upload.");
    }
}





void landingPage::on_pushButton_upload_assign_clicked()
{
    QString file_name= QFileDialog::getOpenFileName(this,"Choose File","/","Text Files (*.txt);;PDF Files (*.pdf);;All Files (*.*) ;; WORD FILES (*.doc);; WORD FILES (*.docx);; PPT FILES (*.ppt) :: PPT FILES(*.pptx)");
    if(!file_name.isEmpty())
    {
        QString destinationDir = "C:/Project Qt/Study Materials/Assignments";

        QFileInfo fileInfo(file_name);
        QString destinationFilePath = destinationDir + "/" + fileInfo.fileName();
        if (QFile::copy(file_name, destinationFilePath))
        {
            QMessageBox::information(this, "Success", "File uploaded successfully to: " + destinationFilePath);

            ui->listWidget_2->clear();
            QDir dir(destinationDir);
            dir.setNameFilters(QStringList()<< "*.txt" << "*.pdf" << "*.doc" <<"*.docx" <<"*.ppt" <<"*.pptx");
            foreach (QFileInfo var, dir.entryInfoList()) {
                ui->listWidget_2->addItem(var.fileName());
            }

        }
        else
        {
            QMessageBox::warning(this, "Error", "Failed to upload the file.");
        }
    }
    else
    {
        QMessageBox::information(this, "No File Selected", "No file was selected for upload.");
    }
}


void landingPage::on_pushButton_upload_slides_clicked()
{
    QString file_name= QFileDialog::getOpenFileName(this,"Choose File","/","Text Files (*.txt);;PDF Files (*.pdf);;All Files (*.*) ;; WORD FILES (*.doc);; WORD FILES (*.docx);; PPT FILES (*.ppt) :: PPT FILES(*.pptx)");
    if(!file_name.isEmpty())
    {
        QString destinationDir = "C:/Project Qt/Study Materials/Slides";

        QFileInfo fileInfo(file_name);
        QString destinationFilePath = destinationDir + "/" + fileInfo.fileName();
        if (QFile::copy(file_name, destinationFilePath))
        {
            QMessageBox::information(this, "Success", "File uploaded successfully to: " + destinationFilePath);

            ui->listWidget_slides->clear();
            QDir dir(destinationDir);
            dir.setNameFilters(QStringList() << "*.txt" << "*.pdf" << "*.doc" <<"*.docx" <<"*.ppt" <<"*.pptx");
            foreach (QFileInfo var, dir.entryInfoList()) {
                ui->listWidget_slides->addItem(var.fileName());
            }

        }
        else
        {
            QMessageBox::warning(this, "Error", "Failed to upload the file.");
        }
    }
    else
    {
        QMessageBox::information(this, "No File Selected", "No file was selected for upload.");
    }
}


void landingPage::on_pushButton_upolad_past_clicked()
{
   QString file_name= QFileDialog::getOpenFileName(this,"Choose File","/","Text Files (*.txt);;PDF Files (*.pdf);;All Files (*.*) ;; WORD FILES (*.doc);; WORD FILES (*.docx);; PPT FILES (*.ppt) :: PPT FILES(*.pptx)");
    if(!file_name.isEmpty())
    {
        QString destinationDir = "C:/Project Qt/Study Materials/Past Questions";

        QFileInfo fileInfo(file_name);
        QString destinationFilePath = destinationDir + "/" + fileInfo.fileName();
        if (QFile::copy(file_name, destinationFilePath))
        {
            QMessageBox::information(this, "Success", "File uploaded successfully to: " + destinationFilePath);

            ui->listWidget_past->clear();
            QDir dir(destinationDir);
            dir.setNameFilters(QStringList() << "*.txt" << "*.pdf" << "*.doc" <<"*.docx" <<"*.ppt" <<"*.pptx");
            foreach (QFileInfo var, dir.entryInfoList()) {
                ui->listWidget_past->addItem(var.fileName());
            }

        }
        else
        {
            QMessageBox::warning(this, "Error", "Failed to upload the file.");
        }
    }
    else
    {
        QMessageBox::information(this, "No File Selected", "No file was selected for upload.");
    }
}


void landingPage::on_pushButton_upload_other_clicked()
{
    QString file_name= QFileDialog::getOpenFileName(this,"Choose File","/","Text Files (*.txt);;PDF Files (*.pdf);;All Files (*.*) ;; WORD FILES (*.doc);; WORD FILES (*.docx);; PPT FILES (*.ppt) :: PPT FILES(*.pptx)");
    if(!file_name.isEmpty())
    {
        QString destinationDir = "C:/Project Qt/Study Materials/Others";

        QFileInfo fileInfo(file_name);
        QString destinationFilePath = destinationDir + "/" + fileInfo.fileName();
        if (QFile::copy(file_name, destinationFilePath))
        {
            QMessageBox::information(this, "Success", "File uploaded successfully to: " + destinationFilePath);

            ui->listWidget_others->clear();
            QDir dir(destinationDir);
            dir.setNameFilters(QStringList() << "*.txt" << "*.pdf" << "*.doc" <<"*.docx" <<"*.ppt" <<"*.pptx");
            foreach (QFileInfo var, dir.entryInfoList()) {
                ui->listWidget_others->addItem(var.fileName());
            }

        }
        else
        {
            QMessageBox::warning(this, "Error", "Failed to upload the file.");
        }
    }
    else
    {
        QMessageBox::information(this, "No File Selected", "No file was selected for upload.");
    }
}


void landingPage::on_actionLogout_triggered()
{
    hide();
    MainWindow *logout = new MainWindow(this);
    logout->show();
}

void landingPage::onNewConnection()
{
    QWebSocket *clientSocket = webSocketServer->nextPendingConnection();

    connect(clientSocket, &QWebSocket::textMessageReceived,
            this, &landingPage::onTextMessageReceived);
    connect(clientSocket, &QWebSocket::disconnected, [this, clientSocket]() {
        clients.removeAll(clientSocket);
        clientSocket->deleteLater();
    });

    clients.append(clientSocket);
    qDebug() << "New client connected.";
}

void landingPage::onTextMessageReceived(const QString &message)
{
    qDebug() << "Message received from client:" << message;


    for (QWebSocket *client : clients) {
        client->sendTextMessage("Server received: " + message);
    }
}

void landingPage::on_pushButton_download_notes_clicked()
{

    QListWidgetItem *selectedItem = ui->listWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "No file selected for download.");
        return;
    }

    QString fileName = selectedItem->text();
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Invalid file name.");
        return;
    }


    QString sourceFilePath = QDir::cleanPath("C:/Project Qt/Study Materials/Notes/" + fileName);
    if (!QFile::exists(sourceFilePath)) {
        QMessageBox::warning(this, "Error", "The selected file does not exist in the source directory.");
        return;
    }


    QString destinationFilePath = QFileDialog::getSaveFileName(this, "Save File As", fileName, "All Files (*.*)");
    if (destinationFilePath.isEmpty()) {
        QMessageBox::information(this, "No Destination Selected", "Please select a destination to save the file.");
        return;
    }


    if (QFile::exists(destinationFilePath)) {
        if (!QFile::remove(destinationFilePath)) {
            QMessageBox::warning(this, "Error", "Failed to overwrite the existing file.");
            return;
        }
    }


    if (QFile::copy(sourceFilePath, destinationFilePath)) {
        QMessageBox::information(this, "Success", "File downloaded successfully to: " + destinationFilePath);
    } else {
        QMessageBox::warning(this, "Error", "Failed to download the file.");
    }
}


void landingPage::on_pushButton_download_assign_clicked()
{
    QListWidgetItem *selectedItem = ui->listWidget_2->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "No file selected for download.");
        return;
    }

    QString fileName = selectedItem->text();
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Invalid file name.");
        return;
    }


    QString sourceFilePath = QDir::cleanPath("C:/Project Qt/Study Materials/Assignments/" + fileName);
    if (!QFile::exists(sourceFilePath)) {
        QMessageBox::warning(this, "Error", "The selected file does not exist in the source directory.");
        return;
    }


    QString destinationFilePath = QFileDialog::getSaveFileName(this, "Save File As", fileName, "All Files (*.*)");
    if (destinationFilePath.isEmpty()) {
        QMessageBox::information(this, "No Destination Selected", "Please select a destination to save the file.");
        return;
    }


    if (QFile::exists(destinationFilePath)) {
 if (!QFile::remove(destinationFilePath)) {
        QMessageBox::warning(this, "Error", "Failed to overwrite the existing file.");
        return;
    }
    }


    if (QFile::copy(sourceFilePath, destinationFilePath)) {
        QMessageBox::information(this, "Success", "File downloaded successfully to: " + destinationFilePath);
    } else {
        QMessageBox::warning(this, "Error", "Failed to download the file.");
    }
}


void landingPage::on_pushButton_download_slides_clicked()
{
    QListWidgetItem *selectedItem = ui->listWidget_slides->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "No file selected for download.");
        return;
    }

    QString fileName = selectedItem->text();
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Invalid file name.");
        return;
    }


    QString sourceFilePath = QDir::cleanPath("C:/Project Qt/Study Materials/Slides/" + fileName);
    if (!QFile::exists(sourceFilePath)) {
        QMessageBox::warning(this, "Error", "The selected file does not exist in the source directory.");
        return;
    }


    QString destinationFilePath = QFileDialog::getSaveFileName(this, "Save File As", fileName, "All Files (*.*)");
    if (destinationFilePath.isEmpty()) {
        QMessageBox::information(this, "No Destination Selected", "Please select a destination to save the file.");
        return;
    }


    if (QFile::exists(destinationFilePath)) {
 if (!QFile::remove(destinationFilePath)) {
        QMessageBox::warning(this, "Error", "Failed to overwrite the existing file.");
        return;
    }
    }


    if (QFile::copy(sourceFilePath, destinationFilePath)) {
        QMessageBox::information(this, "Success", "File downloaded successfully to: " + destinationFilePath);
    } else {
        QMessageBox::warning(this, "Error", "Failed to download the file.");
    }
}


void landingPage::on_pushButton_download_pastqn_clicked()
{
    QListWidgetItem *selectedItem = ui->listWidget_past->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "No file selected for download.");
        return;
    }

    QString fileName = selectedItem->text();
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Invalid file name.");
        return;
    }


    QString sourceFilePath = QDir::cleanPath("C:/Project Qt/Study Materials/Past Questions/" + fileName);
    if (!QFile::exists(sourceFilePath)) {
        QMessageBox::warning(this, "Error", "The selected file does not exist in the source directory.");
        return;
    }


    QString destinationFilePath = QFileDialog::getSaveFileName(this, "Save File As", fileName, "All Files (*.*)");
    if (destinationFilePath.isEmpty()) {
        QMessageBox::information(this, "No Destination Selected", "Please select a destination to save the file.");
        return;
    }


    if (QFile::exists(destinationFilePath)) {
 if (!QFile::remove(destinationFilePath)) {
        QMessageBox::warning(this, "Error", "Failed to overwrite the existing file.");
        return;
    }
    }


    if (QFile::copy(sourceFilePath, destinationFilePath)) {
        QMessageBox::information(this, "Success", "File downloaded successfully to: " + destinationFilePath);
    } else {
        QMessageBox::warning(this, "Error", "Failed to download the file.");
    }
}


void landingPage::on_pushButton_download_others_clicked()
{
    QListWidgetItem *selectedItem = ui->listWidget_others->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "No file selected for download.");
        return;
    }

    QString fileName = selectedItem->text();
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Invalid file name.");
        return;
    }


    QString sourceFilePath = QDir::cleanPath("C:/Project Qt/Study Materials/others/" + fileName);
    if (!QFile::exists(sourceFilePath)) {
        QMessageBox::warning(this, "Error", "The selected file does not exist in the source directory.");
        return;
    }


    QString destinationFilePath = QFileDialog::getSaveFileName(this, "Save File As", fileName, "All Files (*.*)");
    if (destinationFilePath.isEmpty()) {
        QMessageBox::information(this, "No Destination Selected", "Please select a destination to save the file.");
        return;
    }


    if (QFile::exists(destinationFilePath)) {
        if (!QFile::remove(destinationFilePath)) {
            QMessageBox::warning(this, "Error", "Failed to overwrite the existing file.");
            return;
        }
    }


    if (QFile::copy(sourceFilePath, destinationFilePath)) {
        QMessageBox::information(this, "Success", "File downloaded successfully to: " + destinationFilePath);
    } else {
        QMessageBox::warning(this, "Error", "Failed to download the file.");
    }
}

