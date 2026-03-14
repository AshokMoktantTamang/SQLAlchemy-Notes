/********************************************************************************
** Form generated from reading UI file 'aboutus.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTUS_H
#define UI_ABOUTUS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Aboutus
{
public:
    QAction *actionHome;
    QAction *actionexit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QToolBar *toolBar;

    void setupUi(QMainWindow *Aboutus)
    {
        if (Aboutus->objectName().isEmpty())
            Aboutus->setObjectName("Aboutus");
        Aboutus->resize(605, 398);
        Aboutus->setStyleSheet(QString::fromUtf8("background-color: rgb(16, 21, 36);\n"
""));
        actionHome = new QAction(Aboutus);
        actionHome->setObjectName("actionHome");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::GoHome));
        actionHome->setIcon(icon);
        actionHome->setMenuRole(QAction::MenuRole::NoRole);
        actionexit = new QAction(Aboutus);
        actionexit->setObjectName("actionexit");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit));
        actionexit->setIcon(icon1);
        actionexit->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(Aboutus);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1428, 485));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        Aboutus->setCentralWidget(centralwidget);
        toolBar = new QToolBar(Aboutus);
        toolBar->setObjectName("toolBar");
        Aboutus->addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolBar);

        toolBar->addAction(actionHome);
        toolBar->addAction(actionexit);

        retranslateUi(Aboutus);

        QMetaObject::connectSlotsByName(Aboutus);
    } // setupUi

    void retranslateUi(QMainWindow *Aboutus)
    {
        Aboutus->setWindowTitle(QCoreApplication::translate("Aboutus", "MainWindow", nullptr));
        actionHome->setText(QCoreApplication::translate("Aboutus", "Home", nullptr));
        actionexit->setText(QCoreApplication::translate("Aboutus", "exit", nullptr));
        label->setText(QCoreApplication::translate("Aboutus", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">About Us</span></p><p><span style=\" font-size:12pt;\">Welcome to Student Resource Hub, your one-stop destination for academic</span></p><p><span style=\" font-size:12pt;\">success! Our mission is to empower students by providing a comprehensive</span></p><p><span style=\" font-size:12pt;\">platform for accessing high-quality study resources. Whether you're preparing for</span></p><p><span style=\" font-size:12pt;\">exams, working on assignments, or exploring new topics, we've got you covered.</span></p><p><br/></p><p><span style=\" font-size:12pt;\">At Student Resource Hub, we understand the challenges students face in finding</span></p><p><span style=\" font-size:12pt;\">reliable and organized learning materials. That\342\200\231s why we\342\200\231ve created an intuitive</span></p><p><span style=\" font-size:12pt;\">app that brings together curated resources, study guides, and tools to enhance</span></p><p><span style=\" font-size:12pt;"
                        "\">your learning experience\342\200\224all in one place.</span></p><p><span style=\" font-size:12pt;\">Our core values include:</span></p><p><span style=\" font-size:12pt; font-weight:700;\">Accessibility</span><span style=\" font-size:12pt;\">: Knowledge should be available to everyone, anytime, anywhere.</span></p><p><span style=\" font-size:12pt; font-weight:700;\">Quality</span><span style=\" font-size:12pt;\">: We prioritize accurate, well-structured content to support your academic needs.</span></p><p><span style=\" font-size:12pt; font-weight:700;\">Community</span><span style=\" font-size:12pt;\">: Join a network of motivated learners who share your passion for growth and education.</span></p><p><span style=\" font-size:12pt;\">We\342\200\231re constantly working to improve and expand our offerings, ensuring that </span><span style=\" font-size:12pt; font-weight:700;\">Student Resource Hub</span><span style=\" font-size:12pt;\"> evolves alongside your educational journey. Together, let\342\200\231s unl"
                        "ock the potential of learning and make it an enjoyable adventure.</span></p></body></html>", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("Aboutus", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Aboutus: public Ui_Aboutus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTUS_H
