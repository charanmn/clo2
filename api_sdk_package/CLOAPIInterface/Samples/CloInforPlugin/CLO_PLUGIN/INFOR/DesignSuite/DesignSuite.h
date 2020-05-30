#pragma once

#include <QDialog>
#include <string>
#include <iostream>
#include "GeneratedFiles/ui_DesignSuite.h"
/*
*Brief having all the methods declaration to use in DesignSuite.cpp file.
*using private slots to connecting the signals.
*/
using namespace std;

namespace CLOPlugin {

	class DesignSuite : public QDialog, public Ui::DesignSuite
	{
		Q_OBJECT
			static DesignSuite* _instance;

	public:
		DesignSuite(QWidget* parent = 0, Qt::WindowFlags flags = Qt::Dialog | Qt::FramelessWindowHint);
		~DesignSuite();
		static DesignSuite*	GetInstance();
		static void			Destroy();

	private slots:
		void materialSearch();
		void closeWindow();
		void clickedCreatProd();
		void clickedUpdateProd();
		void clickedSearchProd();
		void clickedSearchColors();
		void clickedSearchTrims();
		void clickedLogout();
	};
}