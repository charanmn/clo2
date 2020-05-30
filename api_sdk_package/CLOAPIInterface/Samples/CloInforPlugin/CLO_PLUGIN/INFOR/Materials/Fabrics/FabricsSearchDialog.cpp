#pragma once
#include "FabricsSearchDialog.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QCheckBox>
#include <any>
#include <optional>
#include "GeneratedFiles/ui_FabricsSearchDialog.h"
#include "qlistview.h"
#include "CLO_PLUGIN/INFOR/Utilities/Definitions.h" 
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"
#include "CLO_PLUGIN/INFOR/Utilities/ComboBoxItem.h"
#include "CLO_PLUGIN/INFOR/Utilities/Configuration.h"
#include "CLO_PLUGIN/INFOR/DesignSuite/DesignSuite.h"
#include "FabricsResultTable.h"	
#include "CLO_PLUGIN/INFOR/Libraries/curl/include/curl/curl.h"
#include <iostream>
#include <direct.h>
#include "CLO_PLUGIN/INFOR/Utilities/Configuration.h"
#include "CLO_PLUGIN/INFOR/Utilities/RestAPIUtility.h"
#include "CLO_PLUGIN/INFOR/Utilities/DirectoryUtil.h"

using json = nlohmann::json;

using namespace std;

using mapjson = nlohmann::json;
bool matImageAtt= false;
bool matZfabAtt = false;

namespace CLOPlugin
{
	MaterialSearchDialog* MaterialSearchDialog::_instance = NULL;

	/**
	 * \brief Instantiate MaterialSearchDialog object
	 * \return 
	 */
	MaterialSearchDialog* MaterialSearchDialog::GetInstance()
	{
		Utility::Logger("FabricsSearchDialog -> GetInstance() -> Start");
		if (_instance == NULL)
		{
			_instance = new MaterialSearchDialog();
		}
		Utility::Logger("FabricsSearchDialog -> GetInstance() -> End");
		
		return _instance;
	}
	/**
	 * \brief Destroys instantiated MaterialSearchDialog object
	 */
	void MaterialSearchDialog::Destroy()
	{
		Utility::Logger("FabricsSearchDialog -> Destroy() -> Start");
		if (_instance)
		{
			delete _instance;
			_instance = NULL;
		}
		Utility::Logger("FabricsSearchDialog -> Destroy() -> End");
	}
	/**
	 * \brief Clears all UI fields of QT Widget of Material Search page
	 */
	void MaterialSearchDialog::ClearAllFields()
	{
		Utility::Logger("FabricsSearchDialog -> ClearAllFields() -> Start");

		for (int i = 0; i < MaterialSearchTree->topLevelItemCount(); ++i)
		{
			QTreeWidgetItem* topItem = MaterialSearchTree->topLevelItem(i);
			QWidget* qWidgetColumn0 = MaterialSearchTree->itemWidget(topItem, 0);
			QWidget* qWidgetColumn1 = MaterialSearchTree->itemWidget(topItem, 1);
			QLabel* qlabel = qobject_cast<QLabel*>(qWidgetColumn0);
			string lable = qlabel->text().toStdString();
			QLineEdit* qlineedit = qobject_cast<QLineEdit*>(qWidgetColumn1);

			if (qlineedit)
			{
				qlineedit->setText("");
			}
			else
			{
				QComboBox* qComboBox = qobject_cast<QComboBox*>(qWidgetColumn1);
				if (qComboBox)
				{
					int indexOfEmptyString = qComboBox->findText("Select");
					qComboBox->setCurrentIndex(indexOfEmptyString);
				}
				else
				{
					QTextEdit* qtextEdit = qobject_cast<QTextEdit*>(qWidgetColumn1);
					if (qtextEdit)
					{
						qtextEdit->setText("");
					}
				}
			}
		}
		Utility::Logger("FabricsSearchDialog -> ClearAllFields() -> End");
	}
	MaterialSearchDialog::MaterialSearchDialog(QWidget* parent) : QDialog(parent)
	{
		Utility::Logger("FabricsSearchDialog -> Constructor() -> Start");
		
		setupUi(this);
		QTreeWidgetItem* dataItem = new QTreeWidgetItem;
		
		Qt::ItemFlags flags;
		flags = dataItem->flags();
		flags |= Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
		dataItem->setFlags(flags);
		QFont fontStyle("Times new roman", FONT_SIZE, QFont::Bold);
		this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
		QSize size(TABLE_WIDTH, TABLE_HEIGHT);
		MaterialSearchTree->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		MaterialSearchTree->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		MaterialSearchTree->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
		MaterialSearchTree->setSelectionBehavior(QAbstractItemView::SelectItems);
		MaterialSearchTree->setSelectionMode(QAbstractItemView::NoSelection);
		MaterialSearchTree->setSelectionBehavior(QAbstractItemView::SelectRows);
		MaterialSearchTree->setEditTriggers(QAbstractItemView::CurrentChanged);
		MaterialSearchTree->setTabKeyNavigation(true);
		MaterialSearchTree->setStyleSheet("QTreeWidget::item { border-bottom: 1px solid #232323;""padding : 10px;""height: 25px;""}");
		MaterialSearchTree->setFixedSize(size);
		MaterialSearchTree->setColumnWidth(1, USER_INPUT_WIDTH);
		MaterialSearchTree->setColumnWidth(0, SEARCH_LABEL_WIDTH);
		headerLabel->setFont(fontStyle);
		layout()->setSizeConstraint(QLayout::SetFixedSize);
		this->adjustSize();

		back->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_back_over.svg"));
		back->setIconSize(QSize(iconHieght, iconWidth));
		back->setStyleSheet(buttonFont);

		search->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_search_over.svg"));
		search->setIconSize(QSize(iconHieght, iconWidth));
		search->setStyleSheet(buttonFont);

		QObject::connect(search, SIGNAL(clicked()), this, SLOT(Search_clicked()));
		QObject::connect(back, SIGNAL(clicked()), this, SLOT(back_clicked()));
		QObject::connect(closeWindow, SIGNAL(clicked()), this, SLOT(Cancel_clicked()));
		m_isUserInputEmpty = true;
		m_currentBrandName = "";
		m_isOnlyPercentileFound = false;
		FilterDependencyList();
		
		ReadPLMJson();
		ReadJsonAndDrawDialog();
		SetDefaultPresetValues();
		Utility::Logger("FabricsSearchDialog -> Constructor() -> End");
	}
	/**
	 * \brief Reads JSON for all UI fields and draws
	 */
	void MaterialSearchDialog::ReadJsonAndDrawDialog()
	{
		Utility::Logger("FabricsSearchDialog -> ReadJsonAndDrawDialog() -> Start");
		m_materialsFieldsVector = Utility::ReadJsonForDrawDialogue("Material");
		DrawWidget(m_materialsFieldsVector);		
		Utility::Logger("FabricsSearchDialog -> ReadJsonAndDrawDialog() -> End");
	}
	/**
	 * \brief Draws UI widget using all read fields
	 * \param fieldsVector 
	 */
	void MaterialSearchDialog::DrawWidget(std::vector<Utility::Fields>& fieldsVector)
	{
		Utility::Logger("FabricsSearchDialog -> DrawWidget() -> Start");
		json keyValuePairs = Utility::GetKeyValuePairs();
		Utility::Logger("FabricsSearchDialog -> DrawWidget() -> keyValuePairs:: "+ to_string(keyValuePairs));
		for each(auto field in fieldsVector)
		{
			string tempLabel = field.labelValue.toStdString();
			if (m_attributeMap.find(tempLabel) != m_attributeMap.end()) {
				tempLabel = m_attributeMap.at(tempLabel);
				Utility::Logger("FabricsSearchDialog -> DrawWidget() -> displayValue:: " + tempLabel);
			}
			else {
				QString displayValue = Utility::GetDisplayValueByKey(QString::fromStdString(tempLabel), QString::fromStdString("material"), keyValuePairs);
				Utility::Logger("FabricsSearchDialog -> DrawWidget() -> displayValue:: " + displayValue.toStdString());
				if (displayValue.isNull() || displayValue.isEmpty()) {
					int tempCapsCount = 0;
					for (int capsCount = 0; capsCount < tempLabel.length(); capsCount++)
					{
						if (isupper(tempLabel[capsCount]))
						{
							if (capsCount != tempCapsCount)
							{
								tempCapsCount = capsCount + 1;
								tempLabel = tempLabel.insert(capsCount, " ");
							}
						}
					}
				}
				else {
					tempLabel = displayValue.toStdString();
				}
			}

			if (field.fieldUItype == "text")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();  // Creating new TreeWidgetItem
				QLineEdit* lineEdit = new QLineEdit();						// Creating new LineEdit Widget
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);
				
				label->setText(QString::fromStdString(tempLabel));
				lineEdit->setStyleSheet(inputStyle);
				MaterialSearchTree->addTopLevelItem(topLevel);						// Adding ToplevelItem
				MaterialSearchTree->setItemWidget(topLevel, 0, label);				// Adding label at column 1
				MaterialSearchTree->setItemWidget(topLevel, 1, lineEdit);
			}

			if (field.fieldUItype == "dropdown")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();
				QComboBox* comboBox = new QComboBox(this);
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);

				label->setText(QString::fromStdString(tempLabel));// Setting created font style to label
				comboBox->setStyleSheet(inputStyle);
				
				MaterialSearchTree->addTopLevelItem(topLevel);
				MaterialSearchTree->setItemWidget(topLevel, 0, label);
				MaterialSearchTree->setItemWidget(topLevel, 1, comboBox);
				comboBox->setStyleSheet("font: 75 8pt \"Tahoma\"; combobox-popup:0");
				comboBox->addItems(field.presetValues);
				int indexOfEmptyString = comboBox->findText("Select");
				comboBox->setCurrentIndex(indexOfEmptyString);
				comboBox->setProperty("Id", QString::fromStdString(tempLabel));
				QObject::connect(comboBox, SIGNAL(currentTextChanged(const QString&)), this,
					SLOT(handleDropDownValueChangeEvent(const QString&)));
				
			}

			if (field.fieldUItype == "textarea")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();  // Creating new TreeWidgetItem
				QTextEdit* textEdit = new QTextEdit();						// Creating new LineEdit Widget
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);

				label->setText(QString::fromStdString(tempLabel));
				
				MaterialSearchTree->addTopLevelItem(topLevel);						// Adding ToplevelItem
				MaterialSearchTree->setItemWidget(topLevel, 0, label);				// Adding label at column 1
				MaterialSearchTree->setItemWidget(topLevel, 1, textEdit);
				textEdit->setText(field.userInputValues);
				textEdit->setStyleSheet("border: 1px solid black;"
					"background-color: #222222;"
					"font: 75 8pt \"Tahoma\";"
				);
				textEdit->setMaximumSize(TEXTEDIT_SIZE_WIDTH, TEXTEDIT_SIZE_HEIGHT);
			}

			if (field.fieldUItype == "DateEdit")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();
				QDateEdit* dateTimeEdit = new QDateEdit();
				bool enable = true;
				dateTimeEdit->setCalendarPopup(enable);			// Setting Popup Calendar for Date time picker.
				QString dataricovero("");
				QDate date = QDate::fromString(dataricovero, "");
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);

				label->setText(QString::fromStdString(tempLabel));
				dateTimeEdit->setStyleSheet(inputStyle);
				
				MaterialSearchTree->addTopLevelItem(topLevel);
				MaterialSearchTree->setItemWidget(topLevel, 0, label);
				MaterialSearchTree->setItemWidget(topLevel, 1, dateTimeEdit);
				
			}
		}
		Utility::Logger("FabricsSearchDialog -> DrawWidget() -> End");
	}
	MaterialSearchDialog::~MaterialSearchDialog()
	{
		Utility::Logger("FabricsSearchDialog -> Desturctor() -> Start");
	}

	/**
	 * \brief Using extracted values of User selected values, creates Map of Field and values
	 */
	void MaterialSearchDialog::CreateSearchMap()
	{
		Utility::Logger("FabricsSearchDialog -> CreateSearchMap() -> Start");
		json emptyJsonObject;
		json conditions = json::object();

		m_materialSearchMap["roleId"] = Configuration::GetInstance()->GetRoleId();
		m_materialSearchMap["userId"] = Configuration::GetInstance()->GetUserId();
		m_materialSearchMap["entity"] = "Material";
		m_materialSearchMap["Schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
		m_materialSearchMap["fromAi"] = true;
		m_materialSearchMap["pageType"] = "list";
		m_materialSearchMap["sortInfo"] = emptyJsonObject;

		Utility::CreateSearchCriteriaMap(conditions, m_materialsFieldsVector, m_attsDropdownListMap);
		
		conditions["Search"] = nullptr;

		m_materialSearchMap["dataFilter"] = conditions;
		Utility::Logger("FabricsSearchDialog -> CreateSearchMap() -> End");
	}
	/**
	 * \brief USing fields and value map, Searches for Objects in PLM
	 */
	void MaterialSearchDialog::PLMSearch()
	{
		Utility::Logger("FabricsSearchDialog -> PLMSearch() -> Start");
		
		Utility::Logger("FabricsSearchDialog -> PLMSearch() -> m_materialSearchMap:: "+ to_string(m_materialSearchMap));
		Utility::Logger("FabricsSearchDialog -> PLMSearch() -> FABRIC_SEARCH_API:: " + FABRIC_SEARCH_API);
		string response = RestCall(to_string(m_materialSearchMap), FABRIC_SEARCH_API);
		Utility::CustomMessageBox("response:: " + response);
		Utility::Logger("FabricsSearchDialog::PLMSearch() response - " + response);
		json responseJson;
		string errorResponse = Utility::CheckErrorDescription(response);
		Utility::Logger("FabricsSearchDialog -> PLMSearch() -> errorResponse:: " + errorResponse);

		if (errorResponse.empty() && (errorResponse.length() == 0))
		{
			responseJson = Utility::GetResultsJSON(response);
			CreateResultTable(responseJson);
		}
		else
		{
			UTILITY_API->DisplayMessageBox(errorResponse);
		}
		Utility::Logger("FabricsSearchDialog -> PLMSearch() -> End");
	}
	/**
	 * \brief Recordes Clock of Search by user and send request for Search operation
	 */
	void MaterialSearchDialog::Search_clicked()
	{
		Utility::Logger("FabricsSearchDialog -> Search_clicked() -> Start");
		if (Utility::ExtractAllUIValuesAndMapToJson(MaterialSearchTree, m_materialsFieldsVector) && Utility::SearchValidation(MaterialSearchTree))
		{
			this->hide();
			CreateSearchMap();
			PLMSearch();
			m_isUserInputEmpty = true;
			m_isOnlyPercentileFound = false;
		}
		else
		{
			m_isUserInputEmpty = true;
			m_isOnlyPercentileFound = false;
		}
		Utility::Logger("FabricsSearchDialog -> Search_clicked() -> End");
	}
	/**
	 * \brief Function is used to get header columns of result table
		 */
	map<string, string> MaterialSearchDialog::GetFieldUITypes() 
	{
		Utility::Logger("FabricsSearchDialog -> GetFieldUITypes() -> Start");
		json jsonString;
		map<string, string> fields;
		ifstream filename;
		filename.open(DirectoryUtil::getFabricSearchFilteredJson());
		filename >> jsonString;
		filename.close();
		string completeJsonString, fieldValues, uiTypelist;
		json completeJson, fieldValuesJson, uiTypeJson;
		completeJsonString = jsonString.dump();
		try {
			completeJson = json::parse(completeJsonString);
			fieldValues = completeJson["fieldList"].dump();
			fieldValuesJson = json::parse(fieldValues);

			uiTypelist = completeJson["uiTypeList"].dump();
			uiTypeJson = json::parse(uiTypelist);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("MaterialSearchDialog::GetFieldUITypes()::parsing completeJson exception - " + string(e.what()));
			throw e.what();
		}
		for (int i = 0; i < fieldValuesJson.size(); i++)
		{
			string fieldValuesString = fieldValuesJson[i].dump();
			fieldValuesString = fieldValuesString.erase(0, 1);
			fieldValuesString = fieldValuesString.erase(fieldValuesString.size() - 1);

			string uiType = uiTypeJson[fieldValuesString].dump();
			uiType = uiType.erase(0, 1);
			uiType = uiType.erase(uiType.size() - 1);
			
			fields.insert(make_pair(fieldValuesString, uiType));
		}
		Utility::Logger("FabricsSearchDialog -> GetFieldUITypes() -> End");
		return fields;
	}
	/**
	 * \brief Using results from PLM, create Results table and diaplays
	 * \param responseJson 
	 */
	void MaterialSearchDialog::CreateResultTable(json& responseJson)
	{
		Utility::Logger("FabricsSearchDialog -> CreateResultTable() -> Start");

		Utility::Logger("FabricsSearchDialog -> CreateResultTable() -> responseJson:: "+ to_string(responseJson));
		const char* newDirPath = Configuration::GetInstance()->MATERIALS_TEMP_DIRECTORY.c_str();
		mkdir(newDirPath);

		map<string, string> fieldUITypeMap = GetFieldUITypes();
		string entities = responseJson["entities"].dump();
		json completeEntitiesJson;
		try {
			completeEntitiesJson = json::parse(entities);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("MaterialSearchDialog::CreateResultTable()::parsing completeEntitiesJson exception - " + string(e.what()));
			throw e.what();
		}
		ResultTable::setHeaderColumns(indexColumnIdMap);
		ResultTable::setResultTableColumns(m_attributeMap);
		ResultTable materialResultsTableObject;
		bool isImage = false;
		bool isZfab = false;
		if (completeEntitiesJson.size() != 0)
		{
			int rowCount = 0;
			QPixmap	NoImgpixmap;
			for (int i = 0; i < completeEntitiesJson.size(); i++)
			{
				string entityJson = completeEntitiesJson[i].dump();
				json material;
				try {
					material = json::parse(entityJson);
				}
				catch (exception& e)
				{
					Utility::ErrorLogger("MaterialSearchDialog::CreateResultTable()::parsing material exception - " + string(e.what()));
					throw e.what();
				}
				string name = material["name"].dump();
				name = name.erase(0, 1);
				name = name.erase(name.size() - 1);
				string column, materialId, materialCode, thumbnail, materialAttachmentName, filenameToSave;
				
				map<string, string> fieldValueMap;
				if (name == "Material")
				{
					column = material["column"].dump();
					json columns;
					try {
						columns = json::parse(column);
					}
					catch (exception& e)
					{
						Utility::ErrorLogger("MaterialSearchDialog::CreateResultTable()::parsing columns exception - " + string(e.what()));
						throw e.what();

					}
					materialId = columns["MaterialId"].dump();

					materialCode = columns["MaterialCode"].dump();
					materialCode = materialCode.erase(0, 1);
					materialCode = materialCode.erase(materialCode.size() - 1);

					fieldValueMap.insert(make_pair("MaterialId", materialId));

					for (auto key = indexColumnIdMap.begin(); key != indexColumnIdMap.end(); ++key) {
						string columnValue = Utility::getValue(columns[key->second]);

						if (fieldUITypeMap.at(key->second) == "dropdown") {
							columnValue = Utility::getValue(columns[key->second + "_Lookup"]["Name"]);
						}

						fieldValueMap.insert(make_pair(key->second, columnValue));
					}

					QPixmap pixmap;
					matImageAtt = false;
					bool isImageFormatSupported = false;
					thumbnail = columns["Image"].dump();
					string upperCaseThumb = thumbnail;
					if (thumbnail != "null")
					{
						thumbnail = thumbnail.erase(0, 1);
						thumbnail = thumbnail.erase(thumbnail.size() - 1);

						std::for_each(upperCaseThumb.begin(), upperCaseThumb.end(), [](char& c) {
							c = ::toupper(c);
							});

						size_t foundPng = upperCaseThumb.find(".PNG");
						size_t foundJpg = upperCaseThumb.find(".JPG");
						size_t foundJpeg = upperCaseThumb.find(".JPEG");
						QImage styleIcon;
						if (foundPng != string::npos)
						{
							filenameToSave = materialCode + ".png";
							isImageFormatSupported = true;
							Utility::CustomMessageBox("filenameToSave" + filenameToSave);

						}
						if (foundJpg != string::npos)
						{
							filenameToSave = materialCode + ".jpg";
							isImageFormatSupported = true;
							Utility::CustomMessageBox("filenameToSave" + filenameToSave);
						}
						if (foundJpeg != string::npos)
						{
							filenameToSave = materialCode + ".jpeg";
							isImageFormatSupported = true;
							Utility::CustomMessageBox("filenameToSave" + filenameToSave);
						}

						matImageAtt = true;

						//No need to download the attachments if image format is not supported.
						//currently png, jpg and jpeg formats are supported.
						if (isImageFormatSupported) {
							Utility::Logger("FabricsSearchDialog -> CreateResultTable() filenameToSave - " + filenameToSave);
							Utility::DownloadImageFromURL(thumbnail, Configuration::GetInstance()->MATERIALS_TEMP_DIRECTORY + filenameToSave);
							
							QImageReader imageReader(QString::fromStdString(Configuration::GetInstance()->MATERIALS_TEMP_DIRECTORY + filenameToSave));
							imageReader.setDecideFormatFromContent(true);
							styleIcon = imageReader.read();

							if (styleIcon.isNull()) {
								Utility::Logger("FabricsSearchDialog -> CreateResultTable() Image is not loaded.  ");
							}
							else {
								pixmap = QPixmap::fromImage(styleIcon);
							}
						}
					}
					Utility::Logger("FabricsSearchDialog -> CreateResultTable() -> materialId:: " + materialId);
					Utility::Logger("FabricsSearchDialog -> CreateResultTable() -> materialCode:: " + materialCode);
					DownloadAtachment(materialId, materialCode, materialAttachmentName);

					if (matZfabAtt) {
						isImageFormatSupported = true;
					}
					
					fieldValueMap.insert(make_pair("fabricImageName", filenameToSave));
					fieldValueMap.insert(make_pair("fabricAtachment", matZfabAtt ? "true" : "false"));
					fieldValueMap.insert(make_pair("fabricAtachmentName", materialAttachmentName));
					fieldValueMap.insert(make_pair("fabricImage", matImageAtt ? "true" : "false"));
					fieldValueMap.insert(make_pair("imageSupported", isImageFormatSupported ? "true" : "false"));

					if (matImageAtt|| matZfabAtt)
					{
						rowCount++;
						isImage = matImageAtt;
						isZfab = matZfabAtt;
						if (!pixmap.isNull())
						{
							materialResultsTableObject.AddRowData(fieldValueMap, pixmap);
						}
						else 
						{
							NoImgpixmap = Utility::getNoImageAvailable();
							materialResultsTableObject.AddRowData(fieldValueMap, NoImgpixmap);
						}
						matZfabAtt = false;
						matImageAtt = false;
					}
				}
			}
			
			if (rowCount > GetMaxResultsCount())
			{
				UTILITY_API->DisplayMessageBox("Number of records are exceeding the maximum limit. Please refine your search criteria.");
				this->show();
			}
			else if( ((isImage) || (isZfab)) )
			{
				materialResultsTableObject.setModal(true);
				materialResultsTableObject.exec();
			}
			else 
			{
				UTILITY_API->DisplayMessageBox("This record does not have an image or zfab");
				Utility::Logger("FabricsSearchDialog -> createResultTable() -> This record does not have an image or zfab");
				this->show();
			}
		}
		else
		{
			UTILITY_API->DisplayMessageBox("No result found");
			Utility::Logger("FabricsSearchDialog -> createResultTable() -> No Result Found"); 
			this->show(); 
		}
		Utility::Logger("FabricsSearchDialog -> createResultTable() -> End");
	}

	/*
	*brief read the json file to get maximum number of rows to be displayed on the result table
	*retunr int: number of rows
	*/
	int MaterialSearchDialog::GetMaxResultsCount() {
		json fabricJson, entityData, fabrics;
		ifstream filename(DirectoryUtil::getCLOPLMPluginConfigJson());
		filename >> fabricJson;
		filename.close();
		int maxNoOfRows = 0;
		string entities = fabricJson["entities"].dump();
		try {
			entityData = json::parse(entities);
		}
		catch (exception & e)
		{
			Utility::ErrorLogger("MaterialSearchDialog::GetMaxResultsCount()::parsing entityData exception - " + string(e.what()));
			throw e.what();
		}
		if (entityData.size() != 0) {
			for (int i = 0; i < entityData.size(); i++)
			{
				string entityJson = entityData[i].dump();
				try {
					fabrics = json::parse(entityJson);
				}
				catch (exception & e)
				{
					Utility::ErrorLogger("MaterialSearchDialog::GetMaxResultsCount()::parsing entityJson exception - " + string(e.what()));
					throw e.what();
				}
				string name = fabrics["name"].dump();
				name = name.erase(0, 1);
				name = name.erase(name.size() - 1);

				if (name == "Fabric")
				{
					string maxRows = fabrics["maxResultCount"].dump();
					maxNoOfRows = stoi(maxRows);
				}
			}
		}
		return maxNoOfRows;
	}
	/**
	 * \brief Recordes Clock of Back button by user and stops sending request further.
	 */
	void MaterialSearchDialog::back_clicked()
	{
		Utility::Logger("FabricsSearchDialog -> BackClicked() -> Start");
		this->hide();
		DesignSuite::GetInstance()->setModal(true);
		DesignSuite::GetInstance()->show();
		Utility::Logger("FabricsSearchDialog -> BackClicked() -> End");
	}
	/**
	 * \brief Recordes Clock of Cancel button by user and terminates search action.
	 */
	void MaterialSearchDialog::Cancel_clicked()
	{
		Utility::Logger("FabricsSearchDialog -> CancelClicked() -> Start");
		this->close();
		Utility::Logger("FabricsSearchDialog -> CancelClicked() -> End");
	}
	/**
	 * \brief Reads PLM sent JSON for values
	 */
	void  MaterialSearchDialog::ReadPLMJson() 
	{
		Utility::Logger("FabricsSearchDialog -> ReadPLMJson() -> Start");
		
		ofstream materialDetailsFile;
		materialDetailsFile.open(DirectoryUtil::getFabricSearchJson());
		
		string parameter = "{\"roleId\":" +Configuration::GetInstance()->GetRoleId() +",\"userId\":" + Configuration::GetInstance()->GetUserId() + ",\"entity\":\"Material\",\"pageType\":\"details\",\"dataFilter\":{\"conditions\":[{\"fieldname\":\"MaterialId\",\"operator\":\"=\",\"value\":\"\"}]},\"pageInfo\":{},\"Schema\":" + Configuration::GetInstance()->GetschemaWithQuotes() + "}";
		Utility::Logger("FabricsSearchDialog -> ReadPLMJson() -> parameter:: "+ parameter);
		Utility::Logger("FabricsSearchDialog -> ReadPLMJson() -> FABRIC_DETAILS_API:: " + FABRIC_DETAILS_API);
		string response = RestCall(parameter, FABRIC_DETAILS_API);
		Utility::CustomMessageBox("response:: " + response);
		Utility::Logger("FabricsSearchDialog::ReadPLMJson() response - " + response);
		string errorResponse = Utility::CheckErrorDescription(response);
		Utility::Logger("FabricsSearchDialog -> ReadPLMJson() -> errorResponse:: " + errorResponse);

		json docLibjson;
		if (errorResponse.empty() && (errorResponse.length() == 0))
		{
			try
			{
				docLibjson = json::parse(response);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("MaterialSearchDialog::ReadPLMJson()::parsing docLibjson exception - " + string(e.what()));
				throw e.what();
			}
		}
		else
		{
			UTILITY_API->DisplayMessageBox(errorResponse);
		}
		materialDetailsFile << docLibjson;
		materialDetailsFile.close();
		
		json completeStyleJson;
		m_attsDropdownListMap.clear();
		m_attributeMap.clear();
		ifstream file;
		file.open(DirectoryUtil::getFabricSearchJson());
	
		file >> completeStyleJson;
		file.close();
		
		ofstream materialSearchFile;
		materialSearchFile.open(DirectoryUtil::getFabricSearchFilteredJson());
		json finalJsontoSave;
		auto jsonFieldList = json::array();
		auto jsonUiTypeList = json::object();
		auto presetArray = json::array();
		auto presetList = json::object();
		
		auto jsonMandatoryFieldsList = json::array();
		int uiPresetCount = 0;
		string completeStyleJsonString, componentsString, compObjString, propsString;
		json completeJson, componentsJson, compObjJson, propsJson;
		completeStyleJsonString = completeStyleJson.dump();
		try {
			completeJson = json::parse(completeStyleJsonString);
			componentsString = completeJson["layout"]["components"].dump();
			componentsJson = json::parse(componentsString);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("MaterialSearchDialog::ReadPLMJson()::parsing completeJson exception - " + string(e.what()));
			throw e.what();
		}
		for (int i = 0; i < componentsJson.size(); i++) {
			compObjString = componentsJson[i].dump();
			try {
				compObjJson = json::parse(compObjString);
				propsString = compObjJson["props"].dump();
				propsJson = json::parse(propsString);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("MaterialSearchDialog::ReadPLMJson()::parsing compObjJson exception - " + string(e.what()));
				throw e.what();
			}
			string visible = propsJson["isVisibleAi"].dump();
			if (visible == "true")
			{
				string isRequired = propsJson["isRequired"].dump();

				string tabIndex = propsJson["tabIndex"].dump();
				
				string fieldType = compObjJson["fieldType"].dump();
				fieldType = fieldType.erase(0, 1);
				fieldType = fieldType.erase(fieldType.size() - 1);
				string lookupRef = compObjJson["lookupRef"].dump();
				lookupRef = lookupRef.erase(0, 1);
				lookupRef = lookupRef.erase(lookupRef.size() - 1);

				string dataField = compObjJson["dataField"].dump();
				dataField = dataField.erase(0, 1);
				dataField = dataField.erase(dataField.size() - 1);

				string label = compObjJson["label"].dump();
				label = label.erase(0, 1);
				label = label.erase(label.size() - 1);

				indexColumnIdMap.insert(make_pair(std::stoi(tabIndex), dataField));
				jsonUiTypeList[dataField] = fieldType;

				jsonFieldList.push_back(dataField);
				if (isRequired == "true")
				{
					jsonMandatoryFieldsList.push_back(dataField);
				}

				if (label != "ul") {
					m_attributeMap.insert(std::make_pair(dataField, label));
				}

				if (fieldType == "dropdown")
				{
					string lookups = completeJson["lookups"].dump();
					json lookupsJSON;
					try {
						lookupsJSON = json::parse(lookups);
					}
					catch (exception& e)
					{
						Utility::ErrorLogger("MaterialSearchDialog::ReadPLMJson()::parsing lookupsJSON exception - " + string(e.what()));
						throw e.what();
					}
					map<string, string> tempAttribMap;
					Utility::GetDropDownMap(lookupsJSON, lookupRef, tempAttribMap);
					presetArray.clear();
					presetArray.push_back("Select");
					for (auto it = tempAttribMap.begin(); it != tempAttribMap.end(); it++)
					{
						presetArray.push_back(it->first);
					}
					presetList[dataField] = presetArray;
					m_attsDropdownListMap.insert(std::make_pair(dataField, tempAttribMap));
				}
			}
		}
		auto newJsonFieldList = json::array();
		for (auto itr = indexColumnIdMap.begin(); itr != indexColumnIdMap.end(); itr++) {
			newJsonFieldList.push_back(itr->second);
		}

		finalJsontoSave["fieldList"] = newJsonFieldList;
		finalJsontoSave["uiTypeList"] = jsonUiTypeList;
		finalJsontoSave["presetList"] = presetList;
		finalJsontoSave["mandatory_fieldList"] = jsonMandatoryFieldsList;
		
		materialSearchFile << finalJsontoSave;
		materialSearchFile.close();
		Utility::Logger("FabricsSearchDialog -> ReadPLMJson() -> End");
	}
	
	/**
	 * \brief Downloads attachment using url from JSON
	 * \param materialId 
	 * \param materialCode 
	 */
	void MaterialSearchDialog::DownloadAtachment(string materialId, string materialCode, string &materialAttachmentName)
	{
		Utility::Logger("FabricsSearchDialog -> DownloadAtachment() -> Start");
		
		json materialAttachSearchMap;
		json filterMapAtt;
		json ConditionsAtt = json::object();
		
		materialAttachSearchMap["roleId"] = Configuration::GetInstance()->GetRoleId();
		materialAttachSearchMap["userId"] = Configuration::GetInstance()->GetUserId();
		materialAttachSearchMap["entity"] = "MaterialAttachments";
		materialAttachSearchMap["Schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
		materialAttachSearchMap["personalizationId"] = 0;
		materialAttachSearchMap["pageType"] = "list";
		filterMapAtt["fieldname"] = "Code";
		filterMapAtt["operator"] = "=";
		filterMapAtt["value"] = "E0024";
		ConditionsAtt["Conditions"][0] = filterMapAtt;
		filterMapAtt.clear();
		filterMapAtt["fieldname"] = "IsDeleted";
		filterMapAtt["operator"] = "=";
		filterMapAtt["value"] = 0;
		ConditionsAtt["Conditions"][1] = filterMapAtt;
		filterMapAtt.clear();
		filterMapAtt["fieldname"] = "ReferenceId";
		filterMapAtt["operator"] = "=";
		filterMapAtt["value"] = materialId;
		ConditionsAtt["Conditions"][2] = filterMapAtt;
		filterMapAtt.clear();
		materialAttachSearchMap["dataFilter"] = ConditionsAtt;
		
		materialAttachSearchMap["pageInfo"] = nullptr;
		materialAttachSearchMap["sortInfo"] = nullptr;

		Utility::Logger("FabricsSearchDialog::DownloadAtachment -> materialAttachSearchMap :: " + to_string(materialAttachSearchMap));
		Utility::Logger("FabricsSearchDialog::DownloadAtachment -> GET_ATTACHMENT_INFO_API :: " + GET_ATTACHMENT_INFO_API);
		string attResponse = RestCall(to_string(materialAttachSearchMap), GET_ATTACHMENT_INFO_API);
		Utility::CustomMessageBox("attResponse:: " + attResponse);
		Utility::Logger("FabricsSearchDialog::DownloadAtachment attResponse - " + attResponse);
		json responseJson;
		string errorResponse = Utility::CheckErrorDescription(attResponse);
		Utility::Logger("FabricsSearchDialog::DownloadAtachment -> errorResponse :: " + errorResponse);
		if (errorResponse.empty() && (errorResponse.length() == 0))
		{
			responseJson = Utility::GetResultsJSON(attResponse);
			GetMaterialAttachments(responseJson, materialCode, materialAttachmentName);

		}
		else
		{
			UTILITY_API->DisplayMessageBox(errorResponse);
		}
		Utility::Logger("FabricsSearchDialog -> DownloadAtachment() -> End");
	}
	/**
	 * \brief Gets all Material attachments from JSON
	 * \param response 
	 * \param materialCode 
	 */
	void MaterialSearchDialog::GetMaterialAttachments(json response, string materialCode, string& materialAttachmentName)
	{
		Utility::Logger("FabricsSearchDialog -> GetMaterialAttachments() -> Start");
		string attColumn, attachmentURL;
		json completeEnityJson;
		string responseJsonStrStyle = response["entities"].dump();
		try {
			completeEnityJson = json::parse(responseJsonStrStyle);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("MaterialSearchDialog::GetMaterialAttachments()::parsing completeEnityJson exception - " + string(e.what()));
			throw e.what();
		}
		string responseJsonSize = to_string(completeEnityJson.size());
		string responseString = "";
		if (completeEnityJson.size() > 2)
		{
			
		}
		else if (completeEnityJson.size() != 0)
		{
			json atachEntityJsonStr, columnsJson;
			string atachEntityJson;
			for (int i = 0; i < completeEnityJson.size(); i++)
			{
				atachEntityJson = completeEnityJson[i].dump();
				try {
					atachEntityJsonStr = json::parse(atachEntityJson);

					attColumn = atachEntityJsonStr["column"].dump();
					columnsJson = json::parse(attColumn);
				}
				catch (exception& e)
				{
					Utility::ErrorLogger("MaterialSearchDialog::GetMaterialAttachments()::parsing atachEntityJsonStr exception - " + string(e.what()));
					throw e.what();
				}
				string attachmentsFileName = columnsJson["OFilename"].dump();
				if (attachmentsFileName != "null") 
				{
					string matAtachmentUrl = columnsJson["CFilename"].dump();
					attachmentsFileName = attachmentsFileName.erase(0, 1);
					attachmentsFileName = attachmentsFileName.erase(attachmentsFileName.size() - 1);
					matAtachmentUrl = matAtachmentUrl.erase(0, 1);
					matAtachmentUrl = matAtachmentUrl.erase(matAtachmentUrl.size() - 1);
					attachmentsFileName= attachmentsFileName.substr(attachmentsFileName.find_last_of("."));
					string atachedFilenameToSave = materialCode + attachmentsFileName;
					Utility::Logger("FabricsSearchDialog -> GetMaterialAttachments() -> matAtachmentUrl:: "+ matAtachmentUrl);
					Utility::DownloadFilesFromURL(matAtachmentUrl, DirectoryUtil::getMaterialAssetsDirectory() + atachedFilenameToSave);
					int zfabFileSize = Utility::GetFileSize(DirectoryUtil::getMaterialAssetsDirectory() + atachedFilenameToSave);
					if (zfabFileSize > 0)
					{
						materialAttachmentName = atachedFilenameToSave;
						matZfabAtt = true;
					}

				}
			}
		}
		Utility::Logger("FabricsSearchDialog -> GetMaterialAttachments() -> End");
	}
	/**
	 * \brief This method gives the rest call response to check dependencies for fabrics.
		 * \return string rest call response
	 */
	string MaterialSearchDialog::GetDependencies()
	{
		Utility::Logger("FabricsSearchDialog -> GetDependencies() -> Start");
		json dataFilterMap, conditionsMap, dependencyMap;
		conditionsMap["fieldname"] = "MaterialId";
		conditionsMap["operator"] = "=";
		conditionsMap["value"] = "";
		dataFilterMap["conditions"][0] = conditionsMap;
		dependencyMap["dataFilter"] = dataFilterMap;
		dependencyMap["roleId"] = Configuration::GetInstance()->GetRoleId();
		dependencyMap["userId"] = Configuration::GetInstance()->GetUserId();
		dependencyMap["schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
		dependencyMap["entity"] = "Material";
		dependencyMap["pageType"] = "details";
		dependencyMap["fromAi"] = true;

		Utility::Logger("FabricsSearchDialog -> GetDependencies() -> dependencyMap:: " + to_string(dependencyMap));
		Utility::Logger("FabricsSearchDialog -> GetDependencies() ->" + PRODUCT_DEPENDENCIES_API);
		string response = RestCall(to_string(dependencyMap), PRODUCT_DEPENDENCIES_API);
		Utility::Logger("FabricsSearchDialog::GetDependencies() response - " + response);
		Utility::Logger("FabricsSearchDialog -> GetDependencies() -> End");

		return response;
	}
	
	/**
	 * \brief This method filters the required things to handle dependencies for brand and division. Based on selected brand, it gives the dependency list
	 	 * \return void
	 */
	void MaterialSearchDialog::FilterDependencyList()
	{
		Utility::Logger("FabricsSearchDialog -> FilterDependencyList() -> Start");
		
		string entityJson;
		QStringList dependencyList;
		QString dependencyItem;
		json dependencyJson = SetDependenciesToWidgets();
		string entities = dependencyJson["entities"].dump();
		json completeEntitiesJson;
		try {
			
			completeEntitiesJson = json::parse(entities);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("MaterialSearchDialog::FilterDependencyList()::parsing completeEntitiesJson exception - " + string(e.what()));
			throw e.what();
		}
		if ((completeEntitiesJson.size() != 0))
		{
			json material, columns;
			for (int i = 0; i < completeEntitiesJson.size(); i++)
			{
				entityJson = completeEntitiesJson[i].dump();
				try {
					
					material = json::parse(entityJson);
				}
				catch (exception& e)
				{
					Utility::ErrorLogger("MaterialSearchDialog::FilterDependencyList()::parsing material exception - " + string(e.what()));
					throw e.what();
				}
				string name = material["name"].dump();
				name = name.erase(0, 1);
				name = name.erase(name.size() - 1);
				string column, OrgLevelId, OrgLevelName, ParentId, ParentName, response, gLValueId;
				if (name == "OrgLevelUserFilter")
				{
					column = material["column"].dump();
					try {
						
						columns = json::parse(column);
					}
					catch (exception& e)
					{
						Utility::ErrorLogger("MaterialSearchDialog::FilterDependencyList()::parsing columns exception - " + string(e.what()));
						throw e.what();
					}
					OrgLevelId = columns["OrgLevelId"].dump();
					OrgLevelName = columns["Name"].dump();
					OrgLevelName = QString::fromUtf8(OrgLevelName.c_str()).toStdString();
					OrgLevelName = OrgLevelName.erase(0, 1);
					OrgLevelName = OrgLevelName.erase(OrgLevelName.size() - 1);
					
					ParentId = columns["ParentId"].dump();
					gLValueId = columns["GLValueId"].dump();
					
					string LookupRef = columns["LookupRefDisplay"].dump();
					LookupRef = LookupRef.erase(0, 1);
					LookupRef = LookupRef.erase(LookupRef.size() - 1);
					
					m_parentIDOrgIDMap.insert(std::make_pair(ParentId,OrgLevelId));
					m_NameOrgIDMap.insert(std::make_pair(OrgLevelName, OrgLevelId));
					
					if (LookupRef != "ul")
					{
						m_LookUpOrgNameGLValIDMap.insert(std::make_pair(LookupRef, std::make_pair(OrgLevelName, gLValueId)));
						m_parentIdLookUpMap.insert(std::make_pair(ParentId, LookupRef));
						m_orgLevelIdLookUpMap.insert(std::make_pair(OrgLevelId, LookupRef));
					}
				}
			}
		}

		for (auto it = m_parentIdLookUpMap.begin(); it != m_parentIdLookUpMap.end(); it++)
		{
			for (auto iter = m_orgLevelIdLookUpMap.begin(); iter != m_orgLevelIdLookUpMap.end(); iter++)
			{
				if (it->first == iter->first)
				{
					if (m_hierarchyMap.empty()) 
					{
						m_hierarchyMap.insert(make_pair(iter->second, it->second));
					}
					else 
					{
						bool recordExists = false;
						for (auto itj = m_hierarchyMap.begin(); itj != m_hierarchyMap.end(); itj++)
						{
							if (itj->first == iter->second && itj->second == it->second) {
								recordExists = true;
							}
						}

						if (!recordExists) {
							m_hierarchyMap.insert(make_pair(iter->second, it->second));
						}
					}
				}
			}
		}
		
		
		Utility::Logger("FabricsSearchDialog -> FilterDependencyList() -> End");
	}
		
	/**
	 * \brief This method sets the default preset values to the UI combobox widgets. 
	  * \return void
	 */
	void MaterialSearchDialog::SetDefaultPresetValues()
	{
		Utility::Logger("FabricsSearchDialog -> SetPresetValues() -> Start");
		for (int i = 0; i < MaterialSearchTree->topLevelItemCount(); ++i)
		{
			QTreeWidgetItem* topItem = MaterialSearchTree->topLevelItem(i);
			QWidget* qWidgetColumn0 = MaterialSearchTree->itemWidget(topItem, 0);
			QWidget* qWidgetColumn1 = MaterialSearchTree->itemWidget(topItem, 1);
			QLabel* qlabel = qobject_cast<QLabel*>(qWidgetColumn0);
			string label = qlabel->text().toStdString();
			
			QComboBox* qComboBox = qobject_cast<QComboBox*>(qWidgetColumn1);
			if (qComboBox)
			{	
				bool labelFound = false;
				QStringList presetArray;
				presetArray.clear();
				presetArray.push_back("Select");
				for (auto it = m_LookUpOrgNameGLValIDMap.begin(); it != m_LookUpOrgNameGLValIDMap.end(); it++)
				{
					
						if (label == it->first)
						{
							auto val = it->second;
							presetArray.push_back(QString::fromStdString(std::get<0>(val)));
							labelFound = true;
						}
					
				}
				if (labelFound)
				{
					qComboBox->clear();
					presetArray.removeDuplicates();
					qComboBox->addItems(presetArray);
				}
				
				
			}
		}
		Utility::Logger("FabricsSearchDialog -> SetPresetValues() -> End");
	}

	
	/**
	* Function is used to handle change event of dropdown widgets
	*/
	void MaterialSearchDialog::handleDropDownValueChangeEvent(const QString& item)
	{
		Utility::Logger("MaterialSearchDialog -> handleDropDownValueChangeEvent() -> Start :: " + item.toStdString());
		QString senderCombo = sender()->property("Id").toString();
		

		QStringList dependencies;
		dependencies.clear();
		for (auto i = m_hierarchyMap.begin(); i != m_hierarchyMap.end(); i++)
		{
			if (senderCombo.toStdString() == i->first)
			{
				dependencies.push_back(QString::fromStdString(i->second));
			}
		}

		if (item != "Select" && item != "")
		{
			string orgID;
			auto foundItem = m_NameOrgIDMap.find(item.toStdString());
			if (foundItem != m_NameOrgIDMap.end())
			{
				orgID = foundItem->second;
			}

			typedef std::multimap<string, string>::iterator mapIterator;
			std::pair<mapIterator, mapIterator> result = m_parentIDOrgIDMap.equal_range(orgID);
			
			QStringList childrenOrgIds;
			for (mapIterator it = result.first; it != result.second; it++)
			{
				childrenOrgIds.push_back(QString::fromStdString(it->second));
			}
			

			QStringList childrenNames;
			for (int count = 0; count < childrenOrgIds.size(); count++)
			{
				for (auto& i : m_NameOrgIDMap) 
				{
					if (i.second == childrenOrgIds.at(count).toStdString())
					{
						
						childrenNames.push_back(QString::fromStdString(i.first));
						
						
					}
				}
				
			}
			
			

			for (int i = 0; i < MaterialSearchTree->topLevelItemCount(); ++i)
			{
				QTreeWidgetItem* topItem = MaterialSearchTree->topLevelItem(i);
				QWidget* qWidgetColumn0 = MaterialSearchTree->itemWidget(topItem, 0);
				QWidget* qWidgetColumn1 = MaterialSearchTree->itemWidget(topItem, 1);
				QLabel* qlabel = qobject_cast<QLabel*>(qWidgetColumn0);
				string label = qlabel->text().toStdString();

				QComboBox* qComboBox = qobject_cast<QComboBox*>(qWidgetColumn1);
				if (qComboBox && dependencies.contains(QString::fromStdString(label)))
				{
					bool labelFound = false;
					QStringList presetArray;
					presetArray.clear();
					presetArray.push_back("Select");
					for (auto it = m_LookUpOrgNameGLValIDMap.begin(); it != m_LookUpOrgNameGLValIDMap.end(); it++)
					{
						
						auto val = it->second;
						QString dropdownVal = QString::fromStdString(std::get<0>(val));
						
						if (label == it->first && (childrenNames.contains(dropdownVal)))
						{
							
							presetArray.push_back(dropdownVal);
							labelFound = true;
						}
						else if (label == it->first && childrenNames.size() == 0)
						{
							if (dependencies.contains(QString::fromStdString(label)))
							{
								presetArray.push_back(dropdownVal);
								labelFound = true;
							}
							
						}

					}
					if (labelFound)
					{
						qComboBox->clear();
						presetArray.removeDuplicates();
						qComboBox->addItems(presetArray);
					}


				}
			}
		}
		else if(item == "Select")
		{
			
			for (int i = 0; i < MaterialSearchTree->topLevelItemCount(); ++i)
			{
				QTreeWidgetItem* topItem = MaterialSearchTree->topLevelItem(i);
				QWidget* qWidgetColumn0 = MaterialSearchTree->itemWidget(topItem, 0);
				QWidget* qWidgetColumn1 = MaterialSearchTree->itemWidget(topItem, 1);
				QLabel* qlabel = qobject_cast<QLabel*>(qWidgetColumn0);
				string label = qlabel->text().toStdString();

				QComboBox* qComboBox = qobject_cast<QComboBox*>(qWidgetColumn1);
				
				if (qComboBox && dependencies.contains(QString::fromStdString(label)))
				{
					bool labelFound = false;
					QStringList presetArray;
					presetArray.clear();
					presetArray.push_back("Select");
					
					for (auto it = m_LookUpOrgNameGLValIDMap.begin(); it != m_LookUpOrgNameGLValIDMap.end(); it++)
					{

						if (label == it->first && dependencies.contains(QString::fromStdString(label)))
						{
							auto val = it->second;
							presetArray.push_back(QString::fromStdString(std::get<0>(val)));
							labelFound = true;
						}

					}
					if (labelFound)
					{
						qComboBox->clear();
						presetArray.removeDuplicates();
						qComboBox->addItems(presetArray);
					}

					


				}
			}
			
		}
				

		Utility::Logger("MaterialSearchDialog -> handleDropDownValueChangeEvent() -> End");
	}
	/**
	 * \brief This method gets all the dependencies for dropdown widgets.
	  * \return json: dependency json
	 */
	json MaterialSearchDialog::SetDependenciesToWidgets()
	{
		Utility::Logger("MaterialSearchDialog -> SetDependenciesToWidgets() -> Start");
		string dependencies = GetDependencies();
		Utility::Logger("MaterialSearchDialog -> SetDependenciesToWidgets() -> dependencies:: " + dependencies);
		string errorResponse = Utility::CheckErrorDescription(dependencies);
		Utility::Logger("MaterialSearchDialog -> SetDependenciesToWidgets() -> errorResponse:: " + errorResponse);

		json dependencyJson;
		if (errorResponse.empty() && (errorResponse.length() == 0))
		{
			try
			{
				dependencyJson = json::parse(dependencies);
			}
			catch (exception& e)
			{
				throw e.what();
			}
			
		}
		else
		{
			UTILITY_API->DisplayMessageBox(errorResponse);
		}
		Utility::Logger("MaterialSearchDialog -> SetDependenciesToWidgets() -> End");

		return dependencyJson;
	}
}