#include "TrimsResultTable.h"
#include <qmessagebox.h>
#include <qcheckbox.h>
#include <direct.h>
#include "classes/APICLODataBase.h"
#include "classes/APIStorage.h"
#include <CLOAPIInterface.h>
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"
#include "CLO_PLUGIN/INFOR/Utilities/Definitions.h"
#include "TrimsSearch.h"
#include "CLO_PLUGIN/INFOR/Utilities/DirectoryUtil.h"
/**
 *  This file is used to display the trims results on the result table
	 It allows the user to download the trims 
 */
using namespace std;
/**
 *  CLOPlugin namespace is used to keep all the functions in this class to be under CLOPlugin namespace.
 */
namespace CLOPlugin
{
	TrimsResultTable* TrimsResultTable::_instance = NULL;
	map<int, string> TrimsResultTable::headerColumns;
	map<string, string> TrimsResultTable::resultTableColumns;

	TrimsResultTable* TrimsResultTable::GetInstance()
	{
		if (_instance == NULL)
		{
			_instance = new TrimsResultTable();
		}
		return _instance;
	}
	void TrimsResultTable::Destroy()
	{
		if (_instance)
		{
			delete _instance;
			_instance = NULL;
		}
	}
	/**
	 * \brief TrimsResultTable constructor. It has Qt UI related settings to the trims result table 
		also it contains signals and slots connections
	 * \param inputs: QWidget and WindowFlags
	 **/
	 TrimsResultTable::TrimsResultTable(QWidget* parent, Qt::WindowFlags flags)
		: QDialog(parent, flags) 
	{
		 Utility::Logger("TrimsResultTable -> Constructor() -> Start");
		setupUi(this);
		trims_ResultsTable->setFixedSize(RESULT_TABLE_WIDTH, RESULT_TABLE_HEIGHT);

		setWindowTitle(tr(" Trims Result Table"));
		QString styleSheet = "::section {""color: white;""border: 1px grey;""text-align: right;""font-family: arial;""font-size: 14px; }";
		trims_ResultsTable->horizontalHeader()->setStyleSheet(styleSheet);
		trims_ResultsTable->verticalHeader()->setStyleSheet(styleSheet);
		trims_ResultsTable->horizontalHeader()->setFixedHeight(80);
		trims_ResultsTable->horizontalHeader()->setDefaultSectionSize(80);
		trims_ResultsTable->verticalHeader()->setDefaultSectionSize(80);
		trims_ResultsTable->resizeColumnsToContents();
		trims_ResultsTable->verticalHeader()->blockSignals(true);
		trims_ResultsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		trims_ResultsTable->setMouseTracking(true);
		trims_ResultsTable->viewport()->setMouseTracking(true);
		QFont font;
		font.setPointSize(14);
		font.setBold(true);
		trims_ResultsTable->horizontalHeader()->setFont(font);
		QStringList headerlist;
		trims_ResultsTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
		trims_ResultsTable->setWordWrap(true);
		//trims_ResultsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		QTableWidgetItem* itemCheckbox = new QTableWidgetItem(" ");
		itemCheckbox->setCheckState(Qt::Unchecked);
		QModelIndexList selection = trims_ResultsTable->selectionModel()->selectedRows();
		trims_ResultsTable->setItem(0, 0, itemCheckbox);

		int count = 1;
		headerlist.insert(0, "Select");

		map<int, string> headerColumns = GetHeaderColumns();
		json keyValuePairJson = Utility::GetKeyValuePairs();
		for (auto key = headerColumns.begin(); key != headerColumns.end(); ++key) {
			QString column;
			if (count == 3) {
				headerlist.insert(count, QString("Image"));
				count++;
			}

			if (resultTableColumns.find(key->second) != resultTableColumns.end()) {
				column = QString::fromStdString(resultTableColumns.at(key->second));
			}
			else {
				column = Utility::GetDisplayValueByKey(QString::fromStdString(key->second), QString("trim"), keyValuePairJson);
			}

			std::replace(column.begin(), column.end(), ' ', '\n');
			headerlist.insert(count, column);
			count++;
		}

		trims_ResultsTable->setColumnCount(count);
		trims_ResultsTable->setHorizontalHeaderLabels(headerlist);

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

		QObject::connect(download, SIGNAL(clicked()), this, SLOT(DownloadClicked()));
		QObject::connect(back, SIGNAL(clicked()), this, SLOT(OnBackClicked()));
		QObject::connect(closeWindow, SIGNAL(clicked()), this, SLOT(Cancel_clicked()));
		QObject::connect(SelectAll, SIGNAL(clicked()), this, SLOT(SelectAllClicked()));
		QObject::connect(DeSelectAll, SIGNAL(clicked()), this, SLOT(DeSelectAllClicked()));
		Utility::Logger("TrimsResultTable -> Constructor() -> End");
	}
/**
	 * \brief  destructortor of TrimsResultTable
	 deletes the object of this class.
 */
	TrimsResultTable::~TrimsResultTable()
	{

	}
	/*
	*brief select all the checkbox.
	*higllight all the selected rows.
	*/
	void TrimsResultTable::SelectAllClicked()
	{
		Utility::Logger("TrimsResultTable -> SelectAllClicked() -> Start");
		trims_ResultsTable->setSelectionMode(QAbstractItemView::MultiSelection);
		QStringList selectedRows;
		selectedRows.clear();
		trims_ResultsTable->clearSelection();
		for (int i = 0; i < trims_ResultsTable->rowCount(); i++)
		{
			QWidget* qWidget1 = trims_ResultsTable->cellWidget(i, 0);
			QCheckBox* temp = qobject_cast<QCheckBox*>(qWidget1);
			if (temp->isEnabled())
			{
				temp->setCheckState(Qt::Checked);
				selectedRows << QString::fromStdString(to_string(i));
			}
		}
		for (auto iterate : selectedRows)
		{
			trims_ResultsTable->selectRow(iterate.toInt());
		}
		Utility::Logger("TrimsResultTable -> SelectAllClicked() -> End");
	}
	/*
	*brief de select all the checkbox.
	*/
	void TrimsResultTable::DeSelectAllClicked()
	{
		Utility::Logger("TrimsResultTable -> DeSelectAllClicked() -> Start");
		for (int i = 0; i < trims_ResultsTable->rowCount(); i++)
		{
			QWidget* qWidget1 = trims_ResultsTable->cellWidget(i, 0);
			QCheckBox* temp = qobject_cast<QCheckBox*>(qWidget1);
			if (temp->checkState() == Qt::Checked)
			{
				temp->setCheckState(Qt::Unchecked);
				trims_ResultsTable->clearSelection();
			}
		}
		Utility::Logger("TrimsResultTable -> DeSelectAllClicked() -> End");
	}
	/**
	 * \brief adds rows to the Trims Result Table
	 * \input param structure of Trims Results and QIcon
	 * \return void
	 */
	void TrimsResultTable::AddRowData(map<string, string>& trimsResults, QIcon fabIcon)
	{
		Utility::Logger("TrimsResultTable -> AddRowData() -> Start");
		QTableWidgetItem* headerItem = new QTableWidgetItem();
		AddColumns(headerItem, trimsResults, fabIcon);
		m_trimsResults.push_back(trimsResults);
		Utility::Logger("TrimsResultTable -> AddRowData() -> End");
	}
	/**
	 * \brief adds columns to the Trims Result Table
	 * \input param:  QTableWidget Item, structure of Trims Results and QIcon
	 * \return void
	 */
	void TrimsResultTable::AddColumns(QTableWidgetItem* parent, map<string, string>& TrimResults, QIcon FabIcon)
	{
		Utility::Logger("TrimsResultTable -> AddColumns() -> Start");
		int currentRow = trims_ResultsTable->rowCount();
		trims_ResultsTable->setWordWrap(true);
		trims_ResultsTable->setRowCount(currentRow + 1);

		int count = 1;
		map<int, string> headerColumns = GetHeaderColumns();
		for (auto key = headerColumns.begin(); key != headerColumns.end(); ++key) 
		{
			if (count == 3)
			{
				count++;
			}

			QTableWidgetItem* tableWidget = new QTableWidgetItem(QString::fromUtf8(TrimResults.at(key->second).c_str()));
			tableWidget->setTextAlignment(Qt::AlignCenter);
			tableWidget->setToolTip(QString::fromUtf8(TrimResults.at(key->second).c_str()));
			trims_ResultsTable->setItem(currentRow, count, tableWidget);

			count++;
		}
		for (int c = 0; c < trims_ResultsTable->columnCount(); ++c)
		{
			QTableWidgetItem* dataItem = new QTableWidgetItem;
			dataItem->setFlags(dataItem->flags() | Qt::ItemIsUserCheckable);
			dataItem->setCheckState(Qt::Unchecked);

			QCheckBox* selectItem = new QCheckBox;
			selectItem->setCheckState(Qt::Unchecked);
			selectItem->setProperty("Id", QString::fromStdString(TrimResults.at("Id")));
			//Disable checkbox if image format is not supported.
			if (TrimResults.at("imageSupported") == "false")
			{
				selectItem->setEnabled(false);
			}
			selectItem->setStyleSheet("margin-left:45%; margin-right:55%;");
			trims_ResultsTable->setStyleSheet("QTableWidget::indicator:unchecked {background-color:white;}");
			trims_ResultsTable->setStyleSheet("QToolTip { color: #ffffff; background-color: #000000; border: 1px #000000; }");
			trims_ResultsTable->setCellWidget(currentRow, 0, selectItem);

			QTableWidgetItem* itemImage = new QTableWidgetItem;
			if (TrimResults.at("imageSupported") == "true")
			{
				QWidget* pWidget = new QWidget();
				QLabel* label = new QLabel;
				label->setMaximumSize(QSize(70, 70));
				label->setScaledContents(true);
				QPixmap pixmap = FabIcon.pixmap(QSize(70, 70));
				label->setPixmap(QPixmap(pixmap));
				QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
				pLayout->addWidget(label);
				pLayout->setAlignment(Qt::AlignCenter);
				pLayout->setContentsMargins(0, 0, 0, 0);
				pWidget->setLayout(pLayout);
				trims_ResultsTable->setCellWidget(currentRow, 3, pWidget);
			}
			else
			{
				QTableWidgetItem* itemImage = new QTableWidgetItem("Image format not supported");
				trims_ResultsTable->setItem(currentRow, 3, itemImage);
			}

			QObject::connect(selectItem, SIGNAL(clicked()), this, SLOT(callCheckBoxSelected()));
		}
		Utility::Logger("TrimsResultTable -> AddColumns() -> End");
	}
	/**
	 * \brief calls the check box which is selected in the result table
	 * \input param:  void
	 * \return void
	 */
	void  TrimsResultTable::callCheckBoxSelected()
	{
		Utility::Logger("TrimsResultTable -> callCheckBoxSelected() -> Start");
		int totalRowCount = trims_ResultsTable->rowCount();
		trims_ResultsTable->setSelectionMode(QAbstractItemView::MultiSelection);
		QStringList selectedRows;
		selectedRows.clear();
		for (int rowCount = 0; rowCount < totalRowCount; rowCount++)
		{
			QWidget* qWidget = trims_ResultsTable->cellWidget(rowCount, 0);
			QCheckBox* tempCheckBox = qobject_cast<QCheckBox*>(qWidget);
			if (tempCheckBox->checkState() == Qt::Checked)
			{
				selectedRows << QString::fromStdString(to_string(rowCount));
			}
		}
		trims_ResultsTable->clearSelection();
		for (auto iterate : selectedRows)
		{
			trims_ResultsTable->selectRow(iterate.toInt());
		}
		selectedRows.clear();
		Utility::Logger("TrimsResultTable -> callCheckBoxSelected() -> End");
	}
	/**
	 * \brief After clicking on download button, selected trims will be displyed on the side pane
	 * \input param:  void
	 * \return void
	 */
	void  TrimsResultTable::DownloadClicked()
	{
		Utility::Logger("TrimsResultTable -> DownloadClicked() -> Start");
		int rowCount = trims_ResultsTable->rowCount();
		int columnCount = trims_ResultsTable->columnCount();
		QString TrimID;
		QString brand;
		QString imageLoadPath;
		QString imageSavePath;
		QString imageFileName;
		const char* newDirPath = DirectoryUtil::getTrimAssetsDirectory().c_str();
		mkdir(newDirPath);
		bool isSelected = false;
		for (int row = 0; row < rowCount; row++)
		{
			QWidget* qWidget = trims_ResultsTable->cellWidget(row, 0); 
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
			
			QString imageLoadPath, imageSavePath, code;
			for (int row = 0; row < rowCount; row++)
			{

				QWidget* qWidget = trims_ResultsTable->cellWidget(row, 0);
				QCheckBox* tempCheckBox = qobject_cast<QCheckBox*>(qWidget);
				if (tempCheckBox->checkState() == Qt::Checked)
				{
					TrimID = tempCheckBox->property("Id").toString();
					
					int matchingindex = 0;
					for (int i = 0; i < m_trimsResults.size(); i++)
					{
						if (TrimID == QString::fromStdString(m_trimsResults[i].at("Id")))
						{
							matchingindex = i;
							break;
						}
					}

					if (m_trimsResults[matchingindex].at("trimImage") == "true" || m_trimsResults[matchingindex].at("trimAttachment") == "true") 
					{
						CLOAPISample::LibraryAPIItem* setItem = new CLOAPISample::LibraryAPIItem();
						QString TrimName = QString::fromUtf8(m_trimsResults[matchingindex].at("Name").c_str());
						QString TrimCode = QString::fromStdString(m_trimsResults[matchingindex].at("Code"));
						QString trimImageName = QString::fromUtf8(m_trimsResults[matchingindex].at("trimImageName").c_str());
						QString TrimId = QString::fromStdString(m_trimsResults[matchingindex].at("Id"));

						if (m_trimsResults[matchingindex].at("trimAttachment") == "true") {

							setItem->itemID = TrimCode;
							setItem->itemName = QString::fromUtf8(m_trimsResults[matchingindex].at("attachedFileName").c_str());
							QString itemPath = QString::fromUtf8(m_trimsResults[matchingindex].at("attachedFileName").c_str());
							setItem->sampleItemData.itemPath = itemPath;
							setItem->sampleItemData.iconThumbnailPath = itemPath;
							setItem->sampleItemData.previewThumbnailPath = itemPath;
							setItem->dateTime = "2019-08-20T16:21:41";
							float fileSize = (float)Utility::GetFileSize(DirectoryUtil::getTrimAssetsDirectory() + itemPath.toStdString());
							setItem->filesize = fileSize;
						}
						else {
							QString imageLoadPath, imageSavePath, code;

							setItem->itemID = TrimCode;
							setItem->itemName = trimImageName;
							imageLoadPath = QString::fromStdString(Configuration::GetInstance()->TRIMS_TEMP_DIRECTORY) + trimImageName;
							imageSavePath = QString::fromStdString(DirectoryUtil::getTrimAssetsDirectory()) + trimImageName;
							Utility::copyFile(imageLoadPath.toStdString().c_str(), imageSavePath.toStdString().c_str());
							float fileSize = (float)Utility::GetFileSize(imageSavePath.toStdString());
							setItem->filesize = fileSize;
							setItem->sampleItemData.itemPath = trimImageName;
							setItem->sampleItemData.iconThumbnailPath = trimImageName;
							setItem->sampleItemData.previewThumbnailPath = trimImageName;
							setItem->dateTime = "2019-08-20T16:21:41";
						}

						setItem->metaData[META_DATA_KEY_0_DATA_TYPE] = QString("TRIM");
						setItem->metaData[META_DATA_KEY_2_BRAND] = QString::fromUtf8(m_trimsResults[matchingindex].at("BrandId").c_str());
						setItem->metaData[META_DATA_KEY_6_ID] = QString::fromStdString(m_trimsResults[matchingindex].at("Id"));
						setItem->metaData[META_DATA_KEY_5_NAME] = QString::fromUtf8(m_trimsResults[matchingindex].at("Name").c_str());
						setItem->metaData[META_DATA_KEY_7_NUMBER] = TrimCode;

						bool alreadyExists = false;
						if (API_STORAGE)
						{
							for (int i = 0; i < API_STORAGE->m_LibraryAPIItemList.size(); i++)
							{
								if (API_STORAGE->m_LibraryAPIItemList[i]->metaData[META_DATA_KEY_6_ID].toString() == TrimId)
								{
									API_STORAGE->m_LibraryAPIItemList[i] = setItem;
									alreadyExists = true;
									break;
								}
							}
							if (!alreadyExists)
							{
								API_STORAGE->m_LibraryAPIItemList.push_back(setItem);
							}
						}
					}
				}
			}
			wstring wideString = wstring(Configuration::GetInstance()->TRIMS_TEMP_DIRECTORY.begin(), Configuration::GetInstance()->TRIMS_TEMP_DIRECTORY.end());
			Utility::RemoveDirectory(wideString.c_str());
			UTILITY_API->DisplayMessageBox("Download completed");
		}
		Utility::Logger("TrimsResultTable -> DownloadClicked() -> End");
	}
/**
	 * \brief On click of BACK button in the result table , it will navigate to the trims search page
	 * \input param:  void
	 * \return void
	 */	
	void TrimsResultTable::OnBackClicked()
	{
		Utility::Logger("TrimsResultTable -> OnBackClicked() -> Start");
		this->close();
		TrimsSearch::GetInstance()->setModal(true);
		TrimsSearch::GetInstance()->show();
		Utility::Logger("TrimsResultTable -> OnBackClicked() -> End");
	}
	/**
	 * \brief On click of Close button in the result table , it will close the result table window.
	 * \input param:  void
	 * \return void
	 */
	void TrimsResultTable::Cancel_clicked()
	{
		Utility::Logger("TrimsResultTable -> closeWindowPressed() -> Start");
		this->close();
		Utility::Logger("TrimsResultTable -> closeWindowPressed() -> End");
	}
	/**
	 * \brief Function is used to get header column names
	 */
	map<int, string> TrimsResultTable::GetHeaderColumns() {
		return headerColumns;
	}
	/**
	 * \brief Function is used to set header column names
	 */
	void TrimsResultTable::SetHeaderColumns(map<int, string>& headerColumn) {
		headerColumns = headerColumn;
	}

	void TrimsResultTable::SetResultTableColumns(map<string, string>& columns) {
		resultTableColumns = columns;
	}
}