/********************************************************************************
** Form generated from reading UI file 'FabricsResultTable.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FABRICSRESULTTABLE_H
#define UI_FABRICSRESULTTABLE_H

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

class Ui_ResultTable
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *hearderLabel;
    QToolButton *closeWindow;
    QTableWidget *materialResultTable;
    QSpacerItem *horizontalSpacer;
    QPushButton *SelectAll;
    QPushButton *DeSelectAll;
    QPushButton *back;
    QPushButton *download;

    void setupUi(QDialog *ResultTable)
    {
        if (ResultTable->objectName().isEmpty())
            ResultTable->setObjectName(QString::fromUtf8("ResultTable"));
        ResultTable->resize(1250, 500);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ResultTable->sizePolicy().hasHeightForWidth());
        ResultTable->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        ResultTable->setFont(font);
        ResultTable->setStyleSheet(QString::fromUtf8("#ResultTable \n"
"{\n"
"	margin-left: 5px;\n"
"	margin-right: 5px;\n"
"	margin-top: 5px;\n"
"	margin-bottom: 5px;\n"
"	border : 1.5px solid #232323;\n"
"}"));
        gridLayout_2 = new QGridLayout(ResultTable);
        gridLayout_2->setSpacing(5);
        gridLayout_2->setContentsMargins(10, 10, 10, 10);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hearderLabel = new QLabel(ResultTable);
        hearderLabel->setObjectName(QString::fromUtf8("hearderLabel"));
        hearderLabel->setStyleSheet(QString::fromUtf8("font: 75 10pt \"Tahoma\";\n"
"font-weight: bold;"));
        hearderLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(hearderLabel, 0, 0, 1, 1);

        closeWindow = new QToolButton(ResultTable);
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

        materialResultTable = new QTableWidget(ResultTable);
        materialResultTable->setObjectName(QString::fromUtf8("materialResultTable"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(materialResultTable->sizePolicy().hasHeightForWidth());
        materialResultTable->setSizePolicy(sizePolicy1);
        materialResultTable->setStyleSheet(QString::fromUtf8(""));
        materialResultTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        materialResultTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        materialResultTable->horizontalHeader()->setDefaultSectionSize(60);
        materialResultTable->horizontalHeader()->setMinimumSectionSize(50);
        materialResultTable->verticalHeader()->setDefaultSectionSize(35);
        materialResultTable->verticalHeader()->setMinimumSectionSize(25);

        gridLayout_2->addWidget(materialResultTable, 1, 0, 1, 5);

        horizontalSpacer = new QSpacerItem(600, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 0, 1, 1);

        SelectAll = new QPushButton(ResultTable);
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

        DeSelectAll = new QPushButton(ResultTable);
        DeSelectAll->setObjectName(QString::fromUtf8("DeSelectAll"));
        sizePolicy2.setHeightForWidth(DeSelectAll->sizePolicy().hasHeightForWidth());
        DeSelectAll->setSizePolicy(sizePolicy2);
        DeSelectAll->setMinimumSize(QSize(130, 30));
        DeSelectAll->setMaximumSize(QSize(130, 30));
        DeSelectAll->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";"));

        gridLayout_2->addWidget(DeSelectAll, 2, 2, 1, 1);

        back = new QPushButton(ResultTable);
        back->setObjectName(QString::fromUtf8("back"));
        sizePolicy2.setHeightForWidth(back->sizePolicy().hasHeightForWidth());
        back->setSizePolicy(sizePolicy2);
        back->setMinimumSize(QSize(112, 30));
        back->setMaximumSize(QSize(112, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Tahoma"));
        font1.setPointSize(8);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(9);
        back->setFont(font1);
        back->setFocusPolicy(Qt::NoFocus);
        back->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";"));

        gridLayout_2->addWidget(back, 2, 3, 1, 1);

        download = new QPushButton(ResultTable);
        download->setObjectName(QString::fromUtf8("download"));
        sizePolicy2.setHeightForWidth(download->sizePolicy().hasHeightForWidth());
        download->setSizePolicy(sizePolicy2);
        download->setMinimumSize(QSize(120, 30));
        download->setMaximumSize(QSize(120, 30));
        download->setFont(font1);
        download->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";"));

        gridLayout_2->addWidget(download, 2, 4, 1, 1);


        retranslateUi(ResultTable);

        QMetaObject::connectSlotsByName(ResultTable);
    } // setupUi

    void retranslateUi(QDialog *ResultTable)
    {
        ResultTable->setWindowTitle(QApplication::translate("ResultTable", "Dialog", 0, QApplication::UnicodeUTF8));
        hearderLabel->setText(QApplication::translate("ResultTable", "Infor PLM Fabric Search Results", 0, QApplication::UnicodeUTF8));
        closeWindow->setText(QString());
        SelectAll->setText(QApplication::translate("ResultTable", "Select All", 0, QApplication::UnicodeUTF8));
        DeSelectAll->setText(QApplication::translate("ResultTable", "DeSelect All", 0, QApplication::UnicodeUTF8));
        back->setText(QApplication::translate("ResultTable", "Back", 0, QApplication::UnicodeUTF8));
        download->setText(QApplication::translate("ResultTable", "Download", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ResultTable: public Ui_ResultTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FABRICSRESULTTABLE_H
