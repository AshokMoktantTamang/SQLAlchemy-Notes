/********************************************************************************
** Form generated from reading UI file 'landingpage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LANDINGPAGE_H
#define UI_LANDINGPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_landingPage
{
public:
    QAction *actionHome;
    QAction *actionProfile;
    QAction *actionAbout_Us;
    QAction *actionContact_Us;
    QAction *actionExit;
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *landingPage)
    {
        if (landingPage->objectName().isEmpty())
            landingPage->setObjectName("landingPage");
        landingPage->resize(519, 364);
        landingPage->setStyleSheet(QString::fromUtf8("background-color: rgb(16, 21, 36);\n"
""));
        actionHome = new QAction(landingPage);
        actionHome->setObjectName("actionHome");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::GoHome));
        actionHome->setIcon(icon);
        actionHome->setMenuRole(QAction::MenuRole::NoRole);
        actionProfile = new QAction(landingPage);
        actionProfile->setObjectName("actionProfile");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::CameraWeb));
        actionProfile->setIcon(icon1);
        actionProfile->setMenuRole(QAction::MenuRole::NoRole);
        actionAbout_Us = new QAction(landingPage);
        actionAbout_Us->setObjectName("actionAbout_Us");
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::DialogInformation));
        actionAbout_Us->setIcon(icon2);
        actionAbout_Us->setMenuRole(QAction::MenuRole::NoRole);
        actionContact_Us = new QAction(landingPage);
        actionContact_Us->setObjectName("actionContact_Us");
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::CallStart));
        actionContact_Us->setIcon(icon3);
        actionContact_Us->setMenuRole(QAction::MenuRole::NoRole);
        actionExit = new QAction(landingPage);
        actionExit->setObjectName("actionExit");
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::WindowClose));
        actionExit->setIcon(icon4);
        actionExit->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(landingPage);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 30, 101, 61));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(120, 30, 101, 61));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(340, 30, 101, 61));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(230, 30, 101, 61));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(350, 290, 101, 41));
        landingPage->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(landingPage);
        statusbar->setObjectName("statusbar");
        landingPage->setStatusBar(statusbar);
        toolBar = new QToolBar(landingPage);
        toolBar->setObjectName("toolBar");
        landingPage->addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolBar);

        toolBar->addAction(actionHome);
        toolBar->addAction(actionProfile);
        toolBar->addAction(actionAbout_Us);
        toolBar->addAction(actionContact_Us);
        toolBar->addAction(actionExit);

        retranslateUi(landingPage);

        QMetaObject::connectSlotsByName(landingPage);
    } // setupUi

    void retranslateUi(QMainWindow *landingPage)
    {
        landingPage->setWindowTitle(QCoreApplication::translate("landingPage", "MainWindow", nullptr));
        actionHome->setText(QCoreApplication::translate("landingPage", "Home", nullptr));
        actionProfile->setText(QCoreApplication::translate("landingPage", "Profile", nullptr));
        actionAbout_Us->setText(QCoreApplication::translate("landingPage", "About Us", nullptr));
        actionContact_Us->setText(QCoreApplication::translate("landingPage", "Contact Us", nullptr));
        actionExit->setText(QCoreApplication::translate("landingPage", "Exit", nullptr));
        pushButton->setText(QCoreApplication::translate("landingPage", "Notes", nullptr));
        pushButton_2->setText(QCoreApplication::translate("landingPage", "Slides", nullptr));
        pushButton_3->setText(QCoreApplication::translate("landingPage", "Past Questions", nullptr));
        pushButton_4->setText(QCoreApplication::translate("landingPage", "Assignments", nullptr));
        pushButton_5->setText(QCoreApplication::translate("landingPage", "Upload", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("landingPage", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class landingPage: public Ui_landingPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LANDINGPAGE_H
