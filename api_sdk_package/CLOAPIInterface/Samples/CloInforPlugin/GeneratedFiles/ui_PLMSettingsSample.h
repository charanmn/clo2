/********************************************************************************
** Form generated from reading UI file 'PLMSettingsSample.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLMSETTINGSSAMPLE_H
#define UI_PLMSETTINGSSAMPLE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PLMSettings
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_CloPlugin_Key;
    QLabel *label_PlmSchema_Value;
    QLabel *label_Cloplugin_Value;
    QLabel *lable_PlmVersion_Value;
    QLabel *label_PlmServer_Value;
    QLabel *label_BackendConsumer_Key;
    QLabel *label_PLMTenant_Key;
    QLabel *label_PlmServer_Key;
    QLabel *label_ServerUserName_Key;
    QLabel *label_ServerUser_Value;
    QLabel *label_ConnectionStatus_key;
    QLabel *label_ConnectionStatus_Value;
    QLabel *label_WebAppConsumerKey_Value;
    QLabel *label_WebAppConsumer_Key;
    QComboBox *comboBox_PLMTenant;
    QLabel *label_ConsumerKey_Value;
    QLabel *label_PlmSchema_Key;
    QLabel *lable_PLMVersion_Key;
    QLabel *label_CompanyName_Key;
    QLabel *label_CompanyName_Value;

    void setupUi(QWidget *PLMSettings)
    {
        if (PLMSettings->objectName().isEmpty())
            PLMSettings->setObjectName(QString::fromUtf8("PLMSettings"));
        PLMSettings->resize(548, 564);
        gridLayout_2 = new QGridLayout(PLMSettings);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_CloPlugin_Key = new QLabel(PLMSettings);
        label_CloPlugin_Key->setObjectName(QString::fromUtf8("label_CloPlugin_Key"));

        gridLayout->addWidget(label_CloPlugin_Key, 2, 0, 1, 1);

        label_PlmSchema_Value = new QLabel(PLMSettings);
        label_PlmSchema_Value->setObjectName(QString::fromUtf8("label_PlmSchema_Value"));

        gridLayout->addWidget(label_PlmSchema_Value, 5, 1, 1, 1);

        label_Cloplugin_Value = new QLabel(PLMSettings);
        label_Cloplugin_Value->setObjectName(QString::fromUtf8("label_Cloplugin_Value"));

        gridLayout->addWidget(label_Cloplugin_Value, 2, 1, 1, 1);

        lable_PlmVersion_Value = new QLabel(PLMSettings);
        lable_PlmVersion_Value->setObjectName(QString::fromUtf8("lable_PlmVersion_Value"));

        gridLayout->addWidget(lable_PlmVersion_Value, 1, 1, 1, 1);

        label_PlmServer_Value = new QLabel(PLMSettings);
        label_PlmServer_Value->setObjectName(QString::fromUtf8("label_PlmServer_Value"));

        gridLayout->addWidget(label_PlmServer_Value, 6, 1, 1, 1);

        label_BackendConsumer_Key = new QLabel(PLMSettings);
        label_BackendConsumer_Key->setObjectName(QString::fromUtf8("label_BackendConsumer_Key"));

        gridLayout->addWidget(label_BackendConsumer_Key, 7, 0, 1, 1);

        label_PLMTenant_Key = new QLabel(PLMSettings);
        label_PLMTenant_Key->setObjectName(QString::fromUtf8("label_PLMTenant_Key"));

        gridLayout->addWidget(label_PLMTenant_Key, 4, 0, 1, 1);

        label_PlmServer_Key = new QLabel(PLMSettings);
        label_PlmServer_Key->setObjectName(QString::fromUtf8("label_PlmServer_Key"));

        gridLayout->addWidget(label_PlmServer_Key, 6, 0, 1, 1);

        label_ServerUserName_Key = new QLabel(PLMSettings);
        label_ServerUserName_Key->setObjectName(QString::fromUtf8("label_ServerUserName_Key"));

        gridLayout->addWidget(label_ServerUserName_Key, 9, 0, 1, 1);

        label_ServerUser_Value = new QLabel(PLMSettings);
        label_ServerUser_Value->setObjectName(QString::fromUtf8("label_ServerUser_Value"));

        gridLayout->addWidget(label_ServerUser_Value, 9, 1, 1, 1);

        label_ConnectionStatus_key = new QLabel(PLMSettings);
        label_ConnectionStatus_key->setObjectName(QString::fromUtf8("label_ConnectionStatus_key"));

        gridLayout->addWidget(label_ConnectionStatus_key, 10, 0, 1, 1);

        label_ConnectionStatus_Value = new QLabel(PLMSettings);
        label_ConnectionStatus_Value->setObjectName(QString::fromUtf8("label_ConnectionStatus_Value"));

        gridLayout->addWidget(label_ConnectionStatus_Value, 10, 1, 1, 1);

        label_WebAppConsumerKey_Value = new QLabel(PLMSettings);
        label_WebAppConsumerKey_Value->setObjectName(QString::fromUtf8("label_WebAppConsumerKey_Value"));

        gridLayout->addWidget(label_WebAppConsumerKey_Value, 8, 1, 1, 1);

        label_WebAppConsumer_Key = new QLabel(PLMSettings);
        label_WebAppConsumer_Key->setObjectName(QString::fromUtf8("label_WebAppConsumer_Key"));

        gridLayout->addWidget(label_WebAppConsumer_Key, 8, 0, 1, 1);

        comboBox_PLMTenant = new QComboBox(PLMSettings);
        comboBox_PLMTenant->setObjectName(QString::fromUtf8("comboBox_PLMTenant"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_PLMTenant->sizePolicy().hasHeightForWidth());
        comboBox_PLMTenant->setSizePolicy(sizePolicy);
        comboBox_PLMTenant->setMinimumSize(QSize(300, 20));
        comboBox_PLMTenant->setMaximumSize(QSize(300, 20));
        comboBox_PLMTenant->setDuplicatesEnabled(false);

        gridLayout->addWidget(comboBox_PLMTenant, 4, 1, 1, 1);

        label_ConsumerKey_Value = new QLabel(PLMSettings);
        label_ConsumerKey_Value->setObjectName(QString::fromUtf8("label_ConsumerKey_Value"));

        gridLayout->addWidget(label_ConsumerKey_Value, 7, 1, 1, 1);

        label_PlmSchema_Key = new QLabel(PLMSettings);
        label_PlmSchema_Key->setObjectName(QString::fromUtf8("label_PlmSchema_Key"));

        gridLayout->addWidget(label_PlmSchema_Key, 5, 0, 1, 1);

        lable_PLMVersion_Key = new QLabel(PLMSettings);
        lable_PLMVersion_Key->setObjectName(QString::fromUtf8("lable_PLMVersion_Key"));

        gridLayout->addWidget(lable_PLMVersion_Key, 1, 0, 1, 1);

        label_CompanyName_Key = new QLabel(PLMSettings);
        label_CompanyName_Key->setObjectName(QString::fromUtf8("label_CompanyName_Key"));

        gridLayout->addWidget(label_CompanyName_Key, 0, 0, 1, 1);

        label_CompanyName_Value = new QLabel(PLMSettings);
        label_CompanyName_Value->setObjectName(QString::fromUtf8("label_CompanyName_Value"));

        gridLayout->addWidget(label_CompanyName_Value, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(PLMSettings);

        QMetaObject::connectSlotsByName(PLMSettings);
    } // setupUi

    void retranslateUi(QWidget *PLMSettings)
    {
        PLMSettings->setWindowTitle(QApplication::translate("PLMSettings", "Form", 0, QApplication::UnicodeUTF8));
        label_CloPlugin_Key->setText(QApplication::translate("PLMSettings", "CLO-Vise Version:", 0, QApplication::UnicodeUTF8));
        label_PlmSchema_Value->setText(QApplication::translate("PLMSettings", "Not Available", 0, QApplication::UnicodeUTF8));
        label_Cloplugin_Value->setText(QApplication::translate("PLMSettings", "Not Available", 0, QApplication::UnicodeUTF8));
        lable_PlmVersion_Value->setText(QApplication::translate("PLMSettings", "Not Available", 0, QApplication::UnicodeUTF8));
        label_PlmServer_Value->setText(QApplication::translate("PLMSettings", "Not Available", 0, QApplication::UnicodeUTF8));
        label_BackendConsumer_Key->setText(QApplication::translate("PLMSettings", "Backend Consumer Key:", 0, QApplication::UnicodeUTF8));
        label_PLMTenant_Key->setText(QApplication::translate("PLMSettings", "PLM Tenant:", 0, QApplication::UnicodeUTF8));
        label_PlmServer_Key->setText(QApplication::translate("PLMSettings", "PLM Server URL:", 0, QApplication::UnicodeUTF8));
        label_ServerUserName_Key->setText(QApplication::translate("PLMSettings", "Server User Name:", 0, QApplication::UnicodeUTF8));
        label_ServerUser_Value->setText(QApplication::translate("PLMSettings", "Not Available", 0, QApplication::UnicodeUTF8));
        label_ConnectionStatus_key->setText(QApplication::translate("PLMSettings", "Connection status:", 0, QApplication::UnicodeUTF8));
        label_ConnectionStatus_Value->setText(QApplication::translate("PLMSettings", "Not Available", 0, QApplication::UnicodeUTF8));
        label_WebAppConsumerKey_Value->setText(QApplication::translate("PLMSettings", "Not Available", 0, QApplication::UnicodeUTF8));
        label_WebAppConsumer_Key->setText(QApplication::translate("PLMSettings", "Web App Consumer Key:", 0, QApplication::UnicodeUTF8));
        label_ConsumerKey_Value->setText(QApplication::translate("PLMSettings", "Not Available", 0, QApplication::UnicodeUTF8));
        label_PlmSchema_Key->setText(QApplication::translate("PLMSettings", "Active PLM Schema:", 0, QApplication::UnicodeUTF8));
        lable_PLMVersion_Key->setText(QApplication::translate("PLMSettings", "PLM Client Version:", 0, QApplication::UnicodeUTF8));
        label_CompanyName_Key->setText(QApplication::translate("PLMSettings", "Company Name:", 0, QApplication::UnicodeUTF8));
        label_CompanyName_Value->setText(QApplication::translate("PLMSettings", "Not Available", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PLMSettings: public Ui_PLMSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLMSETTINGSSAMPLE_H
