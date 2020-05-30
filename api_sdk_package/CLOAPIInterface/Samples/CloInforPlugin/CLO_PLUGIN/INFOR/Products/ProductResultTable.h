#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QTreeWidgetItem>
#include "GeneratedFiles/ui_ProductResultTable.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"
#include "CLO_PLUGIN/INFOR/Utilities/Definitions.h"
#include "CLO_PLUGIN/INFOR/Libraries/json.h"

using nlohmann::json;
using namespace std;

namespace CLOPlugin
{
	class ProductResultTable : public QDialog, public Ui::ProductResultTable
	{
		Q_OBJECT
		std::vector<map<string, string>> m_productResults;
		QTreeWidgetItem* m_headerItem;
		string m_attachmentsFileName;
		string m_attachmentsAttaFileListId;
		string m_attachmentURL;
		static map<float, string> headerColumns;
		static map<string, string> resultTableColumns;

	public:
		ProductResultTable(QWidget* parent = 0, Qt::WindowFlags flags = Qt::Dialog | Qt::FramelessWindowHint);
		~ProductResultTable();
		void AddRowData(map<string, string>& productResults, QIcon styleIcon);
		void AddColumns(QTableWidgetItem* parent, map<string, string>& productResults, QIcon styleIcon);
		static void setHeaderColumns(map<float, string>& headerColumns);
		static void setResultTableColumns(map<string, string>& resultTableColumns);

	private:
		static map<float, string> getHeaderColumns();

	private slots:
		 
		void productResultTableBack_clicked();
		void productResultTableCancel_clicked();
		void productResultTableDownload_clicked();
		void callRadioSelected();
	};
}
