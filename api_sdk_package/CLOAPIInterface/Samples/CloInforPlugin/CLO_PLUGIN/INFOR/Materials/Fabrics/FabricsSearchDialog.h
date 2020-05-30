#pragma once

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
#include <map>
#include "GeneratedFiles/ui_FabricsSearchDialog.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
using json = nlohmann::json;

namespace CLOPlugin
{
	class  MaterialSearchDialog : public QDialog, public Ui_MaterialSearchDialog
	{
		Q_OBJECT
			std::vector<Utility::Fields> m_materialsFieldsVector;
			static MaterialSearchDialog* _instance;
			std::map<string, string> m_attributeMap;
			map<string, map<string, string>> m_attsDropdownListMap;
			json m_materialSearchMap;
			bool m_isUserInputEmpty;
			bool m_isOnlyPercentileFound;
			string m_currentBrandName;
			QStringList m_divisionPresetValues;
			map<int, string, less <int> > indexColumnIdMap;

			multimap<string, string> m_parentIDOrgIDMap;
			multimap<string, string> m_NameOrgIDMap;
			multimap<string, string> m_GlVNameOrgIDMap;
			multimap<string, std::pair<string, string>> m_LookUpOrgNameGLValIDMap;
			multimap<string, std::pair<string, string>> m_LookUpRefLookUpNameOrgIdMap;
			multimap<string, string> m_parentIdLookUpMap;
			multimap<string, string> m_orgLevelIdLookUpMap;
			multimap<string, string> m_hierarchyMap;
		
	public:
		MaterialSearchDialog(QWidget* parent = 0);
		static MaterialSearchDialog*	GetInstance();
		static void	Destroy();
		~MaterialSearchDialog(); 
		void ReadPLMJson();
		void ReadJsonAndDrawDialog();
		void DrawWidget(std::vector<Utility::Fields>& fieldsVector);
		void CreateResultTable(json& responseJson);
		void CreateSearchMap();
		void PLMSearch();
		void ClearAllFields();
		void DownloadAtachment(string materialId, string materialCode, string& atachedFilenameToSave);
		void GetMaterialAttachments(json response, string code, string& atachedFilenameToSave);
		json SetDependenciesToWidgets();
		string GetDependencies();
		void FilterDependencyList();
		int GetMaxResultsCount();
		void SetDefaultPresetValues();

	private:
		map<string, string> GetFieldUITypes();

	private slots:

		void Search_clicked();
		void Cancel_clicked();
		void back_clicked();
		void handleDropDownValueChangeEvent(const QString& item);
		

		
		
	};
}
