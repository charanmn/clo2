#pragma once
#include "TrimsSearch.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QCheckBox>
#include <any>
#include <optional>
#include "qlistview.h"
#include "classes/APIDefine.h"
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"
#include "CLO_PLUGIN/INFOR/Utilities/Definitions.h" 
#include "CLO_PLUGIN/INFOR/DesignSuite/DesignSuite.h"
#include "TrimsResultTable.h"
#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "ws2_32.lib")
#include "CLO_PLUGIN/INFOR/Libraries/curl/include/curl/curl.h"
#include <iostream>
#include <direct.h>
#include "CLO_PLUGIN/INFOR/Utilities/Configuration.h"
#include "CLO_PLUGIN/INFOR/Utilities/ComboBoxItem.h"
#include "CLO_PLUGIN/INFOR/Utilities/RestAPIUtility.h"
#include "CLO_PLUGIN/INFOR/Utilities/DirectoryUtil.h"
/**
 *  making use of json and mapjson from nlohmann json
 */
using json = nlohmann::json;
using namespace std;
using mapjson = nlohmann::json;
bool trimImageAtt = false;
bool trimzfabAtt = false;
/**
 *  CLOPlugin namespace is used to keep all the functions in this class to be under CLOPlugin namespace.
 */
namespace CLOPlugin
{
	TrimsSearch* TrimsSearch::_instance = NULL;
	
	/**
	 * \brief Method gets the instance of this class
		if the instance is already existing, it returns the same instance
	 * \param void
	 * \return instance of the class TrimsSearch
*/
	TrimsSearch* TrimsSearch::GetInstance()
	{
		Utility::Logger("TrimsSearch -> GetInstance() -> Start");
		if (_instance == NULL)
		{
			_instance = new TrimsSearch();
		}
		Utility::Logger("TrimsSearch -> GetInstance() -> End");
		return _instance;
	}
	/**
		 * \brief Method deletes the instance of this class
		* \param void
		 * \return void
	*/
	void TrimsSearch::Destroy()
	{
		Utility::Logger("TrimsSearch -> Destroy() -> Start");
		if (_instance)
		{
			delete _instance;
			_instance = NULL;
		}
		Utility::Logger("TrimsSearch -> Destroy() -> End");
	}
	/**
		 * \brief Method clears all the input fields in the trims search dialog.
		* \param void
		 * \return void
	*/
	void TrimsSearch::ClearAllFields()
	{
		Utility::Logger("TrimsSearch -> ClearAllFields() -> Start");
		for (int i = 0; i < TrimsSearchTree->topLevelItemCount(); ++i)
		{
			QTreeWidgetItem* topItem = TrimsSearchTree->topLevelItem(i);
			QWidget* qWidgetColumn0 = TrimsSearchTree->itemWidget(topItem, 0);
			QWidget* qWidgetColumn1 = TrimsSearchTree->itemWidget(topItem, 1);
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
		Utility::Logger("TrimsSearch -> ClearAllFields() -> End");
	}
	/**
	 * \brief Trims search constructor. It has Qt UI related settings to the trims search dialog
		also it contains signals and slots connections
	 * \param inputs: QWidget and WindowFlags
	 **/
	TrimsSearch::TrimsSearch(QWidget* parent) : QDialog(parent)
	{
		Utility::Logger("TrimsSearch -> Constructor() -> Start");
		setupUi(this);
		QTreeWidgetItem* dataItem = new QTreeWidgetItem;
		Qt::ItemFlags flags;
		flags = dataItem->flags();
		flags |= Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
		dataItem->setFlags(flags);
		QFont fontStyle("Times new roman", FONT_SIZE, QFont::Bold);
		this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
		QSize size(TABLE_WIDTH, TABLE_HEIGHT);
		TrimsSearchTree->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		TrimsSearchTree->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

		TrimsSearchTree->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
		TrimsSearchTree->setSelectionBehavior(QAbstractItemView::SelectItems);
		TrimsSearchTree->setSelectionMode(QAbstractItemView::NoSelection);
		TrimsSearchTree->setSelectionBehavior(QAbstractItemView::SelectRows);
		TrimsSearchTree->setEditTriggers(QAbstractItemView::CurrentChanged);
		TrimsSearchTree->setTabKeyNavigation(true);

		TrimsSearchTree->setStyleSheet("QTreeWidget::item { border-bottom: 1px solid #232323;""padding : 10px;""height: 25px;""}");
		TrimsSearchTree->setFixedSize(size);
		TrimsSearchTree->setColumnWidth(1, USER_INPUT_WIDTH);
		TrimsSearchTree->setColumnWidth(0, SEARCH_LABEL_WIDTH);
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
		m_isOnlyPercentileFound = false;
		m_isVisibleAvailable = false;
		m_attachmentExists = false;
		FilterDependencyList();
		ReadPLMJson();
		ReadJsonAndDrawDialog();
		SetDefaultPresetValues();
		Utility::Logger("TrimsSearch -> Constructor() -> End");
	}
	/**
		 * \brief : this method reads the JSON file and fills the trims field vector
		 * \param : void
		 * \return : void
	 **/
	void TrimsSearch::ReadJsonAndDrawDialog()
	{
		Utility::Logger("TrimsSearch -> ReadJsonAndDrawDialog() -> Start");
		m_trimSearchFieldsVector = Utility::ReadJsonForDrawDialogue("Trim");
		DrawWidget(m_trimSearchFieldsVector);
		Utility::Logger("TrimsSearch -> ReadJsonAndDrawDialog() -> End");
	}
	/**
		 * \brief : this method draws the widgets on the trims search dialog based on trims field vector
		 * \param : Vector of type Utility fields
		 * \return : void
	 **/
	void TrimsSearch::DrawWidget(std::vector<Utility::Fields>& fieldsVector)
	{
		Utility::Logger("TrimsSearch -> DrawWidget() -> Start");
		json keyValuePairs = Utility::GetKeyValuePairs();

		for each (auto field in fieldsVector)
		{
			string tempLabel = field.labelValue.toStdString();

			if (m_attributeMap.find(tempLabel) != m_attributeMap.end()) {
				tempLabel = m_attributeMap.at(tempLabel);
			}
			else {
				QString displayValue = Utility::GetDisplayValueByKey(QString::fromStdString(tempLabel), QString::fromStdString("trim"), keyValuePairs);
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
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();  	// Adding Tree widget
				QLineEdit* LineEdit = new QLineEdit();
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);
				label->setProperty("Id", field.labelValue);
				label->setText(QString::fromStdString(tempLabel));
				LineEdit->setStyleSheet(inputStyle);
				TrimsSearchTree->addTopLevelItem(topLevel);						// Adding ToplevelItem
				TrimsSearchTree->setItemWidget(topLevel, 0, label);				// Adding label at column 1
				TrimsSearchTree->setItemWidget(topLevel, 1, LineEdit);
			}
			if (field.fieldUItype == "dropdown")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();
				QComboBox* ComboBox = new QComboBox(this);
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);								// Setting created font trim to label
				label->setText(QString::fromStdString(tempLabel));
				ComboBox->setStyleSheet(inputStyle);

				TrimsSearchTree->addTopLevelItem(topLevel);
				TrimsSearchTree->setItemWidget(topLevel, 0, label);
				TrimsSearchTree->setItemWidget(topLevel, 1, ComboBox);

				ComboBox->setStyleSheet("font: 75 8pt \"Tahoma\"; combobox-popup:0");
				ComboBox->addItems(field.presetValues);
				int indexOfEmptyString = ComboBox->findText("Select");
				ComboBox->setCurrentIndex(indexOfEmptyString); //Setting the current index.

				ComboBox->setProperty("Id", QString::fromStdString(tempLabel));
				QObject::connect(ComboBox, SIGNAL(currentIndexChanged(const QString&)), this,
					SLOT(handleDropDownValueChangeEvent(const QString&)));

			}
			if (field.fieldUItype == "textarea")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();  // Creating new TreeWidgetItem
				QTextEdit* TextEdit = new QTextEdit();						// Creating new LineEdit Widget
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);
				label->setProperty("Id", field.labelValue);
				label->setText(QString::fromStdString(tempLabel));
				label->setText(field.labelValue);
				TrimsSearchTree->addTopLevelItem(topLevel);						// Adding ToplevelItem
				TrimsSearchTree->setItemWidget(topLevel, 0, label);				// Adding label at column 1
				TrimsSearchTree->setItemWidget(topLevel, 1, TextEdit);
				TextEdit->setText(field.userInputValues);
				TextEdit->setStyleSheet("border: 1px solid black;""background-color: #222222;""font: 75 8pt \"Times New Roman\";");
				TextEdit->setMaximumSize(TEXTEDIT_SIZE_WIDTH, TEXTEDIT_SIZE_HEIGHT);
			}
			if (field.fieldUItype == "DateEdit")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();
				QDateEdit* DateTimeEdit = new QDateEdit();
				bool enable = true;
				DateTimeEdit->setCalendarPopup(enable);			// Setting Popup Calendar for Date time picker.
				QString dataricovero("");
				QDate date = QDate::fromString(dataricovero, "");
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);
				label->setProperty("Id", field.labelValue);
				label->setText(QString::fromStdString(tempLabel));
				DateTimeEdit->setStyleSheet(inputStyle);
				TrimsSearchTree->addTopLevelItem(topLevel);
				TrimsSearchTree->setItemWidget(topLevel, 0, label);
				TrimsSearchTree->setItemWidget(topLevel, 1, DateTimeEdit);
			}
		}
		Utility::Logger("TrimsSearch -> DrawWidget() -> End");
	}
	/**
		 * \brief  destructortor of Trims search class
		 deletes the object of this class.
	 */
	TrimsSearch::~TrimsSearch()
	{

	}

	/**
	* Function is used to handle change event of dropdown widgets
	*/
	void TrimsSearch::handleDropDownValueChangeEvent(const QString& item)
	{
		Utility::Logger("TrimsSearch -> handleDropDownValueChangeEvent() -> Start");

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
			for (auto it = m_LookUpRefLookUpNameOrgIdMap.begin(); it != m_LookUpRefLookUpNameOrgIdMap.end(); it++)
			{
				auto val = it->second;
				auto firstVal = val.first;
				if (firstVal == item.toStdString() && it->first == senderCombo.toStdString()) {
					orgID = val.second;
					Utility::Logger("foundItem secVal::" + orgID);
					break;
				}
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
				for (auto& i : m_GlVNameOrgIDMap)
				{
					if (i.second == childrenOrgIds.at(count).toStdString())
					{
						childrenNames.push_back(QString::fromStdString(i.first));
					}
				}
			}

			for (int i = 0; i < TrimsSearchTree->topLevelItemCount(); ++i)
			{
				QTreeWidgetItem* topItem = TrimsSearchTree->topLevelItem(i);
				QWidget* qWidgetColumn0 = TrimsSearchTree->itemWidget(topItem, 0);
				QWidget* qWidgetColumn1 = TrimsSearchTree->itemWidget(topItem, 1);
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
		else if (item == "Select")
		{
			for (int i = 0; i < TrimsSearchTree->topLevelItemCount(); ++i)
			{
				QTreeWidgetItem* topItem = TrimsSearchTree->topLevelItem(i);
				QWidget* qWidgetColumn0 = TrimsSearchTree->itemWidget(topItem, 0);
				QWidget* qWidgetColumn1 = TrimsSearchTree->itemWidget(topItem, 1);
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

		Utility::Logger("TrimsSearch -> handleDropDownValueChangeEvent() -> End");
	}
	void TrimsSearch::SetDefaultPresetValues()
	{
		Utility::Logger("TrimsSearch -> SetDefaultPresetValues() -> Start");
		for (int i = 0; i < TrimsSearchTree->topLevelItemCount(); ++i)
		{
			QTreeWidgetItem* topItem = TrimsSearchTree->topLevelItem(i);
			QWidget* qWidgetColumn0 = TrimsSearchTree->itemWidget(topItem, 0);
			QWidget* qWidgetColumn1 = TrimsSearchTree->itemWidget(topItem, 1);
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
		Utility::Logger("TrimsSearch -> SetPresetValues() -> End");
	}

	/**
	* Method is used to call rest api and filter records for field dependencies
	*/
	void TrimsSearch::FilterDependencyList()
	{
		Utility::Logger("TrimsSearch -> FilterDependencyList() -> Start");
		
		string entityJson;
		QStringList dependencyList;
		QString dependencyItem;
		json dependencyJson = SetDependenciesToWidgets();
		string entities = dependencyJson["entities"].dump();
		json completeEntitiesJson;
		try {
			completeEntitiesJson = json::parse(entities);
		}
		catch (exception & e)
		{
			Utility::ErrorLogger("TrimSearch::FilterDependencyList()::parsing completeEntitiesJson exception - " + string(e.what()));
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
				catch (exception & e)
				{
					Utility::ErrorLogger("TrimSearch::FilterDependencyList()::parsing trim exception - " + string(e.what()));
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
					catch (exception & e)
					{
						Utility::ErrorLogger("TrimSearch::FilterDependencyList()::parsing columns exception - " + string(e.what()));
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
					string LookupRefKey = columns["LookupRef"].dump();

					LookupRef = LookupRef.erase(0, 1);
					LookupRef = LookupRef.erase(LookupRef.size() - 1);

					m_parentIDOrgIDMap.insert(std::make_pair(ParentId, OrgLevelId));
					string lookUpName = Utility::getLookUpName(dependencyJson, gLValueId, LookupRefKey);
					lookUpName = QString::fromUtf8(lookUpName.c_str()).toStdString();

					m_NameOrgIDMap.insert(std::make_pair(OrgLevelName, OrgLevelId));
					m_GlVNameOrgIDMap.insert(std::make_pair(lookUpName, OrgLevelId));
					m_LookUpRefLookUpNameOrgIdMap.insert(std::make_pair(LookupRef, std::make_pair(lookUpName, OrgLevelId)));

					if (LookupRef != "ul")
					{
						m_LookUpOrgNameGLValIDMap.insert(std::make_pair(LookupRef, std::make_pair(lookUpName, gLValueId)));
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

		Utility::Logger("TrimsSearch -> FilterDependencyList() -> End");
	}
	
/**
	 * \brief : this method creates a MAP based on user search criteria. Collects all the conditions given by the user and store it in the map. This map is used for searching.
	 For reference we are writing all the given conditions into a file.
	* \Param  : void
	 * \return : void
	 */
	void TrimsSearch::CreateSearchMap()
	{
		Utility::Logger("TrimsSearch -> CreateSearchMap() -> Start");
		ofstream trimsFile;
		trimsFile.open(DirectoryUtil::getTrimSearchJson());
		json emptyJsonObject;
		json filterMap;
		json conditions = json::object();
		m_TrimSearchMap["roleId"] = Configuration::GetInstance()->GetRoleId();
		m_TrimSearchMap["userId"] = Configuration::GetInstance()->GetUserId();
		m_TrimSearchMap["entity"] = "Trim";
		m_TrimSearchMap["Schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
		m_TrimSearchMap["fromAi"] = true;
		m_TrimSearchMap["pageType"] = "list";
		m_TrimSearchMap["sortInfo"] = emptyJsonObject;

		int count = Utility::CreateSearchCriteriaMap(conditions, m_trimSearchFieldsVector, m_attsDropdownListMap);
		
		filterMap.clear();
		filterMap["fieldname"] = "IsDeleted";
		filterMap["operator"] = "=";
		filterMap["value"] = 0;
		conditions["Conditions"][count++] = filterMap;
		conditions["Search"] = nullptr;
		m_TrimSearchMap["dataFilter"] = conditions;
		trimsFile << m_TrimSearchMap;
		trimsFile.close();
		Utility::Logger("TrimsSearch -> CreateSearchMap() -> End");
	}
	/**
	 * \brief : this method makes a rest call to read the data from the PLM. Based on search map from the createSearchMap method it reads the PLM.
	 Response given by REST call will be used to create the result table.
	* \Param  : void
	 * \return : void
	 */
	void TrimsSearch::PLMSearch()
	{
		Utility::Logger("TrimsSearch -> PLMSearch() -> Start");

		Utility::Logger("TrimsSearch -> PLMSearch() -> m_TrimSearchMap:: "+ to_string(m_TrimSearchMap));
		Utility::Logger("TrimsSearch -> PLMSearch() -> TRIMS_SEARCH_API:: " + TRIMS_SEARCH_API);
		string response = RestCall(to_string(m_TrimSearchMap), TRIMS_SEARCH_API);
		Utility::CustomMessageBox("response:: " + response);
		Utility::Logger("TrimsSearch::PLMSearch() response - " + response);
		json responseJson;
		string errorResponse = Utility::CheckErrorDescription(response);
		Utility::Logger("TrimsSearch -> PLMSearch() -> errorResponse:: " + errorResponse);

		if (errorResponse.empty() && (errorResponse.length() == 0))
		{
			responseJson = Utility::GetResultsJSON(response);
			Utility::Logger("TrimsSearch -> PLMSearch() -> responseJson:: " + to_string(responseJson));
			CreateResultTable(responseJson);
		}
		else
		{
			UTILITY_API->DisplayMessageBox(errorResponse);
		}
		Utility::Logger("TrimsSearch -> PLMSearch() -> End");
	}
	/**
	 * \brief :On click of search button this method extract all the search criteria  entered by the user then creates the search  map and based on search map it searches the values from the PLM.
	 From this PLM search it will create the result table.
	* \Param  : void
	 * \return : void
	 */
	void TrimsSearch::Search_clicked()
	{
		Utility::Logger("TrimsSearch -> Search_clicked() -> Start");

		if (Utility::ExtractAllUIValuesAndMapToJson(TrimsSearchTree, m_trimSearchFieldsVector) && Utility::SearchValidation(TrimsSearchTree))
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
		Utility::Logger("TrimsSearch -> Search_clicked() -> End");
	}
	/**
	 * \brief Function is used to get header columns of result table
	 * \param list
	 */
	map<string, string> TrimsSearch::GetFieldUITypes() {
		Utility::Logger("TrimsSearch -> GetFieldUITypes() -> Start");
		json jsonString;
		map<string, string> fields;
		ifstream filename;
		filename.open(DirectoryUtil::getTrimSearchFilteredJson());
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
			Utility::ErrorLogger("TrimsSearch -> GetFieldUITypes()::parsing completeJson exception - " + string(e.what()));
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
		Utility::Logger("TrimsSearch -> GetFieldUITypes() -> End");
		return fields;
	}
	/**
	 * \brief :This method creates the result table for selected trims.
	* \Param  : json file
	 * \return : void
	 */
	void TrimsSearch::CreateResultTable(json& responseJson)
	{
		Utility::Logger("TrimsSearch -> CreateResultTable() -> Start");
		const char* newDirPath = Configuration::GetInstance()->TRIMS_TEMP_DIRECTORY.c_str();
		mkdir(newDirPath);

		map<string, string> fieldUITypeMap = GetFieldUITypes();
		TrimsResultTable::SetHeaderColumns(m_indexColumnIdMap);
		TrimsResultTable::SetResultTableColumns(m_attributeMap);
		json completeEntitiesJson;
		string entities = responseJson["entities"].dump();
		try {
			completeEntitiesJson = json::parse(entities);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("TrimsSearch::CreateResultTable()::parsing completeEntitiesJson exception - " + string(e.what()));
			throw e.what();
		}
		TrimsResultTable trimResultsTableObject;
		bool isImage = false;
		bool isAttachment = false;
		if (completeEntitiesJson.size() != 0)
		{
			int rowCount = 0;
			json material, columns;
			QPixmap	NoImgpixmap;
			for (int i = 0; i < completeEntitiesJson.size(); i++)
			{
				string entityJson = completeEntitiesJson[i].dump();

				try {
					material = json::parse(entityJson);
				}
				catch (exception& e)
				{
					Utility::ErrorLogger("TrimsSearch::CreateResultTable():: parsing trim exception - " + string(e.what()));
					throw e.what();
				}
				string name = material["name"].dump();
				name = name.erase(0, 1);
				name = name.erase(name.size() - 1);
				map<string, string> fieldValueMap;
				string column, trimId, trimCode, thumbnail, filenameToSave;
				if (name == "Trim")
				{
					column = material["column"].dump();
					try {
						columns = json::parse(column);
					}
					catch (exception& e)
					{
						Utility::ErrorLogger("TrimsSearch::CreateResultTable()::parsing entityJson exception - " + string(e.what()));
						throw e.what();
					}
					trimId = columns["Id"].dump();
					
					trimCode = columns["Code"].dump();
					trimCode = trimCode.erase(0, 1);
					trimCode = trimCode.erase(trimCode.size() - 1);

					fieldValueMap.insert(make_pair("Id", trimId));

					for (auto key = m_indexColumnIdMap.begin(); key != m_indexColumnIdMap.end(); ++key) {
						string columnValue = Utility::getValue(columns[key->second]);

						if (fieldUITypeMap.at(key->second) == "dropdown") {
							columnValue = Utility::getValue(columns[key->second + "_Lookup"]["Name"]);
						}

						fieldValueMap.insert(make_pair(key->second, columnValue));
					}
					
					QPixmap pixmap;
					trimImageAtt = false;
					m_attachmentExists = false;
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
						QImage styleIcon;
						size_t foundPng = upperCaseThumb.find(".PNG");
						size_t foundJpg = upperCaseThumb.find(".JPG");
						size_t foundJpeg = upperCaseThumb.find(".JPEG");
						if (foundPng != string::npos)
						{
							filenameToSave = trimCode + ".png";
							isImageFormatSupported = true;
							Utility::CustomMessageBox("filenameToSave" + filenameToSave);
						}
						if (foundJpg != string::npos)
						{
							filenameToSave = trimCode + ".jpg";
							isImageFormatSupported = true;
							Utility::CustomMessageBox("filenameToSave" + filenameToSave);
						}
						if (foundJpeg != string::npos)
						{
							filenameToSave = trimCode + ".jpeg";
							isImageFormatSupported = true;
							Utility::CustomMessageBox("filenameToSave" + filenameToSave);
						}

						trimImageAtt = true;

						//No need to download the attachments if image format is not supported.
						//currently png, jpg and jpeg formats are supported.
						if (isImageFormatSupported) {
							Utility::DownloadImageFromURL(thumbnail, Configuration::GetInstance()->TRIMS_TEMP_DIRECTORY + filenameToSave);
							
							QImageReader imageReader(QString::fromStdString(Configuration::GetInstance()->TRIMS_TEMP_DIRECTORY + filenameToSave));
							imageReader.setDecideFormatFromContent(true);
							styleIcon = imageReader.read();

							if (styleIcon.isNull()) {
								Utility::Logger("TrimsSearchDialog -> CreateResultTable() Image is not loaded.  ");
							}
							else {
								pixmap = QPixmap::fromImage(styleIcon);
							}
						}
					}

					string attachedFileName = DownloadAtachment(trimId, trimCode);

					if (m_attachmentExists) {
						isImageFormatSupported = true;
					}

					fieldValueMap.insert(make_pair("trimImageName", filenameToSave));
					fieldValueMap.insert(make_pair("trimImage", trimImageAtt ? "true" : "false"));
					fieldValueMap.insert(make_pair("trimAttachment", m_attachmentExists ? "true" : "false"));
					fieldValueMap.insert(make_pair("imageSupported", isImageFormatSupported ? "true" : "false"));
					fieldValueMap.insert(make_pair("attachedFileName", attachedFileName));

					if (trimImageAtt || m_attachmentExists)
					{
						rowCount++;
						isImage = trimImageAtt;
						isAttachment = m_attachmentExists;
						if (!pixmap.isNull()) 
						{
							trimResultsTableObject.AddRowData(fieldValueMap, pixmap);
						}
						else 
						{
							NoImgpixmap = Utility::getNoImageAvailable();
							trimResultsTableObject.AddRowData(fieldValueMap, NoImgpixmap);
						}
						trimImageAtt = false;
						m_attachmentExists = false;
					}
				}
			}
			if (rowCount > m_maxRowCount)
			{
				UTILITY_API->DisplayMessageBox("Number of records are exceeding the maximum limit. Please refine your search criteria.");
				this->show();
			}
			else if (isImage || isAttachment)
			{
				trimResultsTableObject.setModal(true);
				trimResultsTableObject.exec();
			}
			else 
			{
				UTILITY_API->DisplayMessageBox("This record does not have an image or attachment");
				this->show();
			}
		}
		else
		{
			UTILITY_API->DisplayMessageBox("No result found");
			this->show();
		}
		Utility::Logger("TrimsSearch -> CreateResultTable() -> End");
	}

	/**
	 * \brief Downloads attachment using url from JSON
	 * \param trimId
	 * \param trimCode
	 */
	string TrimsSearch::DownloadAtachment(string trimId, string trimCode)
	{
		string fileNameStr;
		Utility::Logger("TrimsSearch -> DownloadAtachment() -> Start");

		json attachmentSearchMap;
		json filterMapAtt;
		json ConditionsAtt = json::object();

		attachmentSearchMap["roleId"] = Configuration::GetInstance()->GetRoleId();
		attachmentSearchMap["userId"] = Configuration::GetInstance()->GetUserId();
		attachmentSearchMap["entity"] = "TrimAttachments";
		attachmentSearchMap["Schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
		attachmentSearchMap["personalizationId"] = 0;
		attachmentSearchMap["pageType"] = "list";
		filterMapAtt["fieldname"] = "Code";
		filterMapAtt["operator"] = "=";
		filterMapAtt["value"] = "E0022";
		ConditionsAtt["Conditions"][0] = filterMapAtt;
		filterMapAtt.clear();
		filterMapAtt["fieldname"] = "IsDeleted";
		filterMapAtt["operator"] = "=";
		filterMapAtt["value"] = 0;
		ConditionsAtt["Conditions"][1] = filterMapAtt;
		filterMapAtt.clear();
		filterMapAtt["fieldname"] = "ReferenceId";
		filterMapAtt["operator"] = "=";
		filterMapAtt["value"] = trimId;
		ConditionsAtt["Conditions"][2] = filterMapAtt;
		filterMapAtt.clear();
		attachmentSearchMap["dataFilter"] = ConditionsAtt;
		attachmentSearchMap["pageInfo"] = nullptr;
		attachmentSearchMap["sortInfo"] = nullptr;

		Utility::Logger("TrimsSearch::DownloadAtachment -> attachmentSearchMap :: " + to_string(attachmentSearchMap));
		Utility::Logger("TrimsSearch::DownloadAtachment -> GET_ATTACHMENT_INFO_API :: " + GET_ATTACHMENT_INFO_API);
		string attResponse = RestCall(to_string(attachmentSearchMap), GET_ATTACHMENT_INFO_API);
		Utility::CustomMessageBox("attResponse:: " + attResponse);
		Utility::Logger("TrimsSearch::DownloadAtachment attResponse - " + attResponse);
		json responseJson;
		string errorResponse = Utility::CheckErrorDescription(attResponse);
		Utility::Logger("TrimsSearch::DownloadAtachment -> errorResponse :: " + errorResponse);
		if (errorResponse.empty() && (errorResponse.length() == 0))
		{
			responseJson = Utility::GetResultsJSON(attResponse);
			fileNameStr = GetTrimAttachments(responseJson, trimCode);

		}
		else
		{
			UTILITY_API->DisplayMessageBox(errorResponse);
		}
		Utility::Logger("TrimsSearch -> DownloadAtachment() -> End");

		return fileNameStr;
	}
	/**
	 * \brief Gets all trim attachments from JSON
	 * \param response
	 * \param trimCode
	 */
	string TrimsSearch::GetTrimAttachments(json response, string trimCode)
	{
		string fileNameStr;
		Utility::Logger("TrimsSearch -> GetTrimAttachments() -> Start");
		string attColumn, attachmentURL;
		json completeEnityJson;
		string responseJsonStrStyle = response["entities"].dump();
		try {
			completeEnityJson = json::parse(responseJsonStrStyle);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("TrimsSearch::GetTrimAttachments()::parsing completeEnityJson exception - " + string(e.what()));
			throw e.what();
		}
		string responseJsonSize = to_string(completeEnityJson.size());
		string responseString = "";
		if (completeEnityJson.size() > 2)
		{
			
		}
		else if (completeEnityJson.size() != 0)
		{
			json attachEntityJsonStr, columnsJson;
			string atachEntityJson;
			vector<string> fileFormats;
			stringstream fileStream(SUPPORTED_TRIM_FILE_FORMATS);

			while (fileStream.good()) {
				string fileFormat;
				getline(fileStream, fileFormat, ',');
				fileFormats.push_back(fileFormat);
			}

			for (int i = 0; i < completeEnityJson.size(); i++)
			{
				atachEntityJson = completeEnityJson[i].dump();
				try {
					attachEntityJsonStr = json::parse(atachEntityJson);

					attColumn = attachEntityJsonStr["column"].dump();
					columnsJson = json::parse(attColumn);
				}
				catch (exception& e)
				{
					Utility::ErrorLogger("TrimsSearch::GetTrimAttachments()::parsing columnsJson exception - " + string(e.what()));
					throw e.what();
				}
				string attachmentsFileName = columnsJson["OFilename"].dump();
				if (attachmentsFileName != "null")
				{
					attachmentsFileName = attachmentsFileName.erase(0, 1);
					attachmentsFileName = attachmentsFileName.erase(attachmentsFileName.size() - 1);

					QFileInfo fileInfo(QString::fromStdString(attachmentsFileName));
					string extension = fileInfo.suffix().toStdString();
					string formatMatch = extension;
					transform(formatMatch.begin(), formatMatch.end(), formatMatch.begin(), ::tolower);
					
					if (std::find(fileFormats.begin(), fileFormats.end(), formatMatch) != fileFormats.end()) {
						string attachmentUrl = columnsJson["CFilename"].dump();
						attachmentUrl = attachmentUrl.erase(0, 1);
						attachmentUrl = attachmentUrl.erase(attachmentUrl.size() - 1);
						string atachedFilenameToSave = trimCode + "." + extension;
						fileNameStr = atachedFilenameToSave;
						Utility::Logger("TrimSearch -> GetTrimAttachments() -> attachmentUrl:: " + attachmentUrl);
						Utility::DownloadFilesFromURL(attachmentUrl, DirectoryUtil::getTrimAssetsDirectory() + atachedFilenameToSave);
						int fileSize = Utility::GetFileSize(DirectoryUtil::getTrimAssetsDirectory() + atachedFilenameToSave);
						if (fileSize > 0)
							m_attachmentExists = true;
					}
				}
			}
		}
		Utility::Logger("TrimsSearch -> GetMaterialAttachments() -> End");

		return fileNameStr;
	}
	/**
	 * \brief On click of BACK button in the trims search dialog, it will navigate to the design suite dialog
	 * \input param:  void
	 * \return void
	 */	
	void TrimsSearch::back_clicked()
	{
		Utility::Logger("TrimsSearch -> back_clicked() -> Start");
		this->hide();
		DesignSuite::GetInstance()->setModal(true);
		DesignSuite::GetInstance()->show();
		Utility::Logger("TrimsSearch -> back_clicked() -> End");
	}
	/**
	 * \brief On click of Cancle button in the  trims search dialog , it will close the trims search dialog.
	 * \input param:  void
	 * \return void
	 */
	void TrimsSearch::Cancel_clicked()
	{
		Utility::Logger("TrimsSearch -> Cancel_clicked() -> Start");
		this->close();
		Utility::Logger("TrimsSearch -> Cancel_clicked() -> End");
	}


	/*
	*brief read the json file to get visible fields for color
	*retunr list of fields
	*/
	std::list<string> TrimsSearch::getVisibleFieldList() {
		Utility::Logger("TrimsSearch -> getVisibleFieldList() -> Start");
		json colorJson, entityData, colors;
		std::list<string> searchColumns;
		ifstream filename(DirectoryUtil::getCLOPLMPluginConfigJson());
		filename >> colorJson;
		filename.close();
		string entities = colorJson["entities"].dump();
		try {
			entityData = json::parse(entities);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("TrimsSearch::getVisibleFieldList()::parsing entityData exception - " + string(e.what()));
			throw e.what();
		}
		if (entityData.size() != 0) {
			for (int i = 0; i < entityData.size(); i++)
			{
				string entityJson = entityData[i].dump();
				try {
					colors = json::parse(entityJson);
				}
				catch (exception& e)
				{
					Utility::ErrorLogger("TrimsSearch::getVisibleFieldList()::parsing colors exception - " + string(e.what()));
					throw e.what();
				}
				string name = colors["name"].dump();
				name = name.erase(0, 1);
				name = name.erase(name.size() - 1);

				if (name == "Trim")
				{
					string searchable_columns = colors["searchable_columns"].dump();
					string maxRows = colors["maxResultCount"].dump();

					m_maxRowCount = stoi(maxRows);
					json colsJson;
					try {
						colsJson = json::parse(searchable_columns);
					}
					catch (exception& e)
					{
						Utility::ErrorLogger("TrimsSearch::getVisibleFieldList()::parsing colsJson exception - " + string(e.what()));
						throw e.what();
					}
					for (int j = 0; j < colsJson.size(); j++) {
						string column = colsJson[j];
						searchColumns.push_back("" + column);
					}

					string tenants = colors["tenants"].dump();
					json tenantsJson;
					try {
						tenantsJson = json::parse(tenants);
					}
					catch (exception& e)
					{
						Utility::ErrorLogger("TrimsSearch::getVisibleFieldList()::parsing tenantsJson exception - " + string(e.what()));
						throw e.what();
					}
					for (int j = 0; j < tenantsJson.size(); j++) {
						string tenant = tenantsJson[j];
						if (Configuration::GetInstance()->GetTenant() == tenant) {
							m_isVisibleAvailable = true;
						}
					}
				}
			}
		}
		Utility::Logger("TrimsSearch -> getVisibleFieldList() -> End");
		return searchColumns;
	}
	/**
	 * \brief This method reads the trimJSONDetails file and and based on some fields it filtered the large file into trimSearchFiltered json file.
	 Also decides the ordering of labels in the search dilalog.
	 * \input param:  void
	 * \return void
	 */
	void  TrimsSearch::ReadPLMJson()
	{
		Utility::Logger("TrimsSearch -> ReadPLMJson() -> Start");
		string parameter = "{\"roleId\":" + Configuration::GetInstance()->GetRoleId() + ",\"userId\":" + Configuration::GetInstance()->GetUserId() + ",\"entity\":\"Trim\",\"pageType\":\"details\",\"dataFilter\":{\"conditions\":[{\"fieldname\":\"Id\",\"operator\":\"=\",\"value\":\"\"}]},\"pageInfo\":{},\"Schema\":" + Configuration::GetInstance()->GetschemaWithQuotes() + "}";

		Utility::GetFilteredJson(parameter, TRIMS_SEARCH_API,"Trim");
		std::list<string> visibleColumns = getVisibleFieldList();
		json completeStyleJson;
		m_attsDropdownListMap.clear();
		m_attributeMap.clear();
		ifstream filename(DirectoryUtil::getTrimDetailJson());
		filename >> completeStyleJson;
		filename.close();
		ofstream newfile(DirectoryUtil::getPLMPluginDirectory() + "trimSearchFiltered.json");
		json finalJsontoSave;
		auto jsonFieldList = json::array();
		auto jsonUiTypeList = json::object();
		auto presetArray = json::array();
		auto presetList = json::object();
		auto jsonDataFieldList = json::object();
		auto jsonMandatoryFieldsList = json::array();
		int uiPresetCount = 0;
		string completeJsonString, componentsString, compObjString;
		json completeJson, componentsJson;
		completeJsonString = completeStyleJson.dump();
		try {
			completeJson = json::parse(completeJsonString);
			componentsString = completeJson["layout"]["components"].dump();
			componentsJson = json::parse(componentsString);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("TrimsSearch::ReadPLMJson()::parsing completeJson exception - " + string(e.what()));
			throw e.what();
		}
		json compObjJson, propsJson;
		string visible, propsString;
		for (int i = 0; i < componentsJson.size(); i++) 
		{
			compObjString = componentsJson[i].dump();
			try {
				compObjJson = json::parse(compObjString);
				propsString = compObjJson["props"].dump();
				propsJson = json::parse(propsString);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("TrimsSearch::ReadPLMJson()::parsing compObjString exception - " + string(e.what()));
				throw e.what();
			}
			bool attVisibilityCheck;
			string visible = propsJson["isVisibleAi"].dump();
			string dataField = compObjJson["dataField"].dump();
			dataField = dataField.erase(0, 1);
			dataField = dataField.erase(dataField.size() - 1);
			
			if (m_isVisibleAvailable) {
				if (visible == "true") {
					attVisibilityCheck = true;
				}
				else {
					attVisibilityCheck = false;
				}
			}
			else {
				if (std::find(visibleColumns.begin(), visibleColumns.end(), dataField) != visibleColumns.end()) {
					attVisibilityCheck = true;
				}
				else {
					attVisibilityCheck = false;
				}
			}
			
			
			if (attVisibilityCheck)
			{
				string isRequired = propsJson["isRequired"].dump();
				string tabIndex = propsJson["tabIndex"].dump();
				string fieldType = compObjJson["fieldType"].dump();
				fieldType = fieldType.erase(0, 1);
				fieldType = fieldType.erase(fieldType.size() - 1);
				string lookupRef = compObjJson["lookupRef"].dump();
				lookupRef = lookupRef.erase(0, 1);
				lookupRef = lookupRef.erase(lookupRef.size() - 1);

				string label = compObjJson["label"].dump();
				label = label.erase(0, 1);
				label = label.erase(label.size() - 1);
				
				m_indexColumnIdMap.insert(make_pair(std::stoi(tabIndex), dataField));
				jsonUiTypeList[dataField] = fieldType;
				jsonDataFieldList[dataField] = dataField;
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
						Utility::ErrorLogger("TrimsSearch::ReadPLMJson()::parsing lookupsJSON exception - " + string(e.what()));
						throw e.what();
					}
					map<string, string> tempAttribMap;
					Utility::GetDropDownMap(lookupsJSON, lookupRef, tempAttribMap/*, presetArray*/);
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
		auto newjsonFieldList = json::array();
		for (auto itr = m_indexColumnIdMap.begin(); itr != m_indexColumnIdMap.end(); itr++) {
			newjsonFieldList.push_back(itr->second);
		}
		
		finalJsontoSave["fieldList"] = newjsonFieldList; 
		finalJsontoSave["uiTypeList"] = jsonUiTypeList;
		finalJsontoSave["presetList"] = presetList;
		finalJsontoSave["mandatory_fieldList"] = jsonMandatoryFieldsList;
		finalJsontoSave["dataFieldList"] = jsonDataFieldList;
		newfile << finalJsontoSave;
		newfile.close();
		Utility::Logger("TrimsSearch -> ReadPLMJson() -> End");
	}

string TrimsSearch::GetDependencies()
	{

		Utility::Logger("TrimsSearch -> GetDependencies() -> Start");
		json dataFilterMap, conditionsMap, dependencyMap;
		conditionsMap["fieldname"] = "Id";
		conditionsMap["operator"] = "=";
		conditionsMap["value"] = "";
		dataFilterMap["conditions"][0] = conditionsMap;
		dependencyMap["dataFilter"] = dataFilterMap;
		dependencyMap["roleId"] = Configuration::GetInstance()->GetRoleId();
		dependencyMap["userId"] = Configuration::GetInstance()->GetUserId();
		dependencyMap["schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
		dependencyMap["entity"] = "Trim";
		dependencyMap["pageType"] = "details";
		dependencyMap["fromAi"] = true;

		Utility::Logger("TrimsSearch -> GetDependencies() -> dependencyMap:: " + to_string(dependencyMap));
		string response = RestCall(to_string(dependencyMap), TRIMS_DEPENDENCY_API);
		Utility::Logger("TrimsSearch::GetDependencies() response - " + response);
		Utility::Logger("TrimsSearch -> GetDependencies() -> End");

		return response;
	}
	
	/**
	 * \brief This method sets the dependencies to the widgets
		 * \return json
	 */
	json TrimsSearch::SetDependenciesToWidgets()
	{
		Utility::Logger("TrimsSearch -> SetDependenciesToWidgets() -> Start");
		string dependencies = GetDependencies();
		Utility::Logger("TrimsSearch -> SetDependenciesToWidgets() -> dependencies:: " + dependencies);
		string errorResponse = Utility::CheckErrorDescription(dependencies);
		Utility::Logger("TrimsSearch -> SetDependenciesToWidgets() -> errorResponse:: " + errorResponse);

		json dependencyJson;
		if (errorResponse.empty() && (errorResponse.length() == 0))
		{
			try
			{
				dependencyJson = json::parse(dependencies);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("TrimsSearch -> SetDependenciesToWidgets()::parsing dependencyJson exception - " + string(e.what()));
				throw e.what();
			}
			Utility::CustomMessageBox("setDependenciesToWidgets ::" + to_string(dependencyJson));
		}
		else
		{
			UTILITY_API->DisplayMessageBox(errorResponse);
		}
		Utility::Logger("TrimsSearch -> SetDependenciesToWidgets() -> End");

		return dependencyJson;
	}
	
}