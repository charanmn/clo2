#pragma once
#include <algorithm> 
#include <fstream>
#include <iostream> 
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QTreeWidgetItem>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QVariant>
#include <QCheckBox>
#include <sstream>
#include <tchar.h>
#include <time.h>
#include <stdio.h>
#include "CLO_PLUGIN/INFOR/Utilities/Definitions.h"
#include "CLO_PLUGIN/INFOR/Utilities/Configuration.h"
#include "CLO_PLUGIN/INFOR/Libraries/jsonQt.h"
#include "CLOAPIInterface.h"
#include "qfileinfo.h"
#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "ws2_32.lib")
#include <direct.h>
#include <iostream>
#include "CLO_PLUGIN/INFOR/Libraries/curl/include/curl/curl.h"
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
#include "CLO_PLUGIN/INFOR/Utilities/RestAPIUtility.h"
#include "DirectoryUtil.h"

using namespace std;
using QtJson::JsonObject;
using json = nlohmann::json;

/**
 * \holds all common variable names used on entire CLO plugin 
 */
namespace Utility
{
	/**
	 * \These are some of the common fields will read from attribute details JSON 
	 */
	struct Fields
	{
		QString labelValue;
		QString fieldUItype;
		QStringList presetValues;
		bool isMandatory;
		QString userInputValues;
		bool isDisabledField;
		QString dataFieldValue;
	};
	/**
	 * \These are variable which will hold values of attributes specific to Colors  
	 */
	struct ColorResults
	{
		QString colorCode;
		QString colorName;
		QString	colorId;
		QString colorSubType;
		QString colorType;
		QString colorShade;
		QString colorFamily;
		QString colorStatus;
		QString colorRGB;
		QString colorCMYK;
		QString colorPantoneCode;
	};
	/**
	 * \brief Method removes spaces from input string and returns back.
	 * \param inputString 
	 * \return string 
	 */
	inline string RemoveSpaces(string  inputString)
	{
		inputString.erase(remove(inputString.begin(), inputString.end(), ' '), inputString.end());
		return inputString;
	}
	/**
	 * \brief Displays Message on screen, when isEnabled is true
	 * \param inputString 
	 */
	inline void CustomMessageBox(string inputString)
	{
		//Move as global variable
		bool isEnabled = false;	//true false

		if (isEnabled)
		{
			UTILITY_API->DisplayMessageBox(inputString);
		}
	}
	/**
	 * \brief Returns current Date & Time in string format
	 * \param inputString 
	 * \return string
	 */
	inline string GetCurrentDateTime()
	{
		time_t now = time(0);
		struct tm  time_struct;
		char  buffer[80];
		time_struct = *localtime(&now);
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", &time_struct); //@To-Do Declare Date Format in Definitions and use here
		return string(buffer);
	}
	/**
	 * \brief Calculates size of the content from file
	 * \param path
	 * \return size_t
	 */
	static size_t GetFileSize(const std::string& path)
	{
		std::streampos begin, end;
		std::ifstream myFile(path.c_str(), std::ios::binary);
		begin = myFile.tellg();
		myFile.seekg(0, std::ios::end);
		end = myFile.tellg();
		myFile.close();
		return ((end - begin) > 0) ? (end - begin) : 0;
	}
	/**
	 * \brief Function is used to read file and forms json object
	 * \param jsonFilePath
	 * \return json
	 */
	inline json ReadJSONFile(string jsonFilePath)
	{		
		std::ifstream fileopen(jsonFilePath.c_str(), std::ios_base::out | std::ios_base::app);
		json readJSON;
		fileopen >> readJSON;
		fileopen.close();
		return readJSON;
	}
	inline void getMaxLogFileSize()
	{
		string plmSettingsFilePath = DirectoryUtil::getCLOPLMPluginConfigJson();
		json plmSettingsJSON = Utility::ReadJSONFile(plmSettingsFilePath);
		string logFileSize = plmSettingsJSON["maximumLogFileSize"].dump();
		long int maxFileSize = std::stoi(logFileSize);
		Configuration::GetInstance()->SetMaxLogFileSize(maxFileSize);
	}
	/**
	 * \brief Method creating log file name.
	 */
	inline void CreateLogFileName()
	{
		time_t time0;
		time(&time0);
		struct tm  time_struct;
		char buffer[80];
		time_struct = *localtime(&time0);
		strftime(buffer, sizeof(buffer), "%H-%M-%S-%Y-%m-%d", &time_struct);
		string  newDirPath = DirectoryUtil::getLogFilePath();
		string LOGPATH = newDirPath + "CLO-Vise_Log_" + string(buffer) + TEXT_FILE_EXTENSION;
		Configuration::GetInstance()->SetLogFileName(LOGPATH);

	}
	inline void CreateErrorLogFileName()
	{

		DirectoryUtil::createDirectories();
		time_t time0;
		time(&time0);
		struct tm  time_struct;
		char buffer[80];
		time_struct = *localtime(&time0);
		strftime(buffer, sizeof(buffer), "%H-%M-%S-%Y-%m-%d", &time_struct);
		string  newDirPath = DirectoryUtil::getLogFilePath();
		string ERRORLOGPATH = newDirPath + "CLO_Vise_Error_Log_" + string(buffer) + TEXT_FILE_EXTENSION;
		Configuration::GetInstance()->SetErrorLogFileName(ERRORLOGPATH);
		getMaxLogFileSize();
	}
	inline long ConvertBytesToMB(int bytes)
	{
		long long MegaBytes = 0;
		MegaBytes = bytes / (1024 * 1000);
		return MegaBytes;
	}
	/**
	 * \brief Method writes log messages to logger file
	 * \param loggerMessage 
	 */
	inline void Logger(string loggerMessage) 
	{
		string logPath;
		logPath = Configuration::GetInstance()->GetLogFileName();//(MIDDLEWARE_DIRECTORY + GetCurrentDateTime(DATE_TEXT) + TEXT_FILE_EXTENSION);
		long int logFilesize = GetFileSize(logPath);
		logFilesize = ConvertBytesToMB(logFilesize);
		if (logFilesize >= Configuration::GetInstance()->GetMaxLogFileSize())
		{
			CreateLogFileName();
			logPath= Configuration::GetInstance()->GetLogFileName();
		}
		std::ofstream logfileopen(logPath.c_str(), std::ios_base::out | std::ios_base::app);
		string now = GetCurrentDateTime();
		logfileopen << now << '\t' << loggerMessage << '\n';
		logfileopen.close();
		
	}
	/**
	 * \brief Method writes error log messages to logger file
	 * \param loggerMessage
	 */
	inline void ErrorLogger(string loggerMessage)
	{

		Logger("ErrorLogger started...");
		string errorLogPath;
		errorLogPath = Configuration::GetInstance()->GetErrorLogFileName();//(MIDDLEWARE_DIRECTORY + GetCurrentDateTime(DATE_TEXT) + TEXT_FILE_EXTENSION);
		long int logFilesize = GetFileSize(errorLogPath);
		logFilesize = ConvertBytesToMB(logFilesize);
		if (logFilesize >= Configuration::GetInstance()->GetMaxLogFileSize())
		{
			CreateErrorLogFileName();
			errorLogPath = Configuration::GetInstance()->GetLogFileName();
		}
		std::ofstream logfileopen(errorLogPath.c_str(), std::ios_base::out | std::ios_base::app);
		string now = GetCurrentDateTime();
		logfileopen << now << '\t' << loggerMessage << '\n';
		logfileopen.close();

	}
	static string basicAuthorizationString;

	/**
	 * \brief Checks the input char is base64 char or not
	 * \param base64Char 
	 * \return bool
	 */
	inline bool IsBase64Char(unsigned char base64Char) 
	{
		return (isalnum(base64Char) || (base64Char == '+') || (base64Char == '/'));
	}
	/**
	 * \brief Reads content of file and returns string of content, given file name as parameter
	 * \param filename 
	 * \return QString
	 */
	inline QString ReadFile(const QString &fileName) 
	{
		Logger("Utility::ReadFile() Started...");
		QFile file(fileName);
		if (!file.open(QFile::ReadWrite | QFile::Text))
		{
			return QString();
		}
		else 
		{
			QTextStream in(&file);
			return in.readAll();
		}
		Logger("Utility::ReadFile() Ended...");

	}
	/**
	 * \brief Converts input string to Base64 String
	 * \param inputString 
	 * \return string
	 */
	inline string ConvertToBase64(const std::string & inputString) 
	{
		Logger("Utility::ConvertToBase64() Started...");
		std::string base64String;
		int upperLimit = 0, lowerLimit = -6;
		
		for (unsigned char c : inputString)
		{
			upperLimit = (upperLimit << 8) + c;
			lowerLimit += 8;
			while (lowerLimit >= 0)
			{
				base64String.push_back(BASE64_CHARS[(upperLimit >> lowerLimit) & 0x3F]);
				lowerLimit -= 6;
			}
		}
		
		if (lowerLimit > -6) base64String.push_back(BASE64_CHARS[((upperLimit << 8) >> (lowerLimit + 8)) & 0x3F]);

		while (base64String.size() % 4) base64String.push_back('=');
		Logger("Utility::ConvertToBase64() Ended...");
		return base64String;
	}
	/**
	 * \brief Reads JSON file and creates JSON Object
	 * \param filePath 
	 * \param searchKey 
	 */
	inline void ReadJsonFile(QString filePath, QString &searchKey)
	{
		Logger("Utility::ReadJsonFile() Started...");
		QString jsonString;
		try {
			jsonString = ReadFile(filePath); // Reading the JSON file
		}
		catch (errno_t) 
		{
			qFatal("Error in readJsonFile() - Could not read JSON file!");
		}
		
		bool parseSuccessful;
		JsonObject jsonObject;
		try {
			jsonObject = QtJson::parse(jsonString, parseSuccessful).toMap(); // Parsing the JSON file and storing it to JSON Object
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("Utility::ReadJsonFile()::parsing jsonObject exception - " + string(e.what()));
			throw e.what();
		}
		if (!parseSuccessful)
		{
			qFatal("Error in readJsonFile() - An error occurred while parsing JSON file");
		}
		
		JsonObject urlsJSON = jsonObject["urlList"].toMap(); //Get URLs from JSON Object jsonObject. @TO-Do urlList move to Definitions.h
		searchKey = urlsJSON[searchKey].toString();
		Logger("Utility::ReadJsonFile() Ended...");

	}
	/**
	 * \brief Forms Basic Authorization string using User Id and Password for Rest Basic Authentication
	 * \param userId 
	 * \param password 
	 */
	inline void SetUserIdAndPassword(string userId, string password)
	{
		basicAuthorizationString = BASIC + ConvertToBase64(userId + ":" + password);
	}
	/**
	 * \brief Hits Rest End point with a HTTP request for Authorization
	 * \param restEndPoint 
	 * \param restCallParameters 
	 * \param response 
	 * \return bool
	 */
	/*inline bool SendJsonRequest(string restEndPoint, string restCallParameters, string &response)
	{
		Logger("Utility::SendJsonRequest() Started...");

		vector<pair<string, string>> headerNameAndValue;
		headerNameAndValue.push_back(make_pair(AUTHORIZATION, basicAuthorizationString));
		headerNameAndValue.push_back(make_pair(INFOR_TENANT, Configuration::GetInstance()->GetTenant()));
		
		response = REST_API->CallRESTPost(restEndPoint, &restCallParameters, headerNameAndValue, HTTP_POST);

		size_t found = response.find(RESPONSE_200);
		if (found != string::npos)
			return true;
		Logger("Utility::SendJsonRequest() Ended...");
		return false;
	}
	/**
	 * \brief Decodes Base 64 Encoded string returns
	 * \param encodedString 
	 * \return string
	 */
	inline string DecodeBase64(std::string const &encodedString)
	{
		Logger("Utility::DecodeBase64() Started...");
		int encodedStringLength = encodedString.size();
		int i = 0;
		int j = 0;
		int charIndex = 0;
		unsigned char charArrayOf4[4], charArrayOf3[3];
		std::string decodedString;
		
		while (encodedStringLength-- && (encodedString[charIndex] != '=') && IsBase64Char(encodedString[charIndex]))
		{
			charArrayOf4[i++] = encodedString[charIndex]; charIndex++;
			if (i == 4) {
				for (i = 0; i < 4; i++)
					charArrayOf4[i] = BASE64_CHARS.find(charArrayOf4[i]);

				charArrayOf3[0] = (charArrayOf4[0] << 2) + ((charArrayOf4[1] & 0x30) >> 4);
				charArrayOf3[1] = ((charArrayOf4[1] & 0xf) << 4) + ((charArrayOf4[2] & 0x3c) >> 2);
				charArrayOf3[2] = ((charArrayOf4[2] & 0x3) << 6) + charArrayOf4[3];

				for (i = 0; (i < 3); i++) 
				{
					decodedString += charArrayOf3[i];
				}

				i = 0;
			}
		}
		if (i)
		{
			for (j = i; j < 4; j++)
				charArrayOf4[j] = 0;

			for (j = 0; j < 4; j++)
				charArrayOf4[j] = BASE64_CHARS.find(charArrayOf4[j]);

			charArrayOf3[0] = (charArrayOf4[0] << 2) + ((charArrayOf4[1] & 0x30) >> 4);
			charArrayOf3[1] = ((charArrayOf4[1] & 0xf) << 4) + ((charArrayOf4[2] & 0x3c) >> 2);
			charArrayOf3[2] = ((charArrayOf4[2] & 0x3) << 6) + charArrayOf4[3];

			for (j = 0; (j < i - 1); j++) 
			{
				decodedString += charArrayOf3[j];
			}
		}
		Logger("Utility::DecodeBase64() Ended...");
		return decodedString;
	}
	/**
	 * \brief Method checks for error decriiption in Rest call response, //@To-Do Modifications are required
	 * \param response 
	 * \return string
	 */
	inline string CheckErrorDescription(string response)
	{
		Logger("Utility::CheckErrorDescription() Started...");
		string finalErrorMessage = "";
		string errorJson="";
		json responseJson, brokenRulesJson, ruleDescriptionMsg;
		string brokenRules ="";
		string	exceptionStr="";
		if (response.length() > 5) {
			int indexForJSON = response.find("{");
			string strForJSON = response.substr(indexForJSON);
			std::replace(strForJSON.begin(), strForJSON.end(), '®', ' ');
			try {
				responseJson = json::parse(QString::fromStdString(strForJSON).toUtf8().constData());
				brokenRules = responseJson["brokenRules"].dump();
				exceptionStr = responseJson["exception"].dump();
				brokenRulesJson = json::parse(brokenRules);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("Utility::CheckErrorDescription()::parsing responseJson exception - " + string(e.what()));
				throw e.what();
			}
			size_t found1 = response.find(UNAUTHORIZED);
			size_t found2 = response.find(INTERNAL_SERVER_ERROR);
			size_t found3 = response.find(TIMEOUT_ERROR);
			size_t found4 = response.find(REQUEST_TIMEOUT);

			if (found1 != string::npos)
			{
				Configuration::GetInstance()->GetRefreshToken();
				Utility::CustomMessageBox(finalErrorMessage);
				return finalErrorMessage;
			}
			if (found2 != string::npos)
			{
				finalErrorMessage = responseJson["error"].dump();
				finalErrorMessage = finalErrorMessage.erase(0, 1);
				finalErrorMessage = finalErrorMessage.erase(finalErrorMessage.size() - 1);
				return finalErrorMessage;
			}
			if (found3 != string::npos)
			{
				finalErrorMessage = TIMEOUT_ERROR_MESSAGE;
				return finalErrorMessage;
			}
			if (found4 != string::npos)
			{
				finalErrorMessage = REQUEST_TIMEOUT;
				return finalErrorMessage;
			}
			if (brokenRulesJson.size() != 0)
			{
				for (int i = 0; i < brokenRulesJson.size(); i++)
				{
					errorJson = brokenRulesJson[i].dump();
					try
					{
						ruleDescriptionMsg = json::parse(errorJson);
					}
					catch (exception& e)
					{
						Utility::ErrorLogger("Utility::CheckErrorDescription())::parsing ruleDescriptionMsg exception - " + string(e.what()));
						throw e.what();
					}
					finalErrorMessage = ruleDescriptionMsg["ruleDescription"].dump();
					finalErrorMessage = finalErrorMessage.erase(0, 1);
					finalErrorMessage = finalErrorMessage.erase(finalErrorMessage.size() - 1);
					return finalErrorMessage;
				}
			}
			if (exceptionStr != "null") {
				json exceptionJson;
				try {
					exceptionJson = json::parse(exceptionStr);
				}
				catch (exception& e)
				{

					Utility::ErrorLogger("Utility::CheckErrorDescription())::parsing exceptionJson exception - " + string(e.what()));
					throw e.what();
				}
				finalErrorMessage = responseJson["exception"]["Message"].dump();
				finalErrorMessage = finalErrorMessage.erase(0, 1);
				finalErrorMessage = finalErrorMessage.erase(finalErrorMessage.size() - 1);
				return finalErrorMessage;
			}
		}
		else {
			finalErrorMessage = NETWORK_ERROR_MESSAGE;
			return finalErrorMessage;
		}
		Logger("CheckErrorDescription() Ended...");
		return finalErrorMessage;
	}
	
	/**
	 * \brief Calls Rest service to Upload files from CLO to Rest Service//@To-Do Modifications are required
	 * \param filePath 
	 * \param token 
	 * \return string
	 */
	inline string UploadFile(string filePath, string token)
	{
		Logger("Utility::UploadFile() Started...");
		QFile templateFile(QString::fromStdString(filePath));
		if (!templateFile.open(QFile::ReadOnly | QFile::Text))
		{
			string errorMessage = "Unable to open template";
			UTILITY_API->DisplayMessageBox(errorMessage);
			return "";
		}
		else    // file opened and ready to read from
		{
			std::string contentType = "";
			QFileInfo fileInfo(templateFile);
			std::string fileName = fileInfo.fileName().toStdString();
			std::string extension = fileInfo.suffix().toStdString();
			if (extension.compare("bmp") == 0 || extension.compare("BMP") == 0) {
				contentType = "image/bmp";
			}
			else if (extension.compare("gif") == 0 || extension.compare("GIF") == 0) {
				contentType = "image/gif";
			}
			else if (extension.compare("jpg") == 0 || extension.compare("JPG") == 0) {
				contentType = "image/jpeg";
			}
			else if (extension.compare("jpeg") == 0 || extension.compare("JPEG") == 0) {
				contentType = "image/jpeg";
			}
			else if (extension.compare("png") == 0 || extension.compare("PNG") == 0) {
				contentType = "image/png";
			}
			else if (extension.compare("pdf") == 0) {
				contentType = "application/pdf";
			}
			else if (extension.compare("doc") == 0 || extension.compare("docx") == 0) {
				contentType = "application/msword";
			}
			else if (extension.compare("ppt") == 0 || extension.compare("pptx") == 0) {
				contentType = "application/vnd.ms-powerpoint";
			}
			else if (extension.compare("zip") == 0 || extension.compare("rar") == 0) {
				contentType = "application/zip";
			}
			else if (extension.compare("rtf") == 0) {
				contentType = "application/rtf";
			}
			else if (extension.compare("xls") == 0 || extension.compare("xlsx") == 0) {
				contentType = "application/vnd.ms-excel";
			}
			else {
				contentType = "application/octet-stream";
			}
			std::ifstream inFile(filePath, std::ios_base::binary);
			inFile.seekg(0, std::ios_base::end);
			size_t length = inFile.tellg();
			inFile.seekg(0, std::ios_base::beg);
			std::vector<char> buffer;
			buffer.reserve(length);
			std::copy(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>(), std::back_inserter(buffer));
			std::stringstream fileStream;
			for (size_t i = 0; i < buffer.size(); ++i)
			{
				fileStream << buffer[i];
			}
			Utility::Logger("contentType------------"+ contentType);
			string requestToken = token;
			std::stringstream ss;
			ss << "Content-Length: " << GetFileSize(filePath) << "";
			std::string contentLength = ss.str();
			string requestParams = "------WebKitFormBoundary7MA4YWxkTrZu0gW\r\nContent-Disposition: form-data; name=\"file\"; filename=\"" + fileName + "\"\r\n";
			requestParams += "Content-Type: " + contentType + "\r\n";
			requestParams += contentLength + "\r\n\r\n";
			requestParams += fileStream.str();
			requestParams += "\r\n";
			requestParams += "------WebKitFormBoundary7MA4YWxkTrZu0gW\r\n";
			requestParams += "Content-Disposition: form-data; name=\"type\"\r\n\r\n";
			requestParams += "sketches";
			requestParams += "\r\n";
			requestParams += "------WebKitFormBoundary7MA4YWxkTrZu0gW\r\n";
			requestParams += "Content-Disposition: form-data; name=\"formType\"\r\n\r\n";
			requestParams += "file";
			requestParams += "\r\n";
			requestParams += "------WebKitFormBoundary7MA4YWxkTrZu0gW\r\n";
			requestParams += "Content-Disposition: form-data; name=\"atta\"\r\n\r\n";
			requestParams += "{\"objectFilePath\": \"blob:https://uat.fplm.awsdev.infor.com/6df777de-584-41d9-b500-715432836119\",  \"objectExtension\": null,  \"sequence\": 0,  \"details\": {\"name\": null,\"note\": null, \"dlType\": 11, \"type\": \"styleImages\"},  \"referenceId\": 1206, \"modifyDate\": \"0001-01-01T00:00:00\",  \"code\": \"\",  \"isDefault\": false,  \"objectId\": 0,  \"originalObjectName\": \"" + fileName + "\", \"objectStream\": null,  \"tempId\": \"\"}";
			requestParams += "\r\n";
			requestParams += "------WebKitFormBoundary7MA4YWxkTrZu0gW\r\n";
			requestParams += "Content-Disposition: form-data; name=\"schema\"\r\n\r\n";
			requestParams += Configuration::GetInstance()->GetschemaWithQuotes();
			requestParams += "\r\n";
			requestParams += "------WebKitFormBoundary7MA4YWxkTrZu0gW--";
			string response = RestCall(requestParams, UPLOAD_FILE, "multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW");
			Utility::CustomMessageBox(response.c_str());			
			Logger("upload file response:: " + response);
			Logger("Utility::UploadFile() Ended...");
			return response;
		}
	}
	/**
	 * \brief Attaches file as attachement to Style by calling rest service//@To-Do Modifications are required
	 * \param param 
	 * \param token 
	 * \return string
	 */
	inline string  LinkAttachmentToStyle(string& param, string& token)
	{
		Logger("Utility::LinkAttachmentToStyle() Started...");
		string response = RestCall(param, LINK_ATTACHMENT, INFOR_TYPE);
		Utility::CustomMessageBox("response::" + response);		
		Logger("Utility::LinkAttachmentToStyle() Ended...");

		return response;
	}
	/**
	 * \brief Download image from URL //@To-Do Modifications are required
	 * \param url 
	 * \param fileName 
	 */
	inline void DownloadImageFromURL(string& url, string& fileName)
	{
		Logger("Utility::DownloadImageFromURL() Started...");
		UTILITY_API->CreateProgressBar();
		CURL* image;
		CURLcode imageResult;
		FILE* fp = nullptr;
	
		const char* tempurl = url.c_str(); 
		image = curl_easy_init();
		
		if (image)
		{
			fp = fopen(fileName.c_str(), "wb");
			if (fp == NULL) UTILITY_API->DisplayMessageBox("File cannot be opened");
			
			curl_easy_setopt(image, CURLOPT_WRITEFUNCTION, NULL);
			curl_easy_setopt(image, CURLOPT_WRITEDATA, fp);
			curl_easy_setopt(image, CURLOPT_URL, tempurl);
			curl_easy_setopt(image, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt(image, CURLOPT_NOPROGRESS, 0);
			curl_easy_setopt(image, CURLOPT_TIMEOUT, 600L);
			curl_easy_setopt(image, CURLOPT_XFERINFOFUNCTION, progress_callback);
			// Grab image
			imageResult = curl_easy_perform(image);
			
			if (imageResult)
				cout << "Cannot grab the image!"+ '\n';
		}
		// Clean up the resources
		curl_easy_cleanup(image);
		// Close the file
		fclose(fp);
		UTILITY_API->DeleteProgressBar(false);
		Logger("Utility::DownloadImageFromURL() Ended...");

	}
	/**
	 * \brief Writes data to file stream
	 * \param ptr 
	 * \param size 
	 * \param nmemb 
	 * \param stream 
	 * \return size_t
	 */
	inline size_t WriteData(void* ptr, size_t size, size_t nmemb, FILE* stream) 
	{
		Logger("Utility::WriteData() Started...");
		size_t written;
		written = fwrite(ptr, size, nmemb, stream);
		Logger("Utility::WriteData() Ended...");
		return written;
	}
	/**
	 * \brief Downloads file from Rest Service URL
	 * \param URL 
	 * \param fileName 
	 */
	inline void DownloadFilesFromURL(string& URL, string& fileName)
	{
		Logger("Utility::DownloadFilesFromURL() Started...");
		UTILITY_API->CreateProgressBar();
		CURL* curl;
		FILE* fp;
		CURLcode res;
		string url1;
		const char* url = URL.c_str();
		curl_version_info_data* vinfo = curl_version_info(CURLVERSION_NOW);
		if (vinfo->features & CURL_VERSION_SSL) {
			printf("CURL: SSL enabled"+ '\n');
		}
		else {
			printf("CURL: SSL not enabled\n");
		}
		curl = curl_easy_init();
		if (curl) {
			fp = fopen(fileName.c_str(), "wb");
			/* Setup the https:// verification options. Note we   */
			/* do this on all requests as there may be a redirect */
			/* from http to https and we still want to verify     */
			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_CAINFO, "./ca-bundle.crt");
			//curl_easy_setopt(curl, CURLOPT_USERPWD, "wcadmin:wcadmin"); //now ani trims image isssue
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, 600L);
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
			curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_callback);

			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			int i = fclose(fp);
		}
		UTILITY_API->DeleteProgressBar(false);
		Logger("Utility::DownloadFilesFromURL() Ended...");
	} 
	/**
	 * \brief Deletes all files and directory of the provided folder
	 * \param folder 
	 */
	inline void RemoveDirectory(const wchar_t* folder)
	{
		Logger("Utility::RemoveDirectory() Started...");
		std::wstring folderPath = std::wstring(folder) + _T("/*.*");
		std::wstring searchPath = std::wstring(folder) + _T("/");
		WIN32_FIND_DATA findData;
		HANDLE hanldeFind = ::FindFirstFile(folderPath.c_str(), &findData);
		if (hanldeFind != INVALID_HANDLE_VALUE) {
			do {
				if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					if (wcscmp(findData.cFileName, _T(".")) != 0 && wcscmp(findData.cFileName, _T("..")) != 0)
					{
						RemoveDirectory((wchar_t*)(searchPath + findData.cFileName).c_str());
					}
				}
				else {
					DeleteFile((searchPath + findData.cFileName).c_str());
				}
			} while (::FindNextFile(hanldeFind, &findData));
			::FindClose(hanldeFind);
			_wrmdir(folder);
		}
		Logger("Utility::RemoveDirectory() Ended...");
	}
	//To-Do Is this required?
	inline int getFileSize(const std::string& fileName)
	{
		Logger("Utility::getFileSize() Started...");
		ifstream file(fileName.c_str(), ifstream::in | ifstream::binary);

		if (!file.is_open())
		{
			return -1;
		}

		file.seekg(0, ios::end);
		int fileSize = file.tellg();
		file.close();
		Logger("Utility::getFileSize() Ended...");
		return fileSize;
	}
	/**
	 * \brief Search for Sub String in a String and deletes it.
	 * \param completeString 
	 * \param toEraseString 
	 */
	inline void EraseSubString(std::string& completeString, const std::string& toEraseString)
	{
		Logger("Utility::EraseSubString() Started...");
		// Search for the substring in string
		size_t pos = completeString.find(toEraseString);

		if (pos != std::string::npos)
		{
			// If found then erase it from string
			completeString.erase(pos, toEraseString.length()+5);
		}
		Logger("Utility::EraseSubString() Ended...");
	}

	/**
	 * \brief Method reads dropdown values from JSON
	 * \param json& lookUpsJson, string attributeValue, map<string, string>& attribMap
	 */
	inline void GetDropDownMap(IN const json& lookUpsJson, IN const string& attributeValue, OUT map<string, string>& attribMap)
	{
		Logger("Utility::GetDropDownMap() Started...");
		map<string, string> tempMap;
		json lookupNameAndIdJson, colNameAndIDJSON;
		for (int i = 0; i < lookUpsJson.size(); i++) {
			string lookupNameAndId = lookUpsJson[i].dump();
			try {
				lookupNameAndIdJson = json::parse(lookupNameAndId);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("Utility::GetDropDownMap()::parsing lookupNameAndIdJson exception - " + string(e.what()));
				throw e.what();
			}
			string colName = lookupNameAndIdJson["name"].dump();
			colName = colName.erase(0, 1);
			colName = colName.erase(colName.size() - 1);
			if (attributeValue.compare(colName) == 0)
			{
				string id, name, status;
				string columnStg = lookupNameAndIdJson["column"].dump();
				try {
					colNameAndIDJSON = json::parse(columnStg);
				}
				catch (exception& e)
				{
					Utility::ErrorLogger("Utility::Utility::GetDropDownMap()::parsing colNameAndIDJSON exception - " + string(e.what()));
					throw e.what();
				}
				id = colNameAndIDJSON["Id"].dump();
				status = colNameAndIDJSON["Status"].dump();
				name = colNameAndIDJSON["Name"].dump();
				name = name.erase(0, 1);
				name = name.erase(name.size() - 1);
				if (!status.empty() && stoi(status) < 2) {
					tempMap.insert(std::make_pair(name, id));
				}
			}
		}
		attribMap = tempMap;

		Logger("Utility::GetDropDownMap() Ended...");
	}

	/**
	 * \brief Method reads dropdown values from JSON
	 * \param json& lookUpsJson, string attributeValue, map<string, string>& attribMap
	 */
	inline void GetDropDownMapWithCode(IN const json& lookUpsJson, 
		IN const string& attributeValue, OUT map<string, string>& attribMap, IN const string& attributeId)
	{
		Logger("Utility::GetDropDownMapWithCode() Started...");
		json lookupNameAndIdJson, colNameAndIDJSON;
		for (int i = 0; i < lookUpsJson.size(); i++) {
			string lookupNameAndId = lookUpsJson[i].dump();
			try {
				lookupNameAndIdJson = json::parse(lookupNameAndId);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("Utility::GetDropDownMapWithCode()::parsing lookupNameAndIdJson exception - " + string(e.what()));
				throw e.what();
			}
			string colName = lookupNameAndIdJson["name"].dump();
			colName = colName.erase(0, 1);
			colName = colName.erase(colName.size() - 1);
			if (attributeValue.compare(colName) == 0)
			{
				string id, name, status, code;
				string columnStg = lookupNameAndIdJson["column"].dump();
				try {
					colNameAndIDJSON = json::parse(columnStg);
				}
				catch (exception& e)
				{
					Utility::ErrorLogger("Utility::Utility::GetDropDownMap()::parsing colNameAndIDJSON exception - " + string(e.what()));
					throw e.what();
				}
				id = colNameAndIDJSON["Id"].dump();
				status = colNameAndIDJSON["Status"].dump();
				code = colNameAndIDJSON["Code"].dump();
				if (code != "null") {
					code = colNameAndIDJSON["Code"].get<string>();
				}
				name = colNameAndIDJSON["Name"].dump();
				name = name.erase(0, 1);
				name = name.erase(name.size() - 1);
				if (!status.empty() && stoi(status) < 2) {
					attribMap.insert(std::make_pair(attributeId+"_"+ code, name));
				}
			}
		}

		Logger("Utility::GetDropDownMapWithCode() Ended...");
	}

	/**
	 * \brief Method to copy a file from SRC to DEST
	 */
	inline bool copyFile(const char* SRC, const char* DEST)
	{
		std::ifstream src(SRC, std::ios::binary);
		std::ofstream dest(DEST, std::ios::binary);
		dest << src.rdbuf();
		return src && dest;
	}
	/**
	 * \brief Function is used to writes string to file
	 * \param jsonFilePath
	 */
	inline void WriteJSONFile(string jsonFilePath, bool clearContent, json jsonObject)
	{
		Logger("Utility::WriteJSONFile() Started...");
		std::ofstream fileofs;
		if (clearContent)
		{
			fileofs.open(jsonFilePath.c_str(), std::ofstream::out | std::ofstream::trunc);
			fileofs << jsonObject;
			fileofs.close();
		}
		else
		{
			fileofs.open(jsonFilePath.c_str(), std::ios_base::out | std::ios_base::app);
			fileofs << jsonObject;
			fileofs.close();
		}
		Logger("Utility::WriteJSONFile() Ended...");
	}
	/**
	 * \brief Function is used to get json of key and display value of attributes
	 * \return json
	 */
	inline json GetKeyValuePairs() {
		Logger("Utility::GetKeyValuePairs() Started...");

		json keyValuePairs;
		string parameter = "{\"locale\" : \"en-US\"}";
		string response = RestCall(parameter, KEY_VALUE_PAIR);
		string errorResponse = Utility::CheckErrorDescription(response);
		Utility::Logger("Utility::GetKeyValuePairs() errorResponse - " + errorResponse);
		
		if (errorResponse.empty() && (errorResponse.length() == 0))
		{
			json responseJson;
			try
			{
				responseJson = json::parse(response);
				string keyValuePairStr = responseJson["keyValuePairs"].dump();
				keyValuePairs = json::parse(keyValuePairStr);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("Utility::GetKeyValuePairs()::parsing responseJson exception - " + string(e.what()));
				throw e.what();
			}
			Logger("Utility::GetKeyValuePairs() Ended...");
			return keyValuePairs;
		}
		else
		{
			UTILITY_API->DisplayMessageBox(errorResponse);
		}
	}
	/**
	 * \brief Function is used to get display value of attribute
	 * \param internal Name, entity
	 * \return Display Value
	 */
	inline QString GetDisplayValueByKey(QString& key, QString& entity, json& keyValuePairs) {
		Logger("Utility::GetDisplayValueByKey() Started...");
		string displayValue = keyValuePairs[entity.toUpper().toStdString() + "." + key.toUpper().toStdString() + ".DISPLAYTEXT"].dump();
		if (!displayValue.empty()) {
			displayValue = displayValue.erase(0, 1);
			displayValue = displayValue.erase(displayValue.size() - 1);
		}

		if (displayValue == "ul") {
			displayValue = "";
		}
		Logger("Utility::GetDisplayValueByKey() Ended...");
		return QString::fromStdString(displayValue);
	}
	/**
	 * \brief Reads JSON object with passed key and trims " if required and returns value
	 * \param json, key, trimQuotes
	 * \return string
	 */
	template <typename tempPar>
	inline string GetJSONValue(json json, tempPar key, bool trimQuotes)
	{
		Logger("Utility::GetJSONValue() Started...");
		string value = json[key].dump();
		if (trimQuotes)
		{
			value.erase(std::remove(value.begin(), value.end(), '"'), value.end());
			Utility::Logger(key + "::" + value);
		}
		Logger("Utility::GetJSONValue() Ended...");
		return value;
	}
	
/**
	 * \brief Converts JSON Array to QStringList, which format is required to write Qt UI 
	 * \param jsonArray
	 * \return QStringList
	 */
	inline QStringList ConvertJSONArrayQStringList(json jsonArray)
	{
		Logger("Utility::ConvertJSONArrayQStringList() Started...");
		QStringList stringList;
		if (jsonArray.is_array())
		{
			string value;
			for (auto count = 0; count < jsonArray.size(); count++)
			{
				value = GetJSONValue<int>(jsonArray, count, true);
				stringList << QString::fromStdString(value);
			}
		}
		Logger("Utility::ConvertJSONArrayQStringList() Ended...");
		return stringList;
	}
	/**
	 * \brief - Method prepare PageINFoMap for Parameters for the restcalls
	 * \return json
	 */
	inline json GetPageInfoMap()
	{
		Logger("Utility::GetPageInfoMap() Started...");
		json pagInfoMap;
		pagInfoMap["Page"] = 1;
		pagInfoMap["PageSize"] = PAGE_SIZE;
		pagInfoMap["pageCount"] = 1;
		pagInfoMap["totalCount"] = 2;
		Logger("Utility::GetPageInfoMap() End...");
		return pagInfoMap;
	}
	/**
	* \brief Prepares a blank JSON map using passed entity and returns json of blank parameter
	* \param entity
	* \return json
	*/
	inline json GetBlankJSONParameter(string entity)
	{
		Logger("Utility::GetBlankJSONParameter() Started...");
		json conditions = json::object();
		json colorPalSearchMap;
		colorPalSearchMap["roleId"] = Configuration::GetInstance()->GetRoleId();
		colorPalSearchMap["userId"] = Configuration::GetInstance()->GetUserId();
		colorPalSearchMap["Schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
		colorPalSearchMap["pageType"] = "list";
		colorPalSearchMap["sortInfo"] = nullptr;
		colorPalSearchMap["PageInfo"] = GetPageInfoMap();
		colorPalSearchMap["entity"] = entity;
		conditions["Conditions"] = json::array();
		conditions["Search"] = nullptr;
		colorPalSearchMap["dataFilter"] = conditions;
		Logger("Utility::GetBlankJSONParameter() End...");
		return colorPalSearchMap;
	}
	/**
	* \brief Prepares a blank JSON map using passed entity and returns json of blank parameter
	* \param entity
	* \return json
	*/
	inline json GetResultsJSON(string response)
	{
		Logger("Utility::GetResultsJSON() Started...");
		json resultsJSON;
		try
		{
			resultsJSON = json::parse(response);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("Utility::GetResultsJSON()::parsing resultsJSON exception - " + string(e.what()));
			throw e.what();
		}
		Logger("Utility::GetResultsJSON() End...");
		return resultsJSON;
	}
	inline bool IsValidParameter(json& parameter)
	{
		Logger("Utility::IsValidParameter() Started...");
		bool validParameter = false;
		json dataFilterJSON = json::object();
		json conditionsJSON = json::array();
		try
		{
			string dataFilter = GetJSONValue<string>(parameter, "dataFilter", false);
			dataFilterJSON = json::parse(dataFilter);
			string conditions = GetJSONValue<string>(dataFilterJSON, "Conditions", false);
			conditionsJSON = json::parse(conditions);
			if (conditionsJSON != "null" && conditionsJSON.size() != 0)
			{
				validParameter = true;
			}
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("Utility::IsValidParameter()::parsing dataFilterJSON exception - " + string(e.what()));
			throw e.what();
		}
		Logger("Utility::IsValidParameter() End...");
		return validParameter;
	}
	
	/*
	*brief validating UI feilds.
	*call from Search_clicked()
	*return boolean.
	*/
	inline bool ExtractAllUIValuesAndMapToJson(QTreeWidget* SearchTree, std::vector<Utility::Fields>& fieldsVector)
	{
		Utility::Logger("Utility -> ExtractAllUIValuesAndMapToJson() -> End");

		bool isUserInputEmpty = true;
		if (SearchTree)
		{
			for (int i = 0; i < SearchTree->topLevelItemCount(); ++i)
			{
				QTreeWidgetItem* topItem = SearchTree->topLevelItem(i); 
				QWidget* qWidgetColumn0 = SearchTree->itemWidget(topItem, 0);
				QWidget* qWidgetColumn1 = SearchTree->itemWidget(topItem, 1);
				QLabel* qlabel = qobject_cast<QLabel*>(qWidgetColumn0);
				string lable = qlabel->text().toStdString();
				QLineEdit* qlineedit = qobject_cast<QLineEdit*>(qWidgetColumn1);
				if (qlineedit)
				{
					fieldsVector[i].userInputValues = qlineedit->text().toUtf8();
					if (!qlineedit->text().isEmpty())
					{
						isUserInputEmpty = false; 
					}
				}
				else
				{
					QComboBox* qComboBox = qobject_cast<QComboBox*>(qWidgetColumn1);
					if (qComboBox)
					{
						fieldsVector[i].userInputValues = qComboBox->currentText().toUtf8();
						if (qComboBox->currentText() != "Select")
						{
							isUserInputEmpty = false;
						}
					}
					else
					{
						QTextEdit* qtextEdit = qobject_cast<QTextEdit*>(qWidgetColumn1);
						if (qtextEdit)
						{
							fieldsVector[i].userInputValues = qtextEdit->toPlainText().toUtf8();
							if (!qtextEdit->toPlainText().isEmpty())
							{
								isUserInputEmpty = false;
							}
						}
					}
				}
			}
		}
		if (isUserInputEmpty)
		{
			UTILITY_API->DisplayMessageBox("Please enter atleast one field to search.");	
			return false;
		}
		Utility::Logger("Utility -> ExtractAllUIValuesAndMapToJson() -> End");
		return true;
	}

	/**
	 * \brief : this method validates all the wildcard search values entered by the user before searching.
	* \Param  : void
	 * \return true or flase
	 */
	inline bool SearchValidation(QTreeWidget* SearchTree)
	{
		Utility::Logger("Utility -> SearchValidation() -> Start");
		if (SearchTree)
		{
			bool isOnlyPercentileFound = false;
			Utility::Logger("ProductSearch -> SearchValidation() -> Start");
			for (int i = 0; i < SearchTree->topLevelItemCount(); ++i)
			{
				QTreeWidgetItem* topItem = SearchTree->topLevelItem(i);
				QWidget* qWidgetColumn1 = SearchTree->itemWidget(topItem, 1);
				QLineEdit* qlineedit = qobject_cast<QLineEdit*>(qWidgetColumn1);
				QTextEdit* qtextEdit = qobject_cast<QTextEdit*>(qWidgetColumn1);
				if (qlineedit)
				{
					if (qlineedit->text() == "%")
					{
						isOnlyPercentileFound = true;
					}
				}
				else if (qtextEdit)
				{
					if (qtextEdit->toPlainText() == "%")
					{
						isOnlyPercentileFound = true;
					}
				}
			}
			if (isOnlyPercentileFound)
			{
				UTILITY_API->DisplayMessageBox("Please enter a valid search criteria.");
				Utility::Logger("ColorSearch -> SearchValidation() -> Please enter a valid search criteria.");
				return false;
			}
			Utility::Logger("Utility -> SearchValidation() -> End");
			return true;
		}
	}
	/*
	*brief calls filteredJson method for respective entities
	*\param entity
	*\return string
	*/
	inline string getDetailJson(string entity) {
		Utility::Logger("Utility -> getDetailJson() -> Start");
		string jsonFilePath = "";
		if (entity == "Style") {
			jsonFilePath = DirectoryUtil::getProdSearchJson();
		}
		else if (entity == "Color") {
			jsonFilePath = DirectoryUtil::getColorDetailJson();
		}
		else if (entity == "Material") {
			jsonFilePath = DirectoryUtil::getFabricSearchJson();
		}
		else if (entity == "Trim") {
			jsonFilePath = DirectoryUtil::getTrimDetailJson();
		}
		Utility::Logger("Utility -> getDetailJson() -> End");
		return jsonFilePath;
	}
	/**
	* \brief Method gets the response for respective entity Details from PLM
	* \param parameter, api, entity
	*/
	inline void GetFilteredJson(string parameter, string api, string entity)
	{
		Utility::Logger("Utility -> GetFilteredJson() -> Start");
		ofstream entityDetailsFile;
		entityDetailsFile.open(getDetailJson(entity));
		Utility::Logger("Utility::GetFilteredJson() parameter - " + parameter);
		string response = RestCall(parameter, api);
		Utility::CustomMessageBox("response::" + response);
		Utility::Logger("ColorSearch::GetFilteredColorJson() response - " + response);
		string errorResponse = Utility::CheckErrorDescription(response);
		Utility::Logger("ColorSearch::GetFilteredColorJson() errorResponse - " + errorResponse);
		json docLibjson;
		if (errorResponse.empty() && (errorResponse.length() == 0))
		{
			try
			{
				docLibjson = json::parse(response);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("Utility -> GetFilteredJson()::parsing docLibjson exception - " + string(e.what()));
				throw e.what();
			}
		}
		else
		{
			UTILITY_API->DisplayMessageBox(errorResponse);
		}
		entityDetailsFile << docLibjson;
		entityDetailsFile.close();

		Utility::Logger("Utility -> GetFilteredJson() -> End");
	}

	/*
	*brief calls filteredJson method for respective entities
	*\param entity
	*\return string
	*/
	inline string GetFilteredFromDetailsJson(string entity) {
		Utility::Logger("Utility -> GetFilteredFromDetailsJson() -> Start");
		string jsonFilePath = "";
		if (entity == "Style") {
			jsonFilePath = DirectoryUtil::getProdSearchFilteredJson();
		}
		else if (entity == "Color") {
			jsonFilePath = DirectoryUtil::getColorSearchFilteredJson();
		}
		else if (entity == "Material") {
			jsonFilePath = DirectoryUtil::getFabricSearchFilteredJson();
		}
		else if (entity == "Trim") {
			jsonFilePath = DirectoryUtil::getTrimSearchFilteredJson();
		}
		Utility::Logger("Utility -> GetFilteredFromDetailsJson() -> End");
		return jsonFilePath;
	}

	/*
	*brief read the filtered json file to draw widget dialogue.
	*\param entity
	*\return vector
	*/
	inline std::vector<Utility::Fields> ReadJsonForDrawDialogue(string entity)
	{
		Utility::Logger("Utility -> ReadJsonForDrawDialogue() -> Start");
		std::vector<Utility::Fields> fieldsVector;
		json jsonString;
		Utility::Fields tempField;

		ifstream entitySearchFile;
		entitySearchFile.open(GetFilteredFromDetailsJson(entity));
		entitySearchFile >> jsonString;
		entitySearchFile.close();
		string completeJsonString, uiTypeJSONObject, presetListJSONObject, fieldValues;
		json completeJson, componentsJson, presetListJSON, fieldValuesJson;
		completeJsonString = jsonString.dump();
		try {
			completeJson = json::parse(completeJsonString);
			uiTypeJSONObject = completeJson["uiTypeList"].dump();
			componentsJson = json::parse(uiTypeJSONObject);
			presetListJSONObject = completeJson["presetList"].dump();
			presetListJSON = json::parse(presetListJSONObject);
			fieldValues = completeJson["fieldList"].dump();
			fieldValuesJson = json::parse(fieldValues);
		}
		catch (exception & e)
		{
			Utility::ErrorLogger("Utility -> ReadJsonForDrawDialogue()::parsing completeJson exception - " + string(e.what()));
			throw e.what();
			
		}
		for (int i = 0; i < fieldValuesJson.size(); i++)
		{
			string fieldValuesString = fieldValuesJson[i].dump();
			fieldValuesString = fieldValuesString.erase(0, 1);
			fieldValuesString = fieldValuesString.erase(fieldValuesString.size() - 1);
			tempField.labelValue = QString::fromStdString(fieldValuesString);
			string uiTypes = componentsJson[fieldValuesString].dump();
			uiTypes = uiTypes.erase(0, 1);
			uiTypes = uiTypes.erase(uiTypes.size() - 1);
			tempField.fieldUItype = QString::fromStdString(uiTypes);
			if (tempField.fieldUItype == "dropdown")
			{
				QStringList listQt;
				json options = presetListJSON[fieldValuesString].get<json>();
				for (int j = 0; j < options.size(); j++)
				{
					listQt.append(QString::fromUtf8(options[j].get<string>().c_str()));
				}
				tempField.presetValues = listQt;
			}
			fieldsVector.push_back(tempField);
		}
		Utility::Logger("Utility -> ReadJsonForDrawDialogue() -> End");
		return fieldsVector;
	}

	/**
	* Function is used to remove invalid characters from file name which are not supported by Windows
	*/
	inline string RemoveInvalidFileNameChars(string& fileName)
	{
		string revisedFileName = "";
		for (auto charItr = fileName.cbegin(); charItr != fileName.cend(); ++charItr) {
			if (INVALID_FILENAME_CHARS.find(*charItr) == string::npos) {
				revisedFileName = revisedFileName + *charItr;
			}
		}

		return revisedFileName;
	}

	/**
	* Function is used to create a search map criteria
	*/
	inline int CreateSearchCriteriaMap(json& conditions, vector<Utility::Fields>& fieldsVector, map<string, map<string, string>>& attsDropdownListMap)
	{
		Utility::Logger("Utility -> CreateSearchCriteriaMap() -> Start");
		int count = 0;
		json mapArray;
		json filterMap;
		for (auto array_element : fieldsVector)
		{
			string attLabel = array_element.labelValue.toStdString();
			string userSelected = array_element.userInputValues.toStdString();
			if ((userSelected != "") && (userSelected != "Select"))
			{
				if ((array_element.fieldUItype == "dropdown") && (array_element.userInputValues != "Select"))
				{
					mapArray["fieldName"] = attLabel;
					map<string, string> attNameIdMap;
					attNameIdMap.clear();
					attNameIdMap.insert(attsDropdownListMap[attLabel].begin(), attsDropdownListMap[attLabel].end());
					for (auto it = attNameIdMap.begin(); it != attNameIdMap.end(); it++)
					{
						if (it->first == userSelected)
						{
							mapArray["operator"] = "=";
							mapArray["value"] = stoi(it->second);
							break;
						}
					}
					conditions["Conditions"][count++] = mapArray;
				}
				else
				{
					filterMap.clear();
					filterMap["fieldName"] = attLabel;
					filterMap["operator"] = "like";
					filterMap["value"] = userSelected;
					filterMap["logicalOperator"] = "AND";
					filterMap["IsSearch"] = true;
					conditions["Conditions"][count++] = filterMap;
				}
			}
		}
		Utility::Logger("Utility -> CreateSearchCriteriaMap() -> End");

		return count;
	}
		
	inline QPixmap getNoImageAvailable()
	{
		QPixmap pixmap;
		QImage styleIcon;
		styleIcon.load(QString::fromStdString(DirectoryUtil::getNoImage()));
		if (styleIcon.isNull()) {
			Utility::Logger("ProductSearchDialog -> CreateResultTable() Image is not loaded.  ");
		}
		else {
			pixmap = QPixmap::fromImage(styleIcon);
		}
		return pixmap;
	}

	/**
	 * Method is used to check
	 * \param boolean
	 */
	inline json ValidateUserLicense(const string& url, const string& userId)
	{
		string alertMessage;
		Utility::Logger("ValidateUserLicense :: License login - START");
		char hostbuffer[256];
		// To retrieve hostname 
		int hostname = gethostname(hostbuffer, sizeof(hostbuffer));

		// To retrieve host information 
		struct hostent* host_entry = gethostbyname(hostbuffer);

		// To convert an Internet network address into ASCII string 
		char* IPbuffer = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));

		string hostName(hostbuffer);
		string IPAddress(IPbuffer);
		Utility::Logger("Host Name : " + hostName + " And IP address : " + IPAddress);
		if (Configuration::GetInstance()->GetCompanyName().empty()) {
			return json::parse(LICENSE_ERROR_CODE_101);
		} else if (Configuration::GetInstance()->GetCompanyApiKey().empty()) {
			return json::parse(LICENSE_ERROR_CODE_102);
		}

		string basic_auth = "Basic " + ConvertToBase64(Configuration::GetInstance()->GetCompanyName()+":"+ Configuration::GetInstance()->GetCompanyApiKey());

		vector<pair<string, string>> authCodeHeader;
		authCodeHeader.push_back(make_pair(CONTENTTYPE, FORM_ENCODED_TYPE));
		authCodeHeader.push_back(make_pair(AUTHORIZATION, basic_auth));
		
		string loginRequestParam = "machineName=" + hostName;
		loginRequestParam += "&privateIp=" + IPAddress;
		loginRequestParam += "&companyName=" + Configuration::GetInstance()->GetCompanyName();
		loginRequestParam += "&userId=" + userId;
		Utility::Logger("License login param : " + loginRequestParam);
		string response = REST_API->CallRESTPost(url, &loginRequestParam, authCodeHeader, HTTP_POST);
		Utility::Logger("License login response : " + response);
		size_t found1 = response.find(UNAUTHORIZED);
		if (found1 != string::npos)
		{
			return json::parse("{\"result_code\": 0}");
		}

		json resJson;
		int flowerBraceIndex = response.find("{");
		string resultsString = response.substr(flowerBraceIndex);

		try
		{
			resJson = json::parse(resultsString);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("ValidateUserLicense :: License login exception - " + string(e.what()));
			throw e.what();
		}
		
		Utility::Logger("ValidateUserLicense :: License login - END");

		return resJson;
	}


	/**
	* Method is used to get the value from json object
	*/
	inline string getValue(json& data) {

		if (data.is_null()) {
			return "";
		}
		else if (data.is_number()) {
			return data.dump();
		}
		else if (data.is_boolean()) {
			return data.get<bool>() ? "true" : "false";
		}
		else if (data.is_string()) {
			return data.get<string>();
		}
		else {
			string value = data.dump();
			if (value.rfind("\"", 0) == 0) {
				value = value.erase(0, 1);
				value = value.erase(value.size() - 1);
			}

			return value;
		}
	}
	inline string getLookUpName(json dependencyJson, string glValueId, string lookupRefName) //Pass lookUpRef
	{
		Utility::Logger("Utilitty:: -> getLookUpName() -> Start");
		string lookups = dependencyJson["lookups"].dump();
		json completeLookUpsJson;
		try {
			completeLookUpsJson = json::parse(lookups);
		}
		catch (exception& e)
		{
			Utility::ErrorLogger("Utility::getLookUpName()::parsing completeLookUpsJson exception - " + string(e.what()));
			throw e.what();
		}
		string lookupId, lookupName, lookupMainName;
		if ((completeLookUpsJson.size() != 0))
		{
			json lookupJson, columns;
			string lookupJsonStr;
			for (int i = 0; i < completeLookUpsJson.size(); i++)
			{
				lookupJsonStr = completeLookUpsJson[i].dump();
				try {

					lookupJson = json::parse(lookupJsonStr);
				}
				catch (exception& e)
				{
					Utility::ErrorLogger("Utility::getLookUpName()::parsing trim exception - " + string(e.what()));
					throw e.what();
				}
				lookupId = lookupJson["column"]["Id"].dump();
				lookupMainName = lookupJson["name"].dump();
				
				if (lookupId == glValueId && lookupRefName == lookupMainName) {
					lookupName = lookupJson["column"]["Name"].dump();
					lookupName = lookupName.erase(0, 1);
					lookupName = lookupName.erase(lookupName.size() - 1);
				}
			}
		}
		Utility::Logger("Utilitty:: -> getLookUpName() -> End");
		return lookupName;
	}
}