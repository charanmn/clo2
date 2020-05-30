/********************************************************************************
** Form generated from reading UI file 'APISearchDialogSample.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APISEARCHDIALOGSAMPLE_H
#define UI_APISEARCHDIALOGSAMPLE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogSearch
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblItemName;
    QLineEdit *lineEdit_ItemName;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblServiceDivision;
    QComboBox *cbServiceDivision;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblBrand;
    QComboBox *cbBrand;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lblProductType;
    QComboBox *cbProductType;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lblSeasonCreated;
    QComboBox *cbSeasonCreated;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacerForButton;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer;
    QLabel *lblTitle;

    void setupUi(QDialog *DialogSearch)
    {
        if (DialogSearch->objectName().isEmpty())
            DialogSearch->setObjectName(QString::fromUtf8("DialogSearch"));
        DialogSearch->resize(285, 227);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogSearch->sizePolicy().hasHeightForWidth());
        DialogSearch->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(DialogSearch);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frame = new QFrame(DialogSearch);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lblItemName = new QLabel(frame);
        lblItemName->setObjectName(QString::fromUtf8("lblItemName"));

        horizontalLayout_2->addWidget(lblItemName);

        lineEdit_ItemName = new QLineEdit(frame);
        lineEdit_ItemName->setObjectName(QString::fromUtf8("lineEdit_ItemName"));

        horizontalLayout_2->addWidget(lineEdit_ItemName);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lblServiceDivision = new QLabel(frame);
        lblServiceDivision->setObjectName(QString::fromUtf8("lblServiceDivision"));

        horizontalLayout_3->addWidget(lblServiceDivision);

        cbServiceDivision = new QComboBox(frame);
        cbServiceDivision->setObjectName(QString::fromUtf8("cbServiceDivision"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cbServiceDivision->sizePolicy().hasHeightForWidth());
        cbServiceDivision->setSizePolicy(sizePolicy2);
        cbServiceDivision->setMinimumSize(QSize(120, 0));
        cbServiceDivision->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_3->addWidget(cbServiceDivision);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lblBrand = new QLabel(frame);
        lblBrand->setObjectName(QString::fromUtf8("lblBrand"));

        horizontalLayout_4->addWidget(lblBrand);

        cbBrand = new QComboBox(frame);
        cbBrand->setObjectName(QString::fromUtf8("cbBrand"));
        sizePolicy2.setHeightForWidth(cbBrand->sizePolicy().hasHeightForWidth());
        cbBrand->setSizePolicy(sizePolicy2);
        cbBrand->setMinimumSize(QSize(120, 0));
        cbBrand->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_4->addWidget(cbBrand);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        lblProductType = new QLabel(frame);
        lblProductType->setObjectName(QString::fromUtf8("lblProductType"));

        horizontalLayout_5->addWidget(lblProductType);

        cbProductType = new QComboBox(frame);
        cbProductType->setObjectName(QString::fromUtf8("cbProductType"));
        sizePolicy2.setHeightForWidth(cbProductType->sizePolicy().hasHeightForWidth());
        cbProductType->setSizePolicy(sizePolicy2);
        cbProductType->setMinimumSize(QSize(120, 0));
        cbProductType->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_5->addWidget(cbProductType);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        lblSeasonCreated = new QLabel(frame);
        lblSeasonCreated->setObjectName(QString::fromUtf8("lblSeasonCreated"));

        horizontalLayout_6->addWidget(lblSeasonCreated);

        cbSeasonCreated = new QComboBox(frame);
        cbSeasonCreated->setObjectName(QString::fromUtf8("cbSeasonCreated"));
        sizePolicy2.setHeightForWidth(cbSeasonCreated->sizePolicy().hasHeightForWidth());
        cbSeasonCreated->setSizePolicy(sizePolicy2);
        cbSeasonCreated->setMinimumSize(QSize(120, 0));
        cbSeasonCreated->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_6->addWidget(cbSeasonCreated);


        verticalLayout->addLayout(horizontalLayout_6);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacerForButton = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacerForButton);

        okButton = new QPushButton(DialogSearch);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setMinimumSize(QSize(73, 29));
        okButton->setMaximumSize(QSize(16777215, 29));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(DialogSearch);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setMinimumSize(QSize(73, 29));
        cancelButton->setMaximumSize(QSize(16777215, 29));

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        lblTitle = new QLabel(DialogSearch);
        lblTitle->setObjectName(QString::fromUtf8("lblTitle"));

        gridLayout->addWidget(lblTitle, 0, 0, 1, 1);


        retranslateUi(DialogSearch);

        QMetaObject::connectSlotsByName(DialogSearch);
    } // setupUi

    void retranslateUi(QDialog *DialogSearch)
    {
        DialogSearch->setWindowTitle(QApplication::translate("DialogSearch", "Search Criteria", 0, QApplication::UnicodeUTF8));
        lblItemName->setText(QApplication::translate("DialogSearch", "Name", 0, QApplication::UnicodeUTF8));
        lblServiceDivision->setText(QApplication::translate("DialogSearch", "CLO Service Division", 0, QApplication::UnicodeUTF8));
        lblBrand->setText(QApplication::translate("DialogSearch", "Brand", 0, QApplication::UnicodeUTF8));
        lblProductType->setText(QApplication::translate("DialogSearch", "Product Type", 0, QApplication::UnicodeUTF8));
        lblSeasonCreated->setText(QApplication::translate("DialogSearch", "Season Created", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("DialogSearch", "OK", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("DialogSearch", "Cancel", 0, QApplication::UnicodeUTF8));
        lblTitle->setText(QApplication::translate("DialogSearch", "Search Criteria", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogSearch: public Ui_DialogSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APISEARCHDIALOGSAMPLE_H
