/********************************************************************************
** Form generated from reading UI file 'contactus.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTACTUS_H
#define UI_CONTACTUS_H

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

class Ui_Contactus
{
public:
    QAction *actionHome;
    QAction *actionexit;
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLabel *label_2;
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QToolBar *toolBar;

    void setupUi(QMainWindow *Contactus)
    {
        if (Contactus->objectName().isEmpty())
            Contactus->setObjectName("Contactus");
        Contactus->resize(559, 368);
        Contactus->setStyleSheet(QString::fromUtf8("background-color: rgb(16, 21, 36);\n"
""));
        actionHome = new QAction(Contactus);
        actionHome->setObjectName("actionHome");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::GoHome));
        actionHome->setIcon(icon);
        actionHome->setMenuRole(QAction::MenuRole::NoRole);
        actionexit = new QAction(Contactus);
        actionexit->setObjectName("actionexit");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit));
        actionexit->setIcon(icon1);
        actionexit->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(Contactus);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(70, 100, 351, 161));
        QFont font;
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
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        label_3->setFont(font1);

        horizontalLayout_2->addWidget(label_3);

        label = new QLabel(groupBox);
        label->setObjectName("label");
        QFont font2;
        font2.setPointSize(10);
        label->setFont(font2);

        horizontalLayout_2->addWidget(label);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setFont(font1);

        horizontalLayout_3->addWidget(label_4);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setFont(font2);

        horizontalLayout_3->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(verticalLayout);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setFont(font);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color:rgb(255, 255, 255,0);\n"
"    min-width: 10px; \n"
"    min-height: 10px; \n"
"    padding: 5px; \n"
"    margin: 0px; \n"
"}\n"
""));

        verticalLayout_2->addWidget(pushButton);

        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Contactus->setCentralWidget(centralwidget);
        toolBar = new QToolBar(Contactus);
        toolBar->setObjectName("toolBar");
        Contactus->addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolBar);

        toolBar->addAction(actionHome);
        toolBar->addAction(actionexit);

        retranslateUi(Contactus);

        QMetaObject::connectSlotsByName(Contactus);
    } // setupUi

    void retranslateUi(QMainWindow *Contactus)
    {
        Contactus->setWindowTitle(QCoreApplication::translate("Contactus", "MainWindow", nullptr));
        actionHome->setText(QCoreApplication::translate("Contactus", "Home", nullptr));
        actionexit->setText(QCoreApplication::translate("Contactus", "exit", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Contactus", "CONTACT US", nullptr));
        label_3->setText(QCoreApplication::translate("Contactus", "Contact No.    :", nullptr));
        label->setText(QCoreApplication::translate("Contactus", "+977-98197811156", nullptr));
        label_4->setText(QCoreApplication::translate("Contactus", "Email Address :", nullptr));
        label_2->setText(QCoreApplication::translate("Contactus", "studentresourceshub00@gmail.com", nullptr));
        pushButton->setText(QCoreApplication::translate("Contactus", "Email Us", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("Contactus", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Contactus: public Ui_Contactus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTACTUS_H
