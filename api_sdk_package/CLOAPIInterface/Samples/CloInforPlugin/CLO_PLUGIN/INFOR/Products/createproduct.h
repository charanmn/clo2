#ifndef CREATEPRODUCT_H
#define CREATEPRODUCT_H

#include <QDialog>
#include <string>
#include <iostream>
#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateTimeEdit> 
#include <QComboBox>
#include <QLabel>
#include <QTreeWidgetItem>
#include <QTableWidgetItem>
#include <vector>
#include <set>
#include <map>
#include "GeneratedFiles/ui_createproduct.h"
#include "CLO_PLUGIN/INFOR/Utilities/Definitions.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"

#include "CLO_PLUGIN/INFOR/Libraries/json.h"
using json = nlohmann::json;

namespace CLOPlugin
{
	class  createProduct : public QDialog, public Ui::createProduct
	{
		Q_OBJECT
		static createProduct* _instance;
		std::vector<Utility::Fields> m_createFieldsVector;
		json m_createProductMap;
		bool m_isSaveClicked;
		std::map<string, string> m_attributeMap;
		std::map<string, string> createColumnsMap;
		map<string, map<string, string>> m_attsDropdownListMap;
		string m_idGenContextVal;
		string m_idGenContextVal2;
		json m_idGenVal;
		bool m_isUserInputEmpty;
		std::map<string, map<string, string>> m_IdGeneratorMap;
		string m_addedCode;
		string m_styleID;
		map<float, string, less <float> > m_indexColumnIdMap;
		bool m_IdGenSettingsAvailable;
		json m_idGenSettingsJson;
		multimap<string, string> m_orgLevelIdMap;
		multimap<string, string> m_parentIdNameMap;
		map<int, string, less<int>> m_orgLevelIdLookUpMap;
		multimap<string, string> m_parentIdLookUpMap;
		multimap<string, string> m_hierarchyMap;
		list<string> m_clearItems;
		map<string, string> m_lookupIdMap;
		set<string> m_nonDependentFields;
		string m_rootItem;
		map<string, string> m_levelLookupMap;
		list<string> m_rootItemOtions;
		QStringList m_statusPresetValues;
		bool m_waikiki;

	public:
		static createProduct* GetInstance();
		static void			Destroy();
		createProduct(QWidget* parent = 0);
		~createProduct();
		string m_ImageNameTemp;
		void ReadJsonAndDrawDialog();
		void DrawWidget(std::vector<Utility::Fields>& fieldsVector);
		void ReadPLMJson();
		void CreateProductCreateMap();
		string CreateImageParam(string response, string key);
		string CreateZipParam(string response, string key);
		void ClearAllFields();
		bool IsSaveClicked();
		void GetIdGeneratorSettings();
		void ParseIDGeneratorJson(json idGenSettingsJson);
		bool ExtractAllUIValues();
		void SetIdGeneratorMap(IN const json& lookUpsJson, IN const string& attributeValue);
		string GetUserInputForIdGeneration(const string& label);
		bool IsStyleCodeEnabled();
		string CreateMetaDataForCurrentGarment();
		map<string, map<string, QString>> SetDropDownValues(string& selectedItem, string& id);
		void FilterDependencyList();

	private slots:
		void Save_clicked();
		void Cancel_clicked();
		void on_Back_clicked();
		void sendToPLM_clicked();
		void handleDropDownValueChangeEvent(const QString& item);

	signals:
		void CreateProductBackClicked();
	};
}
#endif // CREATEPRODUCT_H
