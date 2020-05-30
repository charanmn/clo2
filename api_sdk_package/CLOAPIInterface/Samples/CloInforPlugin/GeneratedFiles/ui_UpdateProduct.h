/********************************************************************************
** Form generated from reading UI file 'UpdateProduct.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEPRODUCT_H
#define UI_UPDATEPRODUCT_H

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

class Ui_UpdateProduct
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *headerLabel;
    QToolButton *closeWindow;
    QTreeWidget *updateProductTree;
    QPushButton *back;
    QPushButton *saveAndClose;
    QPushButton *updateInPlm;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *UpdateProduct)
    {
        if (UpdateProduct->objectName().isEmpty())
            UpdateProduct->setObjectName(QString::fromUtf8("UpdateProduct"));
        UpdateProduct->resize(425, 550);
        UpdateProduct->setMinimumSize(QSize(425, 550));
        UpdateProduct->setMaximumSize(QSize(425, 550));
        UpdateProduct->setStyleSheet(QString::fromUtf8("/*margin-left: 10px;\n"
"margin-right: 10px;\n"
"margin-top: 10px;\n"
"margin-bottom: 10px;*/\n"
"#UpdateProduct {\n"
"	margin-left: 8px;\n"
"	margin-right: 8px;\n"
"	margin-top: 8px;\n"
"	margin-bottom: 8px;\n"
"	border : 1.5px solid #232323;\n"
"}"));
        gridLayout_2 = new QGridLayout(UpdateProduct);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        headerLabel = new QLabel(UpdateProduct);
        headerLabel->setObjectName(QString::fromUtf8("headerLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(headerLabel->sizePolicy().hasHeightForWidth());
        headerLabel->setSizePolicy(sizePolicy);
        headerLabel->setMinimumSize(QSize(400, 30));
        headerLabel->setMaximumSize(QSize(400, 30));
        headerLabel->setStyleSheet(QString::fromUtf8("font: 75 10pt \"Tahoma\";\n"
"font-weight: bold;"));
        headerLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(headerLabel, 0, 0, 1, 1);

        closeWindow = new QToolButton(UpdateProduct);
        closeWindow->setObjectName(QString::fromUtf8("closeWindow"));
        closeWindow->setStyleSheet(QString::fromUtf8("#closeWindow {\n"
"    qproperty-icon: none;\n"
"    image: url(:/CLO_PLUGIN/INFOR/images/icon_cancel_none.svg);\n"
"}\n"
"#closeWindow:hover {\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_cancel_over.svg);\n"
"}"));

        gridLayout->addWidget(closeWindow, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 4);

        updateProductTree = new QTreeWidget(UpdateProduct);
        updateProductTree->setObjectName(QString::fromUtf8("updateProductTree"));
        updateProductTree->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        updateProductTree->setFont(font);
        updateProductTree->setMouseTracking(false);
        updateProductTree->setFocusPolicy(Qt::NoFocus);
        updateProductTree->setContextMenuPolicy(Qt::DefaultContextMenu);
        updateProductTree->setStyleSheet(QString::fromUtf8("/*\n"
"item \n"
"{ \n"
"	font: 75 16pt \"Times New Roman\";\n"
"	border-bottom: 1px solid #232323;\n"
"	//*selection-background-color: transparent;\n"
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
        updateProductTree->setFrameShape(QFrame::StyledPanel);
        updateProductTree->setFrameShadow(QFrame::Sunken);
        updateProductTree->setLineWidth(4);
        updateProductTree->setProperty("showDropIndicator", QVariant(false));
        updateProductTree->setRootIsDecorated(false);
        updateProductTree->setWordWrap(true);
        updateProductTree->setColumnCount(2);
        updateProductTree->header()->setVisible(false);
        updateProductTree->header()->setCascadingSectionResizes(true);
        updateProductTree->header()->setDefaultSectionSize(120);
        updateProductTree->header()->setMinimumSectionSize(40);
        updateProductTree->header()->setStretchLastSection(false);

        gridLayout_2->addWidget(updateProductTree, 1, 0, 1, 4);

        back = new QPushButton(UpdateProduct);
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
        back->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";"));

        gridLayout_2->addWidget(back, 2, 1, 1, 1);

        saveAndClose = new QPushButton(UpdateProduct);
        saveAndClose->setObjectName(QString::fromUtf8("saveAndClose"));
        saveAndClose->setMaximumSize(QSize(16777215, 30));
        saveAndClose->setFont(font1);
        saveAndClose->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";"));

        gridLayout_2->addWidget(saveAndClose, 2, 2, 1, 1);

        updateInPlm = new QPushButton(UpdateProduct);
        updateInPlm->setObjectName(QString::fromUtf8("updateInPlm"));
        updateInPlm->setMaximumSize(QSize(16777215, 30));
        updateInPlm->setFont(font1);
        updateInPlm->setFocusPolicy(Qt::NoFocus);
        updateInPlm->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";"));

        gridLayout_2->addWidget(updateInPlm, 2, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 0, 1, 1);


        retranslateUi(UpdateProduct);
        QObject::connect(back, SIGNAL(clicked()), UpdateProduct, SLOT(accept()));
        QObject::connect(saveAndClose, SIGNAL(clicked()), UpdateProduct, SLOT(reject()));

        QMetaObject::connectSlotsByName(UpdateProduct);
    } // setupUi

    void retranslateUi(QDialog *UpdateProduct)
    {
        UpdateProduct->setWindowTitle(QApplication::translate("UpdateProduct", "Dialog", 0, QApplication::UnicodeUTF8));
        headerLabel->setText(QApplication::translate("UpdateProduct", "Infor PLM Update Product", 0, QApplication::UnicodeUTF8));
        closeWindow->setText(QString());
        back->setText(QApplication::translate("UpdateProduct", "Back", 0, QApplication::UnicodeUTF8));
        saveAndClose->setText(QApplication::translate("UpdateProduct", "Save && Close", 0, QApplication::UnicodeUTF8));
        updateInPlm->setText(QApplication::translate("UpdateProduct", "Update in PLM", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UpdateProduct: public Ui_UpdateProduct {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEPRODUCT_H
