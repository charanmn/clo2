#include "ProductSearch.h"
#include "GeneratedFiles/ui_ProductSearch.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QCheckBox>
#include <any>
#include <optional>
#include "qlistview.h"
#include "CLO_PLUGIN/INFOR/Libraries/curl/include/curl/curl.h"
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
#include "CLO_PLUGIN/INFOR/Libraries/jsonQt.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"
#include "CLO_PLUGIN/INFOR/DesignSuite/DesignSuite.h"
#include "CLO_PLUGIN/INFOR/Utilities/ComboBoxItem.h"
#include "CLO_PLUGIN/INFOR/Utilities/Configuration.h"
#include "ProductResultTable.h"
#include "classes/APIDefine.h"
#include "CLO_PLUGIN/INFOR/Utilities/Configuration.h"
#include "CLO_PLUGIN/INFOR/Utilities/RestAPIUtility.h"
#include "CLO_PLUGIN/INFOR/Utilities/DirectoryUtil.h"
#include <CLO_PLUGIN\INFOR\Products\ProductUtility.h>

using json = nlohmann::json;
using namespace std;
using QtJson::JsonObject;
using QtJson::JsonArray;


namespace CLOPlugin
{
	ProductSearch* ProductSearch::_instance = NULL;
	/**
	 * \brief Instantiate ProductSearch object
	 * \return
	 */
	ProductSearch* ProductSearch::GetInstance()
	{
		Utility::Logger("ProductSearch -> GetInstance() -> Start");

		if (_instance == NULL)
		{
			_instance = new ProductSearch();
		}

		Utility::Logger("ProductSearch -> GetInstance() -> End");
		return _instance;
	}
     /**
	 * \brief brief  destructortor of Product search class
	 *  deletes the object of this class. 
	 */
	void ProductSearch::Destroy()
	{
		Utility::Logger("ProductSearch -> Destroy() -> Start");

		if (_instance)
		{
			delete _instance;
			_instance = NULL;
		}

		Utility::Logger("ProductSearch -> Destroy() -> End");
	}
	 /**
	 * \brief Creates Product Search Dialog
	 * \param  parent
	 */
	ProductSearch::ProductSearch(QWidget* parent) : QDialog(parent)
	{
		Utility::Logger("ProductSearch -> Constructor() -> Start");
		
		setupUi(this);
		bstyleImage = false; 
		bstyleAttachment = false;
		QFont fontStyle("Times new roman", FONT_SIZE, QFont::Bold);
		this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
		QSize size(TABLE_WIDTH, TABLE_HEIGHT);

		ProductSearchTree->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		ProductSearchTree->setStyleSheet("QTreeWidget::item { border-bottom: 1px solid #232323;""padding : 10px;""height: 25px;""}");

		ProductSearchTree->setFixedSize(size);
		ProductSearchTree->setColumnWidth(1, USER_INPUT_WIDTH);
		ProductSearchTree->setColumnWidth(0, SEARCH_LABEL_WIDTH);
		
		QTreeWidgetItem *dataItem= new QTreeWidgetItem;
		Qt::ItemFlags flags;
		flags = dataItem->flags();
		flags |= Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
		dataItem->setFlags(flags);
		ProductSearchTree->setFocusPolicy(Qt::FocusPolicy::StrongFocus);	
		ProductSearchTree->setSelectionBehavior(QAbstractItemView::SelectItems);
		ProductSearchTree->setSelectionMode(QAbstractItemView::NoSelection);
		ProductSearchTree->setSelectionBehavior(QAbstractItemView::SelectRows);
		ProductSearchTree->setEditTriggers(QAbstractItemView::CurrentChanged);
		ProductSearchTree->setTabKeyNavigation(true);
		headerLabel->setFont(fontStyle);
		layout()->setSizeConstraint(QLayout::SetFixedSize);
		this->adjustSize();

		back->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_back_over.svg"));
		back->setIconSize(QSize(iconHieght, iconWidth));
		back->setStyleSheet(buttonFont);

		search->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_search_over.svg"));
		search->setIconSize(QSize(iconHieght, iconWidth));
		search->setStyleSheet(buttonFont);

		QObject::connect(search, SIGNAL(clicked()), this, SLOT(SearchClicked()));
		QObject::connect(back, SIGNAL(clicked()), this, SLOT(backclicked()));
		QObject::connect(closeWindow, SIGNAL(clicked()), this, SLOT(Cancel_clicked()));
		m_isUserInputEmpty = true;
		m_isOnlyPercentileFound = false;

		FilterDependencyList();

		ReadPLMJson();
		ReadJsonAndDrawDialog();
		Utility::Logger("ProductSearch -> Constructor() -> End");
	}
	/**
	 * \brief Add labels in product search page from Json
	 */
	void ProductSearch::ReadJsonAndDrawDialog()
	{
		Utility::Logger("ProductSearch -> ReadJsonAndDrawDialog() -> Start");
		m_searchFieldsVector = Utility::ReadJsonForDrawDialogue("Style");
		DrawWidget(m_searchFieldsVector);
		
		Utility::Logger("ProductSearch -> ReadJsonAndDrawDialog() -> End");
	}
	/**
	 * \brief Sets type of widgets for labels
	 * \param  fieldsVector
	 */
	void ProductSearch::DrawWidget(std::vector<Utility::Fields>& fieldsVector)
	{		
		Utility::Logger("ProductSearch -> DrawWidget() -> Start");
		

		for each (auto field in fieldsVector)
		{
			string tempLabel = field.labelValue.toStdString();

			if (m_attributeMap.find(tempLabel) != m_attributeMap.end()) {
				tempLabel = m_attributeMap.at(tempLabel);
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
				ProductSearchTree->addTopLevelItem(topLevel);						
				ProductSearchTree->setItemWidget(topLevel, 0, label);				
				ProductSearchTree->setItemWidget(topLevel, 1, lineEdit);
				lineEdit->setText(field.userInputValues);
				
			}

			if (field.fieldUItype == "dropdown")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();
				ComboBoxItem* comboBox = new ComboBoxItem(topLevel, 1);
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);
				label->setProperty("Id", field.labelValue);

				label->setText(QString::fromStdString(tempLabel));
				comboBox->setStyleSheet(inputStyle);
				ProductSearchTree->addTopLevelItem(topLevel);
				ProductSearchTree->setItemWidget(topLevel, 0, label);
				ProductSearchTree->setItemWidget(topLevel, 1, comboBox);

				comboBox->setStyleSheet("combobox-popup: 0; font: 75 8pt \"Tahoma\"; ");
				comboBox->addItems(field.presetValues);
				int indexOfEmptyString = comboBox->findText("Select");
				comboBox->setCurrentIndex(indexOfEmptyString);
				comboBox->setProperty("Id", field.labelValue);

				QObject::connect(comboBox, SIGNAL(activated(const QString&)), this,
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
				ProductSearchTree->addTopLevelItem(topLevel);						
				ProductSearchTree->setItemWidget(topLevel, 0, label);				
				ProductSearchTree->setItemWidget(topLevel, 1, TextEdit);
				TextEdit->setText(field.userInputValues);
				TextEdit->setStyleSheet("border: 1px solid black;""background-color: #222222;""font: 75 8pt \"Tahoma\";"
				);
				TextEdit->setMaximumSize(TEXTEDIT_SIZE_WIDTH, TEXTEDIT_SIZE_HEIGHT);
			}

			if (field.fieldUItype == "DateEdit")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();
				QDateEdit* DateTimeEdit = new QDateEdit();
				bool enable = true;
				DateTimeEdit->setCalendarPopup(enable);			
				QString dateRecovery("");
				QDate date = QDate::fromString(dateRecovery, "");
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);
				label->setProperty("Id", field.labelValue);
				
				label->setText(QString::fromStdString(tempLabel));
				ProductSearchTree->addTopLevelItem(topLevel);
				ProductSearchTree->setItemWidget(topLevel, 0, label);
				ProductSearchTree->setItemWidget(topLevel, 1, DateTimeEdit);	
			}
		}

		Utility::Logger("ProductSearch -> DrawWidget() -> End");
	}

	/**
	* Function is used to handle change event of dropdown widgets
	*/
	void ProductSearch::handleDropDownValueChangeEvent(const QString& item)
	{
		Utility::Logger("ProductSearch -> handleDropDownValueChangeEvent() -> Start");
		QString senderCombo = sender()->property("Id").toString();
		bool resetRootItem = false;
		if (m_rootItem == senderCombo.toStdString()) {
			resetRootItem = true;
		}

		if (item.isEmpty()) {
		}
		else if (item == "Select")
		{
			for (int i = 0; i < ProductSearchTree->topLevelItemCount(); ++i)
			{
				QTreeWidgetItem* topItem = ProductSearchTree->topLevelItem(i);
				QWidget* qWidget = ProductSearchTree->itemWidget(topItem, 1);
				QComboBox* qComboBox = qobject_cast<QComboBox*>(qWidget);
				
				if ((qComboBox))
				{
					QString id = qComboBox->property("Id").toString();
					if (resetRootItem) {
						for (auto it = m_hierarchyMap.begin(); it != m_hierarchyMap.end(); it++)
						{
							if (it->first.find(id.toStdString()) == 0 || it->second.find(id.toStdString()) == 0) {
								qComboBox->clear();
								for each (auto field in m_searchFieldsVector) {
									if (id == field.labelValue) {
										qComboBox->addItems(field.presetValues);
										break;
									}
								}
								qComboBox->setCurrentIndex(qComboBox->findText("Select"));
							}
						}
					} else if (senderCombo == id && std::find(m_nonDependentFields.begin(), m_nonDependentFields.end(), id.toStdString()) == m_nonDependentFields.end()) {
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
								GetResetFields(ProductSearchTree, m_hierarchyMap, filterString, m_clearItems, m_searchFieldsVector, false);
							}
						}
					}
				}
			}
			m_clearItems.clear();
			resetRootItem = false;
		}
		else if(item != "Select")
		{
			map<string, map<string, QString>> dropDownValues;
			for (int i = 0; i < ProductSearchTree->topLevelItemCount(); ++i)
			{
				QTreeWidgetItem* topItem = ProductSearchTree->topLevelItem(i);
				QWidget* qWidget = ProductSearchTree->itemWidget(topItem, 1);
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
								for each (auto field in m_searchFieldsVector) {
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
								GetResetFields(ProductSearchTree, m_hierarchyMap, filterString, m_clearItems, m_searchFieldsVector, false);
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
			/*for (auto it = dropDownValues.begin(); it != dropDownValues.end(); it++)
			{
				for (auto itr = it->second.begin(); itr != it->second.end(); itr++)
				{
					Utility::Logger(it->first+"---dropDownValues------"+itr->second.toStdString());
				}
			}*/
			
			if (!dropDownValues.empty())
			{
				for (int i = 0; i < ProductSearchTree->topLevelItemCount(); ++i)
				{
					QTreeWidgetItem* topItem = ProductSearchTree->topLevelItem(i);
					QWidget* qWidget = ProductSearchTree->itemWidget(topItem, 1);
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
						}
					}
				}
			}
			try
			{
				list<string> resetFields;
				for (auto it = m_clearItems.begin(); it != m_clearItems.end(); it++)
				{
					bool dataExits = false;
					for (auto itm = dropDownValues.begin(); itm != dropDownValues.end(); itm++)
					{
						if (itm->first == *it) {
							dataExits = true;
						}
					}

					if (!dataExits) {
						resetFields.push_back(*it);
					}
				}

				for (auto itm = resetFields.begin(); itm != resetFields.end(); itm++)
				{
					ResetNonDependentItems(resetFields);
				}
			}
			catch (const std::exception&)
			{
				Utility::Logger("Exception occured while getting level of field.");
			}
			
			m_clearItems.clear();
		}

		Utility::Logger("ProductSearch -> handleDropDownValueChangeEvent() -> End");
	}

	/**
	* Function to reset field values
	*/
	void ProductSearch::ResetNonDependentItems(list<string>& resetFields)
	{
		for (int i = 0; i < ProductSearchTree->topLevelItemCount(); ++i)
		{
			QTreeWidgetItem* topItem = ProductSearchTree->topLevelItem(i);
			QWidget* qWidget = ProductSearchTree->itemWidget(topItem, 1);
			QComboBox* qComboBox = qobject_cast<QComboBox*>(qWidget);
			if ((qComboBox))
			{
				QString id = qComboBox->property("Id").toString();
				for (auto it = resetFields.begin(); it != resetFields.end(); it++)
				{
					if (id.toStdString() == *it) {
						qComboBox->clear();
						for each (auto field in m_searchFieldsVector) {
							if (id == field.labelValue) {
								qComboBox->addItems(field.presetValues);
								break;
							}
						}
						qComboBox->setCurrentIndex(qComboBox->findText("Select"));
						break;
					}
				}
			}
		}
	}

	/**
	* Method is used to call rest api and filter records for field dependencies
	*/
	void ProductSearch::FilterDependencyList()
	{
		Utility::Logger("ProductSearch -> FilterDependencyList() -> Start");
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
				Utility::ErrorLogger("ProductSearch -> FilterDependencyList()::parsing lookupsJSON exception - " + string(e.what()));
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
			Utility::ErrorLogger("ProductSearch -> FilterDependencyList()::parsing completeEntitiesJson exception - " + string(e.what()));
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
					Utility::ErrorLogger("ProductSearch -> FilterDependencyList()::parsing productCol exception - " + string(e.what()));
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
						Utility::ErrorLogger("ProductSearch -> FilterDependencyList()::parsing columns exception - " + string(e.what()));
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
								m_orgLevelIdLookUpMap.insert(std::make_pair(stoi(OrgLevelId), LookupRef + "_" + OrgLevelName +"|@|"+ OrgLevelId));
								m_parentIdLookUpMap.insert(std::make_pair(ParentId, LookupRef + "_" + OrgLevelName +"|@|"+ OrgLevelId));
							}
						}
					}
					catch (const std::exception& exception)
					{
						Utility::Logger("ProductSearch -> FilterDependencyList():: Exception occured while getting Id from lookupmap."+string(exception.what()));
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

		Utility::Logger("FabricsSearchDialog -> FilterDependencyList() -> End");
	}
	/**
	* \brief Setting Independent Values to widgets 
	* \param  dependencyJson
	*/
	map<string, map<string, QString>> ProductSearch::SetDropDownValues(string& selectedItem, string& id)
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

	ProductSearch::~ProductSearch()
	{

	}

	/**
	* \brief Filter out Product Details Json
	*/
	void  ProductSearch::ReadPLMJson() 
	{
		Utility::Logger("ProductSearch -> ReadPLMJson() -> Start");
		string parameter = "{\"roleId\":" + Configuration::GetInstance()->GetRoleId() + ",\"userId\":" + Configuration::GetInstance()->GetUserId() + ",\"entity\":\"Style\",\"pageType\":\"details\",\"dataFilter\":{\"conditions\":[{\"fieldname\":\"StyleId\",\"operator\":\"=\",\"value\":\"\"}]},\"pageInfo\":{},\"Schema\":" + Configuration::GetInstance()->GetschemaWithQuotes() + "}";
		string entity = "Style";
		Utility::GetFilteredJson(parameter,PRODUCT_DETAILS_API, entity);
		json completeStyleJson;
		m_attsDropdownListMap.clear();
		m_attributeMap.clear();
		ifstream styleDetailsFile;
		styleDetailsFile.open(DirectoryUtil::getProdSearchJson());

		styleDetailsFile >> completeStyleJson;
		styleDetailsFile.close();

		ofstream styleSearchFile;
		styleSearchFile.open(DirectoryUtil::getProdSearchFilteredJson());
		json finalJsontoSave;
		auto jsonFieldList = json::array();
		auto jsonUiTypeList = json::object();
		auto presetArray = json::array();
		json newPresetListObject = json::array();
		auto presetList = json::object();
		auto jsonMandatoryFieldsList = json::array();
		auto jsonDataFieldList = json::object();
		int uiPresetCount = 0;
		list<string> skipElements;
		skipElements.push_back("DivisionId");
		skipElements.push_back("SubCategoryId");

		map<string, string> linkingMap;
		linkingMap.insert(make_pair("BrandId", "DivisionId"));
		linkingMap.insert(make_pair("CategoryId", "SubCategoryId"));

		string completeStyleJsonString, componentsString, compObjString;
		json completeJson, componentsJson;
		completeStyleJsonString = completeStyleJson.dump();
		try {
			completeJson = json::parse(completeStyleJsonString);
			componentsString = completeJson["layout"]["components"].dump();
			componentsJson = json::parse(componentsString);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("ProductSearch -> ReadPLMJson()::parsing completeJson exception - " + string(e.what()));
			throw e.what();
		}
		json compObjJson, propsJson;
		string propsString, visible;
		json keyValuePairs = Utility::GetKeyValuePairs();
		for (int i = 0; i < componentsJson.size(); i++) 
		{
			compObjString = componentsJson[i].dump();
			try {
				compObjJson = json::parse(compObjString);
				propsString = compObjJson["props"].dump();
				propsJson = json::parse(propsString);
				visible = propsJson["isVisibleAi"].dump();
			}
			catch (exception& e)
			{
				Utility::Logger("ProductSearch -> ReadPLMJson()::parsing compObjJson exception - " + string(e.what()));
				throw e.what();
			}
			Utility::Logger("passed data::/n" + visible);

			if (visible == "true")
			{
				string requi = propsJson["isRequired"].dump();
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
				float tabIndexNum = std::stof(tabIndex);
				
				string label = compObjJson["label"].dump();
				label = label.erase(0, 1);
				label = label.erase(label.size() - 1);

				string entity = compObjJson["entity"].dump();
				entity = entity.erase(0, 1);
				entity = entity.erase(entity.size() - 1);

				if (std::find(skipElements.begin(), skipElements.end(), dataField) == skipElements.end()) {
					m_indexColumnIdMap.insert(make_pair(tabIndexNum, dataField));
					if (linkingMap.find(dataField) != linkingMap.end()) {
						tabIndexNum = tabIndexNum + 0.25;
						m_indexColumnIdMap.insert(make_pair(tabIndexNum, linkingMap.at(dataField)));
					}
				}

				if (label != "ul") {
					m_attributeMap.insert(std::make_pair(dataField, QString::fromUtf8(label.c_str()).toStdString()));
				}
				else {
					m_attributeMap.insert(std::make_pair(dataField, Utility::GetDisplayValueByKey(QString::fromStdString(dataField), QString::fromStdString(entity), keyValuePairs).toStdString()));
					
				}
				
				jsonUiTypeList[dataField] = fieldType;
				jsonFieldList.push_back(dataField);
				jsonDataFieldList[dataField] = dataField;
				if (requi == "true")
				{
					jsonMandatoryFieldsList.push_back(dataField);
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
						Utility::ErrorLogger("ProductSearch -> ReadPLMJson()::parsing lookupsJSON exception - " + string(e.what()));
						throw e.what();
					}
					map<string, string> tempAttribMap;
					Utility::GetDropDownMap(lookupsJSON, lookupRef, tempAttribMap);
					presetArray.clear();
					presetArray.push_back("Select");
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

		finalJsontoSave["fieldList"] = newjsonFieldList;// jsonFieldList;
		finalJsontoSave["uiTypeList"] = jsonUiTypeList;
		finalJsontoSave["presetList"] = presetList;
		finalJsontoSave["mandatory_fieldList"] = jsonMandatoryFieldsList;
		finalJsontoSave["dataFieldList"] = jsonDataFieldList;
		styleSearchFile << finalJsontoSave;
		styleSearchFile.close();

		Utility::Logger("ProductSearch -> ReadPLMJson() -> End");
	}

	/**
	* \brief Clear all fields from widgets 
	*/
	void ProductSearch::ClearAllFields()
	{
		Utility::Logger("ProductSearch -> ClearAllFields() -> Start");
		for (int i = 0; i < ProductSearchTree->topLevelItemCount(); ++i)
		{
			QTreeWidgetItem* topItem = ProductSearchTree->topLevelItem(i);
			QWidget* qWidgetColumn0 = ProductSearchTree->itemWidget(topItem, 0);
			QWidget* qWidgetColumn1 = ProductSearchTree->itemWidget(topItem, 1);
			QLabel* qlabel = qobject_cast<QLabel*>(qWidgetColumn0);
			string label = qlabel->text().toStdString();
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
					QString id = qComboBox->property("Id").toString();
					qComboBox->clear();
					for each (auto field in m_searchFieldsVector) {
						if (id == field.labelValue) {
							qComboBox->addItems(field.presetValues);
							break;
						}
					}
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

		Utility::Logger("ProductSearch -> ClearAllFields() -> End");
	}
	/**
	* \brief Creating Map for Searching Product 
	*/
	void ProductSearch::CreateProductSearchMap()
	{
		Utility::Logger("ProductSearch -> createProductSearchMap() -> Start");

		json filterMap;
		json conditions = json::object();
		m_productSearchMap.clear();

		m_productSearchMap["roleId"] = Configuration::GetInstance()->GetRoleId(); 
		m_productSearchMap["userId"] = Configuration::GetInstance()->GetUserId();
		m_productSearchMap["schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
		m_productSearchMap["entity"] = "Style";
		m_productSearchMap["pageType"] = "list";
		m_productSearchMap["personalizationId"] = 0;
		m_productSearchMap["sortInfo"] = nullptr;
		
		int count = Utility::CreateSearchCriteriaMap(conditions, m_searchFieldsVector, m_attsDropdownListMap);

		filterMap.clear();
		filterMap["fieldname"] = "IsDeleted";
		filterMap["operator"] = "=";
		filterMap["value"] = 0;
		conditions["Conditions"][count++] = filterMap;
		conditions["Search"] = nullptr;

		m_productSearchMap["dataFilter"] = conditions;
		Utility::Logger("ProductSearch -> createProductSearchMap() -> End");
	}
	/**
	* \brief Clicked on Search Button,  Calling Search Method  
	*/
	void ProductSearch::SearchClicked()
	{
		Utility::Logger("ProductSearch -> SearchClicked() -> Start");
		
		if (Utility::ExtractAllUIValuesAndMapToJson(ProductSearchTree, m_searchFieldsVector) && Utility::SearchValidation(ProductSearchTree))
		{
			this->hide();
			PLMSearch();
			m_isUserInputEmpty = true;
			m_isOnlyPercentileFound = false;
		}
		else
		{
			m_isUserInputEmpty = true;
			m_isOnlyPercentileFound = false;
		}
		Utility::Logger("ProductSearch -> SearchClicked() -> End");
	}
	/**
	* \brief Making Rest Call for Search Product
	*/
	void ProductSearch::PLMSearch()
	{
		Utility::Logger("ProductSearch -> PLMSearch() -> Start");
		CreateProductSearchMap();
		string parameter, bearerKey;
		json map;
		json emptyArray;
		parameter = to_string(m_productSearchMap);
		vector<pair<string, string>> headerNameAndValueList;
		headerNameAndValueList.push_back(make_pair(CONTENTTYPE, INFOR_TYPE));
		headerNameAndValueList.push_back(make_pair(AUTHORIZATION, Configuration::GetInstance()->GetBearerToken()));
		Utility::Logger("ProductSearch::PLMSearch() parameter:: " + parameter);
		Utility::Logger("ProductSearch::PLMSearch() PRODUCT_SEARCH_API:: " + PRODUCT_SEARCH_API);

		Utility::CustomMessageBox("ProductSearch::PLMSearch() parameter - " + parameter);
		string response = RestCall(parameter, PRODUCT_SEARCH_API);
		Utility::CustomMessageBox("PLMSearch response:: " + response);
		Utility::Logger("PLMSearch response:: " + response);
		json responseJson;
		string errorResponse = Utility::CheckErrorDescription(response);
		Utility::Logger("ProductSearch::PLMSearch() errorResponse:: " + errorResponse);

		if (errorResponse.empty() && (errorResponse.length() == 0))
		{
			responseJson = Utility::GetResultsJSON(response);
			CreateResultTable(responseJson);
		}
		else
		{
			UTILITY_API->DisplayMessageBox(errorResponse);
		}
		Utility::Logger("ProductSearch -> PLMSearch() -> End");
	}
	/**
	 * \brief Function is used to get header columns of result table
	 * \param list
	 */
	map<string, string> ProductSearch::GetFieldUITypes() {

		Utility::Logger("ProductSearch -> GetFieldUITypes() -> Start");

		json jsonString;
		map<string, string> fields;
		ifstream filename;
		filename.open(DirectoryUtil::getProdSearchFilteredJson());
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
			Utility::ErrorLogger("ProductSearch -> GetFieldUITypes()::parsing completeJson exception - " + string(e.what()));
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
		Utility::Logger("ProductSearch -> GetFieldUITypes() -> End");
		return fields;
	}
	/**
	* \brief Creating Result Table based on response
	* \param responseJson
	*/
	void ProductSearch::CreateResultTable(json responseJson) 
	{
		Utility::Logger("ProductSearch -> createResultTable() -> Start");

		const char* newDirPath = Configuration::GetInstance()->PRODUCTS_TEMP_DIRECTORY.c_str();
		mkdir(newDirPath);
		json completeStylesJson;

		map<string, string> fieldUITypeMap = GetFieldUITypes();
		ProductResultTable::setHeaderColumns(m_indexColumnIdMap);
		ProductResultTable::setResultTableColumns(m_attributeMap);

		string responseJsonStrStyle = responseJson["entities"].dump();
		try {
			completeStylesJson = json::parse(responseJsonStrStyle);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("ProductSearch -> createResultTable()::parsing completeStylesJson exception - " + string(e.what()));
			throw e.what();
		}
		string responseJsonsize = to_string(completeStylesJson.size());
		string responseString = "";
		ProductResultTable productResultTableobj;
		int checkStyle = 0;
		if (completeStylesJson.size() != 0)
		{
			json styles, columns;
			string entityJson;
			int rowCount = 0;
			QPixmap	NoImgpixmap;
			for (int i = 0; i < completeStylesJson.size(); i++)
			{
				entityJson = completeStylesJson[i].dump();
				try {
					styles = json::parse(entityJson);
				}
				catch (exception& e)
				{
					Utility::ErrorLogger("ProductSearch -> createResultTable()::parsing styles exception - " + string(e.what()));
					throw e.what();
				}
				string name = styles["name"].dump();
				name = name.erase(0, 1);
				name = name.erase(name.size() - 1);
				map<string, string> fieldValueMap;
				fieldValueMap.clear();
				string column, styleId, styleCode, rowVersionText;
				if (name == "Style")
				{
					checkStyle = checkStyle++;
					column = styles["column"].dump();
					try {
						columns = json::parse(column);
					}
					catch (exception& e)
					{
						Utility::ErrorLogger("ProductSearch -> createResultTable()::parsing columns exception - " + string(e.what()));
						throw e.what();
					}
					styleId = columns["StyleId"].dump();

					styleCode = columns["StyleCode"].dump();
					styleCode = styleCode.erase(0, 1);
					styleCode = styleCode.erase(styleCode.size() - 1);

					rowVersionText = columns["RowVersionText"].dump();
					if (rowVersionText == "null")
					{
						fieldValueMap.insert(make_pair("RowVersionText", ""));
					}
					else
					{
						rowVersionText = rowVersionText.erase(0, 1);
						rowVersionText = rowVersionText.erase(rowVersionText.size() - 1);
						fieldValueMap.insert(make_pair("RowVersionText", rowVersionText));
					}
					fieldValueMap.insert(make_pair("StyleId", styleId));
					for (auto key = m_indexColumnIdMap.begin(); key != m_indexColumnIdMap.end(); ++key) {
						string columnValue = Utility::getValue(columns[key->second]);

						if (fieldUITypeMap.at(key->second) == "dropdown") {
							columnValue = Utility::getValue(columns[key->second + "_Lookup"]["Name"]);
						}
						
						fieldValueMap.insert(make_pair(key->second, columnValue));
					}
					m_downloadAttachmentsMap = CreateDownloadAttachmentsMap(stoi(styleId), "E0013");
					m_downloadImagesMap = CreateDownloadAttachmentsMap(stoi(styleId), "E0012");
					DownloadStyleAttachments();
					DownloadStyleImages();

					QPixmap pixmap;
					QImage styleIcon;
					string thumbnail = m_imageURL.toStdString();

					if (m_imageName != "null")
					{
						string imageFileName = m_imageName.toStdString();
						string upperImageFileName = imageFileName;
						std::for_each(upperImageFileName.begin(), upperImageFileName.end(), [](char& c) {
							c = ::toupper(c);
							});
						size_t foundPng = upperImageFileName.find(".PNG");
						size_t foundJpg = upperImageFileName.find(".JPG");
						size_t foundJpeg = upperImageFileName.find(".JPEG");
						QImage styleIcon;
						bool isImageFormatSupported = false;
						if (foundPng != string::npos)
						{
							isImageFormatSupported = true;
						}
						if (foundJpg != string::npos)
						{
							isImageFormatSupported = true;
						}
						if (foundJpeg != string::npos)
						{
							isImageFormatSupported = true;
						}

						//No need to download the attachments if image format is not supported.
						//currently png, jpg and jpeg formats are supported.
						if (isImageFormatSupported)
						{
							imageFileName = Utility::RemoveInvalidFileNameChars(imageFileName);
							Utility::DownloadImageFromURL(thumbnail, Configuration::GetInstance()->PRODUCTS_TEMP_DIRECTORY + imageFileName);
							Utility::CustomMessageBox("imageFileName::" + imageFileName);

							QImageReader imageReader(QString::fromStdString(Configuration::GetInstance()->PRODUCTS_TEMP_DIRECTORY + imageFileName));
							imageReader.setDecideFormatFromContent(true);
							styleIcon = imageReader.read();
							bstyleImage = true;

							if (styleIcon.isNull())
							{
								Utility::Logger("ProductSearchDialog -> CreateResultTable() Image is not loaded.  ");
							}
							else
							{
								pixmap = QPixmap::fromImage(styleIcon);
							}
						}
					}					
					string mainImage = columns["DefaultAttachment"]["CFilename"].dump();
					mainImage.erase(std::remove(mainImage.begin(), mainImage.end(), '"'), mainImage.end());

					fieldValueMap.insert(make_pair("imageFileName", m_imageName.toStdString()));
					fieldValueMap.insert(make_pair("imageAttaFileListId", m_imageAttaFileListId.toStdString()));
					fieldValueMap.insert(make_pair("StyleAtachment", bstyleAttachment ? "true" : "false"));
					fieldValueMap.insert(make_pair("StyleImage", bstyleImage ? "true" : "false"));
					fieldValueMap.insert(make_pair("attachmentFileName", m_attachmentsName.toStdString()));
					fieldValueMap.insert(make_pair("attachmentFileURL", m_attachmentsURL.toStdString()));
					fieldValueMap.insert(make_pair("attachmentAttaFileListId", m_attachmentsAttaFileListId.toStdString()));
					fieldValueMap.insert(make_pair("mainImage", mainImage));
					rowCount++;
					if (!pixmap.isNull()) 
					{
						productResultTableobj.AddRowData(fieldValueMap, pixmap);
					}
					else 
					{
						NoImgpixmap = Utility::getNoImageAvailable();
						productResultTableobj.AddRowData(fieldValueMap, NoImgpixmap);
					}
				}
			}
		
			if (checkStyle == 0)
			{
				UTILITY_API->DisplayMessageBox("No result found ");
				this->show();

			}
			else if (rowCount > GetMaxResultsCount())
			{
				UTILITY_API->DisplayMessageBox("Number of records are exceeding the maximum limit. Please refine your search criteria.");
				this->show();
			}
			else
			{
				productResultTableobj.setModal(true);
				productResultTableobj.exec();
			}
			
		}
		else 
		{
			UTILITY_API->DisplayMessageBox("No result found ");
			this->show();
		}

		Utility::Logger("ProductSearch -> CreateResultTable() -> End");
	}
	/*
	*brief read the json file to get maximum number of rows to be displayed on the result table
	*retunr int: number of rows 
	*/ 
	int ProductSearch::GetMaxResultsCount()
	{
		json fabricJson, entityData, styles;
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
			Utility::ErrorLogger("ProductSearch::GetMaxResultsCount()::parsing entityData exception - " + string(e.what()));
			throw e.what();
		}
		if (entityData.size() != 0) {
			for (int i = 0; i < entityData.size(); i++)
			{
				string entityJson = entityData[i].dump();
				try {
					styles = json::parse(entityJson);
				}
				catch (exception & e)
				{
					Utility::ErrorLogger("ProductSearch::GetMaxResultsCount()::parsing styles exception - " + string(e.what()));
					throw e.what();
				}
				string name = styles["name"].dump();
				name = name.erase(0, 1);
				name = name.erase(name.size() - 1);

				if (name == "Product")
				{
					string maxRows = styles["maxResultCount"].dump();
					maxNoOfRows = stoi(maxRows);
				}
			}
		}
		return maxNoOfRows;
	}

	/*
	*brief create the parameters to download product attachment
	*params: styleID
	*/
	json ProductSearch::CreateDownloadAttachmentsMap(int styleID, string code)
	{
		Utility::Logger("ProductSearch -> CreateDownloadAttachmentsMap() -> Start");
		json filterMap;
		json downloadMap = json::object();
		json pageInfoMap;
		json conditions = json::object();
		downloadMap.clear();
		downloadMap["roleId"] = 1;
		downloadMap["userId"] = Configuration::GetInstance()->GetUserId();
		downloadMap["schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
		downloadMap["entity"] = "StyleAttachments";
		downloadMap["pageType"] = "list";
		downloadMap["personalizationId"] = 0;
		downloadMap["pageInfo"] = nullptr;
		downloadMap["sortInfo"] = nullptr;
		filterMap.clear();
		filterMap["fieldname"] = "IsDeleted";
		filterMap["operator"] = "=";
		filterMap["value"] = 0;
		conditions["Conditions"][0] = filterMap;
		filterMap.clear();
		filterMap["fieldname"] = "Code";
		filterMap["operator"] = "=";
		filterMap["value"] = code;
		filterMap["logicalOperator"] = "AND";
		conditions["Conditions"][1] = filterMap;
		filterMap.clear();
		filterMap["fieldname"] = "ReferenceId";
		filterMap["operator"] = "=";
		filterMap["value"] = styleID;
		filterMap["logicalOperator"] = "AND";
		conditions["Conditions"][2] = filterMap;
		downloadMap["dataFilter"] = conditions;

		Utility::Logger("ProductSearch -> CreateDownloadAttachmentsMap() -> End");
		return downloadMap;
	}

	/*
	*brief Downloads style attachments (zprj files)
	*/
	void ProductSearch::DownloadStyleAttachments()
	{
		Utility::Logger("ProductSearch -> DownloadStyleAttachments() -> Start");

		Utility::Logger("ProductSearch -> DownloadStyleAttachments() -> m_downloadAttachmentsMap:: "+ to_string(m_downloadAttachmentsMap));
		Utility::Logger("ProductSearch -> DownloadStyleAttachments() -> PRODUCT_ATTCHMENT_API:: " + PRODUCT_ATTCHMENT_API);
		string response = RestCall(to_string(m_downloadAttachmentsMap), PRODUCT_ATTCHMENT_API);
		Utility::Logger("ProductSearch -> DownloadStyleAttachments() -> response:: " + response);

		Utility::CustomMessageBox("response:: " + response);

		json responseJson;
		string errorResponse = Utility::CheckErrorDescription(response);
		if (errorResponse.empty())
		{
			responseJson = Utility::GetResultsJSON(response);
			GetStyleAttachments(responseJson);
		}
		else
		{
			UTILITY_API->DisplayMessageBox(errorResponse);
			Utility::Logger("ProductResultTable -> DownloadStyleAttachments() ->" + errorResponse);
		}

		Utility::Logger("ProductSearch -> DownloadStyleAttachments() -> End");
	}
	void ProductSearch::DownloadStyleImages()
	{
		Utility::Logger("ProductSearch -> DownloadStyleImages() -> Start");

		Utility::Logger("ProductSearch -> DownloadStyleImages() -> m_downloadImagesMap:: " + to_string(m_downloadImagesMap));
		Utility::Logger("ProductSearch -> DownloadStyleImages() -> PRODUCT_ATTCHMENT_API:: " + PRODUCT_ATTCHMENT_API);

		string response = RestCall(to_string(m_downloadImagesMap), PRODUCT_ATTCHMENT_API);
		Utility::Logger("ProductSearch -> DownloadStyleImages() -> response:: " + response);

		Utility::CustomMessageBox("response:: " + response);

		json responseJson;
		string errorResponse = Utility::CheckErrorDescription(response);
		if (errorResponse.empty())
		{
			responseJson = Utility::GetResultsJSON(response);
			GetStyleImages(responseJson);
		}
		else
		{
			UTILITY_API->DisplayMessageBox(errorResponse);
			Utility::Logger("ProductResultTable -> DownloadStyleImages() ->" + errorResponse);
		}

		Utility::Logger("ProductSearch -> DownloadStyleImages() -> End");
	}
	/**
	 * \brief Collects attachements of style from json
	 * \param response
	 */
	void ProductSearch::GetStyleAttachments(json response)
	{
		Utility::Logger("ProductSearch -> GetStyleAttachments() -> Start");
		
		string column, attachmentURL, attachmentName,attaFileListId;
		json completeStylesJson;
		string responseJsonStrStyle = response["entities"].dump();
		try {
			completeStylesJson = json::parse(responseJsonStrStyle);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("ProductSearch -> GetStyleAttachments()::parsing completeStylesJson exception - " + string(e.what()));
			throw e.what();
		}
		Utility::CustomMessageBox("ProductSearch::GetStyleAttachments responseJsonStrStyle::" + responseJsonStrStyle);
		string responseJsonsize = to_string(completeStylesJson.size());
		Utility::CustomMessageBox("ProductSearch::GetStyleAttachments responseJsonsize::" + responseJsonsize);
		if (completeStylesJson.size() > 2)
		{
			Utility::CustomMessageBox("Multiple attachments size::" + responseJsonsize);//@ToDo
			//throw "Styles with multiple 3D Design attachments are not supported";
		}
		Utility::CustomMessageBox("responseJsonsize downloadded ::" + to_string(completeStylesJson));// not // required for multiple attachments
		string responseString = "";
		bool attachmentsPresent = false;
		m_attachmentsURL = "";
		m_attachmentsName = "";
		m_attachmentsAttaFileListId = "";
		if (completeStylesJson.size() >= 1) // required for multiple attachments
		{
			json styles, columns;
			for (int i = 0; i < completeStylesJson.size(); i++)
			{
				string entityJson = completeStylesJson[i].dump();
				try {
					styles = json::parse(entityJson);
				}
				catch (exception& e)
				{
					Utility::Logger("ProductSearch -> GetStyleAttachments()::parsing styles exception - " + string(e.what()));
					throw e.what();
				}
				string name = styles["name"].dump();
				name = name.erase(0, 1);
				name = name.erase(name.size() - 1);
				if (name == "StyleAttachments")
				{
					column = styles["column"].dump();
					try {
						columns = json::parse(column);
					}
					catch (exception& e)
					{
						Utility::ErrorLogger("ProductSearch -> GetStyleAttachments()::parsing columns exception - " + string(e.what()));
						throw e.what();
					}
					attachmentURL = columns["CFilename"].dump(); //m_attachmentsNameList
					if (attachmentURL != "Null")
					{
						attachmentURL = attachmentURL.erase(0, 1);
						attachmentURL = attachmentURL.erase(attachmentURL.size() - 1);
						attachmentName = columns["OFilename"].dump();
						Utility::CustomMessageBox("m_attachmentsFileName::" + attachmentName);
						if (attachmentName != "Null")
						{
							attachmentName = attachmentName.erase(0, 1);
							attachmentName = attachmentName.erase(attachmentName.size() - 1);
						}
						Utility::CustomMessageBox("CFilename::" + attachmentURL);
						attaFileListId = columns["AttaFileListId"].dump();
						
					}
					else
					{
						attachmentURL = "";
					}
					m_attachmentsURL = QString::fromStdString(attachmentURL);
					m_attachmentsName = QString::fromStdString(attachmentName);
					m_attachmentsAttaFileListId = QString::fromStdString(attaFileListId);
					
				}
				
			}
		}
		Utility::Logger("ProductSearch -> getStyleAttachments() -> End");
	}
	/**
	 * \brief Collects attachements of style from json
	 * \param response
	 */
	void ProductSearch::GetStyleImages(json response)
	{
		Utility::Logger("ProductSearch -> GetStyleImages() -> Start");
		string attachmentName = m_attachmentsName.toStdString();
		int indexForJSON = attachmentName.find(".zprj");
		attachmentName = attachmentName.substr(0, indexForJSON);

		string column, imageURL, imageName, imgFileListId;
		json completeStylesJson;
		string responseJsonStrStyle = Utility::GetJSONValue<string>(response, "entities", false);
		try {
			completeStylesJson = json::parse(responseJsonStrStyle);
		}
		catch (exception & e)
		{
			throw e.what();
		}
		json styles, columns;
		m_imageURL = "";
		m_imageName = "";
		m_imageAttaFileListId = "";
		for (int i = 0; i < completeStylesJson.size(); i++)
		{
			string entityJson = Utility::GetJSONValue<int>(completeStylesJson, i, false);
			try {
				styles = json::parse(entityJson);
			}
			catch (exception & e)
			{
				throw e.what();
			}
			string name = Utility::GetJSONValue<string>(styles, "name", true);
			if (name == "StyleAttachments")
			{
				column = Utility::GetJSONValue<string>(styles, "column", false);
				try {
					columns = json::parse(column);
				}
				catch (exception & e)
				{
					throw e.what();
				}
				imageName = Utility::GetJSONValue<string>(columns, "OFilename",true);
				Utility::CustomMessageBox("m_attachmentsFileName::" + imageName);
				
				if (!attachmentName.empty() && !imageName.empty() && imageName.find(attachmentName) != string::npos) {

					imageURL = Utility::GetJSONValue<string>(columns, "CFilename", true);
					Utility::CustomMessageBox("CFilename::" + imageURL);
					imgFileListId = Utility::GetJSONValue<string>(columns, "AttaFileListId", false);
					m_imageURL = QString::fromStdString(imageURL);
					m_imageName = QString::fromStdString(imageName);
					m_imageAttaFileListId = QString::fromStdString(imgFileListId);
					break;
				}
			}
		}
		Utility::Logger("ProductSearch -> getStyleAttachments() -> End");
	}
	/**
	* \brief On Cancel Clicked, closing Product Search UI
	*/
	void ProductSearch::Cancel_clicked()
	{
		Utility::Logger("ProductSearch -> CancelClicked() -> Start");
		for each(auto field in m_searchFieldsVector)
		{
			field.userInputValues.clear();
		}
		this->close();

		Utility::Logger("ProductSearch -> CancelClicked() -> End");
	}
	/** 
	* \brief On back Clicked, coming back to Design suite
	*/
	void ProductSearch::backclicked()
	{
		Utility::Logger("ProductSearch -> BackClicked() -> Start");
		this->hide();
		DesignSuite::GetInstance()->setModal(true);
		DesignSuite::GetInstance()->show();
		Utility::Logger("ProductSearch -> BackClicked() -> End");
	}
}