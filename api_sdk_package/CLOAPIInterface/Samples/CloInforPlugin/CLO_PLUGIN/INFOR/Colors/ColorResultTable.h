
#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QTreeWidgetItem>
#include "Ui_ColorResultTable.h"
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"

using namespace std; 
using nlohmann::json;
/*
*Brief having all the methods declaration to use in ColorResultTable.cpp file.
*using private slots to connecting the signals.
*nlohmann used for parsing and mapping json.
*/
namespace CLOPlugin
{

	class ColorResultTable : public QDialog, public Ui::ColorResultTable
	{
		Q_OBJECT
			
		static ColorResultTable* _instance;
		QTableWidgetItem* m_headerItem;
		std::vector<map<string, string>> m_colorResults;
		static map<int, string> headerColumns;
		static map<string, string> resultTableColumns;

	public:
		string	m_strSwatchName;
		Marvelous::CloApiRgb m_rgbValues;
		CLOAPI::UtilityAPIInterface m_objUtilityAPI;
		int m_count;
		string	m_strRetSwatchColor;
		string  m_colorSwatchfilename;
		
		ColorResultTable(QWidget* parent = 0, Qt::WindowFlags flags = Qt::Dialog | Qt::FramelessWindowHint);
		~ColorResultTable();		
		static ColorResultTable* GetInstance();
		static void	Destroy();			
		void AddRowData(map<string, string>& colorResults);
		void AddColumns(QTableWidgetItem* parent, map<string, string>& colorResults);
		
		void SetRowCount(int count);
		static void setHeaderColumns(map<int, string>& headerColumns);
		static map<int, string> getHeaderColumns();
		static void setResultTableColumns(map<string, string>& columns);

	private slots:
		void colorResultTableBack_clicked();
		void colorResultTableCancel_clicked();
		void colorResultTableDownload_clicked();
		void callCheckBoxSelected();
		void SelectAllClicked();
		void DeSelectAllClicked();
	};
}
