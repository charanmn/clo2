/********************************************************************************
** Form generated from reading UI file 'ColorSearch.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORSEARCH_H
#define UI_COLORSEARCH_H

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

class Ui_ColorSearchDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *headerLabel;
    QToolButton *closeWindow;
    QSpacerItem *horizontalSpacer;
    QPushButton *back;
    QPushButton *search;
    QTreeWidget *ColorSearchTree;

    void setupUi(QDialog *ColorSearchDialog)
    {
        if (ColorSearchDialog->objectName().isEmpty())
            ColorSearchDialog->setObjectName(QString::fromUtf8("ColorSearchDialog"));
        ColorSearchDialog->resize(425, 550);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ColorSearchDialog->sizePolicy().hasHeightForWidth());
        ColorSearchDialog->setSizePolicy(sizePolicy);
        ColorSearchDialog->setMinimumSize(QSize(425, 550));
        ColorSearchDialog->setMaximumSize(QSize(440, 550));
        ColorSearchDialog->setStyleSheet(QString::fromUtf8("/*margin-left: 5px;\n"
"margin-right: 5px;\n"
"margin-top: 5px;\n"
"margin-bottom: 5px;\n"
"border-top : 1px solid #232323;\n"
"border-bottom : 1px solid #232323;\n"
"border-top : 1px solid #232323;\n"
"border-top : 1px solid #232323;*/\n"
"#ColorSearchDialog {\n"
"	margin-left: 8px;\n"
"	margin-right: 8px;\n"
"	margin-top: 8px;\n"
"	margin-bottom: 8px;\n"
"	border : 1.5px solid #232323;\n"
"}"));
        gridLayout_2 = new QGridLayout(ColorSearchDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        headerLabel = new QLabel(ColorSearchDialog);
        headerLabel->setObjectName(QString::fromUtf8("headerLabel"));
        headerLabel->setStyleSheet(QString::fromUtf8("font: 75 10pt \"Tahoma\";\n"
"font-weight: bold;"));
        headerLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(headerLabel, 0, 0, 1, 1);

        closeWindow = new QToolButton(ColorSearchDialog);
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

        back = new QPushButton(ColorSearchDialog);
        back->setObjectName(QString::fromUtf8("back"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(30);
        sizePolicy1.setHeightForWidth(back->sizePolicy().hasHeightForWidth());
        back->setSizePolicy(sizePolicy1);
        back->setMinimumSize(QSize(0, 30));
        back->setMaximumSize(QSize(16777215, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("Tahom"));
        font.setPointSize(8);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        back->setFont(font);
        back->setFocusPolicy(Qt::NoFocus);
        back->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahom\";\n"
"/*font-weight: bold;*/"));

        gridLayout_2->addWidget(back, 2, 1, 1, 1);

        search = new QPushButton(ColorSearchDialog);
        search->setObjectName(QString::fromUtf8("search"));
        search->setMaximumSize(QSize(16777215, 30));
        search->setFont(font);
        search->setStyleSheet(QString::fromUtf8("/*font: 75 12pt \"Times New Roman\";\n"
"font-weight: bold;*/\n"
"font: 75 8pt \"Tahom\";"));

        gridLayout_2->addWidget(search, 2, 2, 1, 1);

        ColorSearchTree = new QTreeWidget(ColorSearchDialog);
        ColorSearchTree->setObjectName(QString::fromUtf8("ColorSearchTree"));
        sizePolicy.setHeightForWidth(ColorSearchTree->sizePolicy().hasHeightForWidth());
        ColorSearchTree->setSizePolicy(sizePolicy);
        ColorSearchTree->setMinimumSize(QSize(399, 440));
        ColorSearchTree->setMaximumSize(QSize(399, 440));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        ColorSearchTree->setFont(font1);
        ColorSearchTree->setMouseTracking(false);
        ColorSearchTree->setFocusPolicy(Qt::NoFocus);
        ColorSearchTree->setContextMenuPolicy(Qt::DefaultContextMenu);
        ColorSearchTree->setStyleSheet(QString::fromUtf8("\n"
"item \n"
"{ \n"
"	font: 75 12pt \"Tahoma\";\n"
"	border-bottom: 1px solid #232323;\n"
"	/*selection-background-color: transparent;*/\n"
"	show-decoration-selected: 0;\n"
"	margin-left: 10px;\n"
"	margin-right: 10px;\n"
"	margin-top: 10px;\n"
"	margin-bottom: 10px;\n"
"}\n"
""));
        ColorSearchTree->setFrameShape(QFrame::StyledPanel);
        ColorSearchTree->setFrameShadow(QFrame::Sunken);
        ColorSearchTree->setLineWidth(4);
        ColorSearchTree->setProperty("showDropIndicator", QVariant(false));
        ColorSearchTree->setRootIsDecorated(false);
        ColorSearchTree->setWordWrap(true);
        ColorSearchTree->setColumnCount(2);
        ColorSearchTree->header()->setVisible(false);
        ColorSearchTree->header()->setCascadingSectionResizes(true);
        ColorSearchTree->header()->setDefaultSectionSize(120);
        ColorSearchTree->header()->setMinimumSectionSize(40);
        ColorSearchTree->header()->setStretchLastSection(false);

        gridLayout_2->addWidget(ColorSearchTree, 1, 0, 1, 3);


        retranslateUi(ColorSearchDialog);

        QMetaObject::connectSlotsByName(ColorSearchDialog);
    } // setupUi

    void retranslateUi(QDialog *ColorSearchDialog)
    {
        ColorSearchDialog->setWindowTitle(QApplication::translate("ColorSearchDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        headerLabel->setText(QApplication::translate("ColorSearchDialog", "Infor PLM Color Search Criteria", 0, QApplication::UnicodeUTF8));
        closeWindow->setText(QString());
        back->setText(QApplication::translate("ColorSearchDialog", "Back", 0, QApplication::UnicodeUTF8));
        search->setText(QApplication::translate("ColorSearchDialog", "Search", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ColorSearchDialog: public Ui_ColorSearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORSEARCH_H
