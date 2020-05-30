/********************************************************************************
** Form generated from reading UI file 'DesignSuite.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESIGNSUITE_H
#define UI_DESIGNSUITE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_DesignSuite
{
public:
    QGridLayout *gridLayout_4;
    QLabel *label;
    QGridLayout *gridLayout_2;
    QToolButton *Cancel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_11;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QToolButton *ShMaterial;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_3;
    QToolButton *trimsSearch;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_4;
    QToolButton *ShColor;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_5;
    QToolButton *searchProducts;
    QSpacerItem *horizontalSpacer;
    QToolButton *CreateProduct;
    QSpacerItem *horizontalSpacer_7;
    QToolButton *UpdateProduct;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_8;
    QToolButton *logout;
    QFrame *line;

    void setupUi(QDialog *DesignSuite)
    {
        if (DesignSuite->objectName().isEmpty())
            DesignSuite->setObjectName(QString::fromUtf8("DesignSuite"));
        DesignSuite->resize(760, 570);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DesignSuite->sizePolicy().hasHeightForWidth());
        DesignSuite->setSizePolicy(sizePolicy);
        DesignSuite->setMinimumSize(QSize(760, 570));
        DesignSuite->setMaximumSize(QSize(760, 570));
        DesignSuite->setAutoFillBackground(false);
        DesignSuite->setStyleSheet(QString::fromUtf8("#DesignSuite {\n"
"	margin-left: 5px;\n"
"	margin-right: 5px;\n"
"	margin-top: 5px;\n"
"	margin-bottom: 5px;\n"
"	border : 1.5px solid #232323;\n"
"}"));
        gridLayout_4 = new QGridLayout(DesignSuite);
        gridLayout_4->setSpacing(5);
        gridLayout_4->setContentsMargins(10, 10, 10, 10);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label = new QLabel(DesignSuite);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(340, 542));
        label->setMaximumSize(QSize(340, 542));
        label->setStyleSheet(QString::fromUtf8("image: url(:/CLO_PLUGIN/INFOR/images/clo-govise-image.png);"));
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);
        label->setMargin(0);
        label->setIndent(-1);

        gridLayout_4->addWidget(label, 0, 0, 3, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(9);
        Cancel = new QToolButton(DesignSuite);
        Cancel->setObjectName(QString::fromUtf8("Cancel"));
        Cancel->setMinimumSize(QSize(30, 30));
        Cancel->setMaximumSize(QSize(30, 30));
        Cancel->setStyleSheet(QString::fromUtf8("#Cancel {\n"
"    qproperty-icon: none;\n"
"    image: url(:/CLO_PLUGIN/INFOR/images/icon_cancel_none.svg);\n"
"}\n"
"#Cancel:hover {\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_cancel_over.svg);\n"
"}"));
        Cancel->setIconSize(QSize(18, 18));

        gridLayout_2->addWidget(Cancel, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(25, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        label_11 = new QLabel(DesignSuite);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);
        label_11->setMinimumSize(QSize(300, 35));
        label_11->setMaximumSize(QSize(300, 35));
        QFont font;
        font.setFamily(QString::fromUtf8("Tahoma"));
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        label_11->setFont(font);
        label_11->setStyleSheet(QString::fromUtf8("/*font: 75 16pt \"Times New Roman\";*/\n"
"font: 75 12pt \"Tahoma\";\n"
"font-weight: bold;"));
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_11, 0, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 0, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        label_2 = new QLabel(DesignSuite);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Tahoma\";\n"
"font-weight: bold;"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        ShMaterial = new QToolButton(DesignSuite);
        ShMaterial->setObjectName(QString::fromUtf8("ShMaterial"));
        ShMaterial->setMinimumSize(QSize(55, 55));
        ShMaterial->setMaximumSize(QSize(55, 55));
        ShMaterial->setStyleSheet(QString::fromUtf8("image: url(:/CLO_PLUGIN/INFOR/images/icon_search_over.svg);\n"
"/*#ShMaterial {\n"
"    qproperty-icon: none;\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_search_none.svg);\n"
"}\n"
"#ShMaterial:hover {\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_search_over.svg);\n"
"}*/"));

        gridLayout->addWidget(ShMaterial, 1, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 2, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 3, 0, 1, 1);

        label_3 = new QLabel(DesignSuite);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Tahoma\";\n"
"font-weight: bold;"));

        gridLayout->addWidget(label_3, 3, 1, 1, 1);

        trimsSearch = new QToolButton(DesignSuite);
        trimsSearch->setObjectName(QString::fromUtf8("trimsSearch"));
        trimsSearch->setMinimumSize(QSize(55, 55));
        trimsSearch->setMaximumSize(QSize(55, 55));
        trimsSearch->setStyleSheet(QString::fromUtf8("image: url(:/CLO_PLUGIN/INFOR/images/icon_search_over.svg);\n"
"/*#trimsSearch {\n"
"    qproperty-icon: none;\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_search_none.svg);\n"
"}\n"
"#trimsSearch:hover {\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_search_over.svg);\n"
"}*/\n"
""));

        gridLayout->addWidget(trimsSearch, 3, 2, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 4, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 5, 0, 1, 1);

        label_4 = new QLabel(DesignSuite);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Tahoma\";\n"
"font-weight: bold;"));

        gridLayout->addWidget(label_4, 5, 1, 1, 1);

        ShColor = new QToolButton(DesignSuite);
        ShColor->setObjectName(QString::fromUtf8("ShColor"));
        ShColor->setMinimumSize(QSize(55, 55));
        ShColor->setMaximumSize(QSize(55, 55));
        ShColor->setStyleSheet(QString::fromUtf8("image: url(:/CLO_PLUGIN/INFOR/images/icon_search_over.svg);\n"
"/*#ShColor {\n"
"    qproperty-icon: none;\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_search_none.svg);\n"
"}\n"
"#ShColor:hover {\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_search_over.svg);\n"
"}*/"));

        gridLayout->addWidget(ShColor, 5, 2, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_5, 6, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 7, 0, 1, 1);

        label_5 = new QLabel(DesignSuite);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Tahoma\";\n"
"font-weight: bold;"));

        gridLayout->addWidget(label_5, 7, 1, 1, 1);

        searchProducts = new QToolButton(DesignSuite);
        searchProducts->setObjectName(QString::fromUtf8("searchProducts"));
        searchProducts->setMinimumSize(QSize(55, 55));
        searchProducts->setMaximumSize(QSize(55, 55));
        searchProducts->setStyleSheet(QString::fromUtf8("image: url(:/CLO_PLUGIN/INFOR/images/icon_search_over.svg);\n"
"/*#searchProducts {\n"
"    qproperty-icon: none;\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_search_none.svg);\n"
"}\n"
"#searchProducts:hover {\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_search_over.svg);\n"
"}*/"));

        gridLayout->addWidget(searchProducts, 7, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 7, 3, 1, 1);

        CreateProduct = new QToolButton(DesignSuite);
        CreateProduct->setObjectName(QString::fromUtf8("CreateProduct"));
        CreateProduct->setMinimumSize(QSize(55, 55));
        CreateProduct->setMaximumSize(QSize(55, 55));
        CreateProduct->setStyleSheet(QString::fromUtf8("image: url(:/CLO_PLUGIN/INFOR/images/icon_add_over.svg);\n"
"/*#CreateProduct {\n"
"    qproperty-icon: none;	\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_add_none.svg);\n"
"}\n"
"#CreateProduct:hover {\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_add_over.svg);\n"
"}*/"));

        gridLayout->addWidget(CreateProduct, 7, 4, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 7, 5, 1, 1);

        UpdateProduct = new QToolButton(DesignSuite);
        UpdateProduct->setObjectName(QString::fromUtf8("UpdateProduct"));
        UpdateProduct->setMinimumSize(QSize(55, 55));
        UpdateProduct->setMaximumSize(QSize(55, 55));
        UpdateProduct->setStyleSheet(QString::fromUtf8("image: url(:/CLO_PLUGIN/INFOR/images/icon_update_over.svg);\n"
"/*#UpdateProduct {\n"
"    qproperty-icon: none;	\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_update_none.svg);\n"
"}\n"
"#UpdateProduct:hover {\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_update_over.svg);\n"
"}*/"));

        gridLayout->addWidget(UpdateProduct, 7, 6, 1, 1);


        gridLayout_4->addLayout(gridLayout, 1, 1, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_8, 1, 0, 1, 1);

        logout = new QToolButton(DesignSuite);
        logout->setObjectName(QString::fromUtf8("logout"));
        logout->setMinimumSize(QSize(45, 45));
        logout->setMaximumSize(QSize(45, 45));
        logout->setStyleSheet(QString::fromUtf8("image: url(:/CLO_PLUGIN/INFOR/images/iconmonstr-log-out-11.svg);\n"
"/*#UpdateProduct {\n"
"    qproperty-icon: none;	\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_update_none.svg);\n"
"}\n"
"#UpdateProduct:hover {\n"
"	image: url(:/CLO_PLUGIN/INFOR/images/icon_update_over.svg);\n"
"}*/"));
        logout->setIconSize(QSize(18, 18));

        gridLayout_3->addWidget(logout, 1, 1, 1, 1);

        line = new QFrame(DesignSuite);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("color: rgb(160, 160, 160);"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(3);
        line->setFrameShape(QFrame::HLine);

        gridLayout_3->addWidget(line, 0, 0, 1, 2);


        gridLayout_4->addLayout(gridLayout_3, 2, 1, 1, 1);


        retranslateUi(DesignSuite);

        QMetaObject::connectSlotsByName(DesignSuite);
    } // setupUi

    void retranslateUi(QDialog *DesignSuite)
    {
        DesignSuite->setWindowTitle(QApplication::translate("DesignSuite", "PLMPanel", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        Cancel->setText(QString());
        label_11->setText(QApplication::translate("DesignSuite", "Infor PLM Design Suite", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DesignSuite", "Fabrics", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ShMaterial->setToolTip(QApplication::translate("DesignSuite", "<html><head/><body><p><span style=\" font-size:10pt; color: #FFFFFF; background-color: #000000;\">Search</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ShMaterial->setText(QString());
        label_3->setText(QApplication::translate("DesignSuite", "Trims", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        trimsSearch->setToolTip(QApplication::translate("DesignSuite", "<html><head/><body><p><span style=\" font-size:10pt; color: #FFFFFF; background-color: #000000;\">Search</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        trimsSearch->setText(QString());
        label_4->setText(QApplication::translate("DesignSuite", "Colors", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ShColor->setToolTip(QApplication::translate("DesignSuite", "<html><head/><body><p><span style=\" font-size:10pt; color: #FFFFFF; background-color: #000000;\">Search</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ShColor->setText(QString());
        label_5->setText(QApplication::translate("DesignSuite", "Products", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        searchProducts->setToolTip(QApplication::translate("DesignSuite", "<html><head/><body><p><span style=\" font-size:10pt; color: #FFFFFF; background-color: #000000;\">Search</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        searchProducts->setText(QString());
#ifndef QT_NO_TOOLTIP
        CreateProduct->setToolTip(QApplication::translate("DesignSuite", "<html><head/><body><p><span style=\" font-size:10pt; color: #FFFFFF; background-color: #000000;\">Create</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        CreateProduct->setText(QString());
#ifndef QT_NO_TOOLTIP
        UpdateProduct->setToolTip(QApplication::translate("DesignSuite", "<html><head/><body><p><span style=\" font-size:10pt; color: #FFFFFF; background-color: #000000;\">Update</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        UpdateProduct->setText(QString());
#ifndef QT_NO_TOOLTIP
        logout->setToolTip(QApplication::translate("DesignSuite", "<html><body><p><span style=\" font-size:10pt; color: #FFFFFF; background-color: #000000;\">Logout</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        logout->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DesignSuite: public Ui_DesignSuite {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESIGNSUITE_H
