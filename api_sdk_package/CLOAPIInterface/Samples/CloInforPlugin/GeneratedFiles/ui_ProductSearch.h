/********************************************************************************
** Form generated from reading UI file 'ProductSearch.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCTSEARCH_H
#define UI_PRODUCTSEARCH_H

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

class Ui_ProductSearch
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *headerLabel;
    QToolButton *closeWindow;
    QPushButton *back;
    QTreeWidget *ProductSearchTree;
    QPushButton *search;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *ProductSearch)
    {
        if (ProductSearch->objectName().isEmpty())
            ProductSearch->setObjectName(QString::fromUtf8("ProductSearch"));
        ProductSearch->resize(425, 550);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ProductSearch->sizePolicy().hasHeightForWidth());
        ProductSearch->setSizePolicy(sizePolicy);
        ProductSearch->setMinimumSize(QSize(425, 550));
        ProductSearch->setMaximumSize(QSize(425, 550));
        ProductSearch->setStyleSheet(QString::fromUtf8("/*margin-left: 10px;\n"
"margin-right: 10px;\n"
"margin-top: 10px;\n"
"margin-bottom: 10px;*/\n"
"#ProductSearch {\n"
"	margin-left: 8px;\n"
"	margin-right: 8px;\n"
"	margin-top: 8px;\n"
"	margin-bottom: 8px;\n"
"	border : 1.5px solid #232323;\n"
"}"));
        gridLayout_2 = new QGridLayout(ProductSearch);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        headerLabel = new QLabel(ProductSearch);
        headerLabel->setObjectName(QString::fromUtf8("headerLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(headerLabel->sizePolicy().hasHeightForWidth());
        headerLabel->setSizePolicy(sizePolicy1);
        headerLabel->setMinimumSize(QSize(400, 30));
        headerLabel->setMaximumSize(QSize(400, 30));
        headerLabel->setStyleSheet(QString::fromUtf8("font: 75 10pt \"Tahoma\";\n"
"font-weight: bold;"));
        headerLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(headerLabel, 0, 0, 1, 1);

        closeWindow = new QToolButton(ProductSearch);
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

        back = new QPushButton(ProductSearch);
        back->setObjectName(QString::fromUtf8("back"));
        back->setMaximumSize(QSize(16777215, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("Tahoma"));
        font.setPointSize(8);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        back->setFont(font);
        back->setFocusPolicy(Qt::NoFocus);
        back->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";\n"
""));

        gridLayout_2->addWidget(back, 2, 1, 1, 1);

        ProductSearchTree = new QTreeWidget(ProductSearch);
        ProductSearchTree->setObjectName(QString::fromUtf8("ProductSearchTree"));
        ProductSearchTree->setMaximumSize(QSize(16777215, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        ProductSearchTree->setFont(font1);
        ProductSearchTree->setMouseTracking(false);
        ProductSearchTree->setFocusPolicy(Qt::NoFocus);
        ProductSearchTree->setContextMenuPolicy(Qt::DefaultContextMenu);
        ProductSearchTree->setStyleSheet(QString::fromUtf8("/*\n"
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
"font: 75 10pt \"Tahoma\";\n"
"border-bottom: 1px solid #232323;\n"
"/*selection-background-color: transparent;*/\n"
"show-decoration-selected: 0;\n"
"margin-left: 5px;\n"
"margin-right: 5px;\n"
"margin-top: 5px;\n"
"margin-bottom: 5px;\n"
"}"));
        ProductSearchTree->setFrameShape(QFrame::StyledPanel);
        ProductSearchTree->setFrameShadow(QFrame::Sunken);
        ProductSearchTree->setLineWidth(4);
        ProductSearchTree->setProperty("showDropIndicator", QVariant(false));
        ProductSearchTree->setRootIsDecorated(false);
        ProductSearchTree->setWordWrap(true);
        ProductSearchTree->setColumnCount(2);
        ProductSearchTree->header()->setVisible(false);
        ProductSearchTree->header()->setCascadingSectionResizes(true);
        ProductSearchTree->header()->setDefaultSectionSize(120);
        ProductSearchTree->header()->setMinimumSectionSize(40);
        ProductSearchTree->header()->setStretchLastSection(false);

        gridLayout_2->addWidget(ProductSearchTree, 1, 0, 1, 3);

        search = new QPushButton(ProductSearch);
        search->setObjectName(QString::fromUtf8("search"));
        search->setMaximumSize(QSize(16777215, 30));
        search->setFont(font);
        search->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";\n"
""));

        gridLayout_2->addWidget(search, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 0, 1, 1);


        retranslateUi(ProductSearch);

        QMetaObject::connectSlotsByName(ProductSearch);
    } // setupUi

    void retranslateUi(QDialog *ProductSearch)
    {
        ProductSearch->setWindowTitle(QApplication::translate("ProductSearch", "Dialog", 0, QApplication::UnicodeUTF8));
        headerLabel->setText(QApplication::translate("ProductSearch", "Infor PLM Product Search Criteria", 0, QApplication::UnicodeUTF8));
        closeWindow->setText(QString());
        back->setText(QApplication::translate("ProductSearch", "Back", 0, QApplication::UnicodeUTF8));
        search->setText(QApplication::translate("ProductSearch", "Search", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ProductSearch: public Ui_ProductSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTSEARCH_H
