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
#include <set>
#include <map>
#include "GeneratedFiles/ui_UpdateProduct.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"

namespace CLOPlugin
{

	class  UpdateProduct : public QDialog, public Ui::UpdateProduct
	{
		Q_OBJECT
			static UpdateProduct* _instance;
		std::vector<Utility::Fields> m_updateFieldsVector;
		map<string, string> m_ProductResults;
		bool m_isSaveClicked;
		QLineEdit* m_lineEdit;
		QLineEdit* m_lineEditBrand;
		std::map<string, string> m_attributeMap;
		map<string, map<string, string>> m_attsDropdownListMap;
		QString LastUsedStyleCode;
		map<float, string, less <float> > m_indexColumnIdMap;
		string m_keyforUploading;
		bool m_isAttachmentDeleted = false;
		bool m_isAttachementUnlinked = false;
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
		string m_styleCode;

	public:
		UpdateProduct(QWidget* parent = nullptr);
		static UpdateProduct* GetInstance();
		static void			Destroy();

		~UpdateProduct();

		void ReadPLMJson();
		void ReadJsonAndDrawDialog();
		void DrawWidget(std::vector<Utility::Fields>& fieldsVector);
		void FillUpdateProductData(map<string, string>& data);
		void ExtractAllUIValues();
		bool UpdateProductMetaData();
		int GetDocumentIdForFile(string& filename);
		void DeleteDocuments(int attachmentDocLibId, int imageDocLibId = NULL);
		void UnlinkDocuments(int attachmentDocLibId, int imageDocLibId = NULL);
		string CreateImageParam(string response, string key);
		string CreateZipParam(string response, string key);
		void ClearAllFields();
		bool IsSaveClicked();
		void SetAllFields();
		void ClearDownloadedProjectData();
		bool MandatoryFieldsValidation();
		bool IsValidProductForUpdate();
		void UploadZprjAndThumbnailFiles();
		void UpdateMetaDataForCurrentGarment();
		bool linkingAttachment(string& zprjFileResponse, string& imageFileResponse);
		map<string, map<string, QString>> SetDropDownValues(string& selectedItem, string& id);
		void FilterDependencyList();
		void SetUserDefinedValues(int& count);
		void SetPLMAttValues(int& count);

	private slots:

		void updateInPlm_clicked();
		void saveAndClose_clicked();
		void back_clicked();
		void closeWindow_clicked();
		void handleDropDownValueChangeEvent(const QString& item);
	};
}