/********************************************************************************
** Form generated from reading UI file 'profile.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILE_H
#define UI_PROFILE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_profile
{
public:
    QAction *actionExit;
    QAction *actionHome;
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *label_name;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLabel *label_phno;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_8;
    QLabel *label_username;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLabel *label_password;
    QLabel *label_prof_status;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QToolBar *toolBar;

    void setupUi(QMainWindow *profile)
    {
        if (profile->objectName().isEmpty())
            profile->setObjectName("profile");
        profile->resize(575, 385);
        profile->setStyleSheet(QString::fromUtf8("background-color: rgb(16, 21, 36);"));
        actionExit = new QAction(profile);
        actionExit->setObjectName("actionExit");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit));
        actionExit->setIcon(icon);
        actionExit->setMenuRole(QAction::MenuRole::NoRole);
        actionHome = new QAction(profile);
        actionHome->setObjectName("actionHome");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::GoHome));
        actionHome->setIcon(icon1);
        actionHome->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(profile);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(120, 30, 271, 241));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 15px;\n"
"    margin-top: 10px; \n"
"    background-color:rgb(255, 255, 255,0);\n"
"    padding: 5px;\n"
"}"));
        groupBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        QFont font;
        font.setBold(true);
        label_2->setFont(font);

        horizontalLayout->addWidget(label_2);

        label_name = new QLabel(groupBox);
        label_name->setObjectName("label_name");

        horizontalLayout->addWidget(label_name);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        QFont font1;
        font1.setBold(true);
        font1.setItalic(false);
        label_4->setFont(font1);

        horizontalLayout_2->addWidget(label_4);

        label_phno = new QLabel(groupBox);
        label_phno->setObjectName("label_phno");

        horizontalLayout_2->addWidget(label_phno);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setFont(font);

        horizontalLayout_4->addWidget(label_8);

        label_username = new QLabel(groupBox);
        label_username->setObjectName("label_username");

        horizontalLayout_4->addWidget(label_username);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setFont(font);

        horizontalLayout_3->addWidget(label_6);

        label_password = new QLabel(groupBox);
        label_password->setObjectName("label_password");

        horizontalLayout_3->addWidget(label_password);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(verticalLayout);

        label_prof_status = new QLabel(centralwidget);
        label_prof_status->setObjectName("label_prof_status");
        label_prof_status->setGeometry(QRect(10, 320, 111, 21));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(190, 280, 131, 71));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        pushButton->setFont(font);
        pushButton->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color:rgb(236, 0, 0);\n"
"    min-width: 10px; \n"
"    min-height: 10px; \n"
"    padding: 5px; \n"
"    margin: 0px; \n"
"}\n"
""));

        verticalLayout_3->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setFont(font);
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color:rgb(255, 255, 255,0);\n"
"    min-width: 10px; \n"
"    min-height: 10px; \n"
"    padding: 5px; \n"
"    margin: 0px; \n"
"}\n"
""));

        verticalLayout_3->addWidget(pushButton_2);

        profile->setCentralWidget(centralwidget);
        toolBar = new QToolBar(profile);
        toolBar->setObjectName("toolBar");
        profile->addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolBar);

        toolBar->addAction(actionHome);
        toolBar->addAction(actionExit);

        retranslateUi(profile);

        QMetaObject::connectSlotsByName(profile);
    } // setupUi

    void retranslateUi(QMainWindow *profile)
    {
        profile->setWindowTitle(QCoreApplication::translate("profile", "MainWindow", nullptr));
        actionExit->setText(QCoreApplication::translate("profile", "Exit", nullptr));
        actionHome->setText(QCoreApplication::translate("profile", "Home", nullptr));
        groupBox->setTitle(QCoreApplication::translate("profile", "Profile Information", nullptr));
        label_2->setText(QCoreApplication::translate("profile", "Name:", nullptr));
        label_name->setText(QString());
        label_4->setText(QCoreApplication::translate("profile", "Phone NO.:", nullptr));
        label_phno->setText(QString());
        label_8->setText(QCoreApplication::translate("profile", "EMAIL/ UserName:", nullptr));
        label_username->setText(QString());
        label_6->setText(QCoreApplication::translate("profile", "Password:", nullptr));
        label_password->setText(QString());
        label_prof_status->setText(QCoreApplication::translate("profile", "TextLabel", nullptr));
        pushButton->setText(QCoreApplication::translate("profile", "DELETE ACCOUNT", nullptr));
        pushButton_2->setText(QCoreApplication::translate("profile", "UPDATE INFO", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("profile", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class profile: public Ui_profile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILE_H
