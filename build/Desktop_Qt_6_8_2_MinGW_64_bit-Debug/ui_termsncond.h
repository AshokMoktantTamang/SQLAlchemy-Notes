/********************************************************************************
** Form generated from reading UI file 'termsncond.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TERMSNCOND_H
#define UI_TERMSNCOND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_termsncond
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QMainWindow *termsncond)
    {
        if (termsncond->objectName().isEmpty())
            termsncond->setObjectName("termsncond");
        termsncond->resize(645, 423);
        termsncond->setStyleSheet(QString::fromUtf8("background-color: rgb(16, 21, 36);\n"
""));
        centralwidget = new QWidget(termsncond);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 850, 697));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
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

        verticalLayout->addWidget(pushButton);

        termsncond->setCentralWidget(centralwidget);

        retranslateUi(termsncond);

        QMetaObject::connectSlotsByName(termsncond);
    } // setupUi

    void retranslateUi(QMainWindow *termsncond)
    {
        termsncond->setWindowTitle(QCoreApplication::translate("termsncond", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("termsncond", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">Terms and Conditions</span></p><p><span style=\" font-size:10pt;\">Welcome to Student Resource Hub. By using our app, you agree to the following Terms and Conditions. Please read them carefully.</span></p><p>1. Acceptance of Terms</p><p>By accessing or using Student Resource Hub, you agree to comply with and be bound by these Terms and Conditions. If you do not agree, you may not use the app.</p><p>2. Purpose of the App</p><p>Student Resource Hub is designed to provide study resources to students. The content, features, and services of the app are for educational purposes only.</p><p>3. User Conduct</p><p>You agree to use the app responsibly and only for lawful purposes.</p><p>Do not share, distribute, or upload any content that is harmful, illegal, or violates intellectual property rights.</p><p>Misuse of the app or its resources (e.g., hacking, unauthorized access) is prohibited.</p><p>4. Intellectual Property</p><p>All content, includin"
                        "g study materials, graphics, and text, is the property of Student Resource Hub or its licensors.</p><p>5. Third-Party Links</p><p>Student Resource Hub may contain links to third-party websites. We are not responsible for the content or privacy practices of these sites. Use them at your own discretion.</p><p>6. Account Security</p><p>Users are responsible for maintaining the confidentiality of their login details and account. Any activity conducted under your account is your responsibility.</p><p>7. Limitation of Liability</p><p>Student Resource Hub is not liable for any errors, omissions, or inaccuracies in the content provided. Users are encouraged to verify the accuracy of resources independently.</p><p>8. Privacy Policy</p><p>Your use of the app is also governed by our Privacy Policy, which outlines how we collect, use, and protect your data.</p><p>9. Modifications to Terms</p><p>Student Resource Hub reserves the right to modify these Terms and Conditions at any time. Changes will be effective upon posting."
                        "</p><p>10. Termination of Use</p><p>We reserve the right to suspend or terminate your access to the app for violations of these terms without prior notice.</p><p><br/></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("termsncond", "Return", nullptr));
    } // retranslateUi

};

namespace Ui {
    class termsncond: public Ui_termsncond {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TERMSNCOND_H
