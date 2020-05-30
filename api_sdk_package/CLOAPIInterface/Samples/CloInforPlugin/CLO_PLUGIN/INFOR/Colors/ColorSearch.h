#pragma once

#include <QDialog>
#include <string>
#include <iostream>
#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QLabel> 
#include <QTreeWidgetItem>
#include <QTableWidgetItem>
#include <vector>
#include <map>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "ui_ColorSearch.h"
#include "GeneratedFiles/ui_ColorSearch.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"
#include "include/UtilityAPIInterface.h"
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
/*
*Brief having all the methods declaration to use in ColorSearch.cpp file.
*using private slots to connecting the signals.
*nlohmann used for parsing and mapping json.
*/
using json = nlohmann::json;

namespace CLOPlugin
{
	class  ColorSearch : public QDialog, public Ui::ColorSearchDialog
	{
		Q_OBJECT
			std::vector<Utility::Fields> m_colorsFieldsVector;
		static ColorSearch* _instance;
		bool m_isUserInputEmpty;
		bool m_colorPaletteSearch;
		json m_colorSearchMap;
		json m_colorPaletteSearchMap;
		std::map<string, string> m_attributeMap;
		std::map<string, string> columnsMap;
		map<string, map<string, string>> m_attsDropdownListMap;
		bool m_solid;
		bool m_isOnlyPercentileFound;
		map<int, string, less <int> > indexColumnIdMap;
		map<string, string> GetFieldUITypes();
		string client_version;
		int m_maxRowCount;
	public:
		ColorSearch(QWidget* parent = 0);
		static ColorSearch* GetInstance();
		static void Destroy();	
		~ColorSearch();
		QString m_strSubType;
		void ReadJsonAndDrawDialog();
		void ReadInforJson();
		void DrawWidget(std::vector<Utility::Fields>& fieldsVector);
		bool ExtractAllUIValuesAndMapToJson();
		void CreateResultTable(json& responseJson);
		void GetFilteredColorJson();
		void ClearAllFields();
		void PLMSearch();
		void CreateSearchMap();
		json GetColorPaletteList();
		json GetPaletteColorSearchResults(json& responseJson);
		json GetColorSearchResults(json& responseJson);
		json GetFilteredColorResults(json& paletteColorsResults, json& colorsResults);
		bool SearchValidation();
		std::list<string> getVisibleFieldList();

	private slots:
		void Search_clicked();

		void Cancel_clicked();

		void back_clicked();

	};
}
