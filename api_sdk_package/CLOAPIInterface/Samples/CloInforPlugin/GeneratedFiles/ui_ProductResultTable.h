/********************************************************************************
** Form generated from reading UI file 'ProductResultTable.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCTRESULTTABLE_H
#define UI_PRODUCTRESULTTABLE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_ProductResultTable
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *headerLabel;
    QToolButton *closeWindow;
    QTableWidget *ProductResultTable_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *back;
    QPushButton *download;

    void setupUi(QDialog *ProductResultTable)
    {
        if (ProductResultTable->objectName().isEmpty())
            ProductResultTable->setObjectName(QString::fromUtf8("ProductResultTable"));
        ProductResultTable->resize(1250, 500);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ProductResultTable->sizePolicy().hasHeightForWidth());
        ProductResultTable->setSizePolicy(sizePolicy);
        ProductResultTable->setStyleSheet(QString::fromUtf8("#ProductResultTable {\n"
"	margin-left: 5px;\n"
"	margin-right: 5px;\n"
"	margin-top: 5px;\n"
"	margin-bottom: 5px;\n"
"	border : 1.5px solid #232323;\n"
"}"));
        gridLayout_2 = new QGridLayout(ProductResultTable);
        gridLayout_2->setSpacing(5);
        gridLayout_2->setContentsMargins(10, 10, 10, 10);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        headerLabel = new QLabel(ProductResultTable);
        headerLabel->setObjectName(QString::fromUtf8("headerLabel"));
        headerLabel->setStyleSheet(QString::fromUtf8("/*font: 75 12pt \"Times New Roman\";*/\n"
"font: 75 10pt \"Tahoma\";\n"
"font-weight: bold;"));
        headerLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(headerLabel, 0, 0, 1, 1);

        closeWindow = new QToolButton(ProductResultTable);
        closeWindow->setObjectName(QString::fromUtf8("closeWindow"));
        closeWindow->setStyleSheet(QString::fromUtf8("#closeWindow {\n"
"    qproperty-icon: none;\n"
"    image: url(:/CLO_PLUGIN/INFOR/images/icon_cancel_none.svg);\n"
"}\n"
"#closeWindow:hover {\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_cancel_over.svg);\n"
"}"));

        gridLayout->addWidget(closeWindow, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 3);

        ProductResultTable_2 = new QTableWidget(ProductResultTable);
        ProductResultTable_2->setObjectName(QString::fromUtf8("ProductResultTable_2"));
        ProductResultTable_2->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(ProductResultTable_2, 1, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(800, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 0, 1, 1);

        back = new QPushButton(ProductResultTable);
        back->setObjectName(QString::fromUtf8("back"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(back->sizePolicy().hasHeightForWidth());
        back->setSizePolicy(sizePolicy1);
        back->setMinimumSize(QSize(112, 30));
        back->setMaximumSize(QSize(112, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("Tahoma"));
        font.setPointSize(8);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        back->setFont(font);
        back->setFocusPolicy(Qt::NoFocus);
        back->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";\n"
"/*font-weight: bold;*/"));

        gridLayout_2->addWidget(back, 2, 1, 1, 1);

        download = new QPushButton(ProductResultTable);
        download->setObjectName(QString::fromUtf8("download"));
        sizePolicy1.setHeightForWidth(download->sizePolicy().hasHeightForWidth());
        download->setSizePolicy(sizePolicy1);
        download->setMinimumSize(QSize(120, 30));
        download->setMaximumSize(QSize(120, 30));
        download->setFont(font);
        download->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";\n"
"/*font-weight: bold;*/"));

        gridLayout_2->addWidget(download, 2, 2, 1, 1);


        retranslateUi(ProductResultTable);

        QMetaObject::connectSlotsByName(ProductResultTable);
    } // setupUi

    void retranslateUi(QDialog *ProductResultTable)
    {
        ProductResultTable->setWindowTitle(QApplication::translate("ProductResultTable", "Dialog", 0, QApplication::UnicodeUTF8));
        headerLabel->setText(QApplication::translate("ProductResultTable", "Infor PLM Product Search Results", 0, QApplication::UnicodeUTF8));
        closeWindow->setText(QString());
        back->setText(QApplication::translate("ProductResultTable", "Back", 0, QApplication::UnicodeUTF8));
        download->setText(QApplication::translate("ProductResultTable", "Download", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ProductResultTable: public Ui_ProductResultTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTRESULTTABLE_H
