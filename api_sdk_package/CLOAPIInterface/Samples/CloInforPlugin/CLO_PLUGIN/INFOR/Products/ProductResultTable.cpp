#pragma once
#include "ProductResultTable.h"
#include "CLO_PLUGIN/INFOR/DesignSuite/DesignSuite.h"
#include "ProductSearch.h"
#include "UpdateProduct.h"
#include <qmessagebox.h>
#include <qcheckbox.h>
#include <direct.h>
#include "classes/APICLODataBase.h"
#include "classes/APIStorage.h"
#include <CLOAPIInterface.h>
#include "qobject.h"
#include "classes/APIStorage.h"
#include "CLO_PLUGIN/INFOR/Utilities/Configuration.h"
#include "CLO_PLUGIN/INFOR/Utilities/DirectoryUtil.h"

using namespace std;
namespace CLOPlugin
{
	map<float, string> ProductResultTable::headerColumns;
	map<string, string> ProductResultTable::resultTableColumns;
	/**
	 * \brief Prepares the complete result table using Widgets as parameter
	 * \param parent
	 * \param flags
	 */
	ProductResultTable::ProductResultTable(QWidget* parent, Qt::WindowFlags flags) : QDialog(parent, flags)
	{
		Utility::Logger("ProductResultTable -> Constructor() -> Start");
		
		setupUi(this);
		ProductResultTable_2->setFixedSize(RESULT_TABLE_WIDTH, RESULT_TABLE_HEIGHT);

		QFont font;
		font.setPointSize(14);
		font.setBold(true);
		ProductResultTable_2->horizontalHeader()->setFont(font);
		ProductResultTable_2->setWordWrap(true);
		ProductResultTable_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		ProductResultTable_2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		ProductResultTable_2->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
		ProductResultTable_2->setStyleSheet("QTableWidget{font-family: Times new roman;}");
		ProductResultTable_2->horizontalHeader()->setFixedHeight(80);
		ProductResultTable_2->horizontalHeader()->setDefaultSectionSize(80);
		ProductResultTable_2->verticalHeader()->setDefaultSectionSize(80);
		ProductResultTable_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
		m_headerItem = new QTreeWidgetItem;
		QStringList headerlist;

		int count = 1;
		headerlist.insert(0, "Select");

		map<float, string> headerColumns = getHeaderColumns();
		for (auto key = headerColumns.begin(); key != headerColumns.end(); ++key) {
			if (count == 3) 
			{
				headerlist.insert(count, QString("Image"));
				count++;
			} 
			if (count == 4) 
			{
				headerlist.insert(count, QString("3D\nDesign"));
				count++;
			}

			QString column = QString::fromStdString(resultTableColumns.at(key->second));
			
			std::replace(column.begin(), column.end(), ' ', '\n');
			headerlist.insert(count, column);
			count++;
		}

		ProductResultTable_2->setColumnCount(count);
		ProductResultTable_2->setHorizontalHeaderLabels(headerlist);
		ProductResultTable_2->setMouseTracking(true);
		ProductResultTable_2->viewport()->setMouseTracking(true);

		back->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_back_over.svg"));
		back->setIconSize(QSize(iconHieght, iconWidth));
		back->setFixedSize(BUTTON_WIDTH_1, BUTTON_HEIGHT);
		back->setStyleSheet(buttonFont);

		download->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_down_over.svg"));
		download->setIconSize(QSize(iconHieght, iconWidth));
		download->setFixedSize(BUTTON_WIDTH_2, BUTTON_HEIGHT);
		download->setStyleSheet(buttonFont);

		QObject::connect(download, SIGNAL(clicked()), this, SLOT(productResultTableDownload_clicked()));
		QObject::connect(closeWindow, SIGNAL(clicked()), this, SLOT(productResultTableCancel_clicked()));
		QObject::connect(back, SIGNAL(clicked()), this, SLOT(productResultTableBack_clicked()));
		m_attachmentsFileName = "";
		
		Utility::Logger("ProductResultTable -> Constructor() -> End");
	}

	ProductResultTable::~ProductResultTable()
	{

	}
	/**
	 * \brief Adds rows data to Results table for Products
	 * \param productResults 
	 * \param styleIcon 
	 */
	void ProductResultTable::AddRowData(map<string, string>& productResults, QIcon styleIcon)
	{
		Utility::Logger("ProductResultTable -> AddRowData() -> Start");
		QTableWidgetItem* headerItem = new QTableWidgetItem();
		AddColumns(headerItem, productResults, styleIcon);
		m_productResults.push_back(productResults);
		Utility::Logger("ProductResultTable -> AddRowData() -> End");
	}
	/**
	 * \brief Add columns to Result table
	 * \param parent 
	 * \param productResults 
	 * \param styleIcon 
	 */
	void ProductResultTable::AddColumns(QTableWidgetItem* parent, map<string, string>& productResults, QIcon styleIcon)
	{
		Utility::Logger("ProductResultTable -> AddColumns() -> Start");
		
		QString styleSheet = "::section {""color: white;""border: 1px grey;""text-align: right;""font-family: arial;""font-size: 14px; }";
		ProductResultTable_2->horizontalHeader()->setStyleSheet(styleSheet);
		ProductResultTable_2->verticalHeader()->setStyleSheet(styleSheet);
		int currentRow = ProductResultTable_2->rowCount();
		ProductResultTable_2->setRowCount(currentRow + 1);
		for (int c = 0; c < ProductResultTable_2->columnCount(); ++c)
		{
			QTableWidgetItem* dataItem = new QTableWidgetItem;
			dataItem->setTextAlignment(Qt::AlignCenter);
			Qt::ItemFlags flags;
			flags = dataItem->flags();
			flags |= Qt::ItemIsSelectable | Qt::ItemIsEditable;
			dataItem->setFlags(flags);
			ProductResultTable_2->setStyleSheet("QTableWidget::indicator:unchecked {background-color:white;}");
			ProductResultTable_2->setStyleSheet("QToolTip { color: #ffffff; background-color: #000000; border: 1px #000000; }");
			
			QRadioButton* radioButton = new QRadioButton;
			radioButton->setCheckable(true);
			radioButton->setStyleSheet("margin-left:30%; margin-right:70%;");
			radioButton->setProperty("StyleId", QString::fromStdString(productResults.at("StyleId")));
			ProductResultTable_2->setCellWidget(currentRow, 0, radioButton);
			QTableWidgetItem* iconItem = new QTableWidgetItem;
			iconItem->setTextAlignment(Qt::AlignCenter);
			QTableWidgetItem* item3DAsset = new QTableWidgetItem(QString::fromUtf8(productResults.at("attachmentFileName").c_str()));//now
			item3DAsset->setTextAlignment(Qt::AlignCenter);
			item3DAsset->setToolTip(QString::fromUtf8(productResults.at("attachmentFileName").c_str()));

			ProductResultTable_2->setIconSize(QSize(80, 80));
			iconItem->setSizeHint(QSize(80, 80));
			iconItem->setIcon(styleIcon);

			ProductResultTable_2->setItem(currentRow, 3, iconItem);
			ProductResultTable_2->setItem(currentRow, 4, item3DAsset);

			int count = 1;
			map<float, string> headerColumns = getHeaderColumns();
			for (auto key = headerColumns.begin(); key != headerColumns.end(); ++key) 
			{
				if (count == 3) 
					count++;
				if (count == 4) 
					count++;
				QTableWidgetItem* tableWidget = new QTableWidgetItem(QString::fromUtf8(productResults.at(key->second).c_str()));
				tableWidget->setTextAlignment(Qt::AlignCenter);
				tableWidget->setToolTip(QString::fromUtf8(productResults.at(key->second).c_str()));
				ProductResultTable_2->setItem(currentRow, count, tableWidget);

				count++;
			}

			QObject::connect(radioButton, SIGNAL(clicked()), this, SLOT(callRadioSelected()));
		}
		
		Utility::Logger("ProductResultTable -> addColoums() -> End");
	}
	/**
	 * \brief When download button clicked by user, it download corresponding details of product
	 */
	void  ProductResultTable::productResultTableDownload_clicked()
	{
		Utility::Logger("ProductResultTable -> ProductResultTableDownloadClicked() -> Start");
		const char* newDirPath = DirectoryUtil::getStyleAttachmentDirectory().c_str();
		mkdir(newDirPath);
		int rowCount = ProductResultTable_2->rowCount();
		int columnCount = ProductResultTable_2->columnCount();
		QString styleCode;
		QString styleName;
		QString styleId;
		QString brand;
		QString imageLoadPath;
		QString imageSavePath;
		QString imageFileName;
		QString attachmentName;
		QString attachmentURL;
		QString attachmentFileListId;
		map<string, string> dataMap;
		bool isSelected = false;
		bool isAttachmetAvailable = false;
		bool isAttachmetValid = false;
		float validateAttachmentSize;
		float imageFileSize;

		for (int row = 0; row < rowCount; row++)
		{
			QTableWidgetItem* item = ProductResultTable_2->verticalHeaderItem(row);
			QWidget* qWidget = ProductResultTable_2->cellWidget(row, 0);
			QRadioButton* tempRadioButton = qobject_cast<QRadioButton*>(qWidget);
			if (tempRadioButton->isChecked())
			{
				isSelected = true;
			}
		}
		if (isSelected == false)
		{
			UTILITY_API->DisplayMessageBox("Select one row to download");
		}
		else
		{
			this->hide();
			for (int row = 0; row < rowCount; row++)
			{
				QTableWidgetItem* item = ProductResultTable_2->verticalHeaderItem(row);
				QWidget* qWidget = ProductResultTable_2->cellWidget(row, 0);
				QRadioButton* tempRadioButton = qobject_cast<QRadioButton*>(qWidget);
				if (tempRadioButton->isChecked())
				{
					styleId = tempRadioButton->property("StyleId").toString();
					for (int i = 0; i < m_productResults.size(); i++)
					{
						if (styleId == QString::fromStdString(m_productResults[i].at("StyleId")))
						{
							styleCode = QString::fromStdString(m_productResults[i].at("StyleCode"));
							styleName = QString::fromUtf8(m_productResults[i].at("Name").c_str());
							imageFileName = QString::fromUtf8(m_productResults[i].at("imageFileName").c_str());
							imageLoadPath = QString::fromStdString(Configuration::GetInstance()->PRODUCTS_TEMP_DIRECTORY) + imageFileName;
							imageSavePath = QString::fromStdString(DirectoryUtil::getStyleAttachmentDirectory()) + imageFileName;
							brand = QString::fromStdString(m_productResults[i].at("BrandId"));
							attachmentName = QString::fromUtf8(m_productResults[i].at("attachmentFileName").c_str());
							attachmentURL = QString::fromStdString(m_productResults[i].at("attachmentFileURL"));
							attachmentFileListId = QString::fromStdString(m_productResults[i].at("attachmentAttaFileListId"));
							dataMap = m_productResults[i];
						}
					}
					
					Utility::copyFile(imageLoadPath.toStdString().c_str(), imageSavePath.toStdString().c_str());

					
					if (attachmentURL != "" && attachmentName != "")
					{
						Utility::DownloadFilesFromURL(attachmentURL.toStdString(), DirectoryUtil::getStyleAttachmentDirectory() + attachmentName.toStdString());
						validateAttachmentSize =(float) Utility::GetFileSize(DirectoryUtil::getStyleAttachmentDirectory() + attachmentName.toStdString());
						if (validateAttachmentSize > 0)
						{
							
							const Marvelous::ImportZPRJOption option;
							IMPORT_API->ImportZprj(DirectoryUtil::getStyleAttachmentDirectory() + attachmentName.toStdString(), option);
							isAttachmetAvailable = true;
							isAttachmetValid = true;
						}
						else
						{
							break;			
						}
					}
					else if (attachmentURL == "")
					{
						UTILITY_API->NewProject();
					}
					
					if (attachmentName != "" || imageFileName != "")
					{
						CLOAPISample::LibraryAPIItem* setItem = new CLOAPISample::LibraryAPIItem();
						setItem->itemID = styleId;
						if (attachmentName != "")
						{
							setItem->itemName = attachmentName;
							setItem->sampleItemData.itemPath = attachmentName;
							setItem->filesize = validateAttachmentSize;
						}
						else
						{
							setItem->itemName = imageFileName;
							setItem->sampleItemData.itemPath = imageFileName;
							imageFileSize = (float)Utility::getFileSize(imageSavePath.toStdString());
							setItem->filesize = imageFileSize;
						}
						setItem->dateTime = "2019-08-20T16:21:41";
						setItem->metaData[META_DATA_KEY_0_DATA_TYPE] = QString("PRODUCT");
						setItem->metaData[META_DATA_KEY_2_BRAND] = brand;
						setItem->metaData[META_DATA_KEY_5_NAME] = styleName;
						setItem->metaData[META_DATA_KEY_7_NUMBER] = styleCode;
						setItem->metaData[META_DATA_KEY_6_ID] = styleId;
						setItem->sampleItemData.iconThumbnailPath = imageFileName;
						setItem->sampleItemData.previewThumbnailPath = imageFileName;
						bool alreadyExists = false;
						if (API_STORAGE)
						{
							for (int i = 0; i < API_STORAGE->m_LibraryAPIItemList.size(); i++)
							{
								if (API_STORAGE->m_LibraryAPIItemList[i]->metaData[META_DATA_KEY_6_ID].toString() == styleId)
								{
									API_STORAGE->m_LibraryAPIItemList[i] = setItem;
									alreadyExists = true;
									break;
								}
							}
							if (!alreadyExists)
								API_STORAGE->m_LibraryAPIItemList.push_back(setItem);
						}
					}
				
					break; 
				}
			}
			
			UpdateProduct::GetInstance()->FillUpdateProductData(dataMap);

			if (isAttachmetAvailable && isAttachmetValid)
			{
				UTILITY_API->DisplayMessageBox("Download of metadata and 3D asset completed");
				Utility::Logger("ProductResultTable -> ProductResultTableDownloadClicked() -> Download of MetaData And 3D Asset Completed");
			}
			else if (!isAttachmetValid && attachmentURL != "")
			{
				UTILITY_API->DisplayMessageBox("Invalid 3D asset file, unable to download");
				Utility::Logger("ProductResultTable -> ProductResultTableDownloadClicked() -> Download product Does Not Have Valid 3D Asset,Download Not Completed.");
			}
			else
			{
				UTILITY_API->DisplayMessageBox("Downloaded product does not have 3D asset, downloading of metadata completed");
				Utility::Logger("ProductResultTable -> ProductResultTableDownloadClicked() -> Download Completed Only MetaData");
			}
			wstring wideString = wstring(Configuration::GetInstance()->PRODUCTS_TEMP_DIRECTORY.begin(), Configuration::GetInstance()->PRODUCTS_TEMP_DIRECTORY.end());
			Utility::RemoveDirectory(wideString.c_str());
		}
		Utility::Logger("ProductResultTable -> ProductResultTableDownloadClicked() -> End"); 
	} 
	/**
	 * \brief Looks for Check box selection and collects all selected rows
	 */
	void ProductResultTable::callRadioSelected()
	{
		Utility::Logger("ProductResultTable -> callRadioSelected() -> Start");

		int rowCount1 = ProductResultTable_2->rowCount();
		for (int row = 0; row < rowCount1; row++)
		{
			QWidget* qWidget = ProductResultTable_2->cellWidget(row, 0);
			QRadioButton* tempRadioButton = qobject_cast<QRadioButton*>(qWidget);  //setCellWidget(currentRow, 0, radioButton);
			if (tempRadioButton->isChecked())
			{
				ProductResultTable_2->selectRow(row);
			}
		}
		Utility::Logger("ProductResultTable -> callRadioSelected() -> End");
	}
	
	
	/**
	 * \brief Recordes Clock of Back button by user and stops sending request further.
	 */
	void ProductResultTable::productResultTableBack_clicked()
	{
		Utility::Logger("ProductResultTable -> ProductResultTableBackClicked() -> Start");
		this->close();
		ProductSearch::GetInstance()->setModal(true);
		ProductSearch::GetInstance()->show();
		Utility::Logger("ProductResultTable -> ProductResultTableBackClicked() -> End");
	}
	/**
	 * \brief Recordes Clock of Cancel button by user and terminates search action.
	 */
	void ProductResultTable::productResultTableCancel_clicked()
	{
		Utility::Logger("ProductResultTable -> ProductResultTableCancelClicked() -> Start");
		this->close();
		Utility::Logger("ProductResultTable -> ProductResultTableCancelClicked() -> End");
	}
	/**
	 * \brief Function is used to get header column names
	 */
	map<float, string> ProductResultTable::getHeaderColumns() {
		return headerColumns;
	}
	/**
	 * \brief Function is used to set header column names
	 */
	void ProductResultTable::setHeaderColumns(map<float, string>& headerColumn) {
		headerColumns = headerColumn;
	}

	void ProductResultTable::setResultTableColumns(map<string, string>& columns) {
		resultTableColumns = columns;
	}
}