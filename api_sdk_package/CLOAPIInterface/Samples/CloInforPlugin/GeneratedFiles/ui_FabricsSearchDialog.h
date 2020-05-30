/********************************************************************************
** Form generated from reading UI file 'FabricsSearchDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FABRICSSEARCHDIALOG_H
#define UI_FABRICSSEARCHDIALOG_H

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
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_MaterialSearchDialog
{
public:
    QGridLayout *gridLayout_2;
    QTreeWidget *MaterialSearchTree;
    QPushButton *search;
    QPushButton *back;
    QGridLayout *gridLayout;
    QLabel *headerLabel;
    QToolButton *closeWindow;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *MaterialSearchDialog)
    {
        if (MaterialSearchDialog->objectName().isEmpty())
            MaterialSearchDialog->setObjectName(QString::fromUtf8("MaterialSearchDialog"));
        MaterialSearchDialog->resize(425, 550);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MaterialSearchDialog->sizePolicy().hasHeightForWidth());
        MaterialSearchDialog->setSizePolicy(sizePolicy);
        MaterialSearchDialog->setMinimumSize(QSize(425, 550));
        MaterialSearchDialog->setMaximumSize(QSize(425, 550));
        MaterialSearchDialog->setStyleSheet(QString::fromUtf8("/*margin-left: 5px;\n"
"margin-right: 5px;\n"
"margin-top: 5px;\n"
"margin-bottom: 5px;\n"
"border-top : 1px solid #232323;\n"
"border-bottom : 1px solid #232323;\n"
"border-top : 1px solid #232323;\n"
"border-top : 1px solid #232323;*/\n"
"#MaterialSearchDialog {\n"
"	margin-left: 8px;\n"
"	margin-right: 8px;\n"
"	margin-top: 8px;\n"
"	margin-bottom: 8px;\n"
"	border : 1.5px solid #232323;\n"
"}"));
        gridLayout_2 = new QGridLayout(MaterialSearchDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        MaterialSearchTree = new QTreeWidget(MaterialSearchDialog);
        MaterialSearchTree->setObjectName(QString::fromUtf8("MaterialSearchTree"));
        MaterialSearchTree->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        MaterialSearchTree->setFont(font);
        MaterialSearchTree->setMouseTracking(false);
        MaterialSearchTree->setFocusPolicy(Qt::NoFocus);
        MaterialSearchTree->setContextMenuPolicy(Qt::DefaultContextMenu);
        MaterialSearchTree->setStyleSheet(QString::fromUtf8("/*\n"
"item \n"
"{ \n"
"	font: 75 16pt \"Times New Roman\";\n"
"	border-bottom: 1px solid #232323;\n"
"	///*selection-background-color: transparent;\n"
"	show-decoration-selected: 0;\n"
"	margin-left: 10px;\n"
"	margin-right: 10px;\n"
"	margin-top: 10px;\n"
"	margin-bottom: 10px;\n"
"}*/\n"
"item\n"
"{\n"
"font: 75 8pt \"Tahoma\";\n"
"border-bottom: 1px solid #232323;\n"
"/*selection-background-color: transparent;*/\n"
"show-decoration-selected: 0;\n"
"margin-left: 5px;\n"
"margin-right: 5px;\n"
"margin-top: 5px;\n"
"margin-bottom: 5px;\n"
"}\n"
""));
        MaterialSearchTree->setFrameShape(QFrame::StyledPanel);
        MaterialSearchTree->setFrameShadow(QFrame::Sunken);
        MaterialSearchTree->setLineWidth(4);
        MaterialSearchTree->setProperty("showDropIndicator", QVariant(false));
        MaterialSearchTree->setSelectionMode(QAbstractItemView::NoSelection);
        MaterialSearchTree->setSelectionBehavior(QAbstractItemView::SelectRows);
        MaterialSearchTree->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        MaterialSearchTree->setRootIsDecorated(false);
        MaterialSearchTree->setWordWrap(true);
        MaterialSearchTree->setColumnCount(2);
        MaterialSearchTree->header()->setVisible(false);
        MaterialSearchTree->header()->setCascadingSectionResizes(true);
        MaterialSearchTree->header()->setDefaultSectionSize(120);
        MaterialSearchTree->header()->setMinimumSectionSize(40);
        MaterialSearchTree->header()->setStretchLastSection(false);

        gridLayout_2->addWidget(MaterialSearchTree, 1, 0, 1, 3);

        search = new QPushButton(MaterialSearchDialog);
        search->setObjectName(QString::fromUtf8("search"));
        search->setMaximumSize(QSize(16777215, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Tahoma"));
        font1.setPointSize(8);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(9);
        search->setFont(font1);
        search->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";\n"
""));

        gridLayout_2->addWidget(search, 2, 2, 1, 1);

        back = new QPushButton(MaterialSearchDialog);
        back->setObjectName(QString::fromUtf8("back"));
        back->setMaximumSize(QSize(16777215, 30));
        back->setFont(font1);
        back->setFocusPolicy(Qt::NoFocus);
        back->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";\n"
""));

        gridLayout_2->addWidget(back, 2, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        headerLabel = new QLabel(MaterialSearchDialog);
        headerLabel->setObjectName(QString::fromUtf8("headerLabel"));
        sizePolicy.setHeightForWidth(headerLabel->sizePolicy().hasHeightForWidth());
        headerLabel->setSizePolicy(sizePolicy);
        headerLabel->setMinimumSize(QSize(400, 30));
        headerLabel->setMaximumSize(QSize(400, 30));
        headerLabel->setStyleSheet(QString::fromUtf8("font: 75 10pt \"Tahoma\";\n"
"font-weight: bold;"));
        headerLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(headerLabel, 0, 0, 1, 1);

        closeWindow = new QToolButton(MaterialSearchDialog);
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

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 0, 1, 1);


        retranslateUi(MaterialSearchDialog);

        QMetaObject::connectSlotsByName(MaterialSearchDialog);
    } // setupUi

    void retranslateUi(QDialog *MaterialSearchDialog)
    {
        MaterialSearchDialog->setWindowTitle(QApplication::translate("MaterialSearchDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        search->setText(QApplication::translate("MaterialSearchDialog", "Search", 0, QApplication::UnicodeUTF8));
        back->setText(QApplication::translate("MaterialSearchDialog", "Back", 0, QApplication::UnicodeUTF8));
        headerLabel->setText(QApplication::translate("MaterialSearchDialog", " Infor PLM Material Search Criteria", 0, QApplication::UnicodeUTF8));
        closeWindow->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MaterialSearchDialog: public Ui_MaterialSearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FABRICSSEARCHDIALOG_H
