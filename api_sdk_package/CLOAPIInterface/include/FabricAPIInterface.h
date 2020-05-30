#pragma once

#include <vector>

#include "DefineDllForWin.h"

using namespace std;

namespace CLOAPI
{
	class MV_CLO_INTERFACE_API FabricAPIInterface {
	public:
		/*
		GetFabricNumber
		@return the number of fabric in object browser for the current project.
		*/
		virtual unsigned int GetFabricCount() { return 0; }

		/*
		GetFabricIndex
		@return the index of selected fabric in object browser for the current project..
		*/
		virtual unsigned int GetCurrentFabricIndex() { return 0; }

		/*
		Export ZFab
		@return Output file path. If an error occurs, return empty string. If filePath parameter is not given, output files will be created in CLO temporary folder.
		*/
		virtual string ExportZFab() { return ""; }
		virtual string ExportZFab(const string& filePath) { return ""; }
		virtual string ExportZFab(const string& filePath, const int& index) { return ""; }
		virtual wstring ExportZFabW(const wstring& filePath, const int& index) { return L""; }
		
		/*
		Export Fabric (to .jfab or .zfab)
		@return Output file path. If an error occurs, return empty string.
		*/
		virtual string ExportFabric(const string& filePath) { return ""; }
		virtual string ExportFabric(const string& filePath, const int& index) { return ""; }
		virtual wstring ExportFabricW(const wstring& filePath, const int& index) { return L""; }

		/*
		Add Fabric into the Object Browser
		@param 'zfab'(clo file) path or 'jfab'(json) path
		@return the index of added fabric in object browser for the current project. .
		*/
		virtual unsigned int AddFabric(const string& inputFilePath) { return 0; }
		virtual unsigned int AddFabricW(const wstring& inputFilePath) { return 0; }

		/*
		Get the main image file name for the first fabric in the object browser for the current colorway index
		@return the name of the image file name without folder path and extension.		
		*/
		virtual string GetFirstFabricTextureName() { return ""; }
		virtual wstring GetFirstFabricTextureNameW() { return L""; }

		/*
		Get the main image file name for the first fabric in the object browser for a colorway index
		@param colorway index
		@return the name of the image file name without folder path and extension.
		*/
		virtual string GetFirstFabricTextureName(unsigned int colorwayIndex) { return ""; }
		virtual wstring GetFirstFabricTextureNameW(unsigned int colorwayIndex) { return L""; }

		/*
		Overwrite all the properties of a fabric with json file(.jfab) 
		@return if it succeeds, return true.
		*/
		virtual bool ChangeFabricWithJson(unsigned int fabricIndex, const string& inputJsonFilePath) { return false; }
		virtual bool ChangeFabricWithJsonW(unsigned int fabricIndex, const wstring& inputJsonFilePath) { return false; }

		/*
		Assign a fabric to a pattern. 
		@return if it succeeds, return true.
		*/
		virtual bool AssignFabricToPattern(unsigned int fabricIndex, unsigned int patternIndex) { return false; }	

		/*
		Import xtex to a fabric. Overwrite all the values described in the xtex file into the Fabric
		@return if it succeeds, return true.
		*/
		virtual bool ImportXtexFile(unsigned int fabricIndex, const string& xTexFilePath) { return false; }
		virtual bool ImportXtexFileW(unsigned int fabricIndex, const wstring& xTexFilePath) { return false; }

		/*
		Apply xtex to a fabric. Only set the values described in the xtex file into the Fabric.
		@return if it succeeds, return true.
		*/
		virtual bool ApplyXtexFile(unsigned int fabricIndex, const string& xTexFilePath) { return false; }
		virtual bool ApplyXtexFileW(unsigned int fabricIndex, const wstring& xTexFilePath) { return false; }
		
		/*
			Delete a fabric. If the fabric was assginged on Patterns, the patterns will have the default fabric
			@return if it succeeds, return true.
		*/
		virtual bool DeleteFabric(unsigned int fabricIndex) { return false; }

		/*
			Get API meta data for the fabric
			@fabricIndex target fabric index on the Object Browser
			@return json string for meta data [key - value] list
		*/
		virtual string GetAPIMetaData(unsigned int fabricIndex) { return "";		}
		virtual wstring GetAPIMetaDataW(unsigned int fabricIndex) { return L""; }

		/*
			Set API meta data for the fabric
			@fabricIndex target fabric index on the Object Browser
			@json api meta data in string format 
			@return if it succeeds, return true
		*/
		virtual bool SetAPIMetaData(unsigned int fabricIndex, string jsonStr) { return ""; }
		virtual bool SetAPIMetaDataW(unsigned int fabricIndex, wstring jsonStr) { return L""; }

		/*
		Change or add Meta Data Value for the fabric with the index
		@fabricIndex: target Fabric 
		@metaDataKey: target Key
		@metaDataValue: the new value for the key		
		*/
		virtual void ChangeMetaDataValueForFabric(unsigned int fabricIndex, const string& metaDataKey, const string& metaDataValue) {}
		virtual void ChangeMetaDataValueForFabric(unsigned int fabricIndex, const wstring& metaDataKey, const wstring& metaDataValue) {}

		/*
			Get the number of fabrics on the Object Browser
			@return return the number of fabrics on the object browser
		*/
		virtual int GetFabricSize() { return 0; } // deprecated. please use 'GetFabricCount()' function


		/*
			Get the fabric index which is assigned on the pattern with the pattern index
			@return fabric index on the object browser for the pattern with the pattenr index
		*/
		virtual int GetFabricIndexForPattern(int patternIndex) { return 0; }

		/*
			Get the fabric index which is using the fabric name
			@return fabric index
		*/
		virtual int GetFabricIndex(const string& fabricName) { return 0; }
		virtual int GetFabricIndexW(const wstring& fabricName) { return 0; }

		/*
			Get the fabric name which is using the fabric index
			@return fabric name
		*/
		virtual string GetFabricName(int fabricIndex) { return ""; }
		virtual wstring GetFabricNameW(int fabricIndex) { return L""; }

		/*
			Get a fabric information for a colorway
			@return json string for fabric information
		*/
		virtual string GetColorwayFabricInfo(int colorwayIndex, int fabricIndex) { return ""; }
		virtual wstring GetColorwayFabricInfoW(int colorwayIndex, int fabricIndex) { return L""; }

		/*
		Get API meta data for the fabric
		@filePath filepath (.zfab / .jfab)
		@return json string for meta data [key - value] list
		*/
		virtual string GetAPIMetaDataFromFile(const string& filePath) { return ""; }
		virtual wstring GetAPIMetaDataFromFileW(const wstring& filePath) { return L""; }
	};
}
