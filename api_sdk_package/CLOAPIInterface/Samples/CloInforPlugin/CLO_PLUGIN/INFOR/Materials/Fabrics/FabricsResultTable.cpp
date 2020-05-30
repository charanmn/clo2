#include "FabricsResultTable.h"
#include <qmessagebox.h>
#include <qcheckbox.h>
#include <direct.h>
#include "classes/APICLODataBase.h"
#include "classes/APIStorage.h"
#include "classes/APIDefine.h"
#include <CLOAPIInterface.h>
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"
#include "CLO_PLUGIN/INFOR/Utilities/Definitions.h"
#include "CLO_PLUGIN/INFOR/Utilities/Configuration.h"
#include "FabricsSearchDialog.h"
#include "CLO_PLUGIN/INFOR/Utilities/Configuration.h" 
#include "CLO_PLUGIN/INFOR/Utilities/RestAPIUtility.h"
#include "CLO_PLUGIN/INFOR/Utilities/DirectoryUtil.h"

using namespace std;
bool checkzfab = false;
namespace CLOPlugin
{	
	ResultTable* ResultTable::_instance = NULL;
	map<int, string> ResultTable::headerColumns;
	map<string, string> ResultTable::resultTableColumns;

	ResultTable* ResultTable::GetInstance()
	{
		if (_instance == NULL)
		{
			_instance = new ResultTable();
		}
		return _instance;
	}
	void ResultTable::Destroy()
	{
		if (_instance)
		{
			delete _instance;
			_instance = NULL;
		}
	}
	/**
	 * \brief Prepares the complete result table using Widgets as parameter 
	 * \param parent 
	 * \param flags 
	 */
	ResultTable::ResultTable(QWidget* parent, Qt::WindowFlags flags) : QDialog(parent, flags)
	{
		Utility::Logger("FabricsResultTable -> Constructor() -> Start");
		
		setupUi(this);
		materialResultTable->setFixedSize(RESULT_TABLE_WIDTH, RESULT_TABLE_HEIGHT);
		QString styleSheet = "::section {""color: white;""border: 1px grey;""text-align: center;""font-family: times new roman;""font-size: 14px; }";

		materialResultTable->horizontalHeader()->setStyleSheet(styleSheet);
		materialResultTable->verticalHeader()->setStyleSheet(styleSheet);
		//materialResultTable->setFocusPolicy(Qt::NoFocus);
		//materialResultTable->setVisible(false);
		materialResultTable->resizeColumnsToContents();
		//materialResultTable->setVisible(true);
		materialResultTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		//materialResultTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		materialResultTable->verticalHeader()->blockSignals(true);
		materialResultTable->horizontalHeader()->setFixedHeight(80);
		materialResultTable->horizontalHeader()->setDefaultSectionSize(80);
		materialResultTable->verticalHeader()->setDefaultSectionSize(80);
		materialResultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		QFont font;
		font.setPointSize(14);
		font.setBold(true);
		materialResultTable->horizontalHeader()->setFont(font);
		QStringList headerlist;
		materialResultTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
		materialResultTable->setWordWrap(true);
		materialResultTable->setMouseTracking(true);
		materialResultTable->viewport()->setMouseTracking(true);
		
		QTableWidgetItem* itemCheckbox = new QTableWidgetItem(" ");
		itemCheckbox->setCheckState(Qt::Unchecked);
		QModelIndexList selection = materialResultTable->selectionModel()->selectedRows();
		materialResultTable->setItem(0, 0, itemCheckbox);
		
		headerlist.insert(0, "Select");
		
		int count = 1;
		map<int, string> headerColumns = getHeaderColumns();
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
				column = Utility::GetDisplayValueByKey(QString::fromStdString(key->second), QString("material"), keyValuePairJson);
			}
			
			std::replace(column.begin(), column.end(), ' ', '\n');
			headerlist.insert(count, column);
			count++;
		}

		materialResultTable->setColumnCount(count);
		materialResultTable->setHorizontalHeaderLabels(headerlist);
	
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

		Utility::Logger("FabricsResultTable -> Constructor() -> End");
	}

	ResultTable::~ResultTable()
	{

	}
	/*
	*brief select all the checkbox.
	*higllight all the selected rows.
	*/
	void ResultTable::SelectAllClicked()
	{
		Utility::Logger("FabricsResultTable -> SelectAllClicked() -> Start");
		materialResultTable->setSelectionMode(QAbstractItemView::MultiSelection);
		QStringList selectedRows;
		selectedRows.clear();
		materialResultTable->clearSelection();
		for (int i = 0; i < materialResultTable->rowCount(); i++)
		{
			QWidget* qWidget1 = materialResultTable->cellWidget(i, 0);
			QCheckBox* temp = qobject_cast<QCheckBox*>(qWidget1);

			if (temp->isEnabled())
			{
				temp->setCheckState(Qt::Checked);
				selectedRows << QString::fromStdString(to_string(i));
			}
		}
		for (auto iterate : selectedRows)
		{
			materialResultTable->selectRow(iterate.toInt());
		}
		Utility::Logger("FabricsResultTable -> SelectAllClicked() -> End");		
	
	}
	/*
	*brief de select all the checkbox.
	*/
	void ResultTable::DeSelectAllClicked()
	{
		
		Utility::Logger("FabricsResultTable -> DeSelectAllClicked() -> Start");
		for (int i = 0; i < materialResultTable->rowCount(); i++)
		{
			QWidget* qWidget1 = materialResultTable->cellWidget(i, 0);
			QCheckBox* temp = qobject_cast<QCheckBox*>(qWidget1);
			if (temp->checkState() == Qt::Checked)
			{
				temp->setCheckState(Qt::Unchecked);
				materialResultTable->clearSelection();
			}			
		}
		Utility::Logger("FabricsResultTable -> DeSelectAllClicked() -> End");
	}
	/**
	 * \brief Adds rows data to Results table for Materials
	 * \param MaterialFabricResults 
	 * \param FabIcon 
	 */
	void ResultTable::AddRowData(map<string, string>& MaterialFabricResults, QIcon FabIcon)
	{
		Utility::Logger("FabricsResultTable -> AddRowData() -> Start");

		QTableWidgetItem* headerItem = new QTableWidgetItem();
		AddColumns(headerItem, MaterialFabricResults, FabIcon);
		m_FabricResults.push_back(MaterialFabricResults);

		Utility::Logger("FabricsResultTable -> AddRowData() -> End");
	}
	/**
	 * \brief Add columns to Result table
	 * \param parent 
	 * \param MaterialFabricResults 
	 * \param FabIcon 
	 */
	void ResultTable::AddColumns(QTableWidgetItem* parent, map<string, string>& MaterialFabricResults, QIcon FabIcon)
	{
		Utility::Logger("FabricsResultTable -> AddColumns() -> Start");
		materialResultTable->setWordWrap(true);
		int currentRow = materialResultTable->rowCount();
		materialResultTable->setRowCount(currentRow + 1);
		int count = 1;
		map<int, string> headerColumns = getHeaderColumns();
	
		for (auto key = headerColumns.begin(); key != headerColumns.end(); ++key) 
		{
			if (count == 3) 
			{
				count++;
			}

			QTableWidgetItem* tableWidget = new QTableWidgetItem(QString::fromUtf8(MaterialFabricResults.at(key->second).c_str()));
			tableWidget->setTextAlignment(Qt::AlignCenter);
			tableWidget->setToolTip(QString::fromUtf8(MaterialFabricResults.at(key->second).c_str()));
			materialResultTable->setItem(currentRow, count, tableWidget);
			count++;
		}

			for (int c = 0; c < materialResultTable->columnCount(); ++c)
			{
				QCheckBox* checkBox = new QCheckBox;
				checkBox->setCheckable(true);
				checkBox->setStyleSheet("margin-left:45%; margin-right:55%;");
				checkBox->setCheckState(Qt::Unchecked);
				checkBox->setProperty("MaterialId", QString::fromStdString(MaterialFabricResults.at("MaterialId")));
				//Disable checkbox if image format is not supported.
				if (MaterialFabricResults.at("imageSupported") == "false") {
					checkBox->setEnabled(false);
				}
				materialResultTable->setStyleSheet("QTableWidget::indicator:unchecked {background-color:white;}");
				materialResultTable->setStyleSheet("QToolTip { color: #ffffff; background-color: #000000; border: 1px #000000; }");
				materialResultTable->setCellWidget(currentRow, 0, checkBox);

				QTableWidgetItem* itemImage = new QTableWidgetItem;
				if (MaterialFabricResults.at("imageSupported") == "true")
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
					materialResultTable->setCellWidget(currentRow, 3, pWidget);
				}
				else
				{
					QTableWidgetItem* itemImage = new QTableWidgetItem("Image format not supported");
					materialResultTable->setItem(currentRow, 3, itemImage);
				}

			QObject::connect(checkBox, SIGNAL(clicked()), this, SLOT(callCheckBoxSelected()));
		}
		Utility::Logger("FabricsResultTable -> AddColumns() -> End");
	}
	/**
	 * \brief Looks for Check box selection and collects all selected rows
	 */
	void  ResultTable::callCheckBoxSelected()
	{
		Utility::Logger("FabricsResultTable -> callCheckBoxSelected() -> Start");
		int totalRowCount = materialResultTable->rowCount();
		materialResultTable->setSelectionMode(QAbstractItemView::MultiSelection);
		QStringList selectedRows;
		selectedRows.clear();
		for (int rowCount = 0; rowCount < totalRowCount; rowCount++)
		{
			QWidget* qWidget = materialResultTable->cellWidget(rowCount, 0);
			QCheckBox* temp = qobject_cast<QCheckBox*>(qWidget);
			if (temp->checkState() == Qt::Checked)
			{			
				selectedRows << QString::fromStdString(to_string(rowCount));
			}

		}
		materialResultTable->clearSelection();
		for (auto iterate : selectedRows)
		{
			materialResultTable->selectRow(iterate.toInt());
		}
		selectedRows.clear();
		Utility::Logger("FabricsResultTable -> callCheckBoxSelected() -> End");
	}
	/**
	 * \brief When download button clicked by user, it download corresponding details of material
	 */
	void  ResultTable::DownloadClicked() 
	{
		Utility::Logger("FabricsResultTable -> DownloadClicked() -> Start");
		
		int rowCount = materialResultTable->rowCount();
		int columnCount = materialResultTable->columnCount();
		QString materialeId;
		QString brand;
		QString imageLoadPath;
		QString imageSavePath;
		QString imageFileName;
		const char* newDirPath = DirectoryUtil::getMaterialAssetsDirectory().c_str();
		mkdir(newDirPath);
		bool isSelected = false;
		
		for (int row = 0; row < rowCount; row++)
		{
			QWidget* qWidget = materialResultTable->cellWidget(row, 0);
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
			QImage imgNew;
			QString imageLoadPath, imageSavePath, code;
			for (int row = 0; row < rowCount; row++)
			{
				QWidget* qWidget = materialResultTable->cellWidget(row, 0);
				QCheckBox* tempCheckBox = qobject_cast<QCheckBox*>(qWidget);
				if (tempCheckBox->checkState() == Qt::Checked)
				{
					materialeId = tempCheckBox->property("MaterialId").toString();
					int matchingindex = 0;
					for (int i = 0; i < m_FabricResults.size(); i++)
					{
						if (materialeId == QString::fromStdString(m_FabricResults[i].at("MaterialId")))
						{
							matchingindex = i;
							break;
						}
					}
					QString imageLoadPath, imageSavePath, code;
					QString materialCode = QString::fromStdString(m_FabricResults[matchingindex].at("MaterialCode"));
					QString MaterialId = QString::fromStdString(m_FabricResults[matchingindex].at("MaterialId"));
					if ( m_FabricResults[matchingindex].at("fabricImage") == "true" || m_FabricResults[matchingindex].at("fabricAtachment") == "true")
					{
						CLOAPISample::LibraryAPIItem* setItem = new CLOAPISample::LibraryAPIItem();
						setItem->itemID = materialCode;
						if (m_FabricResults[matchingindex].at("fabricAtachment") == "true"&& !m_FabricResults[matchingindex].at("fabricAtachmentName").empty())
						{
							QString attachmentName = QString::fromUtf8(m_FabricResults[matchingindex].at("fabricAtachmentName").c_str());
							setItem->itemName = attachmentName;
							float fileSize = (float)Utility::GetFileSize(DirectoryUtil::getMaterialAssetsDirectory() + attachmentName.toStdString());
							setItem->sampleItemData.itemPath = attachmentName;
							setItem->sampleItemData.iconThumbnailPath = attachmentName;
							setItem->sampleItemData.previewThumbnailPath = attachmentName;
							setItem->dateTime = "2019-08-20T16:21:41";							
							setItem->filesize = fileSize;
							
						}
						else
						{
							QString fabricImageName = QString::fromUtf8(m_FabricResults[matchingindex].at("fabricImageName").c_str());
							setItem->itemName = fabricImageName;
							imageLoadPath = QString::fromStdString(Configuration::GetInstance()->MATERIALS_TEMP_DIRECTORY) + fabricImageName;
							Utility::Logger("imageLoadPath::" + imageLoadPath.toStdString());
							imageSavePath = QString::fromStdString(DirectoryUtil::getMaterialAssetsDirectory()) + fabricImageName;
							Utility::Logger("imageSavePath::" + imageSavePath.toStdString());
							Utility::copyFile(imageLoadPath.toStdString().c_str(), imageSavePath.toStdString().c_str());
							float fileSize = (float)Utility::GetFileSize(imageSavePath.toStdString());							
							setItem->sampleItemData.itemPath = fabricImageName;
							setItem->sampleItemData.iconThumbnailPath = fabricImageName;
							setItem->sampleItemData.previewThumbnailPath = fabricImageName;
							setItem->dateTime = "2019-08-20T16:21:41";							
							setItem->filesize = fileSize;
							
						}
						setItem->metaData[META_DATA_KEY_0_DATA_TYPE] = QString("MATERIAL");
						setItem->metaData[META_DATA_KEY_2_BRAND] = QString::fromStdString(m_FabricResults[matchingindex].at("BrandId"));
						setItem->metaData[META_DATA_KEY_6_ID] = QString::fromStdString(m_FabricResults[matchingindex].at("MaterialId"));
						setItem->metaData[META_DATA_KEY_5_NAME] = QString::fromUtf8(m_FabricResults[matchingindex].at("MaterialName").c_str());
						setItem->metaData[META_DATA_KEY_7_NUMBER] = materialCode;

						bool alreadyExists = false;
						if (API_STORAGE)
						{
							for (int i = 0; i < API_STORAGE->m_LibraryAPIItemList.size(); i++)
							{
								if (API_STORAGE->m_LibraryAPIItemList[i]->metaData[META_DATA_KEY_6_ID] == MaterialId)
								{
									API_STORAGE->m_LibraryAPIItemList[i] = setItem; //overwrite the same file
									alreadyExists = true;
									break;
								}
							}
							if (!alreadyExists)
								API_STORAGE->m_LibraryAPIItemList.push_back(setItem);
						}
					}
				}
			}
			wstring wideString = wstring(Configuration::GetInstance()->MATERIALS_TEMP_DIRECTORY.begin(), Configuration::GetInstance()->MATERIALS_TEMP_DIRECTORY.end());
			Utility::RemoveDirectory(wideString.c_str());
			UTILITY_API->DisplayMessageBox("Download completed");
			Utility::Logger("FabricsResultTable -> DownloadClicked() -> Download completed.");
		}
		Utility::Logger("FabricsResultTable -> DownloadClicked() -> End");
	}

	//
	/**
	 * \brief Recordes Click of Back button by user and stops sending request further.
	 */
	void ResultTable::OnBackClicked()
	{
		Utility::Logger("FabricsResultTable -> OnBackClicked() -> Start");

		this->close();
		MaterialSearchDialog::GetInstance()->setModal(true);
		MaterialSearchDialog::GetInstance()->show();

		Utility::Logger("FabricsResultTable -> OnBackClicked() -> End");
	}
	/**
	 * \brief Closes the window
	 */
	void ResultTable::Cancel_clicked()
	{	
		Utility::Logger("FabricsResultTable -> Cancel_clicked() -> Start");

		this->close();

		Utility::Logger("FabricsResultTable -> Cancel_clicked() -> End");
	}
	/**
	 * \brief Function is used to get header column names
	 */
	map<int, string> ResultTable::getHeaderColumns() {
		return headerColumns;
	}
	/**
	 * \brief Function is used to set header column names
	 */
	void ResultTable::setHeaderColumns(map<int, string>& headerColumn) {
		headerColumns = headerColumn;
	}

	void ResultTable::setResultTableColumns(map<string, string>& columns) {
		resultTableColumns = columns;
	}
}