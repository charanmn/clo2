#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QTreeWidgetItem>
#include <QTableWidgetItem>
#include "ui_TrimsResultTable.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
/**
 *  This file all the variable declarations and function declarations which are used in trims result table  
 */
using nlohmann::json;  // making use of json and mapjson from nlohmann json
using namespace std;
/**
 *  CLOPlugin namespace is used to keep all the functions in this class to be under CLOPlugin namespace.
 */
namespace CLOPlugin {
	class TrimsResultTable : public QDialog, public Ui::TrimsResultTable
	{
		Q_OBJECT
			std::vector<map<string, string>> m_trimsResults;
			static TrimsResultTable* _instance;
			static map<int, string> headerColumns;
			static map<string, string> resultTableColumns;

		public:
			TrimsResultTable(QWidget* parent = 0, Qt::WindowFlags flags = Qt::Dialog | Qt::FramelessWindowHint);
			~TrimsResultTable();
			static TrimsResultTable* GetInstance();
			static void	Destroy();
			void AddRowData(map<string, string>& TrimsResults, QIcon FabIcon);
			void AddColumns(QTableWidgetItem* parent, map<string, string>& TrimsResults, QIcon FabIcon);
			static void SetHeaderColumns(map<int, string>& headerColumns);
			static void SetResultTableColumns(map<string, string>& resultTableColumns);

		private:
			static map<int, string> GetHeaderColumns();

		private slots:
			void DownloadClicked();
			void Cancel_clicked();
			void OnBackClicked();
			void callCheckBoxSelected();
			void SelectAllClicked();
			void DeSelectAllClicked();
	};
}
