#pragma once
#include <string>
#include <CLOAPIInterface.h>
using namespace std;

class DirectoryUtil
{
public:
	static void createDirectories();
	static const string getSampleAssetsDirectory();
	static const string getSampleStorageDirectory();
	static const string getMaterialAssetsDirectory();
	static const string getStyleAttachmentDirectory();
	static const string getTrimAssetsDirectory();
	static const string getColorsAssetsDirectory();
	static const string getPLMPluginDirectory();
	static const string getLogFilePath();
	static const string getProdSearchFilteredJson();
	static const string getProdSearchJson();
	static const string getColorSearchFilteredJson();
	static const string getColorSearchJson();
	static const string getColorPaletteSearchJson();
	static const string getColorDetailJson();
	static const string getDetailJson();
	const string getDetailJson(string entity);
	static const string getCLOPLMPluginConfigJson();
	static const string getFabricSearchFilteredJson();
	static const string getFabricSearchJson();
	static const string getTrimSearchFilteredJson();
	static const string getTrimDetailJson();
	static const string getTrimSearchJson();
	static const string getNoImage();
};

