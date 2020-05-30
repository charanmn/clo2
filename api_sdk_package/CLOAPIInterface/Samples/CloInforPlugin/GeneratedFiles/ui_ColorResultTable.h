/********************************************************************************
** Form generated from reading UI file 'ColorResultTable.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORRESULTTABLE_H
#define UI_COLORRESULTTABLE_H

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

class Ui_ColorResultTable
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *headerLabel;
    QToolButton *closeWindow;
    QTableWidget *colorResultsTable;
    QSpacerItem *horizontalSpacer;
    QPushButton *SelectAll;
    QPushButton *DeSelectAll;
    QPushButton *back;
    QPushButton *download;

    void setupUi(QDialog *ColorResultTable)
    {
        if (ColorResultTable->objectName().isEmpty())
            ColorResultTable->setObjectName(QString::fromUtf8("ColorResultTable"));
        ColorResultTable->resize(1250, 500);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ColorResultTable->sizePolicy().hasHeightForWidth());
        ColorResultTable->setSizePolicy(sizePolicy);
        ColorResultTable->setStyleSheet(QString::fromUtf8("#ColorResultTable {\n"
"	margin-left: 5px;\n"
"	margin-right: 5px;\n"
"	margin-top: 5px;\n"
"	margin-bottom: 5px;\n"
"	border : 1.5px solid #232323;\n"
"}"));
        gridLayout_2 = new QGridLayout(ColorResultTable);
        gridLayout_2->setSpacing(5);
        gridLayout_2->setContentsMargins(10, 10, 10, 10);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        headerLabel = new QLabel(ColorResultTable);
        headerLabel->setObjectName(QString::fromUtf8("headerLabel"));
        headerLabel->setStyleSheet(QString::fromUtf8("font: 75 10pt \"Tahoma\";\n"
"font-weight: bold;"));
        headerLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(headerLabel, 0, 0, 1, 1);

        closeWindow = new QToolButton(ColorResultTable);
        closeWindow->setObjectName(QString::fromUtf8("closeWindow"));
        closeWindow->setStyleSheet(QString::fromUtf8("#closeWindow {\n"
"    qproperty-icon: none;\n"
"    image: url(:/CLO_PLUGIN/INFOR/images/icon_cancel_none.svg);\n"
"}\n"
"#closeWindow:hover {\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_cancel_over.svg);\n"
"}"));

        gridLayout->addWidget(closeWindow, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 5);

        colorResultsTable = new QTableWidget(ColorResultTable);
        colorResultsTable->setObjectName(QString::fromUtf8("colorResultsTable"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(80);
        sizePolicy1.setVerticalStretch(80);
        sizePolicy1.setHeightForWidth(colorResultsTable->sizePolicy().hasHeightForWidth());
        colorResultsTable->setSizePolicy(sizePolicy1);
        colorResultsTable->setStyleSheet(QString::fromUtf8(""));
        colorResultsTable->setLineWidth(50);
        colorResultsTable->setMidLineWidth(40);
        colorResultsTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        colorResultsTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        colorResultsTable->setAutoScrollMargin(50);
        colorResultsTable->setDragEnabled(false);
        colorResultsTable->horizontalHeader()->setCascadingSectionResizes(false);
        colorResultsTable->horizontalHeader()->setMinimumSectionSize(80);
        colorResultsTable->horizontalHeader()->setStretchLastSection(false);
        colorResultsTable->verticalHeader()->setDefaultSectionSize(45);
        colorResultsTable->verticalHeader()->setMinimumSectionSize(39);

        gridLayout_2->addWidget(colorResultsTable, 1, 0, 1, 5);

        horizontalSpacer = new QSpacerItem(800, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 0, 1, 1);

        SelectAll = new QPushButton(ColorResultTable);
        SelectAll->setObjectName(QString::fromUtf8("SelectAll"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(SelectAll->sizePolicy().hasHeightForWidth());
        SelectAll->setSizePolicy(sizePolicy2);
        SelectAll->setMinimumSize(QSize(120, 30));
        SelectAll->setMaximumSize(QSize(120, 30));
        SelectAll->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";"));

        gridLayout_2->addWidget(SelectAll, 2, 1, 1, 1);

        DeSelectAll = new QPushButton(ColorResultTable);
        DeSelectAll->setObjectName(QString::fromUtf8("DeSelectAll"));
        sizePolicy2.setHeightForWidth(DeSelectAll->sizePolicy().hasHeightForWidth());
        DeSelectAll->setSizePolicy(sizePolicy2);
        DeSelectAll->setMinimumSize(QSize(130, 30));
        DeSelectAll->setMaximumSize(QSize(130, 30));
        DeSelectAll->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";"));

        gridLayout_2->addWidget(DeSelectAll, 2, 2, 1, 1);

        back = new QPushButton(ColorResultTable);
        back->setObjectName(QString::fromUtf8("back"));
        sizePolicy2.setHeightForWidth(back->sizePolicy().hasHeightForWidth());
        back->setSizePolicy(sizePolicy2);
        back->setMinimumSize(QSize(112, 30));
        back->setMaximumSize(QSize(112, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("Tahoma"));
        font.setPointSize(8);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        back->setFont(font);
        back->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";"));

        gridLayout_2->addWidget(back, 2, 3, 1, 1);

        download = new QPushButton(ColorResultTable);
        download->setObjectName(QString::fromUtf8("download"));
        sizePolicy2.setHeightForWidth(download->sizePolicy().hasHeightForWidth());
        download->setSizePolicy(sizePolicy2);
        download->setMinimumSize(QSize(120, 30));
        download->setMaximumSize(QSize(120, 30));
        download->setFont(font);
        download->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";"));

        gridLayout_2->addWidget(download, 2, 4, 1, 1);


        retranslateUi(ColorResultTable);

        QMetaObject::connectSlotsByName(ColorResultTable);
    } // setupUi

    void retranslateUi(QDialog *ColorResultTable)
    {
        ColorResultTable->setWindowTitle(QApplication::translate("ColorResultTable", "Dialog", 0, QApplication::UnicodeUTF8));
        headerLabel->setText(QApplication::translate("ColorResultTable", "Infor PLM Color Search Results", 0, QApplication::UnicodeUTF8));
        closeWindow->setText(QString());
        SelectAll->setText(QApplication::translate("ColorResultTable", "Select All", 0, QApplication::UnicodeUTF8));
        DeSelectAll->setText(QApplication::translate("ColorResultTable", "DeSelect All", 0, QApplication::UnicodeUTF8));
        back->setText(QApplication::translate("ColorResultTable", "Back", 0, QApplication::UnicodeUTF8));
        download->setText(QApplication::translate("ColorResultTable", "Download", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ColorResultTable: public Ui_ColorResultTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORRESULTTABLE_H
