/********************************************************************************
** Form generated from reading UI file 'updateinfo.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEINFO_H
#define UI_UPDATEINFO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_updateinfo
{
public:
    QAction *actionHome;
    QAction *actionExit;
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_name;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *lineEdit_phno1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_create_email;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_create_password;
    QPushButton *pushButton_2;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *updateinfo)
    {
        if (updateinfo->objectName().isEmpty())
            updateinfo->setObjectName("updateinfo");
        updateinfo->resize(577, 377);
        updateinfo->setStyleSheet(QString::fromUtf8("background-color: rgb(16, 21, 36);"));
        actionHome = new QAction(updateinfo);
        actionHome->setObjectName("actionHome");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::GoHome));
        actionHome->setIcon(icon);
        actionHome->setMenuRole(QAction::MenuRole::NoRole);
        actionExit = new QAction(updateinfo);
        actionExit->setObjectName("actionExit");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit));
        actionExit->setIcon(icon1);
        actionExit->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(updateinfo);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(100, 30, 321, 281));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        groupBox->setFont(font);
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 15px;\n"
"    margin-top: 10px; \n"
"    background-color:rgb(255, 255, 255,0);\n"
"    padding: 5px;\n"
"}"));
        groupBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        label->setFont(font1);

        horizontalLayout->addWidget(label);

        lineEdit_name = new QLineEdit(groupBox);
        lineEdit_name->setObjectName("lineEdit_name");
        lineEdit_name->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color: rgb(255, 255, 255,0);\n"
"    min-width: 8px; \n"
"    min-height: 8px;\n"
"    padding: 5px;\n"
"    margin: 0px;\n"
"}\n"
""));

        horizontalLayout->addWidget(lineEdit_name);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setFont(font1);

        horizontalLayout_5->addWidget(label_4);

        lineEdit_phno1 = new QLineEdit(groupBox);
        lineEdit_phno1->setObjectName("lineEdit_phno1");
        lineEdit_phno1->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color: rgb(255, 255, 255,0);\n"
"    min-width: 8px; \n"
"    min-height: 8px;\n"
"    padding: 5px;\n"
"    margin: 0px;\n"
"}\n"
""));

        horizontalLayout_5->addWidget(lineEdit_phno1);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setFont(font1);

        horizontalLayout_2->addWidget(label_2);

        lineEdit_create_email = new QLineEdit(groupBox);
        lineEdit_create_email->setObjectName("lineEdit_create_email");
        lineEdit_create_email->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color: rgb(255, 255, 255,0);\n"
"    min-width: 8px; \n"
"    min-height: 8px;\n"
"    padding: 5px;\n"
"    margin: 0px;\n"
"}\n"
""));

        horizontalLayout_2->addWidget(lineEdit_create_email);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setFont(font1);

        horizontalLayout_3->addWidget(label_3);

        lineEdit_create_password = new QLineEdit(groupBox);
        lineEdit_create_password->setObjectName("lineEdit_create_password");
        lineEdit_create_password->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color: rgb(255, 255, 255,0);\n"
"    min-width: 8px; \n"
"    min-height: 8px;\n"
"    padding: 5px;\n"
"    margin: 0px;\n"
"}\n"
""));
        lineEdit_create_password->setEchoMode(QLineEdit::EchoMode::PasswordEchoOnEdit);

        horizontalLayout_3->addWidget(lineEdit_create_password);


        verticalLayout->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        QFont font2;
        font2.setBold(true);
        pushButton_2->setFont(font2);
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

        gridLayout->addWidget(pushButton_2, 1, 0, 1, 1);

        updateinfo->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(updateinfo);
        statusbar->setObjectName("statusbar");
        updateinfo->setStatusBar(statusbar);
        toolBar = new QToolBar(updateinfo);
        toolBar->setObjectName("toolBar");
        updateinfo->addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolBar);

        toolBar->addAction(actionHome);
        toolBar->addAction(actionExit);

        retranslateUi(updateinfo);

        QMetaObject::connectSlotsByName(updateinfo);
    } // setupUi

    void retranslateUi(QMainWindow *updateinfo)
    {
        updateinfo->setWindowTitle(QCoreApplication::translate("updateinfo", "MainWindow", nullptr));
        actionHome->setText(QCoreApplication::translate("updateinfo", "Home", nullptr));
        actionExit->setText(QCoreApplication::translate("updateinfo", "Exit", nullptr));
        groupBox->setTitle(QCoreApplication::translate("updateinfo", "UPDATE INFO", nullptr));
        label->setText(QCoreApplication::translate("updateinfo", "Name", nullptr));
        label_4->setText(QCoreApplication::translate("updateinfo", "Phone No.", nullptr));
        label_2->setText(QCoreApplication::translate("updateinfo", "Email", nullptr));
        label_3->setText(QCoreApplication::translate("updateinfo", "Password", nullptr));
        pushButton_2->setText(QCoreApplication::translate("updateinfo", "UPDATE INFO", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("updateinfo", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class updateinfo: public Ui_updateinfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEINFO_H
