/********************************************************************************
** Form generated from reading UI file 'landingpage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LANDINGPAGE_H
#define UI_LANDINGPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_landingPage
{
public:
    QAction *actionProfile;
    QAction *actionAbout_Us;
    QAction *actionContact_Us;
    QAction *actionExit;
    QAction *actionSupport;
    QAction *actionLogout;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_upload_note;
    QPushButton *pushButton_download_notes;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QListWidget *listWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_upload_assign;
    QPushButton *pushButton_download_assign;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QListWidget *listWidget_slides;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_upload_slides;
    QPushButton *pushButton_download_slides;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_8;
    QListWidget *listWidget_past;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_upolad_past;
    QPushButton *pushButton_download_pastqn;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *verticalLayout_10;
    QListWidget *listWidget_others;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_upload_other;
    QPushButton *pushButton_download_others;
    QToolBar *toolBar;

    void setupUi(QMainWindow *landingPage)
    {
        if (landingPage->objectName().isEmpty())
            landingPage->setObjectName("landingPage");
        landingPage->resize(638, 415);
        landingPage->setStyleSheet(QString::fromUtf8("background-color: rgb(16, 21, 36);\n"
""));
        actionProfile = new QAction(landingPage);
        actionProfile->setObjectName("actionProfile");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::CameraWeb));
        actionProfile->setIcon(icon);
        actionProfile->setMenuRole(QAction::MenuRole::NoRole);
        actionAbout_Us = new QAction(landingPage);
        actionAbout_Us->setObjectName("actionAbout_Us");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::DialogInformation));
        actionAbout_Us->setIcon(icon1);
        actionAbout_Us->setMenuRole(QAction::MenuRole::NoRole);
        actionContact_Us = new QAction(landingPage);
        actionContact_Us->setObjectName("actionContact_Us");
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::Phone));
        actionContact_Us->setIcon(icon2);
        actionContact_Us->setMenuRole(QAction::MenuRole::NoRole);
        actionExit = new QAction(landingPage);
        actionExit->setObjectName("actionExit");
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::WindowClose));
        actionExit->setIcon(icon3);
        actionExit->setMenuRole(QAction::MenuRole::NoRole);
        actionSupport = new QAction(landingPage);
        actionSupport->setObjectName("actionSupport");
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::DocumentProperties));
        actionSupport->setIcon(icon4);
        actionSupport->setMenuRole(QAction::MenuRole::NoRole);
        actionLogout = new QAction(landingPage);
        actionLogout->setObjectName("actionLogout");
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::SystemLogOut));
        actionLogout->setIcon(icon5);
        actionLogout->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(landingPage);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        QFont font;
        font.setBold(true);
        tabWidget->setFont(font);
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        tabWidget->setTabPosition(QTabWidget::TabPosition::North);
        tabWidget->setTabShape(QTabWidget::TabShape::Rounded);
        tabWidget->setIconSize(QSize(16, 16));
        tabWidget->setElideMode(Qt::TextElideMode::ElideNone);
        tabWidget->setMovable(true);
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout_3 = new QVBoxLayout(tab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        listWidget = new QListWidget(tab);
        listWidget->setObjectName("listWidget");

        verticalLayout_2->addWidget(listWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton_upload_note = new QPushButton(tab);
        pushButton_upload_note->setObjectName("pushButton_upload_note");
        pushButton_upload_note->setFont(font);
        pushButton_upload_note->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color:rgb(255, 255, 255,0);\n"
"    min-width: 10px; \n"
"    min-height: 10px; \n"
"    padding: 5px; \n"
"    margin: 0px; \n"
"}\n"
""));

        horizontalLayout_2->addWidget(pushButton_upload_note);

        pushButton_download_notes = new QPushButton(tab);
        pushButton_download_notes->setObjectName("pushButton_download_notes");
        pushButton_download_notes->setFont(font);
        pushButton_download_notes->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color:rgb(255, 255, 255,0);\n"
"    min-width: 10px; \n"
"    min-height: 10px; \n"
"    padding: 5px; \n"
"    margin: 0px; \n"
"}\n"
""));

        horizontalLayout_2->addWidget(pushButton_download_notes);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_3->addLayout(verticalLayout_2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayout_5 = new QVBoxLayout(tab_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        listWidget_2 = new QListWidget(tab_2);
        listWidget_2->setObjectName("listWidget_2");

        verticalLayout_4->addWidget(listWidget_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_upload_assign = new QPushButton(tab_2);
        pushButton_upload_assign->setObjectName("pushButton_upload_assign");
        pushButton_upload_assign->setFont(font);
        pushButton_upload_assign->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color:rgb(255, 255, 255,0);\n"
"    min-width: 10px; \n"
"    min-height: 10px; \n"
"    padding: 5px; \n"
"    margin: 0px; \n"
"}\n"
""));

        horizontalLayout_3->addWidget(pushButton_upload_assign);

        pushButton_download_assign = new QPushButton(tab_2);
        pushButton_download_assign->setObjectName("pushButton_download_assign");
        pushButton_download_assign->setFont(font);
        pushButton_download_assign->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color:rgb(255, 255, 255,0);\n"
"    min-width: 10px; \n"
"    min-height: 10px; \n"
"    padding: 5px; \n"
"    margin: 0px; \n"
"}\n"
""));

        horizontalLayout_3->addWidget(pushButton_download_assign);


        verticalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_5->addLayout(verticalLayout_4);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        verticalLayout_7 = new QVBoxLayout(tab_3);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        listWidget_slides = new QListWidget(tab_3);
        listWidget_slides->setObjectName("listWidget_slides");

        verticalLayout_6->addWidget(listWidget_slides);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        pushButton_upload_slides = new QPushButton(tab_3);
        pushButton_upload_slides->setObjectName("pushButton_upload_slides");
        pushButton_upload_slides->setFont(font);
        pushButton_upload_slides->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color:rgb(255, 255, 255,0);\n"
"    min-width: 10px; \n"
"    min-height: 10px; \n"
"    padding: 5px; \n"
"    margin: 0px; \n"
"}\n"
""));

        horizontalLayout_4->addWidget(pushButton_upload_slides);

        pushButton_download_slides = new QPushButton(tab_3);
        pushButton_download_slides->setObjectName("pushButton_download_slides");
        pushButton_download_slides->setFont(font);
        pushButton_download_slides->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color:rgb(255, 255, 255,0);\n"
"    min-width: 10px; \n"
"    min-height: 10px; \n"
"    padding: 5px; \n"
"    margin: 0px; \n"
"}\n"
""));

        horizontalLayout_4->addWidget(pushButton_download_slides);


        verticalLayout_6->addLayout(horizontalLayout_4);


        verticalLayout_7->addLayout(verticalLayout_6);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        verticalLayout_9 = new QVBoxLayout(tab_4);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        listWidget_past = new QListWidget(tab_4);
        listWidget_past->setObjectName("listWidget_past");

        verticalLayout_8->addWidget(listWidget_past);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_upolad_past = new QPushButton(tab_4);
        pushButton_upolad_past->setObjectName("pushButton_upolad_past");
        pushButton_upolad_past->setFont(font);
        pushButton_upolad_past->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color:rgb(255, 255, 255,0);\n"
"    min-width: 10px; \n"
"    min-height: 10px; \n"
"    padding: 5px; \n"
"    margin: 0px; \n"
"}\n"
""));

        horizontalLayout->addWidget(pushButton_upolad_past);

        pushButton_download_pastqn = new QPushButton(tab_4);
        pushButton_download_pastqn->setObjectName("pushButton_download_pastqn");
        pushButton_download_pastqn->setFont(font);
        pushButton_download_pastqn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color:rgb(255, 255, 255,0);\n"
"    min-width: 10px; \n"
"    min-height: 10px; \n"
"    padding: 5px; \n"
"    margin: 0px; \n"
"}\n"
""));

        horizontalLayout->addWidget(pushButton_download_pastqn);


        verticalLayout_8->addLayout(horizontalLayout);


        verticalLayout_9->addLayout(verticalLayout_8);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        verticalLayout_11 = new QVBoxLayout(tab_5);
        verticalLayout_11->setObjectName("verticalLayout_11");
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName("verticalLayout_10");
        listWidget_others = new QListWidget(tab_5);
        listWidget_others->setObjectName("listWidget_others");

        verticalLayout_10->addWidget(listWidget_others);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        pushButton_upload_other = new QPushButton(tab_5);
        pushButton_upload_other->setObjectName("pushButton_upload_other");
        pushButton_upload_other->setFont(font);
        pushButton_upload_other->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color:rgb(255, 255, 255,0);\n"
"    min-width: 10px; \n"
"    min-height: 10px; \n"
"    padding: 5px; \n"
"    margin: 0px; \n"
"}\n"
""));

        horizontalLayout_5->addWidget(pushButton_upload_other);

        pushButton_download_others = new QPushButton(tab_5);
        pushButton_download_others->setObjectName("pushButton_download_others");
        pushButton_download_others->setFont(font);
        pushButton_download_others->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color:rgb(255, 255, 255,0);\n"
"    min-width: 10px; \n"
"    min-height: 10px; \n"
"    padding: 5px; \n"
"    margin: 0px; \n"
"}\n"
""));

        horizontalLayout_5->addWidget(pushButton_download_others);


        verticalLayout_10->addLayout(horizontalLayout_5);


        verticalLayout_11->addLayout(verticalLayout_10);

        tabWidget->addTab(tab_5, QString());

        verticalLayout->addWidget(tabWidget);

        landingPage->setCentralWidget(centralwidget);
        toolBar = new QToolBar(landingPage);
        toolBar->setObjectName("toolBar");
        landingPage->addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolBar);

        toolBar->addAction(actionProfile);
        toolBar->addAction(actionAbout_Us);
        toolBar->addAction(actionContact_Us);
        toolBar->addAction(actionSupport);
        toolBar->addAction(actionExit);
        toolBar->addSeparator();
        toolBar->addAction(actionLogout);

        retranslateUi(landingPage);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(landingPage);
    } // setupUi

    void retranslateUi(QMainWindow *landingPage)
    {
        landingPage->setWindowTitle(QCoreApplication::translate("landingPage", "MainWindow", nullptr));
        actionProfile->setText(QCoreApplication::translate("landingPage", "Profile", nullptr));
        actionAbout_Us->setText(QCoreApplication::translate("landingPage", "About Us", nullptr));
        actionContact_Us->setText(QCoreApplication::translate("landingPage", "Contact Us", nullptr));
        actionExit->setText(QCoreApplication::translate("landingPage", "Exit", nullptr));
        actionSupport->setText(QCoreApplication::translate("landingPage", "Support", nullptr));
        actionLogout->setText(QCoreApplication::translate("landingPage", "Logout", nullptr));
        pushButton_upload_note->setText(QCoreApplication::translate("landingPage", "Upload", nullptr));
        pushButton_download_notes->setText(QCoreApplication::translate("landingPage", "Download", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("landingPage", "Notes", nullptr));
#if QT_CONFIG(tooltip)
        tabWidget->setTabToolTip(tabWidget->indexOf(tab), QCoreApplication::translate("landingPage", "This section has Handwritten Notes.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_upload_assign->setText(QCoreApplication::translate("landingPage", "Upload", nullptr));
        pushButton_download_assign->setText(QCoreApplication::translate("landingPage", "Download", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("landingPage", "Assignment", nullptr));
#if QT_CONFIG(tooltip)
        tabWidget->setTabToolTip(tabWidget->indexOf(tab_2), QCoreApplication::translate("landingPage", "This section provides the assignments.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_upload_slides->setText(QCoreApplication::translate("landingPage", "Upload", nullptr));
        pushButton_download_slides->setText(QCoreApplication::translate("landingPage", "Download", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("landingPage", "Slides", nullptr));
#if QT_CONFIG(tooltip)
        tabWidget->setTabToolTip(tabWidget->indexOf(tab_3), QCoreApplication::translate("landingPage", "This section has the Slides Provided by the teachers.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_upolad_past->setText(QCoreApplication::translate("landingPage", "Upload", nullptr));
        pushButton_download_pastqn->setText(QCoreApplication::translate("landingPage", "Download", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("landingPage", "Past Question", nullptr));
#if QT_CONFIG(tooltip)
        tabWidget->setTabToolTip(tabWidget->indexOf(tab_4), QCoreApplication::translate("landingPage", "This Section Consist of Past questions.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_upload_other->setText(QCoreApplication::translate("landingPage", "Upload", nullptr));
        pushButton_download_others->setText(QCoreApplication::translate("landingPage", "Download", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("landingPage", "Others", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("landingPage", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class landingPage: public Ui_landingPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LANDINGPAGE_H
