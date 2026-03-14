/********************************************************************************
** Form generated from reading UI file 'register.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *pushButton_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
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
    QPushButton *pushButton_register;
    QCheckBox *checkBox_terms;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_sec_status;

    void setupUi(QDialog *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName("Register");
        Register->resize(566, 370);
        Register->setStyleSheet(QString::fromUtf8("background-color: rgb(16, 21, 36);\n"
""));
        groupBox = new QGroupBox(Register);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(100, 10, 361, 301));
        QFont font;
        font.setPointSize(10);
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
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        QFont font1;
        font1.setBold(true);
        pushButton_2->setFont(font1);
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color:rgb(255, 255, 255,0);\n"
"    min-width: 9px; \n"
"    min-height: 9px; \n"
"    padding: 5px; \n"
"    margin: 0px; \n"
"}\n"
""));

        gridLayout->addWidget(pushButton_2, 3, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        label_5->setFont(font2);
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setFont(font);

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
        label_4->setFont(font);

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
        label_2->setFont(font);

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
        label_3->setFont(font);

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
        lineEdit_create_password->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_3->addWidget(lineEdit_create_password);


        verticalLayout->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        pushButton_register = new QPushButton(groupBox);
        pushButton_register->setObjectName("pushButton_register");
        pushButton_register->setFont(font1);
        pushButton_register->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 10px; \n"
"    background-color:rgb(255, 255, 255,0);\n"
"    min-width: 10px; \n"
"    min-height: 10px; \n"
"    padding: 5px; \n"
"    margin: 0px; \n"
"}\n"
""));

        gridLayout->addWidget(pushButton_register, 2, 0, 1, 1);

        checkBox_terms = new QCheckBox(groupBox);
        checkBox_terms->setObjectName("checkBox_terms");

        gridLayout->addWidget(checkBox_terms, 1, 0, 1, 1);

        layoutWidget = new QWidget(Register);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_sec_status = new QLabel(Register);
        label_sec_status->setObjectName("label_sec_status");
        label_sec_status->setGeometry(QRect(70, 330, 121, 21));
        label_sec_status->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255,0);"));

        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QDialog *Register)
    {
        Register->setWindowTitle(QCoreApplication::translate("Register", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Register", "Register", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Register", "Back to Login page", nullptr));
        label_5->setText(QCoreApplication::translate("Register", "Create your account", nullptr));
        label->setText(QCoreApplication::translate("Register", "Name", nullptr));
        label_4->setText(QCoreApplication::translate("Register", "Phone No.", nullptr));
        label_2->setText(QCoreApplication::translate("Register", "Email", nullptr));
        label_3->setText(QCoreApplication::translate("Register", "Password", nullptr));
        pushButton_register->setText(QCoreApplication::translate("Register", "Register", nullptr));
        checkBox_terms->setText(QCoreApplication::translate("Register", "I agree to Terms and Conditions", nullptr));
        label_sec_status->setText(QCoreApplication::translate("Register", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
