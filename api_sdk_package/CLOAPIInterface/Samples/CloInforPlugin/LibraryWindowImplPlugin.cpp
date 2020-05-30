#include "stdafx.h"
#include "LibraryWindowImplPlugin.h"

#include <QFileInfo>
#include <QChar>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QtAlgorithms>

#include "classes/APIDefine.h"
#include "classes/APIStorage.h"
#include "classes/APIUtility.h"

#include "CLOAPIInterface.h"


#include "classes/APISigninDialogSample.h"
#include "classes/APISearchDialogSample.h"
#include "classes/PLMSettingsSample.h"

#include "CLO_PLUGIN/INFOR/Authentication/CLOPLMImplementation.h"
#include "CLO_PLUGIN/INFOR/Authentication/CLOPLMSignIn.h"
#include "CLO_PLUGIN/INFOR/Utilities/Configuration.h"
#include "CLO_PLUGIN/INFOR/Utilities/Definitions.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"


// customizing functions
#define USE_LIBRARY_WINDOW_CUSTOM_TAB  1
#define USE_CUSTOM_TAB_AS_DEFAULT	   1
#define USE_PLM_SETTINGS			   1
#define USE_DOFUNCTION				   1
#define USE_STARTUP_DOFUNCTION		   1
#define USE_AFTER_FILE_LOAD_DOFUNCTION 1

namespace CLOAPI
{
	LibraryWindowImplPlugin::LibraryWindowImplPlugin()
	{
		// prepare api storage instance
		API_STORAGE->GenerateAPIItemListForSample();
	}

	LibraryWindowImplPlugin::~LibraryWindowImplPlugin()
	{
		// release api storage instance
		DESTROY_API_STORAGE;
	}

	bool LibraryWindowImplPlugin::EnableCustomUI()
	{
#if USE_LIBRARY_WINDOW_CUSTOM_TAB 
		return true;
#else
		return false;
#endif
	}

	bool LibraryWindowImplPlugin::IsDefaultTab()
	{
#if USE_CUSTOM_TAB_AS_DEFAULT
		return true;
#else
		return false;
#endif
	}

	string LibraryWindowImplPlugin::GetTabName()
	{
		
		string str = "PLM";
		return str;
	}

	string LibraryWindowImplPlugin::GetItemList(const string& itemId, unsigned int pageNo, unsigned int pageSize, CLO_FINDER_SORT sort, bool bAscending, const string& searchText)
	{
		vector<CLOAPISample::LibraryAPIItem> itemList;
		vector<CLOAPISample::LibraryAPIItem> itemListForThePage;

		// search qvariantmap
		QVariantMap searchKeyValue;
		searchKeyValue[META_DATA_KEY_0_DATA_TYPE] = QString(itemId.c_str());

		if(API_STORAGE)
			itemList = API_STORAGE->GetSearchList("", searchKeyValue);

		// sort item list with ascending / descending 
		// - write code (below is the sample; in general PLM server should return the list as sorted)
		if (sort == NAME)
		{
			if (bAscending)
			{
				// use the list as-is; the sample list is sorted in Acscending in default
			}
			else
			{
				// reverse the list; the sample list is sorted in Acscending in default
				vector<CLOAPISample::LibraryAPIItem> sortedItemList;
				unsigned int listSize = (unsigned int)itemList.size();
				for (unsigned int i = 0; i < listSize; ++i)
					sortedItemList.push_back(itemList.at((listSize - 1) - i));

				itemList.clear();
				itemList = sortedItemList;
			}
		}
		else // DATE_TIME
		{
			unsigned int listSize = (unsigned int)itemList.size();

			if (bAscending)
			{
				for (size_t i = 0; i < listSize - 1; ++i)
					for (size_t j = i + 1; j < listSize; ++j)
					{
						if (itemList.at(i).dateTime > itemList.at(j).dateTime)
						{
							CLOAPISample::LibraryAPIItem tempItem = itemList[j];
							itemList[j] = itemList[i];
							itemList[i] = tempItem;
						}
					}
			}
			else
			{
				for (size_t i = 0; i < listSize - 1; ++i)
					for (size_t j = i + 1; j < listSize; ++j)
					{
						if (itemList.at(i).dateTime < itemList.at(j).dateTime)
						{
							CLOAPISample::LibraryAPIItem tempItem = itemList[j];
							itemList[j] = itemList[i];
							itemList[i] = tempItem;
						}
					}
			}
		}

		// get item list with pageNo / pageSize considered 
		// - write code (below is the sample)
		if (itemList.size() > 0)
		{
			for (int i = (int)pageNo - 1; i < (int)pageNo; ++i)
				for (int j = 0; j < (int)pageSize; ++j)
				{
					int curIndex = i * (int)pageSize + j;

					if (curIndex >= (int)itemList.size())
						continue;

					itemListForThePage.push_back(itemList.at(curIndex));
				}
		}

		// get/return json string
		QString jsonStr = generateJSONFromLibraryAPIItemList(itemList);
		string result = jsonStr.toStdString();
		try
		{
			string logPath = Configuration::GetInstance()->GetLogFileName();
			if (logPath == "")
			{
				Utility::CreateErrorLogFileName();
				Utility::CreateLogFileName();
			}
			//Create Cache of PLM Settings reading PLM Setting file
			Configuration::GetInstance()->CachePLMsettingsFromFile();
			if (itemId.compare("DESIGN SUITE") == 0)
			{
				Utility::Logger("connecting to PLM design suit....");
				//checking if user has filled in all the PLMSettings feilds.
				if(Configuration::GetInstance()->ValidatePLMSettings())
				{ 
					CLOPlugin::CLOPLMImplementation plmSearchDlg;
					plmSearchDlg.SetSearchMode(CLOPlugin::PLM_SEARCH);
				}
				else
				{
					UTILITY_API->DisplayMessageBox("Unable to login. Please verify PLM settings.");
					Utility::Logger("Unable to Login. Please Verify PLMSettings.");
				}
			} 
		}
		catch (exception& e)
		{
			UTILITY_API->DisplayMessageBox("Exception!!" + string(e.what()));
			Utility::Logger("LibraryWindowImplPlugin::GetItemList()::Exception!! - " + string(e.what()));

		}
		catch (const char* msg)
		{
			UTILITY_API->DisplayMessageBox("Exception :: " + string(msg));
			Utility::Logger("LibraryWindowImplPlugin::GetItemList()::Exception - " + string(msg));
		}

		return result;
	}

	string LibraryWindowImplPlugin::GetSearchItemList(unsigned int pageNo, unsigned int pageSize, CLO_FINDER_SORT sort, bool bAscending, const string& searchText)
	{
		string result = "";
		return result;
	}

	bool LibraryWindowImplPlugin::GetSearchItemList(const string& itemId, unsigned int pageNo, unsigned int pageSize, CLO_FINDER_SORT sort, bool bAscending, string& resultItemList)
	{
		string result = "";
		CLOAPISample::APISearchDialogSample searchDlg;
		searchDlg.SetSearchModeByItemId(itemId);

		if (searchDlg.exec())
		{			
			if (searchDlg.result() == QDialog::Accepted)
			{
				resultItemList = searchDlg.GetSearchResult();
				return true;
			}				
		}

		return false;
	}


	bool LibraryWindowImplPlugin::GetParentFolderID(const string& itemId, string& parentFolderID)
	{
		return false;	
	}

	CLO_BYTE* LibraryWindowImplPlugin::GetPNGThumbnail(const string& itemId, unsigned int& sizeInByte)
	{
		CLOAPISample::LibraryAPIItem item;
		
		if (API_STORAGE)
		{
			QString filePath;
			if (API_STORAGE->GetIconThumbnailPathWithID(itemId.c_str(), filePath))
			{				
				if (UTILITY_API->IsCLOFileFormatWithThumbnail(filePath.toStdString()))						// for CLO file format which contains thumbnails
				{
					if (UTILITY_API->IsCLOFileFormatWithTripleThumbnail(filePath.toStdString()))			// for CLO file format which contains 3 preview images (index: 0 = front thumbnail, 1 = back thumbnail)
					{
						return UTILITY_API->GetThumbnailInCLOFile(filePath.toStdString(), 0, sizeInByte);	// index: 0 = front thumbnail, 1 = back thumbnail
					}
					else
					{
						// zfab and sst files are unusual case
						if (UTILITY_API && filePath.contains(".zfab", Qt::CaseInsensitive))
							return UTILITY_API->GetThumbnailInCLOFile(filePath.toStdString(), 0, sizeInByte);
						else if (UTILITY_API && filePath.contains(".sst", Qt::CaseInsensitive))
							return UTILITY_API->GetThumbnailInCLOFile(filePath.toStdString(), 0, sizeInByte); // index: 0 = front thumbnail, 1 = back thumbnail
						else
							return UTILITY_API->GetThumbnailInCLOFile(filePath.toStdString(), 0, sizeInByte); // for CLO file format which contains only one thumnail 
					}
				}
				else if (UTILITY_API->IsReadableImageFormat(filePath.toStdString()))							// for common type of images which can be displayed in Library Windows, CLO software
				{
					return FileLoadViaString(filePath, sizeInByte);
				}					
			}
		}

		return NULL;
	}

	string LibraryWindowImplPlugin::GetMetaData(const string& itemId)
	{
		string result = "";
		return result;
	}

	vector<string> LibraryWindowImplPlugin::GetMetaDataKeyListForUI(const string & itemId)
	{
		vector<string> strList;
		
		//strList.push_back(META_DATA_KEY_0_DATA_TYPE.toStdString()); // do not show in list view
		//strList.push_back(META_DATA_KEY_1_SERVICE_DIVISION.toStdString()); // do not show in list view
		strList.push_back(META_DATA_KEY_2_BRAND.toStdString()); // show brand in list view
		strList.push_back(META_DATA_KEY_3_PRODUCT_TYPE.toStdString()); // show product type in list view
		//strList.push_back(META_DATA_KEY_4_SEASON_CREATED.toStdString()); // do not show in list view

		return strList;
	}

	CLO_BYTE* LibraryWindowImplPlugin::GetPreviewImage(const string& itemId, unsigned int& sizeInByte)
	{
		CLOAPISample::LibraryAPIItem item;

		if (API_STORAGE)
		{
			QString filePath;
			if (API_STORAGE->GetPreviewThumbnailPathWithID(itemId.c_str(), filePath))
			{				
				if (UTILITY_API->IsCLOFileFormatWithThumbnail(filePath.toStdString()))						// for CLO file format which contains thumbnails
				{
					if (UTILITY_API->IsCLOFileFormatWithTripleThumbnail(filePath.toStdString()))			// for CLO file format which contains 3 preview images (index: 0 = front thumbnail, 1 = back thumbnail)
					{
						return UTILITY_API->GetThumbnailInCLOFile(filePath.toStdString(), 0, sizeInByte);	// index: 0 = front thumbnail, 1 = back thumbnail
					}
					else
					{
						// zfab and sst files are unusual case
						if (UTILITY_API && filePath.contains(".zfab", Qt::CaseInsensitive))
							return UTILITY_API->GetThumbnailInCLOFile(filePath.toStdString(), 0, sizeInByte);
						else if (UTILITY_API && filePath.contains(".sst", Qt::CaseInsensitive))
							return UTILITY_API->GetThumbnailInCLOFile(filePath.toStdString(), 0, sizeInByte); // index: 0 = front thumbnail, 1 = back thumbnail
						else
							return UTILITY_API->GetThumbnailInCLOFile(filePath.toStdString(), 0, sizeInByte); // for CLO file format which contains only one thumnail 
					}
				}
				else if (UTILITY_API->IsReadableImageFormat(filePath.toStdString()))							// for common type of images which can be displayed in Library Windows, CLO software
				{
					return FileLoadViaString(filePath, sizeInByte);
				}
			}				
		}

		return NULL;
	}

	CLO_BYTE* LibraryWindowImplPlugin::GetFile(const string& itemId, unsigned int& sizeInByte)
	{
		CLOAPISample::LibraryAPIItem item;

		if (API_STORAGE)
		{
			QString filePath;
			if (API_STORAGE->GetFilePathWithID(itemId.c_str(), filePath))
				return FileLoadViaString(filePath, sizeInByte);
		}

		return NULL;
	}

	bool LibraryWindowImplPlugin::IsSigninEnabled()
	{
		return false; 
	}

	bool LibraryWindowImplPlugin::Signin()
	{
		if (CLOAPISample::APISignIn::getInstance()->GetSignIn())
			return true;

		return CLOAPISample::APISignIn::getInstance()->GetSignIn();
	}

	bool LibraryWindowImplPlugin::Signin(const string& id, const string& pw, string& token)
	{
		return false;
	}

	string LibraryWindowImplPlugin::GetFavoriteList()
	{
		vector<CLOAPISample::LibraryAPIItem> itemList;
		//plmMaterial
		CLOAPISample::LibraryAPIItem material;
		material.itemID = "MATERIAL";
		material.itemType = "FOLDER";
		material.itemName = "Material";
		itemList.push_back(material);

		CLOAPISample::LibraryAPIItem trim;
		trim.itemID = "TRIM";
		trim.itemType = "FOLDER";
		trim.itemName = "Trim";
		itemList.push_back(trim);

		//plmProduct
		CLOAPISample::LibraryAPIItem product;
		product.itemID = "PRODUCT";
		product.itemType = "FOLDER";
		product.itemName = "Product";
		itemList.push_back(product);

		//PLM item
		CLOAPISample::LibraryAPIItem plm;
		plm.itemID = "DESIGN SUITE";
		plm.itemType = "FOLDER";
		plm.itemName = "Design Suite";
		itemList.push_back(plm);

		QString jsonStr = generateJSONFromLibraryAPIItemList(itemList);		
		string str = jsonStr.toStdString();

		return str;
	}

	CLOAPISample::PLMSettingsSample* currentSettingsWidget = nullptr;

	bool LibraryWindowImplPlugin::IsPLMSettingsEnabled()
	{
#if USE_PLM_SETTINGS
		return true;
#else
		return false;
#endif
	}

	void* LibraryWindowImplPlugin::GetPLMSettingsWidget()
	{					
		if (currentSettingsWidget)
			ReleasePLMSettingsWidget();

		currentSettingsWidget = new CLOAPISample::PLMSettingsSample();
		return  static_cast<void*>(currentSettingsWidget);
	}

	void LibraryWindowImplPlugin::ReleasePLMSettingsWidget()
	{
		if (currentSettingsWidget)
		{
			delete currentSettingsWidget;
			currentSettingsWidget = nullptr;
		}
	}

	void LibraryWindowImplPlugin::SetNullptrPLMSettingsWidget()
	{
		currentSettingsWidget = nullptr;
	}
	
	void LibraryWindowImplPlugin::ResetPLMSettingsWidget()
	{
		if (currentSettingsWidget)
			currentSettingsWidget->Reset();
	}

	/// plug-in related functions
	bool LibraryWindowImplPlugin::IsPluginEnabled()
	{
#if USE_DOFUNCTION
		return true;
#else
		return false;
#endif
	}

	void LibraryWindowImplPlugin::DoFunction()
	{
#if USE_DOFUNCTION
		
#endif
	}

	void LibraryWindowImplPlugin::DoFunctionStartUp()
	{
#if USE_STARTUP_DOFUNCTION
		
#endif
	}

	void LibraryWindowImplPlugin::DoFunctionAfterLoadingCLOFile(const char* fileExtenstion)
	{
#if USE_AFTER_FILE_LOAD_DOFUNCTION
		
#endif
	}

	const char* LibraryWindowImplPlugin::GetActionName()
	{
		return "Library Windows Sample Plug-in";
	}

	const char* LibraryWindowImplPlugin::GetObjectNameTreeToAddAction()
	{
		const char* objetNameTree = "menu_Setting / menuPlug_In";

		return objetNameTree;
	}

	int LibraryWindowImplPlugin::GetPositionIndexToAddAction()
	{
		return 1; // 0: Above, 1: below (default = 0)
	}
}



