#pragma once

#include "createproduct.h"
#include "ui_createproduct.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QCheckBox>
#include "qlistview.h"
#include "classes/APIDefine.h"
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
#include "CLO_PLUGIN/INFOR/Libraries/jsonQt.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"
#include "CLO_PLUGIN/INFOR/Utilities/Definitions.h"
#include "CLO_PLUGIN/INFOR/DesignSuite/DesignSuite.h"
#include "CLO_PLUGIN/INFOR/Utilities/ComboBoxItem.h"
#include "CLO_PLUGIN/INFOR/Utilities/Configuration.h"
#include "CLO_PLUGIN/INFOR/Utilities/RestAPIUtility.h"
#include "CLO_PLUGIN/INFOR/Utilities/DirectoryUtil.h"
#include <CLO_PLUGIN\INFOR\Products\ProductUtility.h>

using namespace CLOPlugin;
using json = nlohmann::json;

using namespace std;
using QtJson::JsonObject;
using QtJson::JsonArray;

/**
 * \Handling complete logic for creating Product 
 */
namespace CLOPlugin
{
	createProduct* createProduct::_instance = NULL;

	/**
	 * \brief Creating instance for createProduct class
	 * \return _instance 
	 */
	createProduct* createProduct::GetInstance()
	{
		Utility::Logger("createProduct -> GetInstance() -> Start");
		if (_instance == NULL) {
			_instance = new createProduct();
		}
		Utility::Logger("createProduct -> GetInstance() -> End");
		return _instance;
	}
	/**
	 * \brief Deletes created instance  
	 */
	void createProduct::Destroy()
	{
		Utility::Logger("createProduct -> Destroy() -> Start");
		if (_instance) {
			delete _instance;
			_instance = NULL;
		}
		Utility::Logger("createProduct -> Destroy() -> End");
	}
	
	/**
	 * \brief - Method will Initialize Create Product Dialog
	 * \param QWidget* parent 
	 */
	createProduct::createProduct(QWidget* parent) : QDialog(parent)
	{
		Utility::Logger("createProduct -> Constructor() -> Start");
		setupUi(this);
		QFont fontStyle("Times new roman", FONT_SIZE, QFont::Bold);
		this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
		QSize size(TABLE_WIDTH, TABLE_HEIGHT);
		createProductSearchTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		createProductSearchTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		createProductSearchTable->setStyleSheet("QTreeWidget::item { border-bottom: 1px solid #232323;""padding : 10px;""height: 25px;""}");
		createProductSearchTable->setFixedSize(size);
		createProductSearchTable->setColumnWidth(1, USER_INPUT_WIDTH);
		createProductSearchTable->setColumnWidth(0, SEARCH_LABEL_WIDTH);
		headerLabel->setFont(fontStyle);
		layout()->setSizeConstraint(QLayout::SetFixedSize);
		this->adjustSize();

		back->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_back_over.svg"));
		back->setIconSize(QSize(iconHieght, iconWidth));
		back->setStyleSheet(buttonFont);

		sendToPlm->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_goto_over.svg")); 
		sendToPlm->setIconSize(QSize(iconHieght, iconWidth));
		sendToPlm->setStyleSheet(buttonFont);

		saveAndClose->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_save_over.svg"));
		saveAndClose->setIconSize(QSize(iconHieght, iconWidth));
		saveAndClose->setStyleSheet(buttonFont);

		QObject::connect(saveAndClose, SIGNAL(clicked()), this, SLOT(Save_clicked()));
		QObject::connect(sendToPlm, SIGNAL(clicked()), this, SLOT(sendToPLM_clicked()));
		QObject::connect(closeWindow, SIGNAL(clicked()), this, SLOT(Cancel_clicked()));
		QObject::connect(back, SIGNAL(clicked()), this, SLOT(on_Back_clicked()));
		m_isUserInputEmpty = true;
		m_isSaveClicked = false;
		m_IdGenSettingsAvailable = false;
		m_waikiki = false;
		m_statusPresetValues.clear();
		FilterDependencyList();
		GetIdGeneratorSettings();
		ReadPLMJson();
		ReadJsonAndDrawDialog();
		QTreeWidgetItem *dataItem = new QTreeWidgetItem;
		Qt::ItemFlags flags;
		flags = dataItem->flags();
		flags |= Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
		dataItem->setFlags(flags);
		createProductSearchTable->setFocusPolicy(Qt::FocusPolicy::StrongFocus);	
		createProductSearchTable->setSelectionBehavior(QAbstractItemView::SelectItems);
		createProductSearchTable->setSelectionMode(QAbstractItemView::NoSelection);
		createProductSearchTable->setSelectionBehavior(QAbstractItemView::SelectRows);
		createProductSearchTable->setEditTriggers(QAbstractItemView::CurrentChanged);
		createProductSearchTable->setTabKeyNavigation(true);
		Utility::Logger("createProduct -> Constructor() -> end");
	}
	/**
	 * \brief Method returns true after Save button click on CreteProduct UI
	 * \param
	 * \return boolean
	 */
	bool createProduct::IsSaveClicked()
	{
		Utility::Logger("createProduct -> IsSaveClicked() -> Start");
		if (m_isSaveClicked)
			return true;
		else
			Utility::Logger("createProduct -> IsSaveClicked() -> End");
			return false;
	}
	/**
	 * \brief Read JSON to populate Search field for Product and Draw Dialog 
	 */
	void createProduct::ReadJsonAndDrawDialog()
	{
		Utility::Logger("createProduct -> ReadJsonAndDrawDialog() -> Start");
		json jsonString;
		Utility::Fields tempField;
		ifstream productSearchFile;
		productSearchFile.open(DirectoryUtil::getProdSearchFilteredJson());
		productSearchFile >> jsonString;
		productSearchFile.close();
		string completeJsonString, uiTypeJSONObject, presetListJSONObject, fieldValues, mandatoryFields;
		json completeJson, componentsJson, presetListJSON, fieldValuesJson, mandatoryFieldsJson;
		completeJsonString = jsonString.dump();
		try {
			completeJson = json::parse(completeJsonString);
			uiTypeJSONObject = completeJson["uiTypeList"].dump();
			componentsJson = json::parse(uiTypeJSONObject);
			presetListJSONObject = completeJson["presetList"].dump();
			presetListJSON = json::parse(presetListJSONObject);
			fieldValues = completeJson["fieldList"].dump();
			fieldValuesJson = json::parse(fieldValues);

			mandatoryFields = completeJson["mandatory_fieldList"].dump();
			mandatoryFieldsJson = json::parse(mandatoryFields);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("createProduct -> ReadJsonAndDrawDialog()::parsing completeJson exception - " + string(e.what()));
			throw e.what();
		}
		QStringList mandatoryFieldsList;

		for (int i = 0; i < mandatoryFieldsJson.size(); i++)
		{
			string mandatory = mandatoryFieldsJson[i].dump();
			mandatory = mandatory.erase(0, 1);
			mandatory = mandatory.erase(mandatory.size() - 1);
			mandatoryFieldsList << QString::fromStdString(mandatory);
		}

		for (int i = 0; i < fieldValuesJson.size(); i++)
		{
			string fieldValuesString = fieldValuesJson[i].dump();
			fieldValuesString = fieldValuesString.erase(0, 1);
			fieldValuesString = fieldValuesString.erase(fieldValuesString.size() - 1);
			tempField.labelValue = QString::fromStdString(fieldValuesString);
			string uiTypes = componentsJson[fieldValuesString].dump();
			uiTypes = uiTypes.erase(0, 1);
			uiTypes = uiTypes.erase(uiTypes.size() - 1);
			tempField.fieldUItype = QString::fromStdString(uiTypes);
			if (tempField.fieldUItype == "dropdown")
			{
				QStringList listQt;
				json options = presetListJSON[fieldValuesString].get<json>();
				for (int j = 0; j < options.size(); j++)
				{
					listQt.append(QString::fromUtf8(options[j].get<string>().c_str()));
				}
				tempField.presetValues = listQt;
			}
			tempField.isMandatory = mandatoryFieldsList.contains(QString::fromStdString(fieldValuesString));
			m_createFieldsVector.push_back(tempField);
		}
		DrawWidget(m_createFieldsVector);
		
		Utility::Logger("createProduct -> ReadJsonAndDrawDialog() -> end");
	}
	
	/**
	 * \brief Method creates widgets for the fields read from JSON
	 * \param vector
	 */
	void createProduct::DrawWidget(std::vector<Utility::Fields>& fieldsVector)
	{
		Utility::Logger("createProduct -> DrawWidget() -> Start");
		
		for each (auto field in fieldsVector)
		{
			string tempLabel = field.labelValue.toStdString();

			if (createColumnsMap.find(tempLabel) != createColumnsMap.end()) {
				tempLabel = createColumnsMap.at(tempLabel);
			}

			if (field.fieldUItype == "text")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();  // Creating new TreeWidgetItem
				QLineEdit* lineEdit = new QLineEdit();						// Creating new LineEdit Widget
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);
				label->setProperty("Id", field.labelValue);
				
				label->setText(QString::fromStdString(tempLabel));
				lineEdit->setStyleSheet(inputStyle);
				createProductSearchTable->addTopLevelItem(topLevel);						
				createProductSearchTable->setItemWidget(topLevel, 0, label);				
				createProductSearchTable->setItemWidget(topLevel, 1, lineEdit);
				lineEdit->setText(field.userInputValues);
				if (field.labelValue == "StyleCode")
				{
					if(m_IdGenSettingsAvailable == true)
					{
						lineEdit->setDisabled(true);
						lineEdit->setStyleSheet("color: #696969;" + inputStyle);
						label->setText(QString::fromStdString(tempLabel));
						label->setStyleSheet("color: #696969;" + inputStyle);
					}
					else
					{
						lineEdit->setDisabled(false);
						lineEdit->setStyleSheet(inputStyle);
						label->setStyleSheet(inputFont);
						label->setText(QString::fromStdString(tempLabel) + "<font color='red'>*</font>");
				
					}
					
				}
				
			}

			if (field.fieldUItype == "dropdown")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem;
				ComboBoxItem* comboBoxItem = new ComboBoxItem(topLevel, 1);
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);
				label->setProperty("Id", field.labelValue);
				
				label->setText(QString::fromStdString(tempLabel));
				comboBoxItem->setStyleSheet(inputStyle);
				createProductSearchTable->addTopLevelItem(topLevel);
				createProductSearchTable->setItemWidget(topLevel, 0, label);
				createProductSearchTable->setItemWidget(topLevel, 1, comboBoxItem);
				
				comboBoxItem->setStyleSheet("combobox-popup: 0; font: 75 8pt \"Tahoma\"; ");
				comboBoxItem->setProperty("Id", field.labelValue);

				QObject::connect(comboBoxItem, SIGNAL(activated(const QString&)), this,
					SLOT(handleDropDownValueChangeEvent(const QString&)));
				
			}

			if (field.fieldUItype == "textarea")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();
				QTextEdit* TextEdit = new QTextEdit();
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);
				label->setProperty("Id", field.labelValue);
				
				label->setText(QString::fromStdString(tempLabel));
				createProductSearchTable->addTopLevelItem(topLevel);
				createProductSearchTable->setItemWidget(topLevel, 0, label);
				createProductSearchTable->setItemWidget(topLevel, 1, TextEdit);
				TextEdit->setText(field.userInputValues);
				TextEdit->setStyleSheet("border: 1px solid black;"
					"background-color: #222222;"
					"font: 75 8pt \"Tahoma\";"
				);
				TextEdit->setMaximumSize(TEXTEDIT_SIZE_WIDTH, TEXTEDIT_SIZE_HEIGHT);
				
			}
			if (field.fieldUItype == "DateEdit")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();
				QDateEdit* DateTimeEdit = new QDateEdit();
				bool enable = true;
				DateTimeEdit->setCalendarPopup(enable);
				QString dataRecovery("");
				QDate date = QDate::fromString(dataRecovery, "");
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);
				label->setProperty("Id", field.labelValue);
				
				label->setText(QString::fromStdString(tempLabel));
				createProductSearchTable->addTopLevelItem(topLevel);
				createProductSearchTable->setItemWidget(topLevel, 0, label);
				createProductSearchTable->setItemWidget(topLevel, 1, DateTimeEdit);
				
			}
		}
		
		Utility::Logger("createProduct -> DrawWidget() -> end");
	}

	/**
	* Method is used to call rest api and filter records for field dependencies
	*/
	void createProduct::FilterDependencyList()
	{
		Utility::Logger("createProduct -> FilterDependencyList() -> Start");
		string entityJson;
		QStringList dependencyList;
		QString dependencyItem;
		map<string, string> attributeCodeNameMap;
		json dependencyJson = SetDependenciesToWidgets();
		string componentsString = dependencyJson["layout"]["components"].dump();
		json componentsJson = json::parse(componentsString);

		for (int i = 0; i < componentsJson.size(); i++)
		{
			string compObjString = componentsJson[i].dump();
			json compObjJson = json::parse(compObjString);
			string lookupRef = compObjJson["lookupRef"].dump();
			lookupRef = lookupRef.erase(0, 1);
			lookupRef = lookupRef.erase(lookupRef.size() - 1);

			string dataField = compObjJson["dataField"].dump();
			dataField = dataField.erase(0, 1);
			dataField = dataField.erase(dataField.size() - 1);

			if (lookupRef != "ul") {
				m_lookupIdMap.insert(make_pair(lookupRef, dataField));
			}

			json lookupsJSON;
			string lookUpString = dependencyJson["lookups"].dump();
			try {
				lookupsJSON = json::parse(lookUpString);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("createProduct -> FilterDependencyList()::parsing lookupsJSON exception - " + string(e.what()));
				throw e.what();
			}

			Utility::GetDropDownMapWithCode(lookupsJSON, lookupRef, attributeCodeNameMap, dataField);
		}

		string entities = dependencyJson["entities"].dump();
		json completeEntitiesJson;
		try {
			completeEntitiesJson = json::parse(entities);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("createProduct -> FilterDependencyList()::parsing completeEntitiesJson exception - " + string(e.what()));
			throw e.what();
		}
		if ((completeEntitiesJson.size() != 0))
		{
			json productCol, columns;
			for (int i = 0; i < completeEntitiesJson.size(); i++)
			{
				entityJson = completeEntitiesJson[i].dump();
				try {
					productCol = json::parse(entityJson);
				}
				catch (exception& e)
				{
					Utility::ErrorLogger("createProduct -> FilterDependencyList()::parsing productCol exception - " + string(e.what()));
					throw e.what();
				}
				string name = productCol["name"].dump();
				name = name.erase(0, 1);
				name = name.erase(name.size() - 1);
				string column, OrgLevelId, OrgLevelName, ParentId, response;
				if (name == "OrgLevelUserFilter")
				{
					column = productCol["column"].dump();
					try {
						columns = json::parse(column);
					}
					catch (exception& e)
					{
						Utility::ErrorLogger("createProduct -> FilterDependencyList()::parsing columns exception - " + string(e.what()));
						throw e.what();
					}
					OrgLevelId = columns["OrgLevelId"].dump();
					ParentId = columns["ParentId"].dump();

					string LookupRef = columns["LookupRef"].dump();
					LookupRef = LookupRef.erase(0, 1);
					LookupRef = LookupRef.erase(LookupRef.size() - 1);

					string code = columns["Code"].dump();
					if (code != "null") {
						code = columns["Code"].get<string>();
					}
					string CodeAttId = m_lookupIdMap.at(LookupRef) + "_" + code;

					if (attributeCodeNameMap.find(CodeAttId) != attributeCodeNameMap.end()) {
						OrgLevelName = attributeCodeNameMap.at(CodeAttId);
					}
					else {
						OrgLevelName = columns["Name"].dump();
						OrgLevelName = OrgLevelName.erase(0, 1);
						OrgLevelName = OrgLevelName.erase(OrgLevelName.size() - 1);
					}

					string fieldLevel = columns["Level"].dump();
					try
					{
						if (stoi(ParentId) > 0) {
							m_orgLevelIdMap.insert(std::make_pair(OrgLevelId, OrgLevelName + "_" + ParentId));
						}
						else {
							m_orgLevelIdMap.insert(std::make_pair(OrgLevelId, OrgLevelName));
						}
						m_parentIdNameMap.insert(std::make_pair(ParentId + "_" + LookupRef, OrgLevelName));
						m_levelLookupMap.insert(std::make_pair(OrgLevelId, fieldLevel));

						if (LookupRef != "ul") {
							if (ParentId == "0") {
								m_rootItem = m_lookupIdMap.at(LookupRef);
								m_rootItemOtions.push_back(OrgLevelName);
								m_orgLevelIdLookUpMap.insert(std::make_pair(stoi(OrgLevelId), LookupRef + "_" + OrgLevelName));
								m_parentIdLookUpMap.insert(std::make_pair(ParentId, LookupRef + "_" + OrgLevelName));
							}
							else {
								m_orgLevelIdLookUpMap.insert(std::make_pair(stoi(OrgLevelId), LookupRef + "_" + OrgLevelName + "|@|" + OrgLevelId));
								m_parentIdLookUpMap.insert(std::make_pair(ParentId, LookupRef + "_" + OrgLevelName + "|@|" + OrgLevelId));
							}
						}
					}
					catch (const std::exception& exception)
					{
						Utility::Logger("createProduct -> FilterDependencyList():: Exception occured while getting Id from lookupmap." + string(exception.what()));
					}
				}
			}
		}

		for (auto it = m_orgLevelIdLookUpMap.begin(); it != m_orgLevelIdLookUpMap.end(); it++)
		{
			map<int, string, less <int>> tempMap;
			string parentItem = m_orgLevelIdLookUpMap.at(it->first);
			string subStringParent = parentItem.substr(0, parentItem.find_first_of("_"));
			string parentItemId = m_lookupIdMap.at(subStringParent);
			parentItem.replace(0, subStringParent.length(), parentItemId);

			std::multimap<string, std::string>::const_iterator keys = m_parentIdLookUpMap.find(to_string(it->first));
			int number = m_parentIdLookUpMap.count(to_string(it->first));
			for (int i = 0; i < number; i++)
			{
				try
				{
					string childItem = keys->second;
					if (!childItem.empty()) {
						string subStringChild = childItem.substr(0, childItem.find_first_of("_"));
						string childItemId = m_lookupIdMap.at(subStringChild);
						childItem.replace(0, subStringChild.length(), childItemId);
						if (m_hierarchyMap.empty()) {
							m_hierarchyMap.insert(make_pair(parentItem, childItem));
						}
						else {
							bool recordExists = false;
							for (auto itj = m_hierarchyMap.begin(); itj != m_hierarchyMap.end(); itj++)
							{
								if (itj->first == parentItem && itj->second == childItem) {
									recordExists = true;
								}
							}

							if (!recordExists) {
								m_hierarchyMap.insert(make_pair(parentItem, childItem));
							}
						}
					}
				}
				catch (const std::exception&)
				{
					Utility::Logger("Exception occured while getting parent child items.");
				}
				++keys;
			}
		}

		Utility::Logger("createProduct -> FilterDependencyList() -> End");
	}


	/**
	* Function is used to handle change event of dropdown widgets
	*/
	void createProduct::handleDropDownValueChangeEvent(const QString& item)
	{
		Utility::Logger("createProduct -> handleDropDownValueChangeEvent() -> Start");
		QString senderCombo = sender()->property("Id").toString();
		bool resetRootItem = false;
		if (m_rootItem == senderCombo.toStdString()) {
			resetRootItem = true;
		}

		if (item.isEmpty()) {
		}
		else if (item == "Select")
		{
			for (int i = 0; i < createProductSearchTable->topLevelItemCount(); ++i)
			{
				QTreeWidgetItem* topItem = createProductSearchTable->topLevelItem(i);
				QWidget* qWidget = createProductSearchTable->itemWidget(topItem, 1);
				QComboBox* qComboBox = qobject_cast<QComboBox*>(qWidget);

				if ((qComboBox))
				{
					QString id = qComboBox->property("Id").toString();
					if (resetRootItem) {
						for (auto it = m_hierarchyMap.begin(); it != m_hierarchyMap.end(); it++)
						{
							if ((it->first.find(m_rootItem) == 0 || it->second.find(m_rootItem) == 0)) {
								continue;
							}

							if (it->first.find(id.toStdString()) == 0 || it->second.find(id.toStdString()) == 0) {
								qComboBox->clear();
								qComboBox->addItem("Select");
								qComboBox->setCurrentIndex(qComboBox->findText("Select"));
							}
						}
					}
					else if (senderCombo == id && std::find(m_nonDependentFields.begin(), m_nonDependentFields.end(), id.toStdString()) == m_nonDependentFields.end()) {
						for (int j = 0; j < qComboBox->count(); j++) {

							QString comboValue = qComboBox->itemText(j);
							if (comboValue != "Select") {
								string filterString;
								string itemData = qComboBox->itemData(j).toString().toStdString();
								if (itemData.empty()) {
									filterString = id.toStdString() + "_" + comboValue.toUtf8().constData();
								}
								else {
									filterString = id.toStdString() + "_" + comboValue.toUtf8().constData() + "|@|" + itemData;
								}
								GetResetFields(createProductSearchTable, m_hierarchyMap, filterString, m_clearItems, m_createFieldsVector, true);
							}
						}
					}
				}
			}
			m_clearItems.clear();
			resetRootItem = false;
		}
		else if (item != "Select")
		{
			map<string, map<string, QString>> dropDownValues;
			for (int i = 0; i < createProductSearchTable->topLevelItemCount(); ++i)
			{
				QTreeWidgetItem* topItem = createProductSearchTable->topLevelItem(i);
				QWidget* qWidget = createProductSearchTable->itemWidget(topItem, 1);
				QComboBox* qComboBox = qobject_cast<QComboBox*>(qWidget);

				if ((qComboBox))
				{
					string filterString;
					QString id = qComboBox->property("Id").toString();
					string itemData = qComboBox->itemData(qComboBox->currentIndex()).toString().toStdString();
					if (itemData.empty()) {
						filterString = id.toStdString() + "_" + item.toUtf8().constData();
					}
					else {
						filterString = id.toStdString() + "_" + item.toUtf8().constData() + "|@|" + itemData;
					}

					if (resetRootItem && m_rootItem != id.toStdString()) {
						for (auto it = m_hierarchyMap.begin(); it != m_hierarchyMap.end(); it++)
						{
							if (it->first.find(id.toStdString()) == 0 || it->second.find(id.toStdString()) == 0) {
								qComboBox->clear();
								for each (auto field in m_createFieldsVector) {
									if (id == field.labelValue) {
										qComboBox->addItems(field.presetValues);
										break;
									}
								}
								qComboBox->setCurrentIndex(qComboBox->findText("Select"));
							}
						}
					}

					if (senderCombo == id)
					{
						list<string> subList = GetHierarchyOrder(m_hierarchyMap, filterString);
						m_clearItems.insert(m_clearItems.end(), subList.begin(), subList.end());
						dropDownValues = SetDropDownValues(item.toStdString(), itemData);
						if (dropDownValues.empty()) {
							m_nonDependentFields.insert(id.toStdString());
							if (!itemData.empty()) {
								GetResetFields(createProductSearchTable, m_hierarchyMap, filterString, m_clearItems, m_createFieldsVector, false);
							}

						}
						else {
							if (std::find(m_nonDependentFields.begin(), m_nonDependentFields.end(), id.toStdString()) != m_nonDependentFields.end()) {
								m_nonDependentFields.erase(id.toStdString());
							}
						}
					}
				}
			}
			resetRootItem = false;

			if (!dropDownValues.empty())
			{
				QString selectedOptionForBrand;
				for (int i = 0; i < createProductSearchTable->topLevelItemCount(); ++i)
				{
					QTreeWidgetItem* topItem = createProductSearchTable->topLevelItem(i);
					QWidget* qWidget = createProductSearchTable->itemWidget(topItem, 1);
					QComboBox* qComboBox = qobject_cast<QComboBox*>(qWidget);
					if ((qComboBox))
					{
						QString id = qComboBox->property("Id").toString();
						for (auto it = dropDownValues.begin(); it != dropDownValues.end(); it++)
						{
							if (std::find(m_clearItems.begin(), m_clearItems.end(), it->first) != m_clearItems.end()) {
								m_clearItems.remove(it->first);
							}

							for (auto it = m_clearItems.begin(); it != m_clearItems.end(); it++) {
								if (id.toStdString() == *it) {
									qComboBox->clear();
									qComboBox->addItem("Select");
									break;
								}
							}

							if (id.toStdString() == it->first) {
								qComboBox->clear();
								qComboBox->addItem("Select");

								for (auto its = it->second.begin(); its != it->second.end(); its++)
								{
									QByteArray bArr;
									bArr.append(its->second);
									qComboBox->addItem(QString::fromUtf8(bArr), QString::fromStdString(its->first));
								}
								break;
							}
							
							if (id == "BrandId") {
								selectedOptionForBrand = qComboBox->currentText();
							}
							if ((m_waikiki) && (id == "Status"))
							{
								qComboBox->clear();
								if (selectedOptionForBrand == "Block Fit")
								{
									qComboBox->addItem("Select");
									qComboBox->setCurrentIndex(qComboBox->findText("Select"));
								}
								else
								{
									qComboBox->addItems(m_statusPresetValues);
									qComboBox->setCurrentIndex(qComboBox->findText("1- In Design Process"));
								}
							}
						}
					}
				}
			}
			
			m_clearItems.clear();
		}

		Utility::Logger("createProduct -> handleDropDownValueChangeEvent() -> End");
	}

	/**
	* \brief Setting Independent Values to widgets
	* \param  dependencyJson
	*/
	map<string, map<string, QString>> createProduct::SetDropDownValues(string& selectedItem, string& id)
	{
		Utility::Logger("ProductSearch -> SetPresetValues() -> Start");
		QString dependencyItem;
		map<string, map<string, QString>> dataMap;
		for (std::multimap<std::string, std::string>::iterator Values = m_orgLevelIdMap.begin(); Values != m_orgLevelIdMap.end(); ++Values)
		{
			if (((*Values).second == selectedItem && id.empty()) || ((*Values).first == id && !id.empty()))
			{
				string key = (*Values).first;
				try
				{
					std::multimap<string, std::string>::const_iterator keys = m_parentIdLookUpMap.find(key);
					int number = m_parentIdLookUpMap.count(key);
					for (int i = 0; i < number; i++)
					{
						map<string, QString> dependencyMap;
						string subString = keys->second.substr(0, keys->second.find_first_of("_"));
						std::multimap<std::string, std::string>::const_iterator Values = m_parentIdNameMap.find(key + "_" + subString);
						int Number = m_parentIdNameMap.count(key + "_" + subString);
						for (int i = 0; i < Number; i++)
						{
							QString dependencyItem = QString::fromStdString(Values->second);
							for (auto itt = m_orgLevelIdMap.begin(); itt != m_orgLevelIdMap.end(); itt++)
							{
								if (itt->second == dependencyItem.toStdString() + "_" + key) {
									dependencyMap.insert(make_pair(itt->first, dependencyItem));
									++Values;
									break;
								}
							}

						}
						dataMap.insert(make_pair(m_lookupIdMap.at(subString), dependencyMap));

						keys++;
					}
				}
				catch (const std::exception& exp)
				{
					Utility::Logger("Exception occured while getting lookup name.");
					return dataMap;
				}
			}
		}

		Utility::Logger("ProductSearch -> SetPresetValues() -> End");

		return dataMap;
	}

	/**
	 * \brief Destructor
	 */
	createProduct::~createProduct()
	{
		
	}
	/**
	 * \brief Method clears all the values of the fields
	 */
	void createProduct::ClearAllFields()
	{
		Utility::Logger("createProduct -> ClearAllFields() -> Start");
		for (int i = 0; i < createProductSearchTable->topLevelItemCount(); ++i)
		{
			QTreeWidgetItem* topItem = createProductSearchTable->topLevelItem(i);
			QWidget* qWidgetColumn0 = createProductSearchTable->itemWidget(topItem, 0);
			QWidget* qWidgetColumn1 = createProductSearchTable->itemWidget(topItem, 1);
			QLabel* qlabel = qobject_cast<QLabel*>(qWidgetColumn0);
			QString id = qlabel->property("Id").toString();
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
					qComboBox->clear();
					for each (auto field in m_createFieldsVector) {
						if (id == field.labelValue) {
							bool recordExists = false;
							for (auto itj = m_hierarchyMap.begin(); itj != m_hierarchyMap.end(); itj++)
							{
								if (QString::fromStdString(itj->first).startsWith(field.labelValue) || QString::fromStdString(itj->second).startsWith(field.labelValue)) {
									recordExists = true;
								}
							}
							if (recordExists && m_rootItem != field.labelValue.toStdString()) {
								qComboBox->addItem("Select");
							}
							else {
								qComboBox->addItems(field.presetValues);
							}
							break;
						}
					}
					qComboBox->setCurrentIndex(qComboBox->findText("Select"));

					if (id == "Status")
					{
						int indexOfConcept = qComboBox->findText("In Concept");
						if (indexOfConcept >= 0) {
							qComboBox->setCurrentIndex(indexOfConcept);
						}
						else {
							m_waikiki = true;
							for (int index = 0; index < qComboBox->count(); index++)
							m_statusPresetValues << qComboBox->itemText(index);
							indexOfConcept = qComboBox->findText("1- In Design Process");
							qComboBox->setCurrentIndex(indexOfConcept);
						}
					}
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
		
		Utility::Logger("createProduct -> ClearAllFields() -> End");
	}
		
	/**
	 * \brief Method reads JSON which generated after making RestCall to PLM
	 */
	void  createProduct::ReadPLMJson() 
	{
		Utility::Logger("createProduct -> ReadPLMJson() -> Start");
		string parameter = "{\"roleId\":" + Configuration::GetInstance()->GetRoleId() + ",\"userId\":" + Configuration::GetInstance()->GetUserId() + ",\"entity\":\"Style\",\"pageType\":\"details\",\"dataFilter\":{\"conditions\":[{\"fieldname\":\"StyleId\",\"operator\":\"=\",\"value\":\"\"}]},\"pageInfo\":{},\"Schema\":" + Configuration::GetInstance()->GetschemaWithQuotes() + "}";
		string entity = "Style";
		Utility::GetFilteredJson(parameter, PRODUCT_DETAILS_API, entity);
		json completeStyleJson;
		m_attsDropdownListMap.clear();
		m_attributeMap.clear();
		createColumnsMap.clear();
		ifstream styleDetailsFile;
		styleDetailsFile.open(DirectoryUtil::getProdSearchJson());
		styleDetailsFile >> completeStyleJson;
		styleDetailsFile.close();
		ofstream styleSearchFile;
		styleSearchFile.open(DirectoryUtil::getProdSearchFilteredJson());
		json finalJsontoSave;
		auto jsonFieldList = json::array();
		auto jsonUiTypeList = json::object();
		auto jsonDataFieldList = json::object();
		auto presetArray = json::array();
		auto presetList = json::object();
		auto jsonMandatoryFieldsList = json::array();
		int uiPresetCount = 0;
		list<string> skipElements;
		skipElements.push_back("DivisionId");
		skipElements.push_back("SubCategoryId");

		map<string, string> linkingMap;
		linkingMap.insert(make_pair("BrandId", "DivisionId"));
		linkingMap.insert(make_pair("CategoryId", "SubCategoryId"));
		string completeStyleJsonString, componentsString, compObjString, propsString;
		completeStyleJsonString = completeStyleJson.dump();
		json completeJson, componentsJson, compObjJson, propsJson;
		try {
			completeJson = json::parse(completeStyleJsonString);
			componentsString = completeJson["layout"]["components"].dump();
			componentsJson = json::parse(componentsString);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("createProduct -> ReadPLMJson()::parsing completeJson exception - " + string(e.what()));
			throw e.what();
		}
		json keyValuePairs = Utility::GetKeyValuePairs();
		for (int i = 0; i < componentsJson.size(); i++) {
			compObjString = componentsJson[i].dump();
			try {
				compObjJson = json::parse(compObjString);
				propsString = compObjJson["props"].dump();
				propsJson = json::parse(propsString);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("createProduct -> ReadPLMJson()::parsing compObjJson exception - " + string(e.what()));
				throw e.what();
			}
			string visible = propsJson["isVisibleAi"].dump();
			Utility::Logger("passed data::/n" + visible);
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

				string entity = compObjJson["entity"].dump();
				entity = entity.erase(0, 1);
				entity = entity.erase(entity.size() - 1);

				string label = compObjJson["label"].dump();
				label = label.erase(0, 1);
				label = label.erase(label.size() - 1);

				float tabIndexNum = std::stof(tabIndex);
				if (std::find(skipElements.begin(), skipElements.end(), dataField) == skipElements.end()) {
					m_indexColumnIdMap.insert(make_pair(tabIndexNum, dataField));
					if (linkingMap.find(dataField) != linkingMap.end()) {
						tabIndexNum = tabIndexNum + 0.25;
						m_indexColumnIdMap.insert(make_pair(tabIndexNum, linkingMap.at(dataField)));
					}
				}
				
				jsonUiTypeList[dataField] = fieldType;
				jsonDataFieldList[dataField] = dataField;
				jsonFieldList.push_back(dataField);
				if (isRequired == "true")
				{
					jsonMandatoryFieldsList.push_back(dataField);
				}
				if (lookupRef == "ul")
				{
					m_attributeMap.insert(std::make_pair(dataField, dataField));
				}
				else
				{
					m_attributeMap.insert(std::make_pair(lookupRef, dataField));
				}

				if (label != "ul") {
					createColumnsMap.insert(std::make_pair(dataField, QString::fromUtf8(label.c_str()).toStdString()));
				}
				else {
					createColumnsMap.insert(std::make_pair(dataField, Utility::GetDisplayValueByKey(QString::fromStdString(dataField), QString::fromStdString(entity), keyValuePairs).toStdString()));

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
						Utility::ErrorLogger("createProduct -> ReadPLMJson()::parsing lookupsJSON exception - " + string(e.what()));
						throw e.what();
					}
					map<string, string> tempAttribMap;
					Utility::GetDropDownMap(lookupsJSON, lookupRef, tempAttribMap);
					SetIdGeneratorMap(lookupsJSON, lookupRef);
					presetArray.clear();
					if (dataField != "Status") {
						presetArray.push_back("Select");
					}
					for (auto it = tempAttribMap.begin(); it != tempAttribMap.end(); it++)
					{
						if (m_rootItem == dataField) {
							if (std::find(m_rootItemOtions.begin(), m_rootItemOtions.end(), it->first) != m_rootItemOtions.end()) {
								presetArray.push_back(it->first);
							}
						}
						else {
							presetArray.push_back(it->first);
						}
					}
					presetList[dataField] = presetArray;
					m_attsDropdownListMap.insert(std::make_pair(dataField, tempAttribMap));
				}
			}
		}
		auto newjsonFieldList = json::array();
		for (auto itr = m_indexColumnIdMap.begin(); itr != m_indexColumnIdMap.end(); itr++) {
			newjsonFieldList.push_back(itr->second);
		}

		finalJsontoSave["fieldList"] = newjsonFieldList;//jsonFieldList;
		finalJsontoSave["uiTypeList"] = jsonUiTypeList;
		finalJsontoSave["presetList"] = presetList;
		finalJsontoSave["mandatory_fieldList"] = jsonMandatoryFieldsList;
		finalJsontoSave["dataFieldList"] = jsonDataFieldList;
		styleSearchFile << finalJsontoSave;
		styleSearchFile.close();
		Utility::Logger("createProduct -> readPLMJson() -> End");
	}

	/**
	 * \brief Method Creates map of Key and Fields Values to Send to PLM
	 */
	void createProduct::CreateProductCreateMap()
	{
		Utility::Logger("createProduct -> CreateProductCreateMap() -> Start");
		this->hide();
		string parameter, bearerKey;
		json updateMap;
		json emptyArray;
		json mapArray;
		string dirPath;
		int count = 0;
		m_createProductMap.clear();
		for (auto arrayElement : m_createFieldsVector)
		{
			string attLabel = arrayElement.labelValue.toStdString();  
			string userSelected = arrayElement.userInputValues.toStdString();
			if (userSelected != "Select")
			{
				if (arrayElement.fieldUItype == "dropdown")
				{
					mapArray["fieldName"] = attLabel; 
					map<string, string> attNameIdMap;
					attNameIdMap.clear();
					attNameIdMap.insert(m_attsDropdownListMap[attLabel].begin(), m_attsDropdownListMap[attLabel].end());
					for (auto it = attNameIdMap.begin(); it != attNameIdMap.end(); it++)
					{
						if (it->first == userSelected)
						{
							mapArray["operator"] = "=";
							mapArray["value"] = stoi(it->second);
							break;
						}
					}
					m_createProductMap["fieldValues"][count++] = mapArray;
					Utility::Logger("adding fieldvalues::" + to_string(mapArray));
				}
				else
				{
					if (attLabel == "StyleCode")
					{
						mapArray.clear();
						mapArray["fieldName"] = attLabel;
						mapArray["operator"] = "=";
						if (m_IdGenSettingsAvailable)
						{
							mapArray["value"] = nullptr; // for StyleCode auto generation we need to send null here
						}
						else
						{
							mapArray["value"] = userSelected;
						}
						m_createProductMap["fieldValues"][count++] = mapArray;
					}
					else
					{
						mapArray.clear();
						mapArray["fieldName"] = attLabel;
						mapArray["operator"] = "=";
						mapArray["value"] = userSelected;
						m_createProductMap["fieldValues"][count++] = mapArray;
					}
				}
			}
		}
		
		if (m_IdGenSettingsAvailable)
		{
			m_createProductMap["idGenContextVal"] = m_idGenContextVal;
			m_createProductMap["idGenContextVal2"] = m_idGenContextVal2;
			m_createProductMap["idGenVal"] = m_idGenVal;
		}
		else
		{
			m_createProductMap["idGenContextVal"] = nullptr;
			m_createProductMap["idGenContextVal2"] = nullptr;
			m_createProductMap["idGenVal"] = emptyArray.array();;
			
		}
		m_createProductMap["subEntities"] = emptyArray.array();
		m_createProductMap["modifyId"] = Configuration::GetInstance()->GetUserId();
		
		m_createProductMap["locale"] = "en-US";
		m_createProductMap["notificationMessageKey"] = "CREATED_STYLE_OVERVIEW";
		m_createProductMap["userId"] = Configuration::GetInstance()->GetUserId();
		m_createProductMap["schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
		Utility::Logger("createProductMap::" + to_string(m_createProductMap));
		Utility::Logger("createProduct -> CreateProductCreateMap() -> End");
	}
	/**
	 * \brief Method saves filled values of user from UI
	 */
	void createProduct::Save_clicked()
	{
		Utility::Logger("createProduct -> SaveClicked() -> Start");
		m_isSaveClicked = true;
		if (ExtractAllUIValues())
		{
			CreateProductCreateMap();
			m_isUserInputEmpty = true;
			UTILITY_API->DisplayMessageBox("Newly created product data has been saved successfully locally");
		}
		Utility::Logger("createProduct -> SaveClicked() -> End");
	}
	/**
	 * \brief - Goes to previous UI tab
	 */
	void createProduct::on_Back_clicked()
	{
		Utility::Logger("createProduct -> OnBackClicked() -> Start");
		this->hide();
		if (IsSaveClicked() == false)
		{
			ClearAllFields();
		}
		DesignSuite::GetInstance()->setModal(true);
		DesignSuite::GetInstance()->show();
		Utility::Logger("createProduct -> OnBackClicked() -> End");
	}
	
	/**
	 * \brief Closes the current UI tab
	 */
	void createProduct::Cancel_clicked()
	{
		Utility::Logger("createProduct -> CancelClicked() -> Start");
		this->close();
		if (IsSaveClicked() == false)
		{
			ClearAllFields();
		}
		Utility::Logger("createProduct -> CancelClicked() -> End");
	}

	/**
	 * \brief When User clicks on Send to PLM, Method will collect all the information and sends to PLM
	 */
	void createProduct::sendToPLM_clicked()
	{
		Utility::Logger("createProduct -> SendToPLMClicked() -> Start");
		string errorResponse;
		m_isSaveClicked = false;
		if (ExtractAllUIValues()) // change to check if atleast one field is filled
		{
			
			ParseIDGeneratorJson(m_idGenSettingsJson);
			m_isUserInputEmpty = true;
			CreateProductCreateMap();
			
			this->hide();
			string dirPath;
			bool isSpaceFound = false;
			string parameter = to_string(m_createProductMap);
			Utility::Logger("SEND to PLM Create map::" + parameter);
			string response = RestCall(parameter, PRODUCT_CREATE_API);
			Utility::Logger("createProduct::sendToPLM_clicked() response - " + response);
			errorResponse = Utility::CheckErrorDescription(response);
			Utility::Logger("CheckErrorDescription ::" + errorResponse);
			m_createProductMap.clear();
			if (errorResponse.empty())
			{
				json keyjson = Utility::GetResultsJSON(response);
				m_styleID = keyjson["key"].dump();
				m_addedCode = keyjson["addedCode"].dump();

				string filePathZPRJ = UTILITY_API->GetProjectFilePath();
				string pathOfzprj = UTILITY_API->GetProjectFilePath();
				Utility::EraseSubString(pathOfzprj, UTILITY_API->GetProjectName());
				string checkFileName = UTILITY_API->GetProjectName();
				for (int CheckNameCharecter = 0; CheckNameCharecter < checkFileName.length(); CheckNameCharecter++)
				{
					int space = checkFileName[CheckNameCharecter];
					if (isspace(space))
					{
						isSpaceFound = true;
					}
				}
				if (!isSpaceFound)
				{
					int fileSize = Utility::GetFileSize(filePathZPRJ);
					Utility::Logger("filesize::" + to_string(fileSize));
					if (fileSize > UPLOAD_FILE_SIZE)
					{
						string metaData = CreateMetaDataForCurrentGarment();
						UTILITY_API->SetMetaDataForCurrentGarment(metaData + "\n");
						Utility::Logger("SetMetaDataForCurrentGarment::" + metaData);
						string exportZprj = EXPORT_API->ExportZPrj(filePathZPRJ, true);
						string filepathZip = pathOfzprj + UTILITY_API->GetProjectName() + ".zprj";
						string responseZip = Utility::UploadFile(filepathZip, Configuration::GetInstance()->GetBearerToken());
						Utility::Logger("createProduct::sendToPLM_clicked() upload zprj response - " + responseZip);
						errorResponse = Utility::CheckErrorDescription(responseZip);
						Utility::Logger("errorResponse.." + errorResponse);
						if (errorResponse.empty())
						{
							string filepathImg = pathOfzprj + UTILITY_API->GetProjectName() + ".png"; //zprj and thumb nail
							m_ImageNameTemp = UTILITY_API->GetProjectName() + ".png";

							string responseImg = Utility::UploadFile(filepathImg, Configuration::GetInstance()->GetBearerToken());
							Utility::Logger("createProduct::sendToPLM_clicked() upload image response - " + responseImg);
							errorResponse = Utility::CheckErrorDescription(responseImg);
							if (errorResponse.empty())
							{
								Utility::CustomMessageBox("After Upload File IMG response" + responseImg);
								bool isAttachmentLinked = linkingAttachment(responseZip, responseImg, m_styleID);
								if (isAttachmentLinked)
								{
									UTILITY_API->DisplayMessageBox("Product with style code " + m_addedCode + " created successfully in PLM");
									m_isSaveClicked = false;
									UTILITY_API->NewProject();
									Utility::Logger("createProduct -> getInstance() -> Created Successfully");
								}
								else
								{
									UTILITY_API->DisplayMessageBox(" Product creation failed in PLM ");
									Utility::Logger("createProduct -> getInstance() -> Product Creation Failed");
								}
							}
							else
							{
								UTILITY_API->DisplayMessageBox(errorResponse);
							}
						}
						else if (errorResponse == isFileExists)
						{
							m_isSaveClicked = true; 
							UTILITY_API->DisplayMessageBox("File already exists, please rename the 3D design and create product again");
							Utility::Logger("createProduct -> sendToPLM_clicked() ->" + errorResponse);
						}
						else
						{
							UTILITY_API->DisplayMessageBox(errorResponse);
						}
					}
					else
					{
						m_isSaveClicked = true;
						UTILITY_API->DisplayMessageBox("User doesn't have a design to send to PLM");
					}
				}
				else
				{
					UTILITY_API->DisplayMessageBox("3D design filename has spaces, please rename to remove the spaces and create product");
				}
			}
			else
			{
				UTILITY_API->DisplayMessageBox(errorResponse);
			}			
		}
		Utility::Logger("createProduct -> SendToPLMClicked() -> End");
	}
	/**
		 * \brief creates related parameter for Image to send to PLM
		 * \param string response, string key
		 * \return string
		 */
	string createProduct::CreateImageParam(string response, string key)
	{
		Utility::Logger("createProduct -> createImageParam() -> Start");
		json ImgJson;
		try {
			ImgJson = json::parse(response);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("createProduct -> createImageParam()::parsing ImgJson exception - " + string(e.what()));
			throw e.what();
		}
		string objectKey = ImgJson["addedFiles"][0]["objectKey"].dump();
		objectKey = objectKey.erase(0, 1);
		objectKey = objectKey.erase(objectKey.size() - 1);
		string oldFileName = ImgJson["addedFiles"][0]["oldFileName"].dump();
		oldFileName = oldFileName.erase(0, 1);
		oldFileName = oldFileName.erase(oldFileName.size() - 1);
		json mainMap;
		json attsFileList;
		json detailsMap;
		json details;
		json attaFileListtoMap;
		mainMap["modifyId"] = Configuration::GetInstance()->GetUserId();
		mainMap["Schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
		details["dlType"] = DLTYPECODE_STYLE_IMAGES;
		detailsMap = details;
		attaFileListtoMap["code"] = "E0012";
		attaFileListtoMap["type"] = "Image";
		attaFileListtoMap["objectKey"] = objectKey;
		attaFileListtoMap["oldFileName"] = oldFileName;
		attaFileListtoMap["referenceId"] = key;
		attaFileListtoMap["details"] = detailsMap;
		attaFileListtoMap["IsDefault"] = true;
		attsFileList[0] = attaFileListtoMap;
		mainMap["AttaFileListDto"] = attsFileList;
		Utility::Logger("CreateImageParam main map::" + to_string(mainMap));
		Utility::Logger("createProduct -> createImageParam() -> End");

		return to_string(mainMap);
	}
	/**
	 * \brief creates related parameter for Zprj to send to PLM
	 * \param string response, string key
	 * \return string
	 */
	string createProduct::CreateZipParam(string response, string key)
	{
		Utility::Logger("createProduct -> CreateZipParam() -> Start");
		json ImgJson;
		ImgJson = Utility::GetResultsJSON(response);
		string objectKey = ImgJson["addedFiles"][0]["objectKey"].dump();
		objectKey = objectKey.erase(0, 1);
		objectKey = objectKey.erase(objectKey.size() - 1);
		string oldFileName = ImgJson["addedFiles"][0]["oldFileName"].dump();
		oldFileName = oldFileName.erase(0, 1);
		oldFileName = oldFileName.erase(oldFileName.size() - 1);
		json mainMap;
		json attsFileList;
		json attsFileListtoMap;
		attsFileListtoMap["referenceId"] = key;
		attsFileListtoMap["code"] = "E0013";
		attsFileListtoMap["objectKey"] = objectKey;
		attsFileListtoMap["oldFileName"] = oldFileName;
		attsFileList[0] = attsFileListtoMap;
		mainMap["modifyId"] = Configuration::GetInstance()->GetUserId();
		mainMap["Schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
		mainMap["AttaFileListDto"] = attsFileList;
		Utility::Logger("CreateZipParam main map::" + to_string(mainMap));
		Utility::Logger("createProduct -> createZipParam() -> End");

		return to_string(mainMap);
	}
/*
 * \brief Method gets Id generator settings from Infor
 */
	void createProduct::GetIdGeneratorSettings()
	{
		Utility::Logger("createProduct -> GetIdGeneratorSettings() -> Start");
		string parameter = "{\"Schema\":" + Configuration::GetInstance()->GetschemaWithQuotes() + "}";
		Utility::Logger("createProduct -> GetIdGeneratorSettings() -> parameter:: "+ parameter);
		Utility::Logger("createProduct -> GetIdGeneratorSettings() -> PRODUCT_GET_STYLECODE_GENERATOR_SETTINGS:: " + PRODUCT_GET_STYLECODE_GENERATOR_SETTINGS);

		string response = RestCall(parameter, PRODUCT_GET_STYLECODE_GENERATOR_SETTINGS);
		Utility::Logger("createProduct -> GetIdGeneratorSettings() -> response:: " + response);

		string errorResponse = Utility::CheckErrorDescription(response);
		Utility::Logger("createProduct -> GetIdGeneratorSettings() -> errorResponse:: " + errorResponse);

		string idGenSettings;
		
		if (errorResponse.empty() && (errorResponse.length() == 0))
		{
			try
			{
				m_idGenSettingsJson = json::parse(response);
				ParseIDGeneratorJson(m_idGenSettingsJson);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("createProduct -> GetIdGeneratorSettings()::parsing m_idGenSettingsJson exception - " + string(e.what()));
				throw e.what();
			}
		}
		else
		{
			UTILITY_API->DisplayMessageBox(errorResponse);
		}
		Utility::Logger("createProduct -> GetIdGeneratorSettings() -> End");
	}

	/**
 * \brief Method parses ID generator response
 * \param json idGenSettingsJson
 */
	void createProduct::ParseIDGeneratorJson(json idGenSettingsJson)
	{
		Utility::Logger("createProduct -> ParseIDGeneratorJson() -> Start");
		json mapArray;
		json tempMap;
		m_idGenVal.clear();
		json idRuleJson, idRulesListJson;
		string idRulesList = idGenSettingsJson["idRulesList"].dump();
		try {
			idRulesListJson = json::parse(idRulesList);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("createProduct -> ParseIDGeneratorJson()::parsing idRulesListJson exception - " + string(e.what()));
			throw e.what();
		}
		bool settingsCheck = false;
		for (int i = 0; i < idRulesListJson.size(); i++)
		{
			string idRule = idRulesListJson[i].dump();
			try {
				idRuleJson = json::parse(idRule);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("createProduct -> ParseIDGeneratorJson()::parsing idRuleJson exception - " + string(e.what()));
				throw e.what();
			}
			string moduleId = idRuleJson["moduleId"].dump();
			string isDefault = idRuleJson["isDefault"].dump();

			if (moduleId == "1" && isDefault == "1") // For Style 
			{
				settingsCheck = true;
				m_IdGenSettingsAvailable = true;
				string lookupField1 = idRuleJson["lookupField1"].dump();
				lookupField1 = lookupField1.erase(0, 1);
				lookupField1 = lookupField1.erase(lookupField1.size() - 1);
				

				string lookupField2 = idRuleJson["lookupField2"].dump();
				lookupField2 = lookupField2.erase(0, 1);
				lookupField2 = lookupField2.erase(lookupField2.size() - 1);
				
				m_idGenContextVal2 = "[{\"FieldName\":\"" + lookupField1 + "\",\"Value\":\"\"},{\"FieldName\":\"" + lookupField2 + "\",\"Value\":\"\"}]";
			
				string autoNumberVal = idRuleJson["autoNumberVal"].dump();
				try {
					m_idGenVal = json::parse(autoNumberVal);
				}
				catch (exception& e)
				{
					Utility::ErrorLogger("createProduct -> ParseIDGeneratorJson()::parsing m_idGenVal exception - " + string(e.what()));
					throw e.what();
				}

				string lookUpFirst, lookUpSecond;
				json idGenValJson;
				for (int i = 0; i < m_idGenVal.size(); i++)
				{
					string idGenValString = m_idGenVal[i].dump();
					try {
						idGenValJson = json::parse(idGenValString);
					}
					catch (exception& e)
					{
						Utility::ErrorLogger("createProduct -> ParseIDGeneratorJson()::parsing idGenValJson exception - " + string(e.what()));
						throw e.what();
					}
					string formatTypeId = idGenValJson["formatTypeId"].dump();
					
					if (formatTypeId == "3")
					{
						string fieldId = idGenValJson["fieldId"].dump();
						string codeNameId = idGenValJson["codeNameId"].dump();
						for (auto it = m_attributeMap.begin(); it != m_attributeMap.end(); it++)
						{
							if (it->second == lookupField1 )
							{
								string tempLabel = it->first;
								string tempValue = GetUserInputForIdGeneration(lookupField1);
								if (stoi(codeNameId) == 1) //For Name
								{
									lookUpFirst = tempValue;
									break;
								}
								else if (stoi(codeNameId) == 2) //For Code
								{
									map<string, string> attNameCodeMap;
									attNameCodeMap.clear();
									attNameCodeMap.insert(m_IdGeneratorMap[tempLabel].begin(), m_IdGeneratorMap[tempLabel].end());
									for (auto it = attNameCodeMap.begin(); it != attNameCodeMap.end(); it++)
									{
										if (it->first == tempValue)
										{
											lookUpFirst = it->second;
											break;
										}
									}
								}
							
							}
							else if (it->second == lookupField2)
							{
								string tempLabel = it->first;
								string tempValue = GetUserInputForIdGeneration(lookupField2);
								if (stoi(codeNameId) == 1) //For Name
								{
									lookUpSecond = tempValue;
									break;
								}
								else if (stoi(codeNameId) == 2)//For Code
								{
									map<string, string> attNameCodeMap;
									attNameCodeMap.clear();
									attNameCodeMap.insert(m_IdGeneratorMap[tempLabel].begin(), m_IdGeneratorMap[tempLabel].end());
									for (auto it = attNameCodeMap.begin(); it != attNameCodeMap.end(); it++)
									{
										if (it->first == tempValue)
										{

											lookUpSecond = it->second;
											break;
										}
									}
									
								}
							}
						}
					}
				}
				m_idGenContextVal = "[\""+ lookUpFirst +"\",\""+ lookUpSecond +"\"]";
				break;
			}
			
		}
		if (settingsCheck == false)
		{
			m_IdGenSettingsAvailable = false;
		}
		Utility::Logger("createProduct -> ParseIDGeneratorJson() -> End()");
	}

	/**
 * \brief Method extracts all user input values to send to PLM
 return Value - bool,returns True if atleast one value is filled up, False if no field is entered
 */
	bool createProduct::ExtractAllUIValues()
	{
		Utility::Logger("createProduct -> ExtractAllUIValues() -> Start");
		for (int i = 0; i < createProductSearchTable->topLevelItemCount(); ++i)
		{
			QTreeWidgetItem* topItem = createProductSearchTable->topLevelItem(i);
			QWidget* qWidgetColumn0 = createProductSearchTable->itemWidget(topItem, 0);
			QWidget* qWidgetColumn1 = createProductSearchTable->itemWidget(topItem, 1);
			QLabel* qlabel = qobject_cast<QLabel*>(qWidgetColumn0);
			string lable = qlabel->text().toStdString();
			QLineEdit* qlineedit = qobject_cast<QLineEdit*>(qWidgetColumn1);
			if (qlineedit)
			{
				m_createFieldsVector[i].userInputValues = qlineedit->text().toUtf8(); 
				
				if (qlineedit->isEnabled() && m_createFieldsVector[i].labelValue.contains("StyleCode") && m_createFieldsVector[i].userInputValues.isEmpty())
				{
					UTILITY_API->DisplayMessageBox("Please enter mandatory fields to create product.");
					return false;
				}
				if (!qlineedit->text().isEmpty())
				{
					m_isUserInputEmpty = false;
				}
			}
			else 
			{
				QComboBox* qComboBox = qobject_cast<QComboBox*>(qWidgetColumn1);
				if (qComboBox)
				{
					m_createFieldsVector[i].userInputValues = qComboBox->currentText().toUtf8();
					if (qComboBox->currentText() != "Select")
					{
						m_isUserInputEmpty = false;
					}
				}
				else
				{
					QTextEdit* qtextEdit = qobject_cast<QTextEdit*>(qWidgetColumn1);
					if (qtextEdit)
					{
						m_createFieldsVector[i].userInputValues = qtextEdit->toPlainText().toUtf8();
						if (!qtextEdit->toPlainText().isEmpty())
						{
							m_isUserInputEmpty = false;
						}
					}
				}
			}			
		}

		if (m_isUserInputEmpty)
		{
			UTILITY_API->DisplayMessageBox("Please enter atleast one field to create Product.");
			return false;
		}
		Utility::Logger("createProduct -> ExtractAllUIValues() -> End");
		return true;
	}

	/**
 * \brief Method sets a map of Names and Codes of all dropdown UI fields to be used for ID Generation
 params - lookUpsJson and attributeValue
 */
	void createProduct::SetIdGeneratorMap(IN const json& lookUpsJson, IN const string& attributeValue)
	{
		Utility::Logger("createProduct::SetIdGeneratorMap() Started...");
		map<string, string> tempMap;
		json lookupNameAndIdJson, colNameAndIDJSON;
		for (int i = 0; i < lookUpsJson.size(); i++) 
		{
			string lookupNameAndId = lookUpsJson[i].dump();
			try {
				lookupNameAndIdJson = json::parse(lookupNameAndId);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("createProduct::SetIdGeneratorMap()::parsing lookupNameAndIdJson exception - " + string(e.what()));
				throw e.what();
			}
			string colName = lookupNameAndIdJson["name"].dump();
			colName = colName.erase(0, 1);
			colName = colName.erase(colName.size() - 1);
			if (attributeValue.compare(colName) == 0)
			{
				string name,code;
				string columnStg = lookupNameAndIdJson["column"].dump();
				try {
					colNameAndIDJSON = json::parse(columnStg);
				}
				catch (exception& e)
				{
					Utility::ErrorLogger("createProduct::SetIdGeneratorMap()::parsing colNameAndIDJSON exception - " + string(e.what()));
					throw e.what();
				}
				name = colNameAndIDJSON["Name"].dump();
				name = name.erase(0, 1);
				name = name.erase(name.size() - 1);
				code = colNameAndIDJSON["Code"].dump();
				code = code.erase(0, 1);
				code = code.erase(code.size() - 1);
				tempMap.insert(std::make_pair(name, code));
				
			}
		}
		m_IdGeneratorMap.insert(std::make_pair(attributeValue, tempMap));
		

		Utility::Logger("Utility::SetIdGeneratorMap() Ended...");
	}

	/**
* \brief Method gets user input fro style ID auto Generation
params - label
*/
	string createProduct::GetUserInputForIdGeneration(const string& label)
	{
		Utility::Logger("createProduct -> GetUserInputForIdGeneration() -> Start");
		for (auto arrayElement : m_createFieldsVector)
		{
			string attLabel = arrayElement.labelValue.toStdString();
			string userSelected = arrayElement.userInputValues.toStdString();
			
			if (attLabel == label)
			{
				return userSelected;
			}
		}
		Utility::Logger("createProduct -> GetUserInputForIdGeneration() -> End");
	}

	bool createProduct::IsStyleCodeEnabled()
	{
		if (m_IdGenSettingsAvailable)
		{
			return false;
		}
		return true;
	}
	string createProduct::CreateMetaDataForCurrentGarment()
	{
		json addMetaData;

		for (int i = 0; i < createProductSearchTable->topLevelItemCount(); ++i)
		{
			QTreeWidgetItem* topItem = createProductSearchTable->topLevelItem(i);
			QWidget* qWidgetColumn0 = createProductSearchTable->itemWidget(topItem, 0);
			QLabel* qlabel = qobject_cast<QLabel*>(qWidgetColumn0);
			string label = qlabel->text().toStdString();
			if (label == "Number")
			{
				addMetaData["Style ID"] = m_styleID;
				string styleCode = m_addedCode;
				styleCode = styleCode.erase(0, 1);
				styleCode = styleCode.erase(styleCode.size() - 1);
				addMetaData["Style Code"] = styleCode;
			}
			else if (label == "Brand")
			{
				addMetaData[label] = m_createFieldsVector[i].userInputValues.toStdString();
			}
		}
		return to_string(addMetaData);
	}
}