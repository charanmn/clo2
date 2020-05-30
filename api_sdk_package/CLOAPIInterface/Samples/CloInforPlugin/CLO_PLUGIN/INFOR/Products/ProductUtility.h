#pragma once

#include <string>
#include <QString>
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
#include <CLO_PLUGIN\INFOR\Utilities\Utility.h>
#include <CLO_PLUGIN\INFOR\Products\ProductUtility.h>
#include "CLO_PLUGIN\INFOR\Products\createproduct.h"

using namespace std;

using json = nlohmann::json;

/**
 * \brief This method gives the rest call response to check dependencies for Style.
 * \return string rest call response
 */
inline string GetDependencies()
{
	Utility::Logger("ProductUtility -> GetDependencies() -> Start");
	json dataFilterMap, conditionsMapBrand, dependencyMap;
	conditionsMapBrand["fieldname"] = "StyleId";
	conditionsMapBrand["operator"] = "=";
	conditionsMapBrand["value"] = "";
	dataFilterMap["conditions"][0] = conditionsMapBrand;
	dependencyMap["dataFilter"] = dataFilterMap;
	dependencyMap["roleId"] = Configuration::GetInstance()->GetRoleId();
	dependencyMap["userId"] = Configuration::GetInstance()->GetUserId();
	dependencyMap["schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
	dependencyMap["entity"] = "Style";
	dependencyMap["pageType"] = "details";
	dependencyMap["fromAi"] = true;

	Utility::Logger("ProductUtility -> GetDependencies() -> dependencyMap:: " + to_string(dependencyMap));
	Utility::Logger("ProductUtility -> GetDependencies() -> PRODUCT_DEPENDENCIES_API:: " + PRODUCT_DEPENDENCIES_API);
	string response = RestCall(to_string(dependencyMap), PRODUCT_DEPENDENCIES_API);
	Utility::Logger("ProductUtility::GetDependencies() response - " + response);
	Utility::Logger("ProductUtility -> GetDependencies() -> End");

	return response;
}

/**
 * \brief This method sets the dependencies to the widgets
 * \return json
 */
inline json SetDependenciesToWidgets()
{
	Utility::Logger("ProductUtility -> SetDependenciesToWidgets() -> Start");
	string dependencies = GetDependencies();
	Utility::Logger("ProductUtility -> SetDependenciesToWidgets() -> dependencies:: " + dependencies);
	string errorResponse = Utility::CheckErrorDescription(dependencies);
	Utility::Logger("ProductUtility -> SetDependenciesToWidgets() -> errorResponse:: " + errorResponse);

	string completeDependencies;
	json dependencyJson;
	if (errorResponse.empty() && (errorResponse.length() == 0))
	{
		try
		{
			dependencyJson = json::parse(dependencies);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("ProductUtility -> SetDependenciesToWidgets()::parsing dependencyJson exception - " + string(e.what()));
			throw e.what();
		}
	}
	else
	{
		UTILITY_API->DisplayMessageBox(errorResponse);
	}
	Utility::Logger("ProductUtility -> SetDependenciesToWidgets() -> End");

	return dependencyJson;
}

inline bool linkingAttachment(string& zprjFileResponse, string& imageFileResponse, string& styleID)
{
	string imageResponse, zipResponse;
	string imageErrorResponse, zipErrorResponse;
	bool isAttachmentLinked = false;
	//Linking Zprj
	string paramZip = CLOPlugin::createProduct::GetInstance()->CreateZipParam(zprjFileResponse, styleID);///debug the error uploading zprj and image.
	Utility::Logger("createProducr::paramZip:: - " + paramZip);
	zipResponse = Utility::LinkAttachmentToStyle(paramZip, Configuration::GetInstance()->GetBearerToken());
	zipErrorResponse = Utility::CheckErrorDescription(zipResponse);
	if (zipErrorResponse.empty())
	{
		Utility::Logger("Product ZPRJ Linked Successfully::" + zipResponse);
		//Linking Image
		string paramImg = CLOPlugin::createProduct::GetInstance()->CreateImageParam(imageFileResponse, styleID);
		Utility::Logger("paramImg:: - " + paramImg);
		imageResponse = Utility::LinkAttachmentToStyle(paramImg, Configuration::GetInstance()->GetBearerToken());
		imageErrorResponse = Utility::CheckErrorDescription(imageResponse);
		if (imageErrorResponse.empty())
			Utility::Logger("Product Image Linked Successfully::" + imageResponse);
		return isAttachmentLinked = true;
	}
	return isAttachmentLinked;

}

/**
* Method is used to get fields that needs to be cleared
*/
inline void GetResetFields(QTreeWidget* treeWidget, multimap<string, 
	string>& hierarchyMap, string& selectedItem, list<string>& clearItems, std::vector<Utility::Fields> searchFieldsVector, bool isSelectOpt)
{
	set<string> parentItems;
	set<string> nextItems;
	string subStringId = selectedItem.substr(0, selectedItem.find_first_of("_"));
	
	for (auto it = hierarchyMap.begin(); it != hierarchyMap.end(); it++)
	{
		if (it->second == selectedItem) {
			parentItems.insert(it->first);
		}
	}

	for (auto itr = parentItems.begin(); itr != parentItems.end(); itr++)
	{
		for (auto it = hierarchyMap.begin(); it != hierarchyMap.end(); it++)
		{
			string subString = it->second.substr(0, it->second.find_first_of("_"));
			if (it->first == *itr && subStringId == subString) {
				nextItems.insert(it->second);
			}
		}

		int counter = 0;
		bool executeloop = true;
		list<string> tempItrList;
		tempItrList.insert(tempItrList.end(), nextItems.begin(), nextItems.end());
		do
		{
			list<string> tempList;
			for (auto it = tempItrList.begin(); it != tempItrList.end(); it++)
			{
				std::multimap<string, std::string>::const_iterator keys = hierarchyMap.find(*it);
				int number = hierarchyMap.count(*it);
				for (int i = 0; i < number; i++)
				{
					string subString = keys->second.substr(0, keys->second.find_first_of("_"));
					if (std::find(clearItems.begin(), clearItems.end(), subString) == clearItems.end()) {
						clearItems.push_back(subString);
					}
					tempList.push_back(keys->second);
					++keys;
				}
			}

			if (tempList.empty()) {
				executeloop = false;
			}
			else {
				tempItrList.clear();
				tempItrList.insert(tempItrList.end(), tempList.begin(), tempList.end());
				tempList.clear();
			}

			if (counter > 1000) {
				executeloop = false;
			}
			counter++;

		} while (executeloop);
	}

	for (int i = 0; i < treeWidget->topLevelItemCount(); ++i)
	{
		QTreeWidgetItem* topItem = treeWidget->topLevelItem(i);
		QWidget* qWidget = treeWidget->itemWidget(topItem, 1);
		QComboBox* qComboBox = qobject_cast<QComboBox*>(qWidget);
		if ((qComboBox))
		{
			QString id = qComboBox->property("Id").toString();
			for (auto itr = clearItems.begin(); itr != clearItems.end(); itr++)
			{
				if (id.toStdString() == *itr)
				{
					qComboBox->clear();
					if (isSelectOpt) {
						qComboBox->addItem("Select");
					}
					else {
						for each (auto field in searchFieldsVector) {
							if (id == field.labelValue) {
								qComboBox->addItems(field.presetValues);
								break;
							}
						}
						qComboBox->setCurrentIndex(qComboBox->findText("Select"));
					}
				}
			}
		}
	}
}

inline list<string> GetHierarchyOrder(multimap<string, string>& hierarchyMap, string& filterString)
{
	list<string> nextItems;
	list<string> clearItems;
	for (auto it = hierarchyMap.begin(); it != hierarchyMap.end(); it++)
	{
		if (it->first == filterString) {
			string subString = it->second.substr(0, it->second.find_first_of("_"));
			nextItems.push_back(it->second);
			if (std::find(clearItems.begin(), clearItems.end(), subString) == clearItems.end()) {
				clearItems.push_back(subString);
			}
		}
	}

	int counter = 0;
	bool executeloop = true;
	list<string> tempItrList;
	tempItrList.insert(tempItrList.end(), nextItems.begin(), nextItems.end());
	do
	{
		list<string> tempList;
		for (auto it = tempItrList.begin(); it != tempItrList.end(); it++)
		{
			std::multimap<string, std::string>::const_iterator keys = hierarchyMap.find(*it);
			int number = hierarchyMap.count(*it);
			for (int i = 0; i < number; i++)
			{
				string subString = keys->second.substr(0, keys->second.find_first_of("_"));
				if (std::find(clearItems.begin(), clearItems.end(), subString) == clearItems.end()) {
					clearItems.push_back(subString);
				}
				tempList.push_back(keys->second);
				++keys;
			}
		}

		if (tempList.empty()) {
			executeloop = false;
		}
		else {
			tempItrList.clear();
			tempItrList.insert(tempItrList.end(), tempList.begin(), tempList.end());
			tempList.clear();
		}

		if (counter > 1000) {
			executeloop = false;
		}
		counter++;

	} while (executeloop);

	return clearItems;
}
///**
//* \brief creates related parameter for Image to send to PLM
//* \param string response, string key
//* \return string
//*/
//inline string CreateImageParam(string response, string key)
//{
//	Utility::Logger("createProduct -> createImageParam() -> Start");
//	int indexForSuccessResponse = response.find(RESPONSE_200);
//	string SuccessString = response.substr(indexForSuccessResponse);
//	int indexForFlowerBrace = SuccessString.find("{");
//	string strForJSON = SuccessString.substr(indexForFlowerBrace);
//	json ImgJson;
//	try {
//		ImgJson = json::parse(strForJSON);
//	}
//	catch (exception& e)
//	{
//		throw e.what();
//	}
//	string objectKey = ImgJson["addedFiles"][0]["objectKey"].dump();
//	objectKey = objectKey.erase(0, 1);
//	objectKey = objectKey.erase(objectKey.size() - 1);
//	string oldFileName = ImgJson["addedFiles"][0]["oldFileName"].dump();
//	oldFileName = oldFileName.erase(0, 1);
//	oldFileName = oldFileName.erase(oldFileName.size() - 1);
//	json mainMap;
//	json attsFileList;
//	json detailsMap;
//	json details;
//	json attaFileListtoMap;
//	mainMap["modifyId"] = Configuration::GetInstance()->GetUserId();
//	mainMap["Schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
//	details["dlType"] = DLTYPECODE_STYLE_IMAGES;
//	detailsMap = details;
//	attaFileListtoMap["code"] = "E0012";
//	attaFileListtoMap["type"] = "Image";
//	attaFileListtoMap["objectKey"] = objectKey;
//	attaFileListtoMap["oldFileName"] = oldFileName;
//	attaFileListtoMap["referenceId"] = key;
//	attaFileListtoMap["details"] = detailsMap;
//	attaFileListtoMap["IsDefault"] = true;
//	attsFileList[0] = attaFileListtoMap;
//	mainMap["AttaFileListDto"] = attsFileList;
//	Utility::Logger("CreateImageParam main map::" + to_string(mainMap));
//	Utility::Logger("createProduct -> createImageParam() -> End");
//
//	return to_string(mainMap);
//}
///**
//* \brief creates related parameter for Zprj to send to PLM
//* \param string response, string key
//* \return string
//*/
//inline string CreateZipParam(string response, string key)
//{
//	Utility::Logger("createProduct -> CreateZipParam() -> Start");
//	json ImgJson;
//	ImgJson = Utility::GetResultsJSON(response);
//	string objectKey = ImgJson["addedFiles"][0]["objectKey"].dump();
//	objectKey = objectKey.erase(0, 1);
//	objectKey = objectKey.erase(objectKey.size() - 1);
//	string oldFileName = ImgJson["addedFiles"][0]["oldFileName"].dump();
//	oldFileName = oldFileName.erase(0, 1);
//	oldFileName = oldFileName.erase(oldFileName.size() - 1);
//	json mainMap;
//	json attsFileList;
//	json attsFileListtoMap;
//	attsFileListtoMap["referenceId"] = key;
//	attsFileListtoMap["code"] = "E0013";
//	attsFileListtoMap["objectKey"] = objectKey;
//	attsFileListtoMap["oldFileName"] = oldFileName;
//	attsFileList[0] = attsFileListtoMap;
//	mainMap["modifyId"] = Configuration::GetInstance()->GetUserId();
//	mainMap["Schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
//	mainMap["AttaFileListDto"] = attsFileList;
//	Utility::Logger("CreateZipParam main map::" + to_string(mainMap));
//	Utility::Logger("createProduct -> createZipParam() -> End");
//
//	return to_string(mainMap);
//}
