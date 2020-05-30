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
#include <set>
#include "GeneratedFiles/ui_ProductSearch.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
using json = nlohmann::json;

namespace CLOPlugin
{
	class  ProductSearch : public QDialog, public Ui::ProductSearch
	{
		Q_OBJECT
		std::vector<Utility::Fields> m_searchFieldsVector;
		static ProductSearch* _instance;
		json m_productSearchMap;
		bool m_isUserInputEmpty;		
		bool m_isOnlyPercentileFound;
		std::map<string, string> m_attributeMap;
		map<string, map<string, string>> m_attsDropdownListMap;
		json m_downloadAttachmentsMap;
		json m_downloadImagesMap;
		QString m_attachmentsName;
		QString m_attachmentsURL;
		QString m_attachmentsAttaFileListId;
		QString m_imageName;
		QString m_imageURL;
		QString m_imageAttaFileListId;
		map<float, string, less <float> > m_indexColumnIdMap;
		multimap<string, string> m_orgLevelIdMap;
		multimap<string, string> m_parentIdNameMap;
		map<int, string, less<int>> m_orgLevelIdLookUpMap;
		multimap<string, string> m_parentIdLookUpMap;
		multimap<string, string> m_hierarchyMap;
		list<string> m_clearItems;
		map<string, string> m_lookupIdMap;
		string m_rootItem;
		map<string, string> m_levelLookupMap;
		list<string> m_rootItemOtions;
		set<string> m_nonDependentFields;

	public:
		ProductSearch(QWidget* parent = 0);
		static ProductSearch*	GetInstance();
		static void			Destroy();
		bool			 bstyleImage;
		bool			 bstyleAttachment;

		QStringList		m_divisionPresetValues;
		QStringList		m_categoryPresetValues;
		QStringList		m_subCategoryPresetValues;
		QStringList		m_subSubCategoryPresetValues;
		
		~ProductSearch();

		void ReadJsonAndDrawDialog();
		void DrawWidget(std::vector<Utility::Fields>& fieldsVector);
		void ReadPLMJson();
		void CreateResultTable(json responseJson);
		void CreateProductSearchMap();
		void PLMSearch();
		void ClearAllFields();
		map<string, map<string, QString>> SetDropDownValues(string& selectedItem, string& id);
		json CreateDownloadAttachmentsMap(int styleID, string code);
		void DownloadStyleAttachments();
		void DownloadStyleImages();
		void GetStyleAttachments(json response);
		void GetStyleImages(json response);
		int GetMaxResultsCount();
		void FilterDependencyList();
		void ResetNonDependentItems(list<string>& resetFields);

	private:
		map<string, string> GetFieldUITypes();

	private slots:
		void SearchClicked();
		void Cancel_clicked();
		void backclicked();
		void handleDropDownValueChangeEvent(const QString& item);
		
	};
}

