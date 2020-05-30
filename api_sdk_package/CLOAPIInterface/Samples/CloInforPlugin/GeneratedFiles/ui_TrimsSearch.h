/********************************************************************************
** Form generated from reading UI file 'TrimsSearch.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRIMSSEARCH_H
#define UI_TRIMSSEARCH_H

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

class Ui_TrimsSearch
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *headerLabel;
    QToolButton *closeWindow;
    QTreeWidget *TrimsSearchTree;
    QSpacerItem *horizontalSpacer;
    QPushButton *back;
    QPushButton *search;

    void setupUi(QDialog *TrimsSearch)
    {
        if (TrimsSearch->objectName().isEmpty())
            TrimsSearch->setObjectName(QString::fromUtf8("TrimsSearch"));
        TrimsSearch->resize(425, 550);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TrimsSearch->sizePolicy().hasHeightForWidth());
        TrimsSearch->setSizePolicy(sizePolicy);
        TrimsSearch->setMinimumSize(QSize(425, 550));
        TrimsSearch->setMaximumSize(QSize(425, 550));
        TrimsSearch->setStyleSheet(QString::fromUtf8("/*margin-left: 5px;\n"
"margin-right: 5px;\n"
"margin-top: 5px;\n"
"margin-bottom: 5px;\n"
"border-top : 1px solid #232323;\n"
"border-bottom : 1px solid #232323;\n"
"border-top : 1px solid #232323;\n"
"border-top : 1px solid #232323;*/\n"
"#TrimsSearch \n"
"{\n"
"	margin-left: 8px;\n"
"	margin-right: 8px;\n"
"	margin-top: 8px;\n"
"	margin-bottom: 8px;\n"
"	border : 1.5px solid #232323;\n"
"}"));
        gridLayout_2 = new QGridLayout(TrimsSearch);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        headerLabel = new QLabel(TrimsSearch);
        headerLabel->setObjectName(QString::fromUtf8("headerLabel"));
        headerLabel->setStyleSheet(QString::fromUtf8("font: 75 10pt \"Tahoma\";\n"
"font-weight: bold;"));
        headerLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(headerLabel, 0, 0, 1, 1);

        closeWindow = new QToolButton(TrimsSearch);
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

        TrimsSearchTree = new QTreeWidget(TrimsSearch);
        TrimsSearchTree->setObjectName(QString::fromUtf8("TrimsSearchTree"));
        sizePolicy.setHeightForWidth(TrimsSearchTree->sizePolicy().hasHeightForWidth());
        TrimsSearchTree->setSizePolicy(sizePolicy);
        TrimsSearchTree->setMinimumSize(QSize(399, 440));
        TrimsSearchTree->setMaximumSize(QSize(399, 440));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        TrimsSearchTree->setFont(font);
        TrimsSearchTree->setMouseTracking(false);
        TrimsSearchTree->setFocusPolicy(Qt::NoFocus);
        TrimsSearchTree->setContextMenuPolicy(Qt::DefaultContextMenu);
        TrimsSearchTree->setStyleSheet(QString::fromUtf8("\n"
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
        TrimsSearchTree->setFrameShape(QFrame::StyledPanel);
        TrimsSearchTree->setFrameShadow(QFrame::Sunken);
        TrimsSearchTree->setLineWidth(4);
        TrimsSearchTree->setProperty("showDropIndicator", QVariant(false));
        TrimsSearchTree->setRootIsDecorated(false);
        TrimsSearchTree->setWordWrap(true);
        TrimsSearchTree->setColumnCount(2);
        TrimsSearchTree->header()->setVisible(false);
        TrimsSearchTree->header()->setCascadingSectionResizes(true);
        TrimsSearchTree->header()->setDefaultSectionSize(120);
        TrimsSearchTree->header()->setMinimumSectionSize(40);
        TrimsSearchTree->header()->setStretchLastSection(false);

        gridLayout_2->addWidget(TrimsSearchTree, 1, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 0, 1, 1);

        back = new QPushButton(TrimsSearch);
        back->setObjectName(QString::fromUtf8("back"));
        back->setMaximumSize(QSize(16777215, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Tahoma"));
        font1.setPointSize(8);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(9);
        back->setFont(font1);
        back->setFocusPolicy(Qt::NoFocus);
        back->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";\n"
"/*font-weight: bold;*/"));

        gridLayout_2->addWidget(back, 2, 1, 1, 1);

        search = new QPushButton(TrimsSearch);
        search->setObjectName(QString::fromUtf8("search"));
        search->setMaximumSize(QSize(16777215, 30));
        search->setFont(font1);
        search->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";\n"
"/*font-weight: bold;*/"));

        gridLayout_2->addWidget(search, 2, 2, 1, 1);


        retranslateUi(TrimsSearch);

        QMetaObject::connectSlotsByName(TrimsSearch);
    } // setupUi

    void retranslateUi(QDialog *TrimsSearch)
    {
        TrimsSearch->setWindowTitle(QApplication::translate("TrimsSearch", "Dialog", 0, QApplication::UnicodeUTF8));
        headerLabel->setText(QApplication::translate("TrimsSearch", "Infor PLM Trims Search Criteria", 0, QApplication::UnicodeUTF8));
        closeWindow->setText(QString());
        back->setText(QApplication::translate("TrimsSearch", "Back", 0, QApplication::UnicodeUTF8));
        search->setText(QApplication::translate("TrimsSearch", "Search", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TrimsSearch: public Ui_TrimsSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRIMSSEARCH_H
