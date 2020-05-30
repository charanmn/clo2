#include "ColorSearch.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QCheckBox>
#include <any>
#include <optional>
#include "qlistview.h"
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"
#include "CLO_PLUGIN/INFOR/Utilities/Definitions.h"
#include "CLO_PLUGIN/INFOR/DesignSuite/DesignSuite.h" 
#include "ColorResultTable.h"
#include "classes/APIDefine.h"
#include <iostream>
#include "CLO_PLUGIN/INFOR/Utilities/Configuration.h"
#include "CLO_PLUGIN/INFOR/Utilities/RestAPIUtility.h"
#include "CLO_PLUGIN/INFOR/Utilities/DirectoryUtil.h"

using namespace std;
/*
*brief having the methods for navigating all the functions for color related. 
*nlohmann used for parsing and mapping json. 
*/
using json = nlohmann::json;
namespace CLOPlugin
{
	ColorSearch* ColorSearch::_instance = NULL;
	
	/**
	 * \brief Instantiate ColorSearch object
	 * \return
	 */
	ColorSearch* ColorSearch::GetInstance()
	{
		Utility::Logger("ColorSearch -> GetInstance() -> Start");
		if (_instance == NULL)
		{			
			_instance = new ColorSearch();
		}
		Utility::Logger("ColorSearch -> GetInstance() -> End");
		return _instance;
	}
	/**
	 * \brief Destroys instantiated ColorSearch object
	 */
	void ColorSearch::Destroy()
	{
		Utility::Logger("ColorSearch -> Destroy() -> Start");
		if (_instance)
		{
			delete _instance;
			_instance = NULL;
		}
		Utility::Logger("ColorSearch -> Destroy() -> End");
	}
	/*
	*brief clear all filled values before display UI.
	*/
	void ColorSearch::ClearAllFields()
	{
		Utility::Logger("ColorSearch -> ClearAllFields() -> Start");
		for (int i = 0; i < ColorSearchTree->topLevelItemCount(); ++i)
		{
			QTreeWidgetItem* topItem = ColorSearchTree->topLevelItem(i);
			QWidget* qWidgetColumn0 = ColorSearchTree->itemWidget(topItem, 0);
			QWidget* qWidgetColumn1 = ColorSearchTree->itemWidget(topItem, 1);
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
		Utility::Logger("ColorSearch -> ClearAllFields() -> End");
	}

	ColorSearch::ColorSearch(QWidget* parent) : QDialog(parent)
	{
		Utility::Logger("ColorSearch -> Constructor() -> Start");
		setupUi(this);
		QFont fontStyle("Times new roman", FONT_SIZE, QFont::Bold);
		QTreeWidgetItem* dataItem = new QTreeWidgetItem;
		QSize size(TABLE_WIDTH, TABLE_HEIGHT);
		Qt::ItemFlags flags;
		flags = dataItem->flags();
		flags |= Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
		dataItem->setFlags(flags);
		this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
		ColorSearchTree->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		ColorSearchTree->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		ColorSearchTree->setStyleSheet("QTreeWidget::item { border-bottom: 1px solid #232323;""padding : 10px;""height: 25px;""}");
		
		ColorSearchTree->setFixedSize(size);
		ColorSearchTree->setColumnWidth(1, USER_INPUT_WIDTH);
		ColorSearchTree->setColumnWidth(0, SEARCH_LABEL_WIDTH);
		headerLabel->setFont(fontStyle);
		layout()->setSizeConstraint(QLayout::SetFixedSize);
		this->adjustSize();
		m_solid = false;
		m_maxRowCount = 0;

		back->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_back_over.svg"));
		back->setIconSize(QSize(iconHieght, iconWidth));
		back->setStyleSheet(buttonFont);

		search->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_search_over.svg"));
		search->setIconSize(QSize(iconHieght, iconWidth));
		search->setStyleSheet(buttonFont);

		QObject::connect(search, SIGNAL(clicked()), this, SLOT(Search_clicked()));
		QObject::connect(back, SIGNAL(clicked()), this, SLOT(back_clicked()));
		QObject::connect(closeWindow, SIGNAL(clicked()), this, SLOT(Cancel_clicked())); //now spelling
		m_isUserInputEmpty = true;
		m_isOnlyPercentileFound = false;
		ReadInforJson();
		ReadJsonAndDrawDialog();
		
		ColorSearchTree->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
		ColorSearchTree->setSelectionBehavior(QAbstractItemView::SelectItems);
		ColorSearchTree->setSelectionMode(QAbstractItemView::NoSelection);
		ColorSearchTree->setSelectionBehavior(QAbstractItemView::SelectRows);
		ColorSearchTree->setEditTriggers(QAbstractItemView::CurrentChanged);
		ColorSearchTree->setTabKeyNavigation(true);
		Utility::Logger("ColorSearch -> Constructor() -> End");
	}
	/*
	*brief read the filtered json file.
	*fill read values to the m_ColorsFieldsVector.
	*calling the drawWidget(m_ColorsFieldsVector) to fill the widget.
	*/
	void ColorSearch::ReadJsonAndDrawDialog()
	{
		Utility::Logger("TrimsSearch -> ReadJsonAndDrawDialog() -> Start");
		m_colorsFieldsVector = Utility::ReadJsonForDrawDialogue("Color");
		DrawWidget(m_colorsFieldsVector);	
		Utility::Logger("ColorSearch -> ReadJsonAndDrawDialog() -> End");
	}
	/*
	*brief input from readJsonAndDrawDialog().
	*create labels and widgetitems(combobox,lineEdit,textarea) from the m_ColorsFieldsVector.
	*calling the drawWidget(m_ColorsFieldsVector) to fill the widget.
	*/
	void ColorSearch::DrawWidget(std::vector<Utility::Fields>& fieldsVector)
	{
		Utility::Logger("ColorSearch -> DrawWidget() -> Start");
		json keyValuePairs = Utility::GetKeyValuePairs();

		for each (auto field in fieldsVector)
		{
			string tempLabel = field.labelValue.toStdString();
			if (columnsMap.find(tempLabel) != columnsMap.end()) {
				tempLabel = columnsMap.at(tempLabel);
			}
			else {
				QString displayValue = Utility::GetDisplayValueByKey(QString::fromStdString(tempLabel), QString::fromStdString("color"), keyValuePairs);
				if (displayValue.isNull() || displayValue.isEmpty())
				{
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
				ColorSearchTree->addTopLevelItem(topLevel);
				ColorSearchTree->setItemWidget(topLevel, 0, label);
				ColorSearchTree->setItemWidget(topLevel, 1, lineEdit);
				lineEdit->setText(field.userInputValues);

			}

			if (field.fieldUItype == "dropdown")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();
				QComboBox* comboBox = new QComboBox();
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);
				
				label->setText(QString::fromStdString(tempLabel));
				comboBox->setStyleSheet(inputStyle);
				ColorSearchTree->addTopLevelItem(topLevel);
				ColorSearchTree->setItemWidget(topLevel, 0, label);
				ColorSearchTree->setItemWidget(topLevel, 1, comboBox);
				comboBox->setStyleSheet("combobox-popup: 0; font: 75 8pt \"Times New Roman\"; combobox-popup:0 ");
				comboBox->addItems(field.presetValues);
				int indexOfEmptyString = comboBox->findText("Select");
				comboBox->setCurrentIndex(indexOfEmptyString);
			}

			if (field.fieldUItype == "textarea")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();
				QTextEdit* textEdit = new QTextEdit();
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);
				
				label->setText(QString::fromStdString(tempLabel));
				ColorSearchTree->addTopLevelItem(topLevel);
				ColorSearchTree->setItemWidget(topLevel, 0, label);
				ColorSearchTree->setItemWidget(topLevel, 1, textEdit);
				textEdit->setText(field.userInputValues);
				textEdit->setStyleSheet("border: 1px solid black;" 
					"background-color: #222222;" 
					"font: 75 8pt \"Times New Roman\";");
				textEdit->setMaximumSize(TEXTEDIT_SIZE_WIDTH, TEXTEDIT_SIZE_HEIGHT);
			}

			if (field.fieldUItype == "DateEdit")
			{
				QTreeWidgetItem* topLevel = new QTreeWidgetItem();
				QDateEdit* dateTimeEdit = new QDateEdit();
				bool enable = true;
				dateTimeEdit->setCalendarPopup(enable);
				QString dataricovero("");
				QDate date = QDate::fromString(dataricovero, "");
				QLabel* label = new QLabel();
				label->setStyleSheet(inputFont);
				
				label->setText(QString::fromStdString(tempLabel));
				ColorSearchTree->addTopLevelItem(topLevel);
				ColorSearchTree->setItemWidget(topLevel, 0, label);
				ColorSearchTree->setItemWidget(topLevel, 1, dateTimeEdit);
			}
		}
		Utility::Logger("ColorSearch -> DrawWidget() -> End");
	}

	ColorSearch::~ColorSearch()
	{

	}



	/*
	*brief when the user cliked search button.
	*call validate UI feild.
	*call createSearchMap() to create parameter 
	*PLMSearch to make a rest call.
	*/
	void ColorSearch::Search_clicked()
	{
		Utility::Logger("ColorSearch -> Search_clicked() -> Start");
		
		if (Utility::ExtractAllUIValuesAndMapToJson(ColorSearchTree, m_colorsFieldsVector) && Utility::SearchValidation(ColorSearchTree))
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
		Utility::Logger("ColorSearch -> Search_clicked() -> End");
	}
	/*
	*brief crete map.json file.
	*called from Search_clicked().
	*it have the parameter to make the rest call, what the user filled UI as a input.
	*/
	void ColorSearch::CreateSearchMap()
	{
		Utility::Logger("ColorSearch -> CreateSearchMap() -> Start");
		ofstream newfile;
		newfile.open(DirectoryUtil::getColorSearchJson());
		json emptyJsonObject;
		json mapArray = json::object();
		json pagInfoMap = json::object();
		json filterMap = json::object();
		json conditions = json::object();
		json paletteConditions = json::object();
		conditions["Conditions"] = json::array();
		paletteConditions["Conditions"] = json::array();
		m_colorSearchMap["roleId"] = Configuration::GetInstance()->GetRoleId();
		m_colorSearchMap["userId"] = Configuration::GetInstance()->GetUserId();
		m_colorSearchMap["Schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
		m_colorSearchMap["pageType"] = "list";
		m_colorSearchMap["sortInfo"] = emptyJsonObject;
		//Duplicationg Color Search Map to prepare map for Palette Search
		m_colorPaletteSearchMap = m_colorSearchMap;
		m_colorSearchMap["entity"] = "Colors";
		m_colorSearchMap["fromAi"] = true;
		m_colorPaletteSearchMap["entity"] = "ColorPalette";

		m_colorPaletteSearch = false;
		int count = 0;
		int countPalette = 0;
		string colorPaletteValue = "";
		for (auto arrayElement : m_colorsFieldsVector)
		{
			string attLabel = arrayElement.labelValue.toStdString();
			string userSelected = arrayElement.userInputValues.toStdString();
			if ((userSelected != "") && (userSelected != "Select"))
			{
				if ((arrayElement.fieldUItype == "dropdown") && (arrayElement.userInputValues != "Select"))
				{
					for (auto it = m_attributeMap.begin(); it != m_attributeMap.end(); it++)
					{
						if (it->first == attLabel)
						{
							mapArray["fieldName"] = it->second;
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
							break;
						}
					}
					//Special handling for Palette Search fields
					if (paletteFields.find(attLabel) == string::npos)
					{
						conditions["Conditions"][count++] = mapArray;
					}
					else
					{
						colorPaletteValue = userSelected;
						m_colorPaletteSearch = true;
					}
				}
				else
				{
					filterMap.clear();
					filterMap["fieldName"] = attLabel;
					filterMap["operator"] = "like";
					filterMap["value"] = userSelected;
					//Special handling for Palette Search fields
					if (paletteFields.find(attLabel) == string::npos)
					{
						conditions["Conditions"][count++] = filterMap;
					}
					else
					{
						colorPaletteValue = userSelected;
						m_colorPaletteSearch = true;
					}
				}
			}
		}
		conditions["Search"] = nullptr;
		//Special handling for Palette Search fields
		paletteConditions["Conditions"] = json::array();
		paletteConditions["Search"] = colorPaletteValue;

		m_colorSearchMap["dataFilter"] = conditions;
		m_colorPaletteSearchMap["dataFilter"] = paletteConditions;
		newfile << m_colorSearchMap;
		newfile.close();
		Utility::Logger("ColorSearch -> CreateSearchMap() -> End");
	}
	/*
	*brief make a rest call to get a response from infor.
	*try catch to remove ®.
	*pass the reponse to create result table as json.
	*/
	void ColorSearch::PLMSearch()
	{
		Utility::Logger("ColorSearch -> PLMSearch() -> Start");
		json paletteColorsResults = json::array();
		json colorsResults = json::array();
		json filteredColorsResults = json::array();
		string colorPaletteSearchMapString = to_string(m_colorPaletteSearchMap);
		//Special handling for Palette Search, If this m_colorPaletteSearch which means Search should be Palette search.
		if (m_colorPaletteSearch)
		{
			string response = RestCall(colorPaletteSearchMapString, COLOR_PALETTE_SEARCH_API);
			json responseJson;
			string errorResponse = Utility::CheckErrorDescription(response);
			Utility::Logger("PLMSearch() errorResponse - " + errorResponse);
			if (errorResponse.empty() && (errorResponse.length() == 0))
			{
				responseJson = Utility::GetResultsJSON(response);
				paletteColorsResults = GetPaletteColorSearchResults(responseJson);
			}
			else
			{
				UTILITY_API->DisplayMessageBox(errorResponse);
			}
		}
		if (Utility::IsValidParameter(m_colorSearchMap))
		{
			Utility::Logger("ColorSearch() param - " + to_string(m_colorSearchMap));
			string response = RestCall(to_string(m_colorSearchMap), COLOR_SEARCH_API);
			Utility::Logger("PLMSearch() response - " + response);
			json responseJson;
			string errorResponse = Utility::CheckErrorDescription(response);
			Utility::Logger("PLMSearch() errorResponse - " + errorResponse);
			if (errorResponse.empty() && (errorResponse.length() == 0))
			{
				responseJson = Utility::GetResultsJSON(response);
				colorsResults = GetColorSearchResults(responseJson);
			}
			else
			{
				UTILITY_API->DisplayMessageBox(errorResponse);
			}
		}
		filteredColorsResults = GetFilteredColorResults(paletteColorsResults, colorsResults);
		CreateResultTable(filteredColorsResults);
		Utility::Logger("ColorSearch -> PLMSearch() -> End");
	}

	/*
	*brief GetFilteredColorResults- filter out paletteColor and color critriea matches
	returns - json
	*/
	json ColorSearch::GetFilteredColorResults(json& paletteColorsResults, json& colorsResults)
	{
		Utility::Logger("ColorSearch -> GetFilteredColorResults() -> Start");
		json filteredResults = json::array();
		string paletteColor = "";
		string paletteColorCode = "";
		json paletteColorJSON = "";
		string color = "";
		string colorCode = "";
		json colorJSON = "";
		filteredResults.clear();
		if (m_colorPaletteSearch)
		{
			if (paletteColorsResults.size() != 0)
			{
				if (Utility::IsValidParameter(m_colorSearchMap))
				{
					if (colorsResults.size() != 0)
					{
						for (int i = 0; i < paletteColorsResults.size(); i++)
						{
							paletteColor = Utility::GetJSONValue<int>(paletteColorsResults, i, false);
							paletteColorJSON = json::parse(paletteColor);
							paletteColorCode = Utility::GetJSONValue<string>(paletteColorJSON, "Code", true);
							for (int j = 0; j < colorsResults.size(); j++)
							{
								color = Utility::GetJSONValue<int>(colorsResults, j, false);
								colorJSON = json::parse(color);
								colorCode = Utility::GetJSONValue<string>(colorJSON, "Code", true);
								if (paletteColorCode == colorCode)
								{
									filteredResults.push_back(paletteColorJSON);
									break;
								}
							}
						}
					}
					else
					{
						filteredResults = json::array();
					}
				}
				else
				{
					filteredResults = paletteColorsResults;
				}
			}
		}
		else
		{
			filteredResults = colorsResults;
		}
		Utility::Logger("ColorSearch -> GetFilteredColorResults() -> End");
		return filteredResults;
	}
	/*
	*brief GetColorSearchResults- gives results  based on color critriea matches
	returns - json
	*/
	json ColorSearch::GetColorSearchResults(json& responseJson)
	{
		Utility::Logger("ColorSearch -> GetColorSearchResults() -> Start");
		json colorsarray = json::array();
		json entitiesJSONArray = json::array();
		try {
			string entity = "";
			string name = "";
			json entityJSON = "";
			string color = "";
			json colorJSON = "";
			string entities = Utility::GetJSONValue<string>(responseJson, "entities", false);
			entitiesJSONArray = json::parse(entities);
			if (entitiesJSONArray.size() != 0)
			{
				for (int i = 0; i < entitiesJSONArray.size(); i++)
				{

					entity = Utility::GetJSONValue<int>(entitiesJSONArray, i, false);
					entityJSON = json::parse(entity);
					name = Utility::GetJSONValue<string>(entityJSON, "name", true);

					if (name == "Colors")
					{
						color = Utility::GetJSONValue<string>(entityJSON, "column", false);
						colorJSON = json::parse(color);
						colorsarray.push_back(colorJSON);
					}
				}
			}
		}
		catch (exception & e)
		{
			Utility::Logger("ColorSearch::GetColorSearchResults()::parsing  exception - " + string(e.what()));
			throw e.what();
		}
		Utility::Logger("ColorSearch -> GetColorSearchResults() -> End");
		return colorsarray;
	}

	/*
	*brief GetColorSearchResults- gives results  based on color Palette critriea matches
	returns - json
	*/
	json ColorSearch::GetPaletteColorSearchResults(json& responseJson)
	{
		Utility::Logger("ColorSearch -> GetPaletteColorSearchResults() -> Start");
		json colorsarray = json::array();
		json colors = json::array();
		json entitiesJSONArray = json::array();
		try {
			string entity = "";
			string name = "";
			string column = "";
			string paletteName = "";
			json entityJSON = "";
			json columnJSON = "";
			string entities = Utility::GetJSONValue<string>(responseJson, "entities", false);
			entitiesJSONArray = json::parse(entities);

			if (entitiesJSONArray.size() != 0)
			{
				string color = "";
				string colorName = "";
				string colorCode = "";
				string colorStatus = "";
				string colorStatusLookUp = "";
				json colorJSON = "";
				for (int i = 0; i < entitiesJSONArray.size(); i++)
				{

					entity = Utility::GetJSONValue<int>(entitiesJSONArray, i, false);
					entityJSON = json::parse(entity);

					name = Utility::GetJSONValue<string>(entityJSON, "name", true);

					if (name == "ColorPalette")
					{
						column = Utility::GetJSONValue<string>(entityJSON, "column", false);
						columnJSON = json::parse(column);
						paletteName = Utility::GetJSONValue<string>(columnJSON, "Name", true);
						string ColorPaletteValues = columnJSON["ColorPaletteValues"].dump();
						colors = json::parse(ColorPaletteValues);
						if (colors.size() != 0)
						{
							for (int i = 0; i < colors.size(); i++)
							{
								color = Utility::GetJSONValue<int>(colors, i, false);
								colorJSON = json::parse(color);
								colorName = Utility::GetJSONValue<string>(colorJSON, "ColorName", true);
								colorCode = Utility::GetJSONValue<string>(colorJSON, "ColorCode", true);
								colorStatus = Utility::GetJSONValue<string>(colorJSON, "ColorStatus", true);
								colorStatusLookUp = Utility::GetJSONValue<string>(colorJSON, "ColorStatus_Lookup", false);
								colorJSON["Name"] = colorName;
								colorJSON["Code"] = colorCode;
								colorJSON["Status"] = colorStatus;
								colorJSON[COLOR_PALETTE] = paletteName;
								colorJSON["Status_Lookup"] = json::parse(colorStatusLookUp);
								colorsarray.push_back(colorJSON);
							}
						}
					}
				}
			}
		}
		catch (exception & e)
		{
			Utility::Logger("ColorSearch::GetPaletteColorSearchResults()::parsing  exception - " + string(e.what()));
			throw e.what();
		}
		Utility::Logger("ColorSearch -> GetPaletteColorSearchResults() -> End");
		return colorsarray;
	}
	/*
	*brief segregate the response, passing input to result table and execute it.
	*/
	void ColorSearch::CreateResultTable(json& resultsJSON)
	{
		Utility::Logger("ColorSearch -> CreateResultTable() -> Start");
		this->hide();
		map<string, string> fieldUITypeMap = GetFieldUITypes();
		//Special handling for including Palette on to Result table
		if (m_colorPaletteSearch)
		{
			indexColumnIdMap.insert(std::make_pair(100, COLOR_PALETTE));
		}
		else
		{
			indexColumnIdMap.erase(100);
		}
		ColorResultTable::setHeaderColumns(indexColumnIdMap);

		ColorResultTable colorResultsTableObject;
		if (resultsJSON.size() != 0)
		{
			string result = "";
			json resultJSON = "";
			map<string, string> fieldValueMap;
			bool solid = false;
			int rowCount = 0;
			string qimage, column, strcolorSubType, TypeName, strTypeName, strStatus, strShade, strcolorId, strcolorFamily, strColorName, strColorCode,
				thumbnail, colorSubType, strType, strRGB, strCMYK, strPantoneCode, colorName;
			for (int i = 0; i < resultsJSON.size(); i++)
			{
				fieldValueMap.clear();
				result = Utility::GetJSONValue<int>(resultsJSON, i, false);
				resultJSON = json::parse(result);

				for (auto key = indexColumnIdMap.begin(); key != indexColumnIdMap.end(); ++key)
				{
					string columnValue = Utility::getValue(resultJSON[key->second]);

					if (fieldUITypeMap.at(key->second) == "dropdown") {
						
						if (key->second == "ColorFamily")
						{
							columnValue = Utility::getValue(resultJSON["ColorwayFamilyId_Lookup"]["Name"]);
						}
						else if (key->second == COLOR_PALETTE)
						{
							columnValue = Utility::GetJSONValue<string>(resultJSON, COLOR_PALETTE, true);
						}
						else
						{
							columnValue = Utility::getValue(resultJSON[key->second + "_Lookup"]["Name"]);
						}
					}

					fieldValueMap.insert(make_pair(key->second, columnValue));
				}

				strRGB = resultJSON["RGB"].dump();
				strRGB = strRGB.erase(0, 1);
				strRGB = strRGB.erase(strRGB.size() - 1);
				fieldValueMap.insert(make_pair("RGB", strRGB));

				strCMYK = resultJSON["CMYK"].dump();
				strCMYK = strCMYK.erase(0, 1);
				strCMYK = strCMYK.erase(strCMYK.size() - 1);
				fieldValueMap.insert(make_pair("CMYK", strCMYK));

				strType = resultJSON["Type"].dump();
				{
					TypeName = resultJSON["Color_Type_Lookup"]["Name"].dump();
					TypeName = TypeName.erase(0, 1);
					TypeName = TypeName.erase(TypeName.size() - 1);
				}

				if (strType == "1")
				{
					strTypeName = "Single";
					m_solid = true;
				}
				else if (strType == "2")
				{
					strTypeName = "Combination";
					m_solid = false;
				}
				else if (strType == "3")
				{
					strTypeName = "Print";
					m_solid = false;
				}

				colorName = resultJSON["Name"].dump();
				if (colorName != "null")
				{
					colorName = colorName.erase(0, 1);
					colorName = colorName.erase(colorName.size() - 1);
				}
				else
					colorName = " ";
				fieldValueMap.insert(make_pair("Name", colorName));

				strPantoneCode = resultJSON["PantoneCode"].dump();
				if (strPantoneCode != "null")
				{
					strPantoneCode = strPantoneCode.erase(0, 1);
					strPantoneCode = strPantoneCode.erase(strPantoneCode.size() - 1);
				}
				else
					strPantoneCode = " ";
				fieldValueMap.insert(make_pair("Pantone", strPantoneCode));


				string family = resultJSON["ColorwayFamilyId"].dump();
				if (family != "null")
				{
					strcolorFamily = resultJSON["ColorwayFamilyId_Lookup"]["Name"].dump();
					strcolorFamily = strcolorFamily.erase(0, 1);
					strcolorFamily = strcolorFamily.erase(strcolorFamily.size() - 1);
				}
				else
					strcolorFamily = " ";
				fieldValueMap.insert(make_pair("ColorFamily", strcolorFamily));


				string AltName = resultJSON["AltName"].dump();
				if (AltName != "null")
				{
					AltName = AltName.erase(0, 1);
					AltName = AltName.erase(AltName.size() - 1);
				}
				else
					AltName = " ";
				fieldValueMap.insert(make_pair("AltName", AltName));
				if (strTypeName == "Single")
				{
					rowCount++;
					solid = m_solid;
					colorResultsTableObject.AddRowData(fieldValueMap);
					m_solid = false;
				}
			}
			if (rowCount > m_maxRowCount)
			{
				UTILITY_API->DisplayMessageBox("Number of records are exceeding the maximum limit. Please refine your search criteria.");
				this->show();
			}
			else if (solid)
			{
				colorResultsTableObject.setModal(true);
				colorResultsTableObject.exec();
			}
			else
			{
				UTILITY_API->DisplayMessageBox("Non solid colors are not supported");
				this->show();
			}
		}
		else
		{
			UTILITY_API->DisplayMessageBox("No result found");
			this->show();
		}
		Utility::Logger("ColorSearch -> CreateResultTable() -> End");
	} 
	/*
	*brief clik of back buuton go back to the DesignSuite UI. 
	*/
	void ColorSearch::back_clicked()
	{
		Utility::Logger("ColorSearch -> back_clicked() -> Start");
		this->hide();
		DesignSuite::GetInstance()->setModal(true);
		DesignSuite::GetInstance()->show();
		Utility::Logger("ColorSearch -> back_clicked() -> End");
	}
	/*
	*brief clik of Cancle button close the current UI.
	*/
	void ColorSearch::Cancel_clicked()
	{
		Utility::Logger("ColorSearch -> Cancel_clicked() -> Start");
		this->close();
		Utility::Logger("ColorSearch -> Cancel_clicked() -> End");
	}



	/*
	*brief read the json file to get visible fields for color
	*retunr list of fields
	*/
	std::list<string> ColorSearch::getVisibleFieldList() {
		Utility::Logger("ColorSearch::getVisibleFieldList() Started...");
		json colorJson, entityData;
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
			Utility::Logger("ColorSearch::getVisibleFieldList()::parsing entities exception - " + string(e.what()));
			throw e.what();
		}
		if (entityData.size() != 0) {
			json colors, colsJson;
			for (int i = 0; i < entityData.size(); i++)
			{
				string entityJson = entityData[i].dump();
				try {
					colors = json::parse(entityJson);
				}
				catch (exception& e)
				{
					Utility::Logger("ColorSearch::getVisibleFieldList()::parsing entityJson exception - " + string(e.what()));
					throw e.what();
				}
				string name = colors["name"].dump();
				name = name.erase(0, 1);
				name = name.erase(name.size() - 1);

				if(name == "Colors")
				{
					client_version = colors["client-version"].dump();
					string maxRows = colors["maxResultCount"].dump();
					m_maxRowCount = stoi(maxRows);
					if (client_version != "null" && !client_version.empty())
					{
						client_version = client_version.erase(0, 1);
						client_version = client_version.erase(client_version.size() - 1);
					}

					string searchable_columns = colors["searchable_columns"].dump();
					try {
						colsJson = json::parse(searchable_columns);
					}
					catch (exception& e)
					{
						Utility::ErrorLogger("ColorSearch::getVisibleFieldList() exception - " + string(e.what()));
						throw e.what();
					}
					for (int j = 0; j < colsJson.size(); j++) {
						string column = colsJson[j];
						searchColumns.push_back(column);
					}
				}
			}
		}
		Utility::Logger("ColorSearch::getVisibleFieldList() Ended...");
		return searchColumns;
	}
	/*
	*brief read the colorDetails.json file crete the colorSearchFiltered.json.
	*colorSearchFiltered.json file is input for the ColorSearch UI.
	*/
	void  ColorSearch::ReadInforJson() 
	{
		Utility::Logger("ColorSearch -> ReadInforJson() -> Start");
		std::list<string> visibleColumns = getVisibleFieldList();
		string entity = "Color";
		string parameter = "{\"roleId\":" + Configuration::GetInstance()->GetRoleId() + ",\"userId\":" + Configuration::GetInstance()->GetUserId() + ",\"entity\":\"Colors\",\"pageType\":\"details\",\"dataFilter\":{\"conditions\":[{\"fieldname\":\"Id\",\"operator\":\"=\",\"value\":\"\"}]},\"pageInfo\":null,\"Schema\":" + Configuration::GetInstance()->GetschemaWithQuotes() + "}";
		Utility::GetFilteredJson(parameter,COLOR_DETAILS_API, entity);
		json completeStyleJson;
		m_attsDropdownListMap.clear();
		m_attributeMap.clear();
		columnsMap.clear();
		ifstream filename(DirectoryUtil::getColorDetailJson());
		filename >> completeStyleJson;
		filename.close();
		ofstream newfile(DirectoryUtil::getColorSearchFilteredJson());
		json finalJsontoSave;
		auto jsonFieldList = json::array();
		auto jsonUiTypeList = json::object();
		auto presetArray = json::array();
		auto presetList = json::object();
		auto jsonDataFieldList = json::object();
		auto jsonMandatoryFieldsList = json::array();
		int uiPresetCount = 0;
		string completeStyleJsonString, componentsString, compObjString;
		completeStyleJsonString = completeStyleJson.dump();
		json jsonObject, componentsJson;
		try {
			jsonObject = json::parse(completeStyleJsonString);
			componentsString = jsonObject["layout"]["components"].dump();
			componentsJson = json::parse(componentsString);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("ColorSearch::ReadInforJson()::parsing jsonObject exception - " + string(e.what()));
			throw e.what();
		}
		m_attributeMap.insert(std::make_pair(COLOR_PALETTE, COLOR_PALETTE));
		jsonUiTypeList[COLOR_PALETTE] = "text";
		jsonDataFieldList[COLOR_PALETTE] = COLOR_PALETTE;
		json compObjJson, propsJson;
		string propsString;
		for (int i = 0; i < componentsJson.size(); i++) {
			compObjString = componentsJson[i].dump();
			try {
				compObjJson = json::parse(compObjString);
				propsString = compObjJson["props"].dump();
				propsJson = json::parse(propsString);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("ColorSearch::ReadInforJson()::parsing entityJson exception - " + string(e.what()));
				throw e.what();
			}
			string visible = propsJson["isVisibleAi"].dump();
			string dataField = compObjJson["dataField"].dump();
			dataField = dataField.erase(0, 1);
			dataField = dataField.erase(dataField.size() - 1);

			if (std::find(visibleColumns.begin(), visibleColumns.end(), dataField) != visibleColumns.end())
			{
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
				
				string requi = propsJson["isRequired"].dump();
				if (lookupRef == "ul")
				{
					m_attributeMap.insert(std::make_pair(dataField, dataField));
					jsonUiTypeList[dataField] = fieldType;
					jsonDataFieldList[dataField] = dataField;
					jsonFieldList.push_back(dataField);
					indexColumnIdMap.insert(make_pair(std::stoi(tabIndex), dataField));
					if (requi == "true")
					{
						jsonMandatoryFieldsList.push_back(dataField);
					}
					if (label != "ul") {
						columnsMap.insert(std::make_pair(dataField, label));
					}
				}
				else
				{
					m_attributeMap.insert(std::make_pair(lookupRef, dataField));
					jsonUiTypeList[lookupRef] = fieldType;
					jsonDataFieldList[lookupRef] = dataField;
					indexColumnIdMap.insert(make_pair(std::stoi(tabIndex), lookupRef));
					jsonFieldList.push_back(lookupRef);
					if (requi == "true")
					{
						jsonMandatoryFieldsList.push_back(lookupRef);
					}
					if (label != "ul") {
						columnsMap.insert(std::make_pair(lookupRef, label));
					}
				}

				if (fieldType == "dropdown")
				{
					string lookups = jsonObject["lookups"].dump();
					json lookupsJSON;
					try {
						lookupsJSON = json::parse(lookups);
					}
					catch (exception& e)
					{
						Utility::ErrorLogger("ColorSearch::ReadInforJson()::parsing lookupsJSON exception - " + string(e.what()));
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
					presetList[lookupRef] = presetArray;
					m_attsDropdownListMap.insert(std::make_pair(lookupRef, tempAttribMap));
				}

			}
		}

		auto newjsonFieldList = json::array();
		for (auto itr = indexColumnIdMap.begin(); itr != indexColumnIdMap.end(); itr++)
		{
			newjsonFieldList.push_back(itr->second);
		}
		//presetList[COLOR_PALETTE] = GetColorPaletteList();
		newjsonFieldList.push_back(COLOR_PALETTE);
		finalJsontoSave["fieldList"] = newjsonFieldList;
		finalJsontoSave["uiTypeList"] = jsonUiTypeList;
		finalJsontoSave["presetList"] = presetList;
		finalJsontoSave["mandatory_fieldList"] = jsonMandatoryFieldsList;
		finalJsontoSave["dataFieldList"] = jsonDataFieldList;
		newfile << finalJsontoSave;
		newfile.close();
		Utility::Logger("ColorSearch -> ReadInforJson() -> End");
	}
	/*
	*brief GetColorPaletteList- get palette list
	returns - json
	*/
	json ColorSearch::GetColorPaletteList()
	{
		Utility::Logger("ColorSearch -> GetColorPaletteList() -> Started");
		auto presetArray = json::array();

		json colorPalSearchMap = Utility::GetBlankJSONParameter("ColorPalette");
		string response = RestCall(to_string(colorPalSearchMap), COLOR_PALETTE_SEARCH_API);
		string errorResponse = Utility::CheckErrorDescription(response);
		Utility::Logger("GetColorPaletteList() errorResponse - " + errorResponse);
		if (errorResponse.empty() && (errorResponse.length() == 0))
		{
			try
			{
				json responseJson = Utility::GetResultsJSON(response);
				string entities = Utility::GetJSONValue<string>(responseJson, "entities", false);
				json completeEntitiesJson = json::parse(entities);
				presetArray.push_back("Select");
				if (completeEntitiesJson.size() != 0)
				{
					string entity = "";
					json entityJSON = json::object();
					string name = "";
					string column = "";
					string columnValue = "";
					json columnJSON = json::object();
					for (int i = 0; i < completeEntitiesJson.size(); i++)
					{
						entity = Utility::GetJSONValue<int>(completeEntitiesJson, i, false);
						entityJSON = json::parse(entity);
						name = Utility::GetJSONValue<string>(entityJSON, "name", true);
						if (name == "ColorPalette")
						{
							column = Utility::GetJSONValue<string>(entityJSON, "column", false);
							//columnJSON = json::parse(column);
							columnJSON = json::parse(QString::fromStdString(column).toUtf8().constData());
							columnValue = Utility::GetJSONValue<string>(columnJSON, "Name", true);
							presetArray.push_back(columnValue);
							map<string, string> tempAttribMap;
						}
					}
				}
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("ColorSearch::GetColorPaletteList()::parsing  exception - " + string(e.what()));
				throw e.what();
			}
		}
		else
		{
			UTILITY_API->DisplayMessageBox(errorResponse);
		}
		Utility::Logger("ColorSearch -> GetColorPaletteList() -> End");
		return presetArray;
	}
	/**
	 * \brief Function is used to get header columns of result table
	 * \param list
	 */
	map<string, string> ColorSearch::GetFieldUITypes() 
	{
		Utility::Logger("ColorSearch::GetFieldUITypes() Started...");
		json jsonString;
		map<string, string> fields;
		ifstream filename;
		filename.open(DirectoryUtil::getColorSearchFilteredJson());
		filename >> jsonString;
		filename.close();
		string completeJsonString, fieldValues, uiTypelist;
		completeJsonString = jsonString.dump();
		json completeJson, fieldValuesJson, uiTypeJson;
		try {
			completeJson = json::parse(completeJsonString);
			fieldValues = completeJson["fieldList"].dump();
			fieldValuesJson = json::parse(fieldValues);

			uiTypelist = completeJson["uiTypeList"].dump();
			uiTypeJson = json::parse(uiTypelist);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("ColorSearch::GetFieldUITypes() ::parsing  exception - " + string(e.what()));
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
		Utility::Logger("ColorSearch::GetFieldUITypes() Ended...");
		return fields;
	}
}