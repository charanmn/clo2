/********************************************************************************
** Form generated from reading UI file 'CreateProduct.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEPRODUCT_H
#define UI_CREATEPRODUCT_H

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

class Ui_createProduct
{
public:
    QGridLayout *gridLayout_2;
    QTreeWidget *createProductSearchTable;
    QGridLayout *gridLayout;
    QLabel *headerLabel;
    QToolButton *closeWindow;
    QPushButton *back;
    QPushButton *saveAndClose;
    QPushButton *sendToPlm;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *createProduct)
    {
        if (createProduct->objectName().isEmpty())
            createProduct->setObjectName(QString::fromUtf8("createProduct"));
        createProduct->resize(425, 550);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(createProduct->sizePolicy().hasHeightForWidth());
        createProduct->setSizePolicy(sizePolicy);
        createProduct->setMinimumSize(QSize(425, 550));
        createProduct->setMaximumSize(QSize(425, 550));
#ifndef QT_NO_TOOLTIP
        createProduct->setToolTip(QString::fromUtf8(""));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        createProduct->setStatusTip(QString::fromUtf8(""));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        createProduct->setWhatsThis(QString::fromUtf8(""));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        createProduct->setAccessibleName(QString::fromUtf8(""));
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        createProduct->setAccessibleDescription(QString::fromUtf8(""));
#endif // QT_NO_ACCESSIBILITY
        createProduct->setStyleSheet(QString::fromUtf8("/*margin-left: 10px;\n"
"margin-right: 10px;\n"
"margin-top: 10px;\n"
"margin-bottom: 10px;*/\n"
"#createProduct {\n"
"	margin-left: 8px;\n"
"	margin-right: 8px;\n"
"	margin-top: 8px;\n"
"	margin-bottom: 8px;\n"
"	border : 1.5px solid #232323;\n"
"}"));
        gridLayout_2 = new QGridLayout(createProduct);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        createProductSearchTable = new QTreeWidget(createProduct);
        createProductSearchTable->setObjectName(QString::fromUtf8("createProductSearchTable"));
        createProductSearchTable->setMaximumSize(QSize(16777215, 16777215));
        createProductSearchTable->setStyleSheet(QString::fromUtf8("/*\n"
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
        createProductSearchTable->setFrameShape(QFrame::StyledPanel);
        createProductSearchTable->setFrameShadow(QFrame::Sunken);
        createProductSearchTable->setLineWidth(4);
        createProductSearchTable->setProperty("showDropIndicator", QVariant(false));
        createProductSearchTable->setRootIsDecorated(false);
        createProductSearchTable->setWordWrap(true);
        createProductSearchTable->setColumnCount(2);
        createProductSearchTable->header()->setVisible(false);
        createProductSearchTable->header()->setCascadingSectionResizes(true);
        createProductSearchTable->header()->setDefaultSectionSize(120);
        createProductSearchTable->header()->setMinimumSectionSize(40);
        createProductSearchTable->header()->setStretchLastSection(false);

        gridLayout_2->addWidget(createProductSearchTable, 1, 0, 1, 4);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        headerLabel = new QLabel(createProduct);
        headerLabel->setObjectName(QString::fromUtf8("headerLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(headerLabel->sizePolicy().hasHeightForWidth());
        headerLabel->setSizePolicy(sizePolicy1);
        headerLabel->setMinimumSize(QSize(400, 30));
        headerLabel->setMaximumSize(QSize(400, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("Tahoma"));
        font.setPointSize(10);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        headerLabel->setFont(font);
#ifndef QT_NO_TOOLTIP
        headerLabel->setToolTip(QString::fromUtf8(""));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        headerLabel->setStatusTip(QString::fromUtf8(""));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        headerLabel->setWhatsThis(QString::fromUtf8(""));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        headerLabel->setAccessibleName(QString::fromUtf8(""));
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        headerLabel->setAccessibleDescription(QString::fromUtf8(""));
#endif // QT_NO_ACCESSIBILITY
        headerLabel->setStyleSheet(QString::fromUtf8("font: 75 10pt \"Tahoma\";\n"
"font-weight: bold;"));
        headerLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(headerLabel, 0, 0, 1, 1);

        closeWindow = new QToolButton(createProduct);
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

        back = new QPushButton(createProduct);
        back->setObjectName(QString::fromUtf8("back"));
        sizePolicy1.setHeightForWidth(back->sizePolicy().hasHeightForWidth());
        back->setSizePolicy(sizePolicy1);
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
""));

        gridLayout_2->addWidget(back, 2, 1, 1, 1);

        saveAndClose = new QPushButton(createProduct);
        saveAndClose->setObjectName(QString::fromUtf8("saveAndClose"));
        saveAndClose->setMaximumSize(QSize(16777215, 30));
        saveAndClose->setFont(font1);
        saveAndClose->setFocusPolicy(Qt::StrongFocus);
        saveAndClose->setContextMenuPolicy(Qt::DefaultContextMenu);
        saveAndClose->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";\n"
""));
        saveAndClose->setDefault(false);

        gridLayout_2->addWidget(saveAndClose, 2, 2, 1, 1);

        sendToPlm = new QPushButton(createProduct);
        sendToPlm->setObjectName(QString::fromUtf8("sendToPlm"));
        sendToPlm->setMaximumSize(QSize(16777215, 30));
        sendToPlm->setFont(font1);
        sendToPlm->setFocusPolicy(Qt::NoFocus);
        sendToPlm->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";\n"
""));

        gridLayout_2->addWidget(sendToPlm, 2, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 0, 1, 1);


        retranslateUi(createProduct);

        QMetaObject::connectSlotsByName(createProduct);
    } // setupUi

    void retranslateUi(QDialog *createProduct)
    {
        createProduct->setWindowTitle(QApplication::translate("createProduct", "Create Product", 0, QApplication::UnicodeUTF8));
        headerLabel->setText(QApplication::translate("createProduct", "Infor PLM Create Product", 0, QApplication::UnicodeUTF8));
        closeWindow->setText(QString());
        back->setText(QApplication::translate("createProduct", "Back", 0, QApplication::UnicodeUTF8));
        saveAndClose->setText(QApplication::translate("createProduct", " Save && Close", 0, QApplication::UnicodeUTF8));
        sendToPlm->setText(QApplication::translate("createProduct", "Send to PLM", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class createProduct: public Ui_createProduct {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEPRODUCT_H
