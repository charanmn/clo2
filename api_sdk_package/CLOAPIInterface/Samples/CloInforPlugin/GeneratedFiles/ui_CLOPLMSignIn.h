/********************************************************************************
** Form generated from reading UI file 'CLOPLMSignIn.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOPLMSIGNIN_H
#define UI_CLOPLMSIGNIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_CLOPLMSignIn
{
public:
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QLabel *label_3;
    QGridLayout *gridLayout_3;
    QLabel *label_2;
    QFrame *line;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer_9;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *headerLabel;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *closeWindow;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_7;
    QGridLayout *gridLayout;
    QLineEdit *PLMInputId;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *PLMInputPwd;
    QLabel *passwordLabel;
    QPushButton *loginButton;
    QSpacerItem *verticalSpacer_3;
    QLabel *userNameLabel;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QDialog *CLOPLMSignIn)
    {
        if (CLOPLMSignIn->objectName().isEmpty())
            CLOPLMSignIn->setObjectName(QString::fromUtf8("CLOPLMSignIn"));
        CLOPLMSignIn->resize(450, 475);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CLOPLMSignIn->sizePolicy().hasHeightForWidth());
        CLOPLMSignIn->setSizePolicy(sizePolicy);
        CLOPLMSignIn->setMinimumSize(QSize(450, 475));
        CLOPLMSignIn->setMaximumSize(QSize(450, 475));
        CLOPLMSignIn->setStyleSheet(QString::fromUtf8("/*margin-left: 5px;\n"
"image: url(:/CLO_PLUGIN/INFOR/images/GoViseLogo.png);\n"
"margin-right: 5px;\n"
"margin-top: 5px;\n"
"margin-bottom: 5px;*/\n"
"\n"
"#CLOPLMSignIn {\n"
"	margin-left: 5px;\n"
"	margin-right: 5px;\n"
"	margin-top: 5px;\n"
"	margin-bottom: 5px;\n"
"	border : 1.5px solid #232323;\n"
"}"));
        gridLayout_6 = new QGridLayout(CLOPLMSignIn);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(13, -1, -1, -1);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setVerticalSpacing(0);
        label_3 = new QLabel(CLOPLMSignIn);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(40, 40));
        label_3->setMaximumSize(QSize(40, 40));
        label_3->setStyleSheet(QString::fromUtf8("image: url(:/CLO_PLUGIN/INFOR/images/GoViseLogo.png);"));

        gridLayout_5->addWidget(label_3, 1, 1, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(9);
        gridLayout_3->setVerticalSpacing(0);
        label_2 = new QLabel(CLOPLMSignIn);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(0, 15));
        label_2->setMaximumSize(QSize(16777215, 15));
        label_2->setStyleSheet(QString::fromUtf8("font: 75 5pt \"Tahoma\";\n"
"color: rgb(225, 225, 225);\n"
"font-weight: bold;"));
        label_2->setLineWidth(1);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_2, 0, 1, 1, 1);

        line = new QFrame(CLOPLMSignIn);
        line->setObjectName(QString::fromUtf8("line"));
        line->setSizeIncrement(QSize(0, 0));
        line->setBaseSize(QSize(0, 0));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        line->setFont(font);
        line->setStyleSheet(QString::fromUtf8("color: rgb(160, 160, 160);"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(3);
        line->setMidLineWidth(0);
        line->setFrameShape(QFrame::HLine);

        gridLayout_3->addWidget(line, 1, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 1, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 0, 0, 2, 1);


        gridLayout_5->addLayout(gridLayout_3, 0, 0, 1, 3);

        horizontalSpacer_4 = new QSpacerItem(165, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_4, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(165, 13, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 1, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 1, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalSpacer_9 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_9, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(158, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        headerLabel = new QLabel(CLOPLMSignIn);
        headerLabel->setObjectName(QString::fromUtf8("headerLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(headerLabel->sizePolicy().hasHeightForWidth());
        headerLabel->setSizePolicy(sizePolicy2);
        headerLabel->setMaximumSize(QSize(85, 50));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Tahoma"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        headerLabel->setFont(font1);
        headerLabel->setStyleSheet(QString::fromUtf8("/*font: 75 12pt \"Times New Roman\";*/\n"
"image: url(:/CLO_PLUGIN/INFOR/images/CI_CLO_Virtual_Fashion_White.png);\n"
"font: 75 12pt \"Tahoma\";\n"
"font-weight: bold;"));
        headerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(headerLabel, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(120, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        closeWindow = new QToolButton(CLOPLMSignIn);
        closeWindow->setObjectName(QString::fromUtf8("closeWindow"));
        closeWindow->setMaximumSize(QSize(25, 25));
        closeWindow->setStyleSheet(QString::fromUtf8("#closeWindow {\n"
"    qproperty-icon: none;\n"
"    image: url(:/CLO_PLUGIN/INFOR/images/icon_cancel_none.svg);\n"
"}\n"
"#closeWindow:hover {\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_cancel_over.svg);\n"
"}"));

        gridLayout_2->addWidget(closeWindow, 0, 3, 1, 1);

        label = new QLabel(CLOPLMSignIn);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMaximumSize(QSize(16777215, 30));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Tahoma"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setWeight(75);
        label->setFont(font2);
        label->setStyleSheet(QString::fromUtf8("font: 75 10pt \"Tahoma\";\n"
"font-weight: bold;"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label, 1, 0, 1, 4);


        gridLayout_4->addLayout(gridLayout_2, 0, 1, 1, 2);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_4->addItem(verticalSpacer, 1, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_7, 2, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        PLMInputId = new QLineEdit(CLOPLMSignIn);
        PLMInputId->setObjectName(QString::fromUtf8("PLMInputId"));
        PLMInputId->setMinimumSize(QSize(0, 30));
        PLMInputId->setMaximumSize(QSize(16777215, 30));
        PLMInputId->setStyleSheet(QString::fromUtf8("font: 75 10pt \"Tahoma\";\n"
""));

        gridLayout->addWidget(PLMInputId, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 2, 0, 1, 1);

        PLMInputPwd = new QLineEdit(CLOPLMSignIn);
        PLMInputPwd->setObjectName(QString::fromUtf8("PLMInputPwd"));
        PLMInputPwd->setMinimumSize(QSize(0, 30));
        PLMInputPwd->setMaximumSize(QSize(16777215, 30));
        PLMInputPwd->setStyleSheet(QString::fromUtf8("font: 75 10pt \"Tahoma\";"));

        gridLayout->addWidget(PLMInputPwd, 4, 0, 1, 1);

        passwordLabel = new QLabel(CLOPLMSignIn);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));
        passwordLabel->setMinimumSize(QSize(0, 25));
        passwordLabel->setMaximumSize(QSize(16777215, 35));
        passwordLabel->setStyleSheet(QString::fromUtf8("font: 75 10pt \"Tahoma\";\n"
"font-weight: bold;"));

        gridLayout->addWidget(passwordLabel, 3, 0, 1, 1);

        loginButton = new QPushButton(CLOPLMSignIn);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(8);
        sizePolicy3.setHeightForWidth(loginButton->sizePolicy().hasHeightForWidth());
        loginButton->setSizePolicy(sizePolicy3);
        loginButton->setMinimumSize(QSize(80, 35));
        loginButton->setMaximumSize(QSize(16777215, 35));
        loginButton->setAutoFillBackground(false);
        loginButton->setStyleSheet(QString::fromUtf8("font: 75 10pt \"Tahoma\";\n"
"background-color: rgb(30, 116, 255);\n"
"font-weight: bold;\n"
"/*font: 75 8pt \"Tahoma\";\n"
"image: url(:/CLO_PLUGIN/INFOR/icon_ok_over.svg);\n"
"font-weight: bold;*/\n"
"/*\n"
"#okButton {\n"
"	font: 75 8pt \"Tahoma\";\n"
"	font-weight: bold;\n"
"    /*qproperty-icon: none;\n"
"    image: url(:/CLO_PLUGIN/INFOR/icon_cancel_none.svg); \n"
"	qproperty-icon: url(\" \"); /* empty image \n"
"    qproperty-iconSize: 24px 24px; /* space for the background image \n"
"    background-image: url(:/CLO_PLUGIN/INFOR/icon_cancel_none.svg);\n"
"    background-repeat: no-repeat;\n"
"	background-attachment: fixed;\n"
"  	background-position: left;\n"
"	\n"
"}\n"
"\n"
"#okButton:hover {\n"
"	font: 75 8pt \"Tahoma\";\n"
"	font-weight: bold;\n"
"   /* image: url(:/CLO_PLUGIN/INFOR/icon_cancel_over.svg);  \n"
"	qproperty-icon: url(\" \"); /* empty image \n"
"    qproperty-iconSize: 18px 18px; /* space for the background image \n"
"    background-image: url(:/CLO_PLUGIN/INFOR/icon_cancel_over.svg);\n"
""
                        "    background-repeat: no-repeat;\n"
"	background-attachment: fixed;	\n"
"  	background-position: left;\n"
"}\n"
"*/"));
        loginButton->setIconSize(QSize(24, 24));

        gridLayout->addWidget(loginButton, 6, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 5, 0, 1, 1);

        userNameLabel = new QLabel(CLOPLMSignIn);
        userNameLabel->setObjectName(QString::fromUtf8("userNameLabel"));
        userNameLabel->setMinimumSize(QSize(0, 25));
        userNameLabel->setMaximumSize(QSize(16777215, 35));
        userNameLabel->setStyleSheet(QString::fromUtf8("font: 75 10pt \"Tahoma\";\n"
"font-weight: bold;"));

        gridLayout->addWidget(userNameLabel, 0, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout, 2, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_8, 2, 2, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_4->addItem(verticalSpacer_5, 3, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout_4, 0, 0, 1, 1);


        retranslateUi(CLOPLMSignIn);

        QMetaObject::connectSlotsByName(CLOPLMSignIn);
    } // setupUi

    void retranslateUi(QDialog *CLOPLMSignIn)
    {
        CLOPLMSignIn->setWindowTitle(QApplication::translate("CLOPLMSignIn", "Dialog", 0, QApplication::UnicodeUTF8));
        label_3->setText(QString());
        label_2->setText(QApplication::translate("CLOPLMSignIn", "POWERED BY", 0, QApplication::UnicodeUTF8));
        headerLabel->setText(QString());
        closeWindow->setText(QString());
        label->setText(QApplication::translate("CLOPLMSignIn", "CLO-Vise for Infor", 0, QApplication::UnicodeUTF8));
        PLMInputId->setPlaceholderText(QApplication::translate("CLOPLMSignIn", "UserName", 0, QApplication::UnicodeUTF8));
        PLMInputPwd->setPlaceholderText(QApplication::translate("CLOPLMSignIn", "Password", 0, QApplication::UnicodeUTF8));
        passwordLabel->setText(QApplication::translate("CLOPLMSignIn", "Password", 0, QApplication::UnicodeUTF8));
        loginButton->setText(QApplication::translate("CLOPLMSignIn", "Login", 0, QApplication::UnicodeUTF8));
        userNameLabel->setText(QApplication::translate("CLOPLMSignIn", "UserName", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CLOPLMSignIn: public Ui_CLOPLMSignIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOPLMSIGNIN_H
