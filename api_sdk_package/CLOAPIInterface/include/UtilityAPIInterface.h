#pragma once

#include <vector>
#include <map>

#include "DefineDllForWin.h"
#include "CloApiData.h"

using namespace std;

namespace CLOAPI
{
	class MV_CLO_INTERFACE_API UtilityAPIInterface {
	public:
		/*
		@return Get the temporary folder path to store temporary files used when exporting to server
		*/
		virtual string GetCLOTemporaryFolderPath() { return ""; }
		virtual wstring GetCLOTemporaryFolderPathW() { return L""; }

		/*
		Display a message box to show input string on CLO. This can be used for debugging.
		*/
		virtual void DisplayMessageBox(string str) {}
		virtual void DisplayMessageBoxW(wstring str) {}

		/*
		@return The current project name. When you opening "test.zprj" file at last, then the project name is given as "test"
		*/
		virtual string GetProjectName() { return ""; }
		virtual wstring GetProjectNameW() { return L""; }

		/*
		@return The current project file path. If you load a project file saved in "c://download/default.zprj", this function returns the full path - "c://download/default.zprj". If you never load project files, then it returns "NULL".
		*/
		virtual string GetProjectFilePath() { return ""; }
		virtual wstring GetProjectFilePathW() { return L""; }

		/*
		@return Major version of SW. ex) 5 of 5.0.72
		*/
		virtual unsigned int GetMajorVersion() { return 0; }

		/*
		@return Minor version of SW. ex) 0 of 5.0.72
		*/
		virtual unsigned int GetMinorVersion() { return 0; }

		/*
		@return Patch version of SW. ex) 72 of 5.0.72
		*/
		virtual unsigned int GetPatchVersion() { return 0; }

		/*
		@return string in UTF8 from wstring encoded by UCS-2 in Windows or UTF-8 in Mac OS
		*/
		virtual std::string toUtf8(const std::wstring &str) { return ""; }

		/*
		@return The the size of Colorway for the current project.
		*/
		virtual unsigned int GetColorwayCount() { return 0; }

		/*
		@return The current colorway index.
		*/
		virtual unsigned int GetCurrentColorwayIndex() { return 0; }

		/*
		Change the colorway
		*/
		virtual void SetCurrentColorwayIndex(unsigned int index) { }

		/*
		Change the colorway name
		*/
		virtual void SetColorwayName(unsigned int index, const string& str) {}
		virtual void SetColorwayNameW(unsigned int index, const wstring& wstr) {}

		/*
		Get the colorway name
		*/
		virtual string GetColorwayName(unsigned int index) { return ""; }
		virtual wstring GetColorwayNameW(unsigned int index) { return L""; }

		/*
		Refresh Colorway Dialog
		*/
		virtual void RefreshColorwayDialog(bool bCheckIfColorwayMode = true) {}

		/*
		return Json stream including the data of Custom View such as Camera Matrix, FOV, and so on.
		{
			"customViewList": [
				{
					"cameraMatrix": [ // row vector 0, 1, 2 of "local to world camera matrix"
					  1.0,
					  0.000166,
					  -0.001024,
					  0.352125,
					  0.0,
					  0.987069,
					  0.160306,
					  2592.8,
					  0.001039,
					  -0.160306,
					  0.987068,
					  7973.05
					],
					"fov": 40.0
				}
			]
		}
		*/
		virtual string GetCustomViewInformation() { return ""; }
		virtual wstring GetCustomViewInformationW() { return L""; }

		/*
		Simulate the cloth in a step. All dynamics properties (time step, CG iteration count, ...) follows the current simulation properties
		*/
		//virtual void SimulateOneStep() {}

		/*
		Get the position array of cloth shape. Each three array has x, y, z position of each vertex. 
		*/
		virtual void GetClothPositions(vector<float>& positions) {}

		/*
		Restore the shape of cloth to when the cloth was loaded
		*/
		virtual void ResetClothArrangement() {}

		/*
		Get thumbnail file buffer(png type) from the CLO file format(.zprj, .zpac, .zfab, .sst, and so on)
		@return thumbnail(png) buffer
		*/
		virtual unsigned char* GetThumbnailInCLOFile(std::string filePath, unsigned int thumbnailIndex, unsigned int& fileSize) { return nullptr; }

		/*
		Get Meta data for the current Garment
		*/
		virtual string GetMetaDataForCurrentGarment() { return ""; }
		virtual wstring GetMetaDataForCurrentGarmentW() { return L""; }

		/*
		Overwrite Meta data for the current Garment
		*/
		virtual void SetMetaDataForCurrentGarment(const string& metaDataStr) { return; }

		/*
		Change Meta Data Value for the current Garment
		@metaDataKey: target Key
		@metaDataValue: the new value for the key
		*/
		virtual void ChangeMetaDataValueForCurrentGarment(const string& metaDataKey, const string& metaDataValue) {}

		/*
		Create Progress Bar to show progress 
		*/
		virtual void CreateProgressBar() {}

		/*
		Set progress on the Progress Bar
		*/
		virtual void SetProgress(const string& title, int progress) {}
		virtual void SetProgressW(const wstring& title, int progress) {}

		/*
		Delete the current Progress Bar
		@bForce: true - retry to delete progress bar; false - try only once to delete progress bar
		*/
		virtual void DeleteProgressBar(bool bForce) {}

		/*
		Create MD5 hashing string from string
		@return MD5 hashed string
		*/
		virtual string stringToMD5(const string& str) { return ""; }

		/*
		Add Color Swatch
		@colorList - list for color name and rbg values
		@swatchName - swatchName which will be shown in the color palette and the swatch file name to save
		@return - added swatch file name(.aco) inside the asset folder for the current version of CLO
		*/
		virtual string AddColorSwatch(const map<string, string>& plmIDtoNameList, const map<string, Marvelous::CloApiRgb>& plmIDtoColorList, const string& swatchName) { return ""; }
		virtual wstring AddColorSwatchW(const map<wstring, wstring>& plmIDtoNameList, const map<wstring, Marvelous::CloApiRgb>& plmIDtoColorList, const wstring& swatchName) { return L""; }

		/*
		New Project
		*/
		virtual void NewProject() {}
		
		/*
		API calls; especially for Library Windows Sample Demo.
		- IsReadableImageFormatFromExtension / IsReadableImageFormatFromExtensionW
		  : Check if the file stream loaded from the filepath used in Library Windows Implementations can be displayed on Library Windows for item thumbnail and/or preview dialog.
		    (The files should not contain image data over 8bits per channel for 1 ~ 4 channels image.)
		- IsCLOFileFormatWithThumbnailExtension / IsCLOFileFormatWithThumbnailExtensionW
		  : Check if the CLO file format has the thumbnail memory.
			
		- IsCLOFileFormatWithTripleThumbnailExtension / IsCLOFileFormatWithTripleThumbnailExtensionW
		  : Check if the CLO file format has the three images memory for preview thumbnail for the Library Preview Dialog.
		*/
		virtual bool IsReadableImageFormat(const string& filePath) { return false; }
		virtual bool IsReadableImageFormatW(const wstring& filePath) { return false; }

		virtual bool IsCLOFileFormatWithThumbnail(const string& filePath) { return false; }
		virtual bool IsCLOFileFormatWithThumbnailW(const wstring& filePath) { return false; }
		
		virtual bool IsCLOFileFormatWithTripleThumbnail(const string& filePath) { return false; }
		virtual bool IsCLOFileFormatWithTripleThumbnailW(const wstring& filePath) { return false; }

		/*
		@param bLinuxTypePathDelimeter - true: set path delimiter to '/', false: set path delimiter to '\'
		@return Get the executable folder path for the current version of CLO software
		*/
		virtual string GetCLOExecutableFolderPath(bool bLinuxTypePathDelimeter = true) { return ""; }
		virtual wstring GetCLOExecutableFolderPathW(bool bLinuxTypePathDelimeter = true) { return L""; }

		/*
		@param bLinuxTypePathDelimeter - true: set path delimiter to '/', false: set path delimiter to '\'
		@return Get the asset folder path where the CLO asset files are located in
		*/
		virtual string GetCLOAssetFolderPath(bool bLinuxTypePathDelimeter = true) { return ""; }
		virtual wstring GetCLOAssetFolderPathW(bool bLinuxTypePathDelimeter = true) { return L""; }
	};
}