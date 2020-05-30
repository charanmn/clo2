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
#include "GeneratedFiles/ui_TrimsSearch.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h" 
#include "CLO_PLUGIN/INFOR/Libraries/json.h" 
/**
 *  CLOPlugin namespace is used to keep all the functions in this class to be under CLOPlugin namespace.
 */
using json = nlohmann::json; // making use of json and mapjson from nlohmann json
/**
 *  CLOPlugin namespace is used to keep all the functions and attributes in this class to be under CLOPlugin namespace.
 */
namespace CLOPlugin
{
	class  TrimsSearch : public QDialog, public Ui::TrimsSearch
	{
		Q_OBJECT
			std::vector<Utility::Fields> m_trimSearchFieldsVector;
			static TrimsSearch* _instance;
			std::map<string, string> m_attributeMap;
			map<string, map<string, string>> m_attsDropdownListMap;
			json m_TrimSearchMap;
			bool m_isUserInputEmpty;
			bool m_isOnlyPercentileFound;
			map<int, string, less <int> > m_indexColumnIdMap;
			bool m_isVisibleAvailable;
			int m_maxRowCount;
			bool m_attachmentExists;
			multimap<string, string> m_parentIDOrgIDMap;
			multimap<string, string> m_NameOrgIDMap;
			multimap<string, string> m_GlVNameOrgIDMap;
			multimap<string, std::pair<string, string>> m_LookUpOrgNameGLValIDMap; 
			multimap<string, std::pair<string, string>> m_LookUpRefLookUpNameOrgIdMap;
			multimap<string, string> m_parentIdLookUpMap;
			multimap<string, string> m_orgLevelIdLookUpMap;
			multimap<string, string> m_hierarchyMap; 
			 
	public:
		TrimsSearch(QWidget* parent = 0);
		static TrimsSearch* GetInstance();
		static void	Destroy();
		~TrimsSearch();
		void ReadPLMJson();
		void ReadJsonAndDrawDialog();
		void DrawWidget(std::vector<Utility::Fields>& fieldsVector);
		string DownloadAtachment(string trimId, string trimCode);
		string GetTrimAttachments(json response, string code);
		void CreateResultTable(json& responseJson);
		void CreateSearchMap();
		void PLMSearch();
		void ClearAllFields();
		string GetDependencies();
		json SetDependenciesToWidgets();
		std::list<string> getVisibleFieldList();
		void FilterDependencyList();
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
