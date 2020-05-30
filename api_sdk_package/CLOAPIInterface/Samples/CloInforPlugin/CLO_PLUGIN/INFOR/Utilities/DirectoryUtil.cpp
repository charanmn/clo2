#include "DirectoryUtil.h"
#include "direct.h"

void DirectoryUtil::createDirectories() {
	string sample_assets = UTILITY_API->GetCLOAssetFolderPath(false) + "CLOPLMPlugin_Assets\\";
	mkdir(sample_assets.c_str());
	string plm_folder = sample_assets + "plm\\";
	mkdir(plm_folder.c_str());
	string plm_plugin = sample_assets + "config\\";
	mkdir(plm_plugin.c_str());
	string logs = sample_assets + "logs\\";
	mkdir(logs.c_str());
	string product_dir = plm_folder + "product\\";
	mkdir(product_dir.c_str());
	string material_dir = plm_folder + + "material\\";
	mkdir(material_dir.c_str());
	string trim_dir = plm_folder + + "trim\\";
	mkdir(trim_dir.c_str());
	string color_dir = plm_folder + + "color\\";
	mkdir(color_dir.c_str());
}

const string DirectoryUtil::getSampleAssetsDirectory() {
	return UTILITY_API->GetCLOAssetFolderPath(false) + "CLOPLMPlugin_Assets\\";
}

const string DirectoryUtil::getSampleStorageDirectory() {
	return getSampleAssetsDirectory()+ "plm\\";
}

const string DirectoryUtil::getMaterialAssetsDirectory() {
	return getSampleStorageDirectory() + "material\\";
}

const string DirectoryUtil::getStyleAttachmentDirectory() {
	return getSampleStorageDirectory() + "product\\";
}

const string DirectoryUtil::getTrimAssetsDirectory() {
	return getSampleStorageDirectory() + "trim\\";
}

const string DirectoryUtil::getColorsAssetsDirectory() {
	return getSampleStorageDirectory() + "color\\";
}

const string DirectoryUtil::getPLMPluginDirectory() {
	return getSampleAssetsDirectory() + "config\\";
}

const string DirectoryUtil::getLogFilePath() {
	return getSampleAssetsDirectory() + "logs\\";
}

const string DirectoryUtil::getProdSearchFilteredJson() {
	return getPLMPluginDirectory() + "productSearchFiltered.json";
}

const string DirectoryUtil::getProdSearchJson() {
	return getPLMPluginDirectory() + "styleDetails.json";
}

const string DirectoryUtil::getColorSearchFilteredJson() {
	return getPLMPluginDirectory() + "colorSearchFiltered.json";
}

const string DirectoryUtil::getColorSearchJson() {
	return getPLMPluginDirectory() + "color.json";
}
const string DirectoryUtil::getColorPaletteSearchJson() {
	return getPLMPluginDirectory() + "colorPalette.json";
}

const string DirectoryUtil::getColorDetailJson() {
	return getPLMPluginDirectory() + "ColorDetails.json";
}

const string DirectoryUtil::getCLOPLMPluginConfigJson() {
	return getPLMPluginDirectory() + "cloplmpluginconfig.json";
}

const string DirectoryUtil::getFabricSearchFilteredJson() {
	return getPLMPluginDirectory() + "materialSearchFiltered.json";
}

const string DirectoryUtil::getFabricSearchJson() {
	return getPLMPluginDirectory() + "materialDetails.json";
}

const string DirectoryUtil::getTrimSearchFilteredJson() {
	return getPLMPluginDirectory() + "trimSearchFiltered.json";
}

const string DirectoryUtil::getTrimDetailJson() {
	return getPLMPluginDirectory() + "trimDetails.json";
}

const string DirectoryUtil::getTrimSearchJson() {
	return getPLMPluginDirectory() + "trims.json";
}
const string DirectoryUtil::getNoImage() {
	return getPLMPluginDirectory() + "NoImage.png";
}