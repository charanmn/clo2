#include "UpdateProduct.h"
#include "ui_UpdateProduct.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QCheckBox>
#include <any>
#include <optional>
#include "qlistview.h"
#include "CLO_PLUGIN/INFOR/Libraries/jsonQt.h"
#include "CLO_PLUGIN/INFOR/Libraries/json.h" 
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"
#include "CLO_PLUGIN/INFOR/DesignSuite/DesignSuite.h"
#include "CLO_PLUGIN/INFOR/Utilities/ComboBoxItem.h"
#include "CLO_PLUGIN/INFOR/Utilities/Configuration.h"
#include "ProductResultTable.h"
#include "classes/APIDefine.h"
#include "CLO_PLUGIN/INFOR/Utilities/RestAPIUtility.h"
#include "CLO_PLUGIN/INFOR/Utilities/DirectoryUtil.h"
#include "CLO_PLUGIN/INFOR/Products/CreateProduct.h"
#include <iostream>
#include <CLO_PLUGIN\INFOR\Products\ProductUtility.h>

//#include <CLO_PLUGIN\INFOR\Utilities\RestAPIUtility.h>

using json = nlohmann::json;

using namespace std;
using QtJson::JsonObject;
using QtJson::JsonArray;

namespace CLOPlugin
{
	UpdateProduct* UpdateProduct::_instance = NULL;

	UpdateProduct* UpdateProduct::GetInstance()
	{
		Utility::Logger("UpdateProduct -> GetInstance() -> Start");

		if (_instance == NULL)
		{
			_instance = new UpdateProduct();
		}

		Utility::Logger("UpdateProduct -> GetInstance() -> End");
		return _instance;
	}
	/**
	* \brief destructor of update product class
	*  deletes the object of this class.
	*/
	void UpdateProduct::Destroy()
	{
		Utility::Logger("UpdateProduct -> Destroy() -> Start");

		if (_instance)
		{
			delete _instance;
			_instance = NULL;
		}

		Utility::Logger("UpdateProduct -> Destroy() -> End");
	}

	UpdateProduct::UpdateProduct(QWidget* parent) : QDialog(parent)
	{
		Utility::Logger("UpdateProduct -> Constructor() -> Start");

		setupUi(this);
		QFont fontStyle("Times new roman", FONT_SIZE, QFont::Bold);
		this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
		QSize size(TABLE_WIDTH, TABLE_HEIGHT);

		updateProductTree->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		updateProductTree->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		updateProductTree->setStyleSheet("QTreeWidget::item { border-bottom: 1px solid #232323;""padding : 10px;""height: 25px;""}");
		updateProductTree->setFixedSize(size);
		updateProductTree->setColumnWidth(1, USER_INPUT_WIDTH);
		updateProductTree->setColumnWidth(0, SEARCH_LABEL_WIDTH);
		headerLabel->setFont(fontStyle);
		layout()->setSizeConstraint(QLayout::SetFixedSize);
		this->adjustSize();

		back->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_back_over.svg"));
		back->setIconSize(QSize(iconHieght, iconWidth));
		back->setStyleSheet(buttonFont);

		updateInPlm->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_update_over.svg"));
		updateInPlm->setIconSize(QSize(iconHieght, iconWidth));
		updateInPlm->setStyleSheet(buttonFont);

		saveAndClose->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_save_over.svg"));
		saveAndClose->setIconSize(QSize(iconHieght, iconWidth));
		saveAndClose->setStyleSheet(buttonFont);

		QObject::connect(updateInPlm, SIGNAL(clicked()), this, SLOT(updateInPlm_clicked()));
		QObject::connect(saveAndClose, SIGNAL(clicked()), this, SLOT(saveAndClose_clicked()));
		QObject::connect(back, SIGNAL(clicked()), this, SLOT(back_clicked()));
		QObject::connect(closeWindow, SIGNAL(clicked()), this, SLOT(closeWindow_clicked()));
		m_isSaveClicked = false;
		LastUsedStyleCode = "";
		FilterDependencyList();
		ReadPLMJson();
		ReadJsonAndDrawDialog();

		QTreeWidgetItem* dataItem1 = new QTreeWidgetItem;
		Qt::ItemFlags flags;
		flags = dataItem1->flags();
		flags |= Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
		dataItem1->setFlags(flags);
		updateProductTree->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
		updateProductTree->setSelectionBehavior(QAbstractItemView::SelectItems);
		updateProductTree->setSelectionMode(QAbstractItemView::NoSelection);
		updateProductTree->setSelectionBehavior(QAbstractItemView::SelectRows);
		updateProductTree->setEditTriggers(QAbstractItemView::CurrentChanged);
		updateProductTree->setTabKeyNavigation(true);

		Utility::Logger("UpdateProduct -> Constructor() -> End");
	}
	/**
	 * \brief Add labels in Update Product page from Json
	 */
	void UpdateProduct::ReadJsonAndDrawDialog()
	{
		Utility::Logger("UpdateProduct -> ReadJsonAndDrawDialog() -> Start");
		json jsonString;
		Utility::Fields tempField;
		ifstream styleSearchFile;
		styleSearchFile.open(DirectoryUtil::getProdSearchFilteredJson());
		styleSearchFile >> jsonString;
		styleSearchFile.close();
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
			Utility::ErrorLogger("UpdateProduct -> ReadJsonAndDrawDialog()::parsing mandatoryFieldsJson exception - " + string(e.what()));
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
			m_updateFieldsVector.push_back(tempField);
		}
		DrawWidget(m_updateFieldsVector);

		Utility::Logger("UpdateProduct -> ReadJsonAndDrawDialog() -> End");
	}
	/**
	 * \brief Validates Mandatory Fields for Update Product
	 * \return bool
	 */
	bool UpdateProduct::MandatoryFieldsValidation()
	{
		Utility::Logger("UpdateProduct -> MandatoryFieldsValidation() -> Start");

		QLineEdit* qlineedit;
		string userValue;
		QString label;
		for (int i = 0; i < updateProductTree->topLevelItemCount(); ++i)
		{
			QTreeWidgetItem* topItem = updateProductTree->topLevelItem(i);
			QWidget* qWidgetColumn0 = updateProductTree->itemWidget(topItem, 0);
			QWidget* qWidgetColumn1 = updateProductTree->itemWidget(topItem, 1);
			QLabel* qlabel = qobject_cast<QLabel*>(qWidgetColumn0);
			label = qlabel->text();

			qlineedit = qobject_cast<QLineEdit*>(qWidgetColumn1);
			if (qlineedit) {
				m_updateFieldsVector[i].userInputValues = qlineedit->text().toUtf8();
				if (qlineedit->isEnabled() && m_updateFieldsVector[i].labelValue.contains("StyleCode") && m_updateFieldsVector[i].userInputValues.isEmpty())
				{
					UTILITY_API->DisplayMessageBox("Please enter mandatory fields to create product.");
					return false;
				}
			}
			else
			{
				QComboBox* qComboBox = qobject_cast<QComboBox*>(qWidgetColumn1); 
				if (qComboBox)
				{
					m_updateFieldsVector[i].userInputValues = qComboBox->currentText().toUtf8();
				}
				else
				{
					QTextEdit* qtextEdit = qobject_cast<QTextEdit*>(qWidgetColumn1);
					if (qtextEdit)
					{
						m_updateFieldsVector[i].userInputValues = qtextEdit->toPlainText().toUtf8();
					}
				}
			}

		}

		Utility::Logger("UpdateProduct -> MandatoryFieldsValidation() -> End");
		return true;
	}
	/**
	 * \brief Setting feild types for attributes for update Product
	 * \return bool
	 */
	void UpdateProduct::SetAllFields()
	{
		Utility::Logger("UpdateProduct -> SetAllFields() -> Start");
		string selectedRootItem;
		list<string> hierarchyOder;
		bool loadUserFilledValues = false;
		if (IsSaveClicked() && LastUsedStyleCode == QString::fromStdString(m_ProductResults.at("StyleCode")))
		{
			loadUserFilledValues = true;
		}

		if (loadUserFilledValues) {
			for (int i = 0; i < m_updateFieldsVector.size(); i++)
			{
				if (m_rootItem == m_updateFieldsVector[i].labelValue.toStdString()) {
					selectedRootItem = m_updateFieldsVector[i].userInputValues.toStdString();
					break;
				}
			}
		}
		else {
			if (m_ProductResults.find(m_rootItem) != m_ProductResults.end()) {
				selectedRootItem = m_ProductResults.at(m_rootItem);
			}
		}

		if (!selectedRootItem.empty()) {
			hierarchyOder.push_back(m_rootItem);
			selectedRootItem = m_rootItem + "_" + QString::fromStdString(selectedRootItem).toUtf8().constData();
			list<string> subList = GetHierarchyOrder(m_hierarchyMap, selectedRootItem);
			hierarchyOder.insert(hierarchyOder.end(), subList.begin(), subList.end());
		}
		if (hierarchyOder.empty()) {
			for (int i = 0; i < updateProductTree->topLevelItemCount(); ++i)
			{
				if (loadUserFilledValues) {
					SetUserDefinedValues(i);
				}
				else {
					SetPLMAttValues(i);
				}
			}
		}
		else {
			for (auto itemItr = hierarchyOder.begin(); itemItr != hierarchyOder.end(); itemItr++) {
				Utility::Logger("Processing item-----"+ *itemItr);
				for (int i = 0; i < updateProductTree->topLevelItemCount(); ++i)
				{
					QTreeWidgetItem* topItem = updateProductTree->topLevelItem(i);
					QWidget* qWidget = updateProductTree->itemWidget(topItem, 0);
					QLabel* qlabel = qobject_cast<QLabel*>(qWidget);
					QString id = qlabel->property("Id").toString();
					if (*itemItr == id.toStdString()) {
						if (loadUserFilledValues) {
							SetUserDefinedValues(i);
						}
						else {
							SetPLMAttValues(i);
						}
						break;
					}
				}
			}

			for (int i = 0; i < updateProductTree->topLevelItemCount(); ++i)
			{
				QTreeWidgetItem* topItem = updateProductTree->topLevelItem(i);
				QWidget* qWidget = updateProductTree->itemWidget(topItem, 0);
				QLabel* qlabel = qobject_cast<QLabel*>(qWidget);
				QString id = qlabel->property("Id").toString();
				if (std::find(hierarchyOder.begin(), hierarchyOder.end(), id.toStdString()) == hierarchyOder.end()) {
					if (loadUserFilledValues) {
						SetUserDefinedValues(i);
					}
					else {
						SetPLMAttValues(i);
					}
				}
			}
		}
		
		Utility::Logger("UpdateProduct -> SetAllFields() -> End");
	}

	/**
	* Method is used to set user filled values to widget
	*/
	void UpdateProduct::SetUserDefinedValues(int& count)
	{
		QTreeWidgetItem* topItem = updateProductTree->topLevelItem(count);
		QWidget* qWidgetColumn0 = updateProductTree->itemWidget(topItem, 0);
		QWidget* qWidgetColumn1 = updateProductTree->itemWidget(topItem, 1);
		QLabel* qlabel = qobject_cast<QLabel*>(qWidgetColumn0);
		string label = qlabel->text().toStdString();
		QLineEdit* qlineedit = qobject_cast<QLineEdit*>(qWidgetColumn1);

		QByteArray byteArr;
		byteArr.append(m_updateFieldsVector[count].userInputValues);
		if (qlineedit)
		{
			qlineedit->setText(QString::fromUtf8(byteArr.data()));
		}
		else
		{
			QComboBox* qComboBox = qobject_cast<QComboBox*>(qWidgetColumn1);
			if (qComboBox)
			{
				int index = qComboBox->findText(QString::fromUtf8(byteArr.data()));
				qComboBox->setCurrentIndex(index);
				QMetaObject::invokeMethod(qComboBox, "activated", Q_ARG(const QString&, qComboBox->currentText()));
			}
			else
			{
				QTextEdit* qtextEdit = qobject_cast<QTextEdit*>(qWidgetColumn1);
				if (qtextEdit)
				{
					qtextEdit->setText(QString::fromUtf8(byteArr.data()));
				}
			}
		}
	}

	/**
	* Method is used to set plm attribute values to widget
	*/
	void UpdateProduct::SetPLMAttValues(int& count)
	{
		QTreeWidgetItem* topItem = updateProductTree->topLevelItem(count);
		QWidget* qWidget = updateProductTree->itemWidget(topItem, 0);
		QWidget* qWidget1 = updateProductTree->itemWidget(topItem, 1);
		QLabel* qlabel = qobject_cast<QLabel*>(qWidget);
		QString id = qlabel->property("Id").toString();
		QLineEdit* qlineedit = qobject_cast<QLineEdit*>(qWidget1);

		if (qlineedit)
		{
			qlineedit->setText(QString::fromUtf8(m_ProductResults.at(id.toStdString()).c_str()));
		}
		else
		{
			QComboBox* qComboBox = qobject_cast<QComboBox*>(qWidget1);
			if (qComboBox)
			{
				QString fieldValue = QString::fromUtf8(m_ProductResults.at(id.toStdString()).c_str());
				if (fieldValue.isEmpty()) {
					fieldValue = "Select";
				}
				int comboBoxIndex = qComboBox->findText(fieldValue);
				qComboBox->setCurrentIndex(comboBoxIndex);
				QMetaObject::invokeMethod(qComboBox, "activated", Q_ARG(const QString&, qComboBox->currentText()));
			}
			else
			{
				QTextEdit* qtextEdit = qobject_cast<QTextEdit*>(qWidget1);
				if (qtextEdit)
				{
					qtextEdit->setText(QString::fromUtf8(m_ProductResults.at(id.toStdString()).c_str()));

					if (qtextEdit->toPlainText() == "ul")
					{
						qtextEdit->setText("");
					}
				}
			}
		}
	}

	/**
	* \brief Filter out Product Details Json
	*/
	void UpdateProduct::ReadPLMJson()
	{
		Utility::Logger("UpdateProduct -> ReadPLMJson() -> Start");
		string entity = "Style";
		string parameter = "{\"roleId\":" + Configuration::GetInstance()->GetRoleId() + ",\"userId\":" + Configuration::GetInstance()->GetUserId() + ",\"entity\":\"Style\",\"pageType\":\"details\",\"dataFilter\":{\"conditions\":[{\"fieldname\":\"StyleId\",\"operator\":\"=\",\"value\":\"\"}]},\"pageInfo\":{},\"Schema\":" + Configuration::GetInstance()->GetschemaWithQuotes() + "}";
		Utility::GetFilteredJson(parameter, PRODUCT_DETAILS_API, entity);
		json completeStyleJson;
		m_attsDropdownListMap.clear();
		m_attributeMap.clear();
		ifstream styleDetailsFile;
		styleDetailsFile.open(DirectoryUtil::getProdSearchJson());

		styleDetailsFile >> completeStyleJson;
		styleDetailsFile.close();

		ofstream productSearchFile;
		productSearchFile.open(DirectoryUtil::getProdSearchFilteredJson());
		json finalJsontoSave;
		auto jsonFieldList = json::array();
		auto jsonUiTypeList = json::object();
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
			Utility::ErrorLogger("UpdateProduct -> ReadPLMJson()::parsing completeJson exception - " + string(e.what()));
			throw e.what();
		}
		json compObjJson, propsJson;
		string propsString, visible;
		json keyValuePairs = Utility::GetKeyValuePairs();
		for (int i = 0; i < componentsJson.size(); i++) {
			compObjString = componentsJson[i].dump();
			try {
				compObjJson = json::parse(compObjString);
				propsString = compObjJson["props"].dump();
				propsJson = json::parse(propsString);
				visible = propsJson["isVisibleAi"].dump();
				Utility::Logger("passed data::/n" + visible);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("UpdateProduct -> ReadPLMJson()::parsing compObjJson exception - " + string(e.what()));
				throw e.what();
			}
			if (visible == "true")
			{
				string isRequired = propsJson["isRequired"].dump();
				string tabIndex = propsJson["tabIndex"].dump();
				string fieldType = compObjJson["fieldType"].dump();
				string lookupRef = compObjJson["lookupRef"].dump();
				fieldType = fieldType.erase(0, 1);
				fieldType = fieldType.erase(fieldType.size() - 1);
				lookupRef = lookupRef.erase(0, 1);
				lookupRef = lookupRef.erase(lookupRef.size() - 1);

				string dataField = compObjJson["dataField"].dump();
				dataField = dataField.erase(0, 1);
				dataField = dataField.erase(dataField.size() - 1);

				string label = compObjJson["label"].dump();
				label = label.erase(0, 1);
				label = label.erase(label.size() - 1);

				string entity = compObjJson["entity"].dump();
				entity = entity.erase(0, 1);
				entity = entity.erase(entity.size() - 1);

				float tabIndexNum = std::stof(tabIndex);

				if (std::find(skipElements.begin(), skipElements.end(), dataField) == skipElements.end()) {
					m_indexColumnIdMap.insert(make_pair(tabIndexNum, dataField));
					if (linkingMap.find(dataField) != linkingMap.end()) {
						tabIndexNum = tabIndexNum + 0.25;
						m_indexColumnIdMap.insert(make_pair(tabIndexNum, linkingMap.at(dataField)));
					}
				}

				jsonUiTypeList[dataField] = fieldType;
				jsonFieldList.push_back(dataField);
				if (isRequired == "true")
				{
					jsonMandatoryFieldsList.push_back(dataField);
				}

				if (label != "ul") {
					m_attributeMap.insert(std::make_pair(dataField, QString::fromUtf8(label.c_str()).toStdString()));
				}
				else {
					m_attributeMap.insert(std::make_pair(dataField, Utility::GetDisplayValueByKey(QString::fromStdString(dataField), QString::fromStdString(entity), keyValuePairs).toStdString()));

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
						Utility::ErrorLogger("UpdateProduct -> ReadPLMJson()::parsing lookupsJSON exception - " + string(e.what()));
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

		finalJsontoSave["fieldList"] = newjsonFieldList; // jsonFieldList;

		finalJsontoSave["uiTypeList"] = jsonUiTypeList;
		finalJsontoSave["presetList"] = presetList;
		finalJsontoSave["mandatory_fieldList"] = jsonMandatoryFieldsList;
		productSearchFile << finalJsontoSave;
		productSearchFile.close();

		Utility::Logger("UpdateProduct -> ReadPLMJson() -> End");
	}

	/**
	* \brief Clear all fields from widgets
	*/
	void UpdateProduct::ClearAllFields()
	{
		Utility::Logger("UpdateProduct -> ClearAllFields() -> Start");
		for (int i = 0; i < updateProductTree->topLevelItemCount(); ++i)
		{
			QTreeWidgetItem* topItem = updateProductTree->topLevelItem(i);
			QWidget* qWidgetColumn0 = updateProductTree->itemWidget(topItem, 0);
			QWidget* qWidgetColumn1 = updateProductTree->itemWidget(topItem, 1);
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
					for each (auto field in m_updateFieldsVector) {
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

		Utility::Logger("UpdateProduct -> ClearAllFields() -> End");
	}
	/**
	* \brief Clears Downloaded Project Data
	*/
	void UpdateProduct::ClearDownloadedProjectData()
	{
		Utility::Logger("UpdateProduct -> ClearDownloadedProjectData() -> Start");

		m_ProductResults.clear();
		LastUsedStyleCode = "";

		Utility::Logger("UpdateProduct -> ClearDownloadedProjectData() -> End");
	}
	/**
	* \brief Read User input values from Update product UI
	*/
	void UpdateProduct::ExtractAllUIValues()
	{
		Utility::Logger("UpdateProduct -> ExtractAllUIValues() -> Start");

		for (int i = 0; i < updateProductTree->topLevelItemCount(); ++i)
		{
			QTreeWidgetItem* topItem = updateProductTree->topLevelItem(i);
			QWidget* qWidgetColumn0 = updateProductTree->itemWidget(topItem, 0);
			QWidget* qWidgetColumn1 = updateProductTree->itemWidget(topItem, 1);
			QLabel* qlabel = qobject_cast<QLabel*>(qWidgetColumn0);
			QString id = qlabel->property("Id").toString();
			QLineEdit* qlineedit = qobject_cast<QLineEdit*>(qWidgetColumn1);

			if (qlineedit)
			{
				m_updateFieldsVector[i].userInputValues = qlineedit->text().toUtf8();
				if (id == "StyleCode")
				{
					LastUsedStyleCode = qlineedit->text();
				}
			}
			else
			{
				QComboBox* qComboBox = qobject_cast<QComboBox*>(qWidgetColumn1);
				if (qComboBox)
				{
					m_updateFieldsVector[i].userInputValues = qComboBox->currentText().toUtf8();
				}
				else
				{
					QTextEdit* qtextEdit = qobject_cast<QTextEdit*>(qWidgetColumn1);
					if (qtextEdit)
					{
						m_updateFieldsVector[i].userInputValues = qtextEdit->toPlainText().toUtf8();
					}
				}
			}
		}

		Utility::Logger("UpdateProduct -> ExtractAllUIValues() -> End");
	}
	/**
	* \brief Sets type of widgets for labels
	* \param  fieldsVector
	*/
	void UpdateProduct::DrawWidget(std::vector<Utility::Fields>& fieldsVector)
	{
		Utility::Logger("UpdateProduct -> DrawWidget() -> Start");
		bool isStyleCodeEnabled = createProduct::GetInstance()->IsStyleCodeEnabled();

		for each (auto field in fieldsVector)
		{
			string tempLabel = field.labelValue.toStdString();

			if (m_attributeMap.find(tempLabel) != m_attributeMap.end()) {
				tempLabel = m_attributeMap.at(tempLabel);
			}

			if (field.fieldUItype == "text")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();
				QLineEdit* lineEdit = new QLineEdit();
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);
				label->setProperty("Id", field.labelValue);

				label->setText(QString::fromStdString(tempLabel));
				lineEdit->setStyleSheet(inputStyle);
				updateProductTree->addTopLevelItem(topLevel);
				updateProductTree->setItemWidget(topLevel, 0, label);
				updateProductTree->setItemWidget(topLevel, 1, lineEdit);

				if (field.labelValue == "StyleCode" || field.labelValue == "Number")
				{
					if (isStyleCodeEnabled == true)
					{
						lineEdit->setDisabled(false);
						label->setText(QString::fromStdString(tempLabel) + "<font color='red'>*</font>");
					}
					else
					{
						lineEdit->setDisabled(true);
						lineEdit->setStyleSheet("color: #696969;" + inputStyle);
						label->setStyleSheet("color: #696969;" + inputStyle);
					}
				}
				/*if (field.isMandatory)
				{
					label->setText(QString::fromStdString(tempLabel) + "<font color='gray'>*</font>");
				}*/
			}

			if (field.fieldUItype == "dropdown")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();
				ComboBoxItem* ComboBox = new ComboBoxItem(topLevel, 1);
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);
				label->setProperty("Id", field.labelValue);

				label->setText(QString::fromStdString(tempLabel));
				ComboBox->setStyleSheet(inputStyle);
				updateProductTree->addTopLevelItem(topLevel);
				updateProductTree->setItemWidget(topLevel, 0, label);
				updateProductTree->setItemWidget(topLevel, 1, ComboBox);
				
				ComboBox->setStyleSheet("combobox-popup: 0; font: 75 8pt \"Tahoma\"; ");
				bool recordExists = false;
				for (auto itj = m_hierarchyMap.begin(); itj != m_hierarchyMap.end(); itj++)
				{
					if (itj->first.find(field.labelValue.toStdString()) == 0 && itj->second.find(field.labelValue.toStdString()) == 0) {
						recordExists = true;
					}
				}
				if (recordExists && m_rootItem != field.labelValue.toStdString()) {
					ComboBox->addItem("Select");
				}
				else {
					ComboBox->addItems(field.presetValues);
				}
				int indexOfEmptyString = ComboBox->findText("Select");
				ComboBox->setCurrentIndex(indexOfEmptyString);
				ComboBox->setEditText(field.userInputValues);
				ComboBox->setProperty("Id", field.labelValue);

				QObject::connect(ComboBox, SIGNAL(activated(const QString&)), this,
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
				updateProductTree->addTopLevelItem(topLevel);
				updateProductTree->setItemWidget(topLevel, 0, label);
				updateProductTree->setItemWidget(topLevel, 1, TextEdit);
				TextEdit->setText(field.userInputValues);
				TextEdit->setStyleSheet("border: 1px solid black;"
					"background-color: #222222;"
					"font: 75 8pt \"Tahoma\";"
					);
				TextEdit->setMaximumSize(TEXTEDIT_SIZE_WIDTH, TEXTEDIT_SIZE_HEIGHT);
				/*if (field.isMandatory)
				{
					label->setText(QString::fromStdString(tempLabel) + "<font color='red'>*</font>");
				}*/
			}

			if (field.fieldUItype == "DateEdit")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();
				QDateEdit* dateTimeEdit = new QDateEdit();
				bool enable = true;
				dateTimeEdit->setCalendarPopup(enable);
				QString datericovero("");
				QDate date = QDate::fromString(datericovero, "");
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);
				label->setProperty("Id", field.labelValue);

				label->setText(QString::fromStdString(tempLabel));
				updateProductTree->addTopLevelItem(topLevel);
				updateProductTree->setItemWidget(topLevel, 0, label);
				updateProductTree->setItemWidget(topLevel, 1, dateTimeEdit);

			}
		}

		Utility::Logger("UpdateProduct -> DrawWidget() -> End");
	}

	/**
	* Method is used to call rest api and filter records for field dependencies
	*/
	void UpdateProduct::FilterDependencyList()
	{
		Utility::Logger("UpdateProduct -> FilterDependencyList() -> Start");
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
				Utility::ErrorLogger("UpdateProduct -> FilterDependencyList()::parsing lookupsJSON exception - " + string(e.what()));
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
			Utility::ErrorLogger("UpdateProduct -> FilterDependencyList()::parsing completeEntitiesJson exception - " + string(e.what()));
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
					Utility::ErrorLogger("UpdateProduct -> FilterDependencyList()::parsing productCol exception - " + string(e.what()));
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
						Utility::ErrorLogger("UpdateProduct -> FilterDependencyList()::parsing columns exception - " + string(e.what()));
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
						Utility::Logger("UpdateProduct -> FilterDependencyList():: Exception occured while getting Id from lookupmap." + string(exception.what()));
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

		Utility::Logger("UpdateProduct -> FilterDependencyList() -> End");
	}


	/**
	* Function is used to handle change event of dropdown widgets
	*/
	void UpdateProduct::handleDropDownValueChangeEvent(const QString& item)
	{
		Utility::Logger("UpdateProduct -> handleDropDownValueChangeEvent() -> Start");
		QString senderCombo = sender()->property("Id").toString();
		bool resetRootItem = false;
		if (m_rootItem == senderCombo.toStdString()) {
			resetRootItem = true;
		}

		if (item.isEmpty()) {
		}
		else if (item == "Select")
		{
			for (int i = 0; i < updateProductTree->topLevelItemCount(); ++i)
			{
				QTreeWidgetItem* topItem = updateProductTree->topLevelItem(i);
				QWidget* qWidget = updateProductTree->itemWidget(topItem, 1);
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

							if ((it->first.find(id.toStdString()) == 0 || it->second.find(id.toStdString()) == 0)) {
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
								GetResetFields(updateProductTree, m_hierarchyMap, filterString, m_clearItems, m_updateFieldsVector, true);
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
			for (int i = 0; i < updateProductTree->topLevelItemCount(); ++i)
			{
				QTreeWidgetItem* topItem = updateProductTree->topLevelItem(i);
				QWidget* qWidget = updateProductTree->itemWidget(topItem, 1);
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
								for each (auto field in m_updateFieldsVector) {
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
								GetResetFields(updateProductTree, m_hierarchyMap, filterString, m_clearItems, m_updateFieldsVector, false);
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
				for (int i = 0; i < updateProductTree->topLevelItemCount(); ++i)
				{
					QTreeWidgetItem* topItem = updateProductTree->topLevelItem(i);
					QWidget* qWidget = updateProductTree->itemWidget(topItem, 1);
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
			m_clearItems.clear();
		}

		Utility::Logger("UpdateProduct -> handleDropDownValueChangeEvent() -> End");
	}

	/**
	* \brief Setting Independent Values to widgets
	* \param  dependencyJson
	*/
	map<string, map<string, QString>> UpdateProduct::SetDropDownValues(string& selectedItem, string& id)
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

	UpdateProduct::~UpdateProduct()
	{

	}
	/**
	* \brief Making Rest call to Update Product metadata and uploads latest document
	*/
	bool UpdateProduct::UpdateProductMetaData()
	{
		Utility::Logger("UpdateProduct -> UpdateProductMetaData() -> Start");

		string parameter, bearerKey;
		json updateMap;
		json updateArray;
		json mapArray;

		string styleCodeForFilename = m_ProductResults.at("StyleCode");
		string dirPath;
		int count = 0;

		for (auto array_element : m_updateFieldsVector)
		{
			string attLabel = array_element.labelValue.toStdString();
			string userSelected = array_element.userInputValues.toStdString();
			if (userSelected != "")
			{
				if (array_element.fieldUItype == "dropdown")
				{
					mapArray.clear();
					mapArray["fieldName"] = attLabel;
					map<string, string> attNameIdMap;
					attNameIdMap.clear();
					attNameIdMap.insert(m_attsDropdownListMap[attLabel].begin(), m_attsDropdownListMap[attLabel].end());
					for (auto it = attNameIdMap.begin(); it != attNameIdMap.end(); it++)
					{
						if ((it->first == userSelected) && (userSelected != "Select"))
						{
							mapArray["operator"] = "=";
							mapArray["value"] = stoi(it->second);
							break;
						}
						else if (userSelected == "Select")
						{
							mapArray["operator"] = "=";
							mapArray["value"] = nullptr;
							break;
						}
					}
					updateMap["fieldValues"][count++] = mapArray;
					Utility::Logger("UpdateProduct::UpdateProductMetaData() to_string(mapArray) - " + to_string(mapArray));
				}
				else
				{
					if (attLabel != "StyleCode")
					{
						mapArray.clear();
						mapArray["fieldName"] = attLabel;
						mapArray["operator"] = "=";
						mapArray["value"] = userSelected;
						updateMap["fieldValues"][count++] = mapArray;
					}
				}
			}
		}
		updateMap["idGenContextVal"] = nullptr;
		updateMap["idGenVal"] = updateArray.array();
		updateMap["key"] = m_ProductResults.at("StyleId");

		updateMap["locale"] = "en-US";
		updateMap["modifyId"] = Configuration::GetInstance()->GetUserId();
		updateMap["notificationMessageKey"] = "UPDATED_STYLE_OVERVIEW";
		updateMap["schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
		updateMap["subEntities"] = updateArray.array();
		updateMap["userId"] = Configuration::GetInstance()->GetUserId();
		updateMap["rowVersionText"] = m_ProductResults.at("RowVersionText");

		string completeZprjProjectPath;
		bool isSpaceFound = false;

		if (QString::fromStdString(m_ProductResults.at("attachmentFileName")).isEmpty())
		{
			completeZprjProjectPath = UTILITY_API->GetProjectFilePath();
		}
		else
		{
			completeZprjProjectPath = DirectoryUtil::getStyleAttachmentDirectory() + m_ProductResults.at("attachmentFileName");

		}

		string checkFileName = m_ProductResults.at("attachmentFileName");
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
			int fileSize = Utility::GetFileSize(completeZprjProjectPath);
			Utility::Logger("filesize::" + to_string(fileSize));
			if (fileSize > UPLOAD_FILE_SIZE)
			{
				UpdateMetaDataForCurrentGarment();
				Utility::Logger("UpdateMetaDataForCurrentGarment::" + UTILITY_API->GetMetaDataForCurrentGarment());
				EXPORT_API->ExportZPrj(completeZprjProjectPath, true);
				Utility::Logger("UpdateProduct::UpdateProductMetaData() updateMap - " + to_string(updateMap));
				Utility::Logger("UpdateProduct::UpdateProductMetaData() PRODUCT_UPDATE_API - " + PRODUCT_UPDATE_API);
				string response = RestCall(to_string(updateMap), PRODUCT_UPDATE_API);
				Utility::CustomMessageBox("response -> updateProductMetaData() -> UpdateProduct :: " + response);
				Utility::Logger("UpdateProduct::UpdateProductMetaData() response:: " + response);
				string errorResponse = Utility::CheckErrorDescription(response);
				Utility::Logger("UpdateProduct::UpdateProductMetaData() errorResponse:: " + errorResponse);

				if (errorResponse.empty() && (errorResponse.length() == 0))
				{
					this->close();
					json keyJson = Utility::GetResultsJSON(response);
					m_keyforUploading = keyJson["key"].dump();
					return true;
				}
				else
				{
					UTILITY_API->DisplayMessageBox(errorResponse);
					Utility::Logger("UpdateProduct -> updateProductMetaData() ->" + errorResponse);
					return false;
				}
			}
			else
			{
				UTILITY_API->DisplayMessageBox("User doesn't have a design to send to PLM");
				Utility::Logger("UpdateProduct -> updateProductMetaData() -> User not having design to PushToPLM");
				return false;
			}
		}
		else
		{
			UTILITY_API->DisplayMessageBox("Please check your 3D asset name");
			return false;
		}

		Utility::Logger("UpdateProduct -> updateProductMetaData() -> End");
	}
	/**
	* \brief Creates Request to make Rest Call for Upload attachment
	* \param response
	* \param key
	* \return string
	*/
	string UpdateProduct::CreateZipParam(string response, string key)
	{
		Utility::Logger("UpdateProduct -> CreateZipParam() -> Start");
		json imgJson = Utility::GetResultsJSON(response);
		string objectKey = imgJson["addedFiles"][0]["objectKey"].dump();
		objectKey = objectKey.erase(0, 1);
		objectKey = objectKey.erase(objectKey.size() - 1);
		string oldFileName = imgJson["addedFiles"][0]["oldFileName"].dump();
		oldFileName = oldFileName.erase(0, 1);
		oldFileName = oldFileName.erase(oldFileName.size() - 1);
		json mainMap;
		json attaFileListDto;
		json attaFileListDtoMap;
		attaFileListDtoMap["referenceId"] = key;
		attaFileListDtoMap["code"] = "E0013";
		attaFileListDtoMap["objectKey"] = objectKey;
		attaFileListDtoMap["oldFileName"] = oldFileName;
		attaFileListDto[0] = attaFileListDtoMap;
		mainMap["modifyId"] = Configuration::GetInstance()->GetUserId();
		mainMap["Schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
		mainMap["AttaFileListDto"] = attaFileListDto;

		Utility::Logger("UpdateProduct -> CreateZipParam() -> End");
		return to_string(mainMap);
	}
	/**
	* \brief Creates Request to make Rest Call for Upload Image
	* \param response
	* \param key
	* \return string
	*/
	string UpdateProduct::CreateImageParam(string response, string key)
	{
		Utility::Logger("UpdateProduct -> createImageParam() -> Start");

		string downloadedImgName = m_ProductResults.at("imageFileName");
		size_t position = downloadedImgName.find(".");
		string extractedName = (string::npos == position) ? downloadedImgName : downloadedImgName.substr(0, position);
		string currentImgName = UTILITY_API->GetProjectName();
		json imgJson;
		string isImageExists = m_ProductResults.at("StyleImage");
		string mainImage = m_ProductResults.at("mainImage");
		size_t positionMI = mainImage.find(".");
		mainImage = (string::npos == positionMI) ? mainImage : mainImage.substr(0, positionMI);

		try {
			imgJson = json::parse(response);
		}
		catch (exception & e)
		{
			Utility::ErrorLogger("UpdateProduct -> ReadJsonAndDrawDialog()::parsing imgJson exception - " + string(e.what()));
			throw e.what();
		}
		string objectKey = imgJson["addedFiles"][0]["objectKey"].dump();
		objectKey = objectKey.erase(0, 1);
		objectKey = objectKey.erase(objectKey.size() - 1);
		string oldFileName = imgJson["addedFiles"][0]["oldFileName"].dump();
		oldFileName = oldFileName.erase(0, 1);
		oldFileName = oldFileName.erase(oldFileName.size() - 1);
		json mainMap;
		json attaFileListDto;
		json detailsMap;
		json details;
		json attaFileListDtoMap;
		mainMap["modifyId"] = Configuration::GetInstance()->GetUserId();
		mainMap["Schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
		details["dlType"] = DLTYPECODE_STYLE_IMAGES;
		detailsMap = details;
		attaFileListDtoMap["code"] = "E0012";
		attaFileListDtoMap["type"] = "Image";
		attaFileListDtoMap["objectKey"] = objectKey;
		attaFileListDtoMap["oldFileName"] = oldFileName;
		attaFileListDtoMap["referenceId"] = key;
		attaFileListDtoMap["details"] = detailsMap;
		attaFileListDtoMap["IsDefault"] = true;

		if (mainImage != "null" && mainImage != currentImgName)
		{
			attaFileListDtoMap["IsDefault"] = false;
		}
		attaFileListDto[0] = attaFileListDtoMap;
		mainMap["AttaFileListDto"] = attaFileListDto;

		Utility::Logger("UpdateProduct -> createImageParam() -> End");
		return to_string(mainMap);
	}
	/**
	* \brief On Click of UpdateInPLM,  Deleting old documents from Library,
	* Unlinking Documents from product and updating metadeta and uplaoding latest document
	*/
	void UpdateProduct::updateInPlm_clicked()
	{
		Utility::Logger("UpdateProduct -> UpdateInPLMClicked() -> Start");

		string filepathImg, downloadedImgName, currentImgName;
		filepathImg = DirectoryUtil::getStyleAttachmentDirectory() + m_ProductResults.at("imageFileName");
		downloadedImgName = m_ProductResults.at("imageFileName");
		size_t position = downloadedImgName.find(".");
		string extractedName = (string::npos == position) ? downloadedImgName : downloadedImgName.substr(0, position);
		currentImgName = UTILITY_API->GetProjectName();
		m_isSaveClicked = false;
		if (MandatoryFieldsValidation())
		{
			this->hide();
			ExtractAllUIValues();
			if (UpdateProductMetaData())
			{
				int imageDocID = GetDocumentIdForFile(m_ProductResults.at("imageFileName"));
				int attachmentDocID = GetDocumentIdForFile(m_ProductResults.at("attachmentFileName"));
				int imageId, attachmentsId;
				std::stringstream ss1(m_ProductResults.at("imageAttaFileListId"));
				ss1 >> imageId;
				std::stringstream ss2(m_ProductResults.at("attachmentAttaFileListId"));
				ss2 >> attachmentsId;

				if (extractedName != currentImgName)
				{
					DeleteDocuments(attachmentDocID);
					if(m_isAttachmentDeleted)
						UnlinkDocuments(attachmentsId);
				}
				else
				{
					DeleteDocuments(attachmentDocID, imageDocID);
					if (m_isAttachmentDeleted)
						UnlinkDocuments(attachmentsId, imageId);
				}
				if (m_isAttachmentDeleted && m_isAttachementUnlinked)
				{
					UploadZprjAndThumbnailFiles();					
				}
				else
				{
					UTILITY_API->DisplayMessageBox("Product updated failed in PLM");
					Utility::Logger("UpdateProduct -> Product updated failed");
				}
			}


		}
		if (!m_isAttachmentDeleted)
			UTILITY_API->DisplayMessageBox("Update failed");

		Utility::Logger("UpdateProduct -> UpdateInPLMClicked() -> End");
	}

	void UpdateProduct::UploadZprjAndThumbnailFiles()
	{
		string filepathImg, downloadedImgName, currentImgName;
		filepathImg = DirectoryUtil::getStyleAttachmentDirectory() + m_ProductResults.at("imageFileName");
		downloadedImgName = m_ProductResults.at("imageFileName");
		size_t position = downloadedImgName.find(".");
		string extractedName = (string::npos == position) ? downloadedImgName : downloadedImgName.substr(0, position);
		currentImgName = UTILITY_API->GetProjectName();
		string completeZprjProjectPath, pathOfZprj;
		if (QString::fromStdString(m_ProductResults.at("attachmentFileName")).isEmpty())
		{
			completeZprjProjectPath = UTILITY_API->GetProjectFilePath();
		}
		else
		{
			completeZprjProjectPath = DirectoryUtil::getStyleAttachmentDirectory() + m_ProductResults.at("attachmentFileName");

		}

		if ((m_ProductResults.at("imageFileName").empty()) || (extractedName != currentImgName))
		{
			pathOfZprj = UTILITY_API->GetProjectFilePath();
			Utility::EraseSubString(pathOfZprj, UTILITY_API->GetProjectName());
			filepathImg = pathOfZprj + UTILITY_API->GetProjectName() + ".png";
		}
		else
		{
			filepathImg = DirectoryUtil::getStyleAttachmentDirectory() + m_ProductResults.at("imageFileName");
			//assuming that the image name is also same as the downloaded zprj , 
			//just the extension is .png instead of .zprj
		}
		string errorResponse;
		string responseImg = Utility::UploadFile(filepathImg, Configuration::GetInstance()->GetBearerToken());
		errorResponse = Utility::CheckErrorDescription(responseImg);
		if (errorResponse.empty())
		{	
			
			Utility::Logger("UpdateProduct::UpdateProductMetaData() completeZprjProjectPath:: " + completeZprjProjectPath);
			string responseZip = Utility::UploadFile(completeZprjProjectPath, Configuration::GetInstance()->GetBearerToken());
			Utility::Logger("UpdateProduct::UpdateProductMetaData() responseZip:: " + responseZip);
			errorResponse = Utility::CheckErrorDescription(responseZip);
			if (errorResponse.empty())
			{
				bool isAttachmentLinked = linkingAttachment(responseZip, responseImg);
				if (isAttachmentLinked)
				{
					UTILITY_API->DisplayMessageBox("Product with style code " + m_styleCode + " updated successfully in PLM");
					UTILITY_API->NewProject();
					ClearDownloadedProjectData();
					Utility::Logger("UpdateProduct -> Product updated successfully");
				}
				else
				{
					UTILITY_API->DisplayMessageBox("Product updated failed in PLM");
					Utility::Logger("UpdateProduct -> Product updated failed");
				}
			}
		}
		if (!errorResponse.empty())
		{
			UTILITY_API->DisplayMessageBox(errorResponse + "\n" + "update failed");
		}
	}
	/**
	* \brief Makes Rest call to Unlink documents from product
	* \param imageAttaFileListId
	* \param attachmentAttaFileListId 
	*/
	void UpdateProduct::UnlinkDocuments(int attachmentAttaFileListId, int imageAttaFileListId)
	{
		Utility::Logger("UpdateProduct -> UnlinkDocuments() -> Start");

		json mainMap;

		mainMap["AttaFileListIds"][0] = attachmentAttaFileListId;
		if (imageAttaFileListId != NULL)
			mainMap["AttaFileListIds"][1] = imageAttaFileListId;

		mainMap["Schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();

		Utility::Logger("UpdateProduct::UnlinkDocuments() mainMap - " + to_string(mainMap));
		Utility::Logger("UpdateProduct::UnlinkDocuments() PRODUCT_UNLINK_ATTACHMENT_API - " + PRODUCT_UNLINK_ATTACHMENT_API);
		string responseUnLink = RestCall(to_string(mainMap), PRODUCT_UNLINK_ATTACHMENT_API);

		Utility::CustomMessageBox("responseUnLink -> UnlinkDocuments() -> UpdateProduct :: " + responseUnLink);
		Utility::Logger("UpdateProduct::UnlinkDocuments() responseUnLink - " + responseUnLink);
		string errorResponse = Utility::CheckErrorDescription(responseUnLink);
		if (errorResponse.empty())
		{
			m_isAttachementUnlinked = true;
		}
		Utility::Logger("UpdateProduct -> UnlinkDocuments() -> End");
	}
	/**
	* \brief Makes Rest call to delete documents from product
	* \param imageDocLibId
	* \param attachmentDocLibId
	*/
	void UpdateProduct::DeleteDocuments(int attachmentDocLibId, int imageDocLibId)
	{
		Utility::Logger("UpdateProduct -> DeleteDocuments() -> Start");

		json mainMap;

		mainMap["ids"][0] = attachmentDocLibId;
		if (imageDocLibId != NULL)
		mainMap["ids"][1] = imageDocLibId;

		mainMap["Schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();

		Utility::Logger("UpdateProduct::DeleteDocuments() mainMap - " + to_string(mainMap));
		Utility::Logger("UpdateProduct::DeleteDocuments() PRODUCT_DELETE_ATTACHMENT_API - " + PRODUCT_DELETE_ATTACHMENT_API);
		string responseDelete = RestCall(to_string(mainMap), PRODUCT_DELETE_ATTACHMENT_API);

		Utility::CustomMessageBox("responseDelete -> DeleteDocuments() -> UpdateProduct :: " + responseDelete);
		Utility::Logger("UpdateProduct::DeleteDocuments() responseDelete:: " + responseDelete);
		string errorResponse = Utility::CheckErrorDescription(responseDelete);
		if (errorResponse.empty())
			m_isAttachmentDeleted = true;
		else
			UTILITY_API->DisplayMessageBox(errorResponse);
		Utility::Logger("UpdateProduct -> DeleteDocuments() -> End");
	}

	/**
	* \brief Makes rest call to get Document Id, which is used to delelte documents
	* \param filename
	* \return int
	*/
	int UpdateProduct::GetDocumentIdForFile(string& filename)
	{
		Utility::Logger("UpdateProduct -> GetDocumentIdForFile() -> Start");

		string column, docLibId;
		json mainMap;
		json conditionsFilter;
		json conditionMap;
		json pageInfoMap;
		mainMap.clear();
		mainMap["roleId"] = Configuration::GetInstance()->GetRoleId();
		mainMap["userId"] = Configuration::GetInstance()->GetUserId();
		mainMap["entity"] = "DocLib";
		mainMap["personalizationId"] = 0;
		mainMap["pageType"] = "list";
		conditionsFilter["FieldName"] = "Filename";
		conditionsFilter["Operator"] = "=";
		conditionsFilter["Value"] = filename;
		conditionMap["Conditions"][0] = conditionsFilter;
		mainMap["dataFilter"] = conditionMap;
		pageInfoMap["page"] = 1;
		pageInfoMap["pageSize"] = PAGE_SIZE;
		mainMap["pageInfo"] = pageInfoMap;
		mainMap["Schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();


		Utility::Logger("UpdateProduct::GetDocumentIdForFile() mainMap:: " + to_string(mainMap));
		Utility::Logger("UpdateProduct::GetDocumentIdForFile() PRODUCT_GET_ATTCHMENT_API:: " + PRODUCT_GET_ATTCHMENT_API);

		//Using this FileName we will Search for StyleAttachments By Below Rest Call.
		string responseStyleList = RestCall(to_string(mainMap), PRODUCT_GET_ATTCHMENT_API);

		Utility::CustomMessageBox("responseStyleList -> GetDocumentIdForFile() -> UpdateProduct :: " + responseStyleList);
		Utility::Logger("UpdateProduct::GetDocumentIdForFile() responseStyleList - " + responseStyleList);
		//From this response we will get DocObjId
		string errorResponse = Utility::CheckErrorDescription(responseStyleList);
		Utility::Logger("UpdateProduct::GetDocumentIdForFile() errorResponse:: " + errorResponse);

		if (errorResponse.empty() && (errorResponse.length() == 0))
		{
			json docLibjson = Utility::GetResultsJSON(responseStyleList);

			json completeDocLibsJson;
			string responseJsonStrStyle = docLibjson["entities"].dump();
			try {

				completeDocLibsJson = json::parse(responseJsonStrStyle);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("UpdateProduct -> GetDocumentIdForFile()::parsing completeDocLibsJson exception - " + string(e.what()));
				throw e.what();
			}
			if (completeDocLibsJson.size() != 0)
			{
				json entities, columns;
				for (int i = 0; i < completeDocLibsJson.size(); i++)
				{
					string entityJson = completeDocLibsJson[i].dump();
					try {
						entities = json::parse(entityJson);

					}
					catch (exception& e)
					{
						Utility::ErrorLogger("UpdateProduct -> GetDocumentIdForFile()::parsing entities exception - " + string(e.what()));
						throw e.what();
					}
					string name = entities["name"].dump();
					name = name.erase(0, 1);
					name = name.erase(name.size() - 1);

					if (name == "DocLib")
					{
						try {
							column = entities["column"].dump();

							columns = json::parse(column);
							docLibId = columns["DocLibId"].dump();
						}
						catch (exception& e)
						{
							Utility::ErrorLogger("UpdateProduct -> GetDocumentIdForFile()::parsing columns exception - " + string(e.what()));
							throw e.what();
						}
					}
				}
			}
		}
		else
		{
			UTILITY_API->DisplayMessageBox(errorResponse);
		}
		int docLibID;
		std::stringstream ss(docLibId);
		ss >> docLibID;

		Utility::Logger("UpdateProduct -> GetDocumentIdForFile() -> End");
		return docLibID;
	}
	/**
	* \brief Saves the user entered values and closes the UI
	*/
	void UpdateProduct::saveAndClose_clicked()
	{
		Utility::Logger("UpdateProduct -> SaveAndCloseClicked() -> Start");

		m_isSaveClicked = true;
		if (MandatoryFieldsValidation())
		{
			ExtractAllUIValues();
			UTILITY_API->DisplayMessageBox("Product data has been updated and saved successfully locally");
		}
		Utility::Logger("UpdateProduct -> SaveAndCloseClicked() -> End");
	}
	/**
	* \brief On Back Clicked, It returns back to Design Suite
	*/
	void UpdateProduct::back_clicked()
	{
		Utility::Logger("UpdateProduct -> BackClicked() -> Start");

		this->hide();
		if (IsSaveClicked() == false)
		{
			ClearAllFields();
		}
		DesignSuite::GetInstance()->setModal(true);
		DesignSuite::GetInstance()->show();

		Utility::Logger("UpdateProduct -> BackClicked() -> End");
	}
	/**
	* \brief Stores User entered values for Update product
	* \param  data
	*/
	void UpdateProduct::FillUpdateProductData(map<string, string>& data)
	{
		Utility::Logger("UpdateProduct -> FillUpdateProductData() -> Start");
		m_ProductResults = data;
		Utility::Logger("UpdateProduct -> FillUpdateProductData() -> End");
	}
	/**
	* \brief Closes the update product window
	*/
	void UpdateProduct::closeWindow_clicked()
	{
		Utility::Logger("UpdateProduct -> CloseWindowClicked() -> Start");

		this->close();
		if (IsSaveClicked() == false)
		{
			ClearAllFields();
		}

		Utility::Logger("UpdateProduct -> CloseWindowClicked() -> End");
	}
	/**
	* \brief Checks user save the entered data or not
	*/
	bool UpdateProduct::IsSaveClicked()
	{
		Utility::Logger("UpdateProduct -> IsSaveClicked() -> Start");

		if (m_isSaveClicked)
			return true;
		else
			return false;
	}

	/**
	* \Funtional is used to check if there is a product in cache or not.
	*/
	bool UpdateProduct::IsValidProductForUpdate()
	{
		QString styleCode;
		if (m_ProductResults.find("StyleCode") == m_ProductResults.end()) {
			return false;
		}
		else {
			styleCode = QString::fromStdString(m_ProductResults.at("StyleCode"));
		}

		if (styleCode.isNull() || styleCode.isEmpty()) {
			return false;
		}
		else {
			return true;
		}
	}
	void UpdateProduct::UpdateMetaDataForCurrentGarment()
	{
		for (int i = 0; i < updateProductTree->topLevelItemCount(); ++i)
		{
			QTreeWidgetItem* topItem = updateProductTree->topLevelItem(i);
			QWidget* qWidgetColumn0 = updateProductTree->itemWidget(topItem, 0);
			QLabel* qlabel = qobject_cast<QLabel*>(qWidgetColumn0);
			string label = qlabel->text().toStdString();
			if (label == "Number")
			{
				UTILITY_API->ChangeMetaDataValueForCurrentGarment("Style ID", m_ProductResults.at("StyleId"));
				UTILITY_API->ChangeMetaDataValueForCurrentGarment("Style Code", m_updateFieldsVector[i].userInputValues.toStdString());
				m_styleCode = m_ProductResults.at("StyleCode");
			}
			else if (label == "Brand")
			{
				UTILITY_API->ChangeMetaDataValueForCurrentGarment(label, m_updateFieldsVector[i].userInputValues.toStdString());
			}
		}
	}
	bool UpdateProduct::linkingAttachment(string& zprjFileResponse, string& imageFileResponse)
	{
		string imageResponse, zipResponse;
		string imageErrorResponse, zipErrorResponse;
		bool isAttachmentLinked = false;
		//Linking Zprj
		string paramZip = CreateZipParam(zprjFileResponse, m_keyforUploading);///debug the error uploading zprj and image.
		Utility::Logger("UpdateProduct::UpdateProductMetaData() paramZip:: - " + paramZip);
		zipResponse = Utility::LinkAttachmentToStyle(paramZip, Configuration::GetInstance()->GetBearerToken());
		zipErrorResponse = Utility::CheckErrorDescription(zipResponse);
		if (zipErrorResponse.empty())
		{
			Utility::Logger("Product ZPRJ Linked Successfully::" + zipResponse);
			//Linking Image
			string paramImg = CreateImageParam(imageFileResponse, m_keyforUploading);
			Utility::Logger("paramImg:: - " + paramImg);
			imageResponse = Utility::LinkAttachmentToStyle(paramImg, Configuration::GetInstance()->GetBearerToken());
			imageErrorResponse = Utility::CheckErrorDescription(imageResponse);
			if (imageErrorResponse.empty())
				Utility::Logger("Product image Linked Successfully::" + imageResponse);
				return isAttachmentLinked=true;
		}
		return isAttachmentLinked;
	}

}