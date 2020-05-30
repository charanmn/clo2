#include "ColorResultTable.h"
#include "CLO_PLUGIN/INFOR/DesignSuite/DesignSuite.h"
#include <qmessagebox.h>
#include <qcheckbox.h>
#include <direct.h>
#include "classes/APICLODataBase.h"
#include "classes/APIStorage.h"
#include <CLOAPIInterface.h>
#include "ColorSearch.h"
#include <iostream>
#include "classes/APIStorage.h"
#include "CLO_PLUGIN/INFOR/Utilities/Definitions.h"
map<string, string> plmColorIDtoColorNameList; 
map<string, Marvelous::CloApiRgb> plmIDtoColorList; 
/* 
*brief having the methods for navigating all the functions for colorResult related.
*/
using namespace std;

namespace CLOPlugin
{
	ColorResultTable* ColorResultTable::_instance = NULL;
	map<int, string> ColorResultTable::headerColumns;
	map<string, string> ColorResultTable::resultTableColumns;

	ColorResultTable* ColorResultTable::GetInstance()
	{
		Utility::Logger("ColorResultTable -> GetInstance() -> Start");
		if (_instance == NULL)
		{
			_instance = new ColorResultTable();
		}
		Utility::Logger("ColorResultTable -> GetInstance() -> End");
		return _instance;
	}

	void ColorResultTable::Destroy()
	{
		Utility::Logger("ColorResultTable -> Destroy() -> Start");
		if (_instance)
		{
			delete _instance;
			_instance = NULL;
		}
		Utility::Logger("ColorResultTable -> Destroy() -> End");
	}

	ColorResultTable::ColorResultTable(QWidget* parent, Qt::WindowFlags flags) : QDialog(parent, flags)
	{
		Utility::Logger("ColorResultTable -> Costructor() -> Start");
		setupUi(this);
		colorResultsTable->setFixedSize(RESULT_TABLE_WIDTH, RESULT_TABLE_HEIGHT);
		m_strSwatchName = "PLM Solid Colors";
		QFont font;
		font.setPointSize(15);
		font.setBold(true);
		font.setFamily("Times New Roman");	

		colorResultsTable->resizeColumnsToContents();
		colorResultsTable->resizeRowsToContents();
		colorResultsTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
		colorResultsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		colorResultsTable->horizontalHeader()->setFont(font);
		colorResultsTable->setWordWrap(true);
		colorResultsTable->horizontalHeader()->setStretchLastSection(true);
		m_headerItem = new QTableWidgetItem;
		colorResultsTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		colorResultsTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		colorResultsTable->horizontalHeader()->setFixedHeight(80);
		colorResultsTable->horizontalHeader()->setDefaultSectionSize(80);
		colorResultsTable->resizeColumnsToContents();
		colorResultsTable->verticalHeader()->setDefaultSectionSize(80);
		colorResultsTable->verticalHeader()->blockSignals(true);
		colorResultsTable->setMouseTracking(true);
		colorResultsTable->viewport()->setMouseTracking(true);
		QStringList headerlist;
		int count = 1;
		headerlist.insert(0, "Select");

		map<int, string> headerColumns = getHeaderColumns();
		colorResultsTable->setColumnCount(headerColumns.size()+ 2);
		
		json keyValuePairJson = Utility::GetKeyValuePairs();
		for (auto key = headerColumns.begin(); key != headerColumns.end(); ++key) {
			QString column;
			if (count == 3) {
				headerlist.insert(count, QString("Color"));
				count++;
			}

			if (resultTableColumns.find(key->second) != resultTableColumns.end()) {
				column = QString::fromStdString(resultTableColumns.at(key->second));
			}
			else {
				column = Utility::GetDisplayValueByKey(QString::fromStdString(key->second), QString("color"), keyValuePairJson);
			}
			
			std::replace(column.begin(), column.end(), ' ', '\n');
			if (column == "")
			{
				headerlist.insert(count, QString::fromStdString(key->second));
			}
			else
			{
				headerlist.insert(count, column);
			}
			count++;
		}


		QTableWidgetItem* itemCheckbox = new QTableWidgetItem(" ");
		itemCheckbox->setCheckState(Qt::Unchecked);
		QModelIndexList selection = colorResultsTable->selectionModel()->selectedRows();
		colorResultsTable->setItem(0, 0, itemCheckbox);
		colorResultsTable->setHorizontalHeaderLabels(headerlist);

		back->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_back_over.svg"));
		back->setIconSize(QSize(iconHieght, iconWidth));
		back->setFixedSize(BUTTON_WIDTH_1, BUTTON_HEIGHT);
		back->setStyleSheet(buttonFont);

		download->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_down_over.svg"));
		download->setIconSize(QSize(iconHieght, iconWidth));
		download->setFixedSize(BUTTON_WIDTH_2, BUTTON_HEIGHT);
		download->setStyleSheet(buttonFont);

		SelectAll->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_ok_over.svg"));
		SelectAll->setIconSize(QSize(iconHieght, iconWidth));
		SelectAll->setFixedSize(BUTTON_WIDTH_2, BUTTON_HEIGHT);
		SelectAll->setStyleSheet(buttonFont);

		DeSelectAll->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_ok_none.svg"));
		DeSelectAll->setIconSize(QSize(iconHieght, iconWidth));
		DeSelectAll->setFixedSize(BUTTON_WIDTH_3, BUTTON_HEIGHT);
		DeSelectAll->setStyleSheet(buttonFont);

		QObject::connect(download, SIGNAL(clicked()), this, SLOT(colorResultTableDownload_clicked()));
		QObject::connect(closeWindow, SIGNAL(clicked()), this, SLOT(colorResultTableCancel_clicked()));
		QObject::connect(back, SIGNAL(clicked()), this, SLOT(colorResultTableBack_clicked()));
		QObject::connect(SelectAll, SIGNAL(clicked()), this, SLOT(SelectAllClicked()));
		QObject::connect(DeSelectAll, SIGNAL(clicked()), this, SLOT(DeSelectAllClicked()));

		Utility::Logger("ColorResultTable -> Costructor() -> End");
	}

	ColorResultTable::~ColorResultTable()
	{

	}
	/*
	*brief select all the checkbox.
	*higllight all the selected rows.
	*/
	void ColorResultTable::SelectAllClicked()
	{
		Utility::Logger("ColorResultTable::SelectAllClicked() Started...");
		colorResultsTable->setSelectionMode(QAbstractItemView::MultiSelection);
		QStringList selectedRows;
		selectedRows.clear();
		colorResultsTable->clearSelection();
		for (int i = 0; i < colorResultsTable->rowCount(); i++)
		{
			QWidget* qWidget1 = colorResultsTable->cellWidget(i, 0);
			QCheckBox* temp = qobject_cast<QCheckBox*>(qWidget1);
			if (temp->isEnabled())
			{
				temp->setCheckState(Qt::Checked);
				selectedRows << QString::fromStdString(to_string(i));
			}
		}
		for (auto iterate : selectedRows)
		{
			colorResultsTable->selectRow(iterate.toInt());
		}
		Utility::Logger("ColorResultTable::SelectAllClicked() Ended...");
	}
	/*
	*brief de select all the checkbox.
	*/
	void ColorResultTable::DeSelectAllClicked()
	{
		Utility::Logger("ColorResultTable::DeSelectAllClicked() Started...");
		for (int i = 0; i < colorResultsTable->rowCount(); i++)
		{
			QWidget* qWidget1 = colorResultsTable->cellWidget(i, 0);
			QCheckBox* temp = qobject_cast<QCheckBox*>(qWidget1);
			if (temp->checkState() == Qt::Checked)
			{
				temp->setCheckState(Qt::Unchecked);
				colorResultsTable->clearSelection();
			}
		}
		Utility::Logger("ColorResultTable::DeSelectAllClicked() Ended...");
	}
	/*
	*brief click of back button go back to ColorSearch UI.
	*/
	void ColorResultTable::colorResultTableBack_clicked()
	{
		Utility::Logger("ColorResultTable -> colorResultTableBack_clicked() -> Start");
		this->hide();
		ColorSearch::GetInstance()->setModal(true);
		ColorSearch::GetInstance()->show();
		Utility::Logger("ColorResultTable -> colorResultTableBack_clicked() -> End");
	}
	/*
	*brief click of cancel button close ColorResultTable UI.
	*/
	void ColorResultTable::colorResultTableCancel_clicked()
	{
		Utility::Logger("ColorResultTable -> colorResultTableCancel_clicked() -> Start");
		this->close();
		Utility::Logger("ColorResultTable -> colorResultTableCancel_clicked() -> End");
	}
	/*
	*brief adding rows to ColorResultTable UI.
	*input from ColorSearch.cpp file.
	*/
	void ColorResultTable::AddRowData(map<string, string>& colorResults)
	{
		Utility::Logger("ColorResultTable -> AddRowData() -> Start");
		QTableWidgetItem* headerItem = new QTableWidgetItem();

		AddColumns(headerItem, colorResults);

		m_colorResults.push_back(colorResults);
		Utility::Logger("ColorResultTable -> AddRowData() -> End");
	}
	/*
	*brief sets rowCount in color result table
	*input count of rows
	*/
	void ColorResultTable::SetRowCount(int count)
	{
		Utility::Logger("ColorResultTable -> SetRowCount() -> Start");
		colorResultsTable->setRowCount(count);
		Utility::Logger("ColorResultTable -> SetRowCount() -> End");
	}
	/*
	*brief adding colomns to ColorResultTable UI.
	*input from addColoums().
	*/
	void ColorResultTable::AddColumns(QTableWidgetItem* parent, map<string, string>& colorResults)
	{
		Utility::Logger("ColorResultTable -> AddColumns() -> Start");
			QString styleSheet = "::section {"

			"color: white;"
			"border: 1px grey;"
			"text-align: right;"
			"font-family: arial;"
			"font-size: 14px; }";

		colorResultsTable->horizontalHeader()->setStyleSheet(styleSheet);
		colorResultsTable->verticalHeader()->setStyleSheet(styleSheet);
		colorResultsTable->setWordWrap(true);
		colorResultsTable->resizeColumnToContents(3);		
		int currentRow = colorResultsTable->rowCount();
		colorResultsTable->setRowCount(currentRow + 1);

		
		QTableWidgetItem* dataItem = new QTableWidgetItem;
		dataItem->setTextAlignment(Qt::AlignCenter);			
		dataItem->setCheckState(Qt::Unchecked);
		int count = 1;
		map<int, string> headerColumns = getHeaderColumns();
		for (auto key = headerColumns.begin(); key != headerColumns.end(); ++key) {
			
			if (count == 3) {
				count++;
			}

			QTableWidgetItem* tableWidget = new QTableWidgetItem(QString::fromUtf8(colorResults.at(key->second).c_str()));
			tableWidget->setTextAlignment(Qt::AlignCenter);
			tableWidget->setToolTip(QString::fromUtf8(colorResults.at(key->second).c_str()));
			colorResultsTable->setItem(currentRow, count, tableWidget);

			count++;
		}
			
		colorResultsTable->setIconSize(QSize(90, 90));
		colorResultsTable->setWordWrap(true);

		QTableWidgetItem* iconItem = new QTableWidgetItem;
		iconItem->setSizeHint(QSize(90, 90));

		QStringList listRGB;
		QString colorRGB = QString::fromStdString(colorResults.at("RGB"));
		QString colorCMYK = QString::fromStdString(colorResults.at("CMYK"));
		listRGB = colorRGB.split(',');
		int red =  listRGB.at(0).toInt();
		int green =  listRGB.at(1).toInt();
		int blue =  listRGB.at(2).toInt();
		QColor color(red, green, blue);
		QImage image(90, 90, QImage::Format_ARGB32);
		image.fill(color);
		iconItem->setIcon(QIcon(QPixmap::fromImage(image)));
		iconItem->setToolTip(colorRGB);
		colorResultsTable->setItem(currentRow, 3, iconItem);

		QCheckBox* selectItem = new QCheckBox;
		selectItem->setCheckState(Qt::Unchecked);
		selectItem->setStyleSheet("margin-left:45%; margin-right:55%;");
		colorResultsTable->setStyleSheet("QTableWidget::indicator:unchecked {background-color:white;}");
		colorResultsTable->setStyleSheet("QToolTip { color: #ffffff; background-color: #000000; border: 1px #000000; }");
		colorResultsTable->setCellWidget(currentRow, 0, selectItem);
			   			
		QObject::connect(selectItem, SIGNAL(clicked()), this, SLOT(callCheckBoxSelected())); //to select multiple rows
		
		Utility::Logger("ColorResultTable -> AddColumns() -> End");
	}
	/*
	*brief used to highilght the row. if checkbox is selected.
	*/	
	void  ColorResultTable::callCheckBoxSelected()
	{
		Utility::Logger("ColorResultTable -> callCheckBoxSelected() -> Start");
		int totalRowCount = colorResultsTable->rowCount();
		colorResultsTable->setSelectionMode(QAbstractItemView::MultiSelection);
		QStringList selectedRows;
		selectedRows.clear();
		for (int rowCount = 0; rowCount < totalRowCount; rowCount++)
		{
			QWidget* qWidget = colorResultsTable->cellWidget(rowCount, 0);
			QCheckBox* temp = qobject_cast<QCheckBox*>(qWidget);
			if (temp->checkState() == Qt::Checked)
			{			
				selectedRows << QString::fromStdString(to_string(rowCount));
			}
		}
		colorResultsTable->clearSelection();
		for (auto iterate : selectedRows)
		{
			colorResultsTable->selectRow(iterate.toInt());
		}
		selectedRows.clear();
		Utility::Logger("ColorResultTable -> callCheckBoxSelected() -> End");
	}
	/*
	*brief click of download button selected rows getting dounload to clo files.
	*/
	void  ColorResultTable::colorResultTableDownload_clicked()
	{
		Utility::Logger("ColorResultTable -> colorResultTableDownload_clicked() -> Start");
		int rowCount = colorResultsTable->rowCount();
		QString colorName, colorCode, colorRGB, type;
	
		bool isSelected = false;
		
		for (int row = 0; row < rowCount; row++)
		{
			QWidget* qWidget = colorResultsTable->cellWidget(row, 0); //to select multiple rows
			QCheckBox* tempCheckBox = qobject_cast<QCheckBox*>(qWidget);
			if (tempCheckBox->checkState() == Qt::Checked)
			{
				isSelected = true;
			}
		}
		if (isSelected == false) 
		{
			UTILITY_API->DisplayMessageBox("Select atleast one row to download");
		}
		else
		{ 
			this->hide();
			for (int row = 0; row < rowCount; row++)
			{
				QWidget* qWidget = colorResultsTable->cellWidget(row, 0); //to select multiple rows
				QCheckBox* tempCheckBox = qobject_cast<QCheckBox*>(qWidget);
				if (tempCheckBox->checkState() == Qt::Checked)
				{
					
					colorName = QString::fromUtf8(m_colorResults[row].at("Name").c_str());
					
					colorCode = QString::fromStdString(m_colorResults[row].at("Code"));
					
					colorRGB = QString::fromStdString(m_colorResults[row].at("RGB"));
					
		
					QStringList listRGB;
					listRGB = colorRGB.split(',');
					m_rgbValues.R = listRGB.at(0).toInt();
					m_rgbValues.G = listRGB.at(1).toInt();
					m_rgbValues.B = listRGB.at(2).toInt();
					plmColorIDtoColorNameList.insert(make_pair(colorCode.toStdString(), colorName.toStdString())); // code and name
					plmIDtoColorList.insert(make_pair(colorCode.toStdString(), m_rgbValues));	//code and RGB list
						
					m_strRetSwatchColor = UTILITY_API->AddColorSwatch(plmColorIDtoColorNameList, plmIDtoColorList, m_strSwatchName);
					m_colorSwatchfilename = m_strRetSwatchColor;
					size_t index1 = 0;
					while (true) 
					{
						index1 = m_colorSwatchfilename.find("/", index1);
						if (index1 == std::string::npos) break;
						m_colorSwatchfilename.replace(index1, 1, "\\\\");
						index1 += 1;
					}
					Utility::CustomMessageBox("m_colorSwatchfilename::" + m_colorSwatchfilename);
					
					
					
				}
			}
			
			CLOAPISample::APIStorage::getInstance()->SendFileName(m_colorSwatchfilename);
			UTILITY_API->DisplayMessageBox("Download completed");
			this->close();
		}

		
		Utility::Logger("ColorResultTable -> colorResultTableDownload_clicked() -> End");
	}
	/**
	 * \brief Function is used to get header column names
	 */
	map<int, string> ColorResultTable::getHeaderColumns() {
		return headerColumns;
	}
	/**
	 * \brief Function is used to set header column names
	 */
	void ColorResultTable::setHeaderColumns(map<int, string>& headerColumn) {
		headerColumns = headerColumn;
	}

	void ColorResultTable::setResultTableColumns(map<string, string>& columns) {
		resultTableColumns = columns;
	}
}