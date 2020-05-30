#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QTreeWidgetItem>
#include <QTableWidgetItem>
#include "GeneratedFiles/ui_FabricsResultTable.h"
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h" 
/**
 *  This file all the variable declarations and function declarations which are used in Fabrics result table
 */
using nlohmann::json; // making use of json and mapjson from nlohmann json
using namespace std;
/**
 *  CLOPlugin namespace is used to keep all the functions and attributes in this class to be under CLOPlugin namespace.
 */
namespace CLOPlugin {
	class ResultTable : public QDialog, public Ui::ResultTable
	{
		Q_OBJECT

		static ResultTable* _instance;
		static map<int, string> headerColumns;
		static map<string, string> resultTableColumns;
		std::vector<map<string, string>> m_FabricResults;
		json m_downloadAttachmentsMap;
		string m_attachmentsFileName;
		string m_attachmentsAttaFileListId;

	public:
		ResultTable(QWidget* parent = 0, Qt::WindowFlags flags = Qt::Dialog | Qt::FramelessWindowHint);
		~ResultTable();
		static ResultTable* GetInstance();
		static void	Destroy();
		void AddRowData(map<string, string>& MaterialFabricResults, QIcon FabIcon);
		void AddColumns(QTableWidgetItem* parent, map<string, string>& MaterialFabricResults, QIcon FabIcon);
		static void setHeaderColumns(map<int, string>& headerColumns);
		static void setResultTableColumns(map<string, string>& resultTableColumns);

	private:
		static map<int, string> getHeaderColumns();
	private slots:
		void DownloadClicked();
		void Cancel_clicked();
		void OnBackClicked();
		void callCheckBoxSelected();
		void SelectAllClicked();
		void DeSelectAllClicked();
	};
}
