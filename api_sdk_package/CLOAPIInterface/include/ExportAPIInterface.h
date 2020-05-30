#pragma once


#include <vector>

#include "DefineDllForWin.h"

#include "CloApiData.h"

#if defined(__APPLE__)
#include <string>
#endif

using namespace std;

namespace CLOAPI
{
	class MV_CLO_INTERFACE_API ExportAPIInterface {
	public:
		/*
		Export ZPac
		@return Output file path. If an error occurs, return empty string. If filePath parameter is not given, output files will be created in CLO temporary folder.
		*/
		virtual string ExportZPac() { return ""; }
		virtual string ExportZPac(const string& _filePath) { return ""; }
		virtual wstring ExportZPacW(const wstring& _filePath) { return L""; }

		/*
		Export ZPrj
		@param if bCreateThumbnail is true, 'png' file will be created along 'zprj' file.
		@return Output file path. If an error occurs, return empty string. If filePath parameter is not given, output files will be created in CLO temporary folder.
		*/
		virtual string ExportZPrj() { return ""; }
		virtual string ExportZPrj(const string& _filePath) { return ""; }
		virtual string ExportZPrj(const string& _filePath, bool _bCreateThumbnail) { return ""; }
		virtual wstring ExportZPrjW(const wstring& _filePath, bool _bCreateThumbnail) { return L""; }

		/*
		Export OBJ
		@param options If "options" is given, it exports OBJ according to options, not allowing user for selecting options in Export Dialog.
		@return Output file paths. It outputs the file paths of an OBJ file and multiple MTL files for colorways. If the value "bSaveInZipWithTextures" in ImportExportOption is true, it outputs a file path of a zipped file. If an error occurs, return empty string. If filePath parameter is not given, output files will be created in CLO temporary folder.
		*/
		virtual vector<string> ExportOBJ()
		{
			vector<string> interface_vector;
			return interface_vector;
		}

		virtual vector<string> ExportOBJ(const string& _filePath)
		{
			vector<string> interface_vector;
			return interface_vector;
		}

		virtual vector<string> ExportOBJ(const Marvelous::ImportExportOption& _options)
		{
			vector<string> interface_vector;
			return interface_vector;
		}

		virtual vector<string> ExportOBJ(const string& _filePath, const Marvelous::ImportExportOption& _options)
		{
			vector<string> interface_vector;
			return interface_vector;
		}

		virtual vector<wstring> ExportOBJW(const wstring& _filePath, const Marvelous::ImportExportOption& _options)
		{
			vector<wstring> interface_vector;
			return interface_vector;
		}

		/*
		Export GLTF
		@param options If "options" is given, it exports GLTF according to options, not allowing user for selecting options in Export Dialog.
		@return Output file paths. 
		*/
		virtual vector<string> ExportGLTF(const string& _filePath, const Marvelous::ImportExportOption& _options)
		{
			vector<string> interface_vector;
			return interface_vector;
		}

		virtual vector<wstring> ExportGLTFW(const wstring& _filePath, const Marvelous::ImportExportOption& _options)
		{
			vector<wstring> interface_vector;
			return interface_vector;
		}

		/*
		Export DXF
		@return Output file path. If an error occurs, return empty string. If filePath parameter is not given, output files will be created in CLO temporary folder.
		*/
		virtual string ExportDXF() { return ""; }
		virtual string ExportDXF(const string& _filePath) { return ""; }
		virtual string ExportDXF(const string& _filePath, const Marvelous::ExportDxfOption& _exportOption) { return ""; } // without dialog
		virtual wstring ExportDXFW(const wstring& _filePath, const Marvelous::ExportDxfOption& _exportOption) { return L""; } // without dialog

		/*
		Export Tech Pack data in json file and associated image files.
		@param filePath Should be given in "*.json" format
		@param bWithCaptureImage Set as true to save with associated images.
		@param bWithTextures Set as true to save with all the textures included in the materials
		*/
		virtual void ExportTechPack(const string& _filePath, const Marvelous::ExportTechpackOption& _exportOption) {}
		virtual void ExportTechPackW(const wstring& _filepath, const Marvelous::ExportTechpackOption& _exportOption) {}

		/*
		Export Tech Pack data in string and associated image files.
		@param Output folder path where the image files are located by ExportTechpack
		@return Output stream for JSON data with the output folder path at the first line. If an error occurs, return empty string.
		*/
		virtual string ExportTechPackToStream(string& _outputImageFolderPath) { _outputImageFolderPath = "";  return ""; }
		virtual wstring ExportTechPackToStreamW(wstring& _outputImageFolderPath) { _outputImageFolderPath = L"";  return L""; }

		/*
		Export thumbnail of the current scene
		@return Output file path. If an error occurs, return empty string. If filePath parameter is not given, output files will be created in CLO temporary folder.
		*/
		virtual string ExportThumbnail3D() { return ""; }
		virtual string ExportThumbnail3D(const string& _filePath) { return ""; }
		virtual wstring ExportThumbnail3DW(const wstring& _filePath) { return L""; }

		/*
		Export snapshot images. This function displays the same dialog as CLO so that users can configure the snapshots.
		If user turns on the option "Save Separate Images", then series of images will be saved with the name followed by the postfix "_01", "_02", ...
		@return Return the list of the path of output files per colorway. The first item of each array is the file path of the unified image. If filePath parameter is not given, output files will be created in CLO temporary folder.
		*/
		virtual vector< vector < string > > ExportSnapshot3D(const string& _filePath)
		{
			vector< vector < string > > interface_vector;
			return interface_vector;
		}

		virtual vector< vector < string > > ExportSnapshot3D()
		{
			vector< vector < string > > interface_vector;
			return interface_vector;
		}


		virtual vector< vector < wstring > > ExportSnapshot3DW(const wstring& _filePath)
		{
			vector< vector < wstring > > interface_vector;
			return interface_vector;
		}

		/*
		Export snapshot images of Custom View.
		outputPrefix: If you set the 'outputPrefix' as empty value - "", then the saved file names will start with the index in the custom view; 
		              or if you set the 'outputPrefix' as some letters, the saved file names will have it as the first letters.
		*/
		virtual vector < string > ExportCustomViewSnapshot(const string& _targetFolderPath, unsigned int _width, unsigned int _height, string _outputPrefix = "")
		{
			vector<string> interface_vector;
			return interface_vector;
		}

		virtual vector < wstring > ExportCustomViewSnapshotW(const wstring& _targetFolderPath, unsigned int _width, unsigned int _height, wstring _outputPrefix = L"")
		{
			vector<wstring> interface_vector;
			return interface_vector;
		}

		/*
		Export Rendering Image.
		@param bRenderAllColorways If true, output the images for all colorways. Otherwise, it returns the images for the current colorway specified by CLO user.
		@param savedFilePathList Return the list of the path of output files per colorway. If filePath parameter is not given, output files will be created in CLO temporary folder.
		@param colorwayIndex It starts with 0 index. It must not be over the total colorway size.
		@return If the rendering call fails, then output filepath will be empty.
		*/
		virtual vector< vector < string > > ExportRenderingImage(const string& _filePath)
		{
			vector< vector < string > > interface_vector;
			return interface_vector;
		}

		virtual vector< vector < string > > ExportRenderingImage(const string& _filePath, bool _bRenderAllColorways)
		{
			vector< vector < string > > interface_vector;
			return interface_vector;
		}

		virtual vector< vector < string > > ExportRenderingImage(bool _bRenderAllColorways)
		{
			vector< vector < string > > interface_vector;
			return interface_vector;
		}

		virtual vector< vector < wstring > > ExportRenderingImageW(const wstring& _filePath, bool _bRenderAllColorways)
		{
			vector< vector < wstring > > interface_vector;
			return interface_vector;
		}

		virtual vector < string > ExportSingleColorwayRenderingImage(const string& _filePath, unsigned int _colorwayIndex)
		{
			vector < string > interface_vector;
			return interface_vector;
		}

		virtual vector < string > ExportSingleColorwayRenderingImage(unsigned int _colorwayIndex)
		{
			vector < string > interface_vector;
			return interface_vector;
		}

		virtual vector < wstring > ExportSingleColorwayRenderingImageW(const wstring& _filePath, unsigned int _colorwayIndex)
		{
			vector < wstring > interface_vector;
			return interface_vector;
		}

		/*
		Get File name list for the recently exported rendering images
		@return savedFilePathList for all the exported rendering images recently
		*/
		virtual vector < string >  GetTotalRenderImagePaths()
		{
			vector < string > interface_vector;
			return interface_vector;
		}

		virtual vector < wstring >  GetTotalRenderImagePathsW()
		{
			vector < wstring > interface_vector;
			return interface_vector;
		}

		/*
		Get File name list for the exported rendering images
		@return savedFilePathList for all the exported rendering images in run-time
		*/
		virtual vector < string >  GetCurrentRenderImagePaths()
		{
			vector < string > interface_vector;
			return interface_vector;
		}

		virtual vector < wstring >  GetCurrentRenderImagePathsW()
		{
			vector < wstring > interface_vector;
			return interface_vector;
		}

		/*
		Get File name on the Image/Video property in Render function
		@return "File Name". If fails, return ""
		*/
		virtual string GetFileNameOnRenderingProperty()
		{
			string str = "";
			return str;
		}

		virtual wstring GetFileNameOnRenderingPropertyW()
		{
			wstring str = L"";
			return str;
		}

		/*
		Export garment information in json file. The information is the same as given in Garment Information Dialog in CLO (you can see this dialog by clicking File > Information > Garment menu in CLO)
		@return Output file path. If an error occurs, return empty string. If filePath parameter is not given, output files will be created in CLO temporary folder.
		*/
		virtual string ExportGarmentInformation() { return ""; }
		virtual string ExportGarmentInformation(const string& _filePath) { return ""; }
		virtual wstring ExportGarmentInformationW(const wstring& _filePath) { return L""; }
		/*
		Export garment information in string.
		@param Output folder path where json file is located by ExportGarmentInformation
		@return Output stream for JSON data with the output folder path at the first line. If an error occurs, return empty string.
		*/
		virtual string ExportGarmentInformationToStream() { return ""; }
		virtual wstring ExportGarmentInformationToStreamW() { return L""; }

		/*
		Export turntable video. This function requires XVid Mpeg-4 codec installed on user's computer.
		@return Output file path. If an error occurs, return empty string. If filePath parameter is not given, output files will be created in CLO temporary folder.
		*/
		virtual string ExportTurntableVideo() { return ""; }
		virtual string ExportTurntableVideo(const string& _filePath) { return ""; }
		virtual wstring ExportTurntableVideoW(const wstring& _filePath) { return L""; }

		/*
		Export animation video. This function requires XVid Mpeg-4 codec installed on user's computer.
		@return Output file path. If an error occurs, return empty string. If filePath parameter is not given, output files will be created in CLO temporary folder.
		*/
		virtual string ExportAnimationVideo() { return ""; }
		virtual string ExportAnimationVideo(const string& _filePath) { return ""; }
		virtual wstring ExportAnimationVideoW(const wstring& _filePath) { return L""; }

		//////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////

		/*
		@return total count of colorways
		*/
		virtual unsigned int GetColorwayCount() { return 0; }

		/*
		@return the current colorway index
		*/
		virtual unsigned int GetCurrentColorwayIndex() { return 0; }

		/*
		@return the list of name of all colorways
		*/
		virtual vector<string> GetColorwayNameList()
		{
			vector < string > interface_vector;
			return interface_vector;
		}

		virtual vector<wstring> GetColorwayNameListW()
		{
			vector < wstring > interface_vector;
			return interface_vector;
		}

		/*
		@return total count of avatars
		*/
		virtual unsigned int GetAvatarCount() { return 0; }

		/*
		@return the list of name of all avatars
		*/
		virtual vector<string> GetAvatarNameList()
		{
			vector < string > interface_vector;
			return interface_vector;
		}

		virtual vector<wstring> GetAvatarNameListW()
		{
			vector < wstring > interface_vector;
			return interface_vector;
		}

		/*
		@return the list of gender of all avatars. 0 : male, 1 : female, -1: unknown
		*/
		virtual vector<int> GetAvatarGenderList()
		{
			vector < int > interface_vector;
			return interface_vector;
		}

		/*
		@return total count of sizes/gradings
		*/
		virtual unsigned int GetSizeCount() { return 0; }

		/*
		@return the current index of size/grading
		*/
		virtual unsigned int GetCurrentSizeIndex() { return 0; }

		/*
		@return the list of name of all sizes/gradings
		*/
		virtual vector<string> GetSizeNameList()
		{
			vector < string > interface_vector;
			return interface_vector;
		}

		virtual vector<wstring> GetSizeNameListW()
		{
			vector < wstring > interface_vector;
			return interface_vector;
		}

		/*
		Export turntable images for current colorway.
		@return Output file path list. If an error occurs, return empty string. If filePath parameter is not given, output files will be created in CLO temporary folder.
		*/
		virtual vector<string> ExportTurntableImages(int _numberOfImages)
		{
			vector < string > interface_vector;
			return interface_vector;
		}

		virtual vector<string> ExportTurntableImages(const string& _filePath, int _numberOfImages, int _width = 2500, int _height = 2500) 
		{ 
			vector < string > interface_vector;
			return interface_vector;
		}

		virtual vector<wstring> ExportTurntableImagesW(const wstring& _filePath, int _numberOfImages, int _width = 2500, int _height = 2500)
		{ 
			vector < wstring > interface_vector;
			return interface_vector;
		}
	};
}
