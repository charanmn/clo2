
#include "Configuration.h"
#include "CLOAPIInterface.h"
#include "CLO_PLUGIN/INFOR/Authentication/CLOPLMSignIn.h"
#include "Utility.h"
#include "CLO_PLUGIN/INFOR/Utilities/Definitions.h"
#include <fstream>
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
#include "DirectoryUtil.h"

using json = nlohmann::json;

Configuration* Configuration::_instance = NULL;
Configuration* Configuration::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new Configuration();
	}
	return _instance;
}
void  Configuration::Destroy()
{
	if (_instance)
	{
		delete _instance;
		_instance = NULL;
	}
}

string  Configuration::GetBearerToken()
{
	return m_bearerToken;
}

void Configuration::SetBearerToken(string bearerToken)
{
	m_bearerToken = bearerToken;
}

string  Configuration::GetRefreshTokenResponse()
{
	return m_refreshToken;
}

void Configuration::SetRefreshTokenResponse(string refreshToken)
{
	m_refreshToken = refreshToken;
}

string  Configuration::GetPLMUrl()
{
	return m_url;
}

void Configuration::SetPLMUrl(string str)
{
	m_url = str;
}

string  Configuration::GetAuth1()
{
	return m_auth1;
}

void Configuration::SetAuth1(string str)
{
	m_auth1 = str;
}

string  Configuration::GetAuth2()
{
	return m_auth2;
}

void Configuration::SetAuth2(string str)
{
	m_auth2 = str;
}

string  Configuration::GetConsumerKey()
{
	return m_consumerKey;
}

void Configuration::SetConsumerKey(string str)
{
	m_consumerKey = str;
}
string  Configuration::GetWebAppConsumerKey()
{
	return m_webAppConsumerKey;
}

void Configuration::SetWebAppConsumerKey(string str)
{
	m_webAppConsumerKey = str;
}

string  Configuration::GetSecretKey()
{
	return m_secretKey;
}

void Configuration::SetSecretKey(string str)
{
	m_secretKey = str;
}
string  Configuration::GetLogFileName()
{
	return m_logFileName;
}

void Configuration::SetLogFileName(string logFileName)
{
	m_logFileName = logFileName;
}
string  Configuration::GetErrorLogFileName()
{
	return m_errorLogFileName;
}

void Configuration::SetErrorLogFileName(string errorLogFileName)
{
	m_errorLogFileName = errorLogFileName;
}

string Configuration::GetCompanyName()
{
	return m_companyName;
}

void Configuration::SetCompanyName(string companyName)
{
	m_companyName = companyName;
}

string Configuration::GetCompanyApiKey()
{
	return m_companyApiKey;
}

void Configuration::SetCompanyApiKey(string companyApiKey)
{
	m_companyApiKey = companyApiKey;
}

/**
*\creating refreshtoken when the user getting Unauthorized.
*/
void Configuration::GetRefreshToken()
{
	Utility::Logger("Configuration::GetRefreshToken() Started...");
	string id = GetConsumerKey(); // set the clo id
	string pw = GetSecretKey();; // set the clo pw
	string basicAuthorizationString = BASIC + Utility::ConvertToBase64(id + ":" + pw); ////Converting Id and Password to Base64
	vector<pair<string, string>> headerNameAndValueList;
	headerNameAndValueList.push_back(make_pair(AUTHORIZATION, basicAuthorizationString));
	headerNameAndValueList.push_back(make_pair("Content-Type", "application/x-www-form-urlencoded"));
	headerNameAndValueList.push_back(make_pair(INFOR_TENANT, Configuration::GetInstance()->GetTenant()));
	string parameter = "grant_type=refresh_token";
	parameter += "&refresh_token=" + GetRefreshTokenResponse();
	Utility::CustomMessageBox("parameter::" + parameter);
	Utility::Logger("Configuration::GetRefreshToken() parameter - " + parameter);
	string response = REST_API->CallRESTPost(GetAuth2() + GET_REFRESH_TOKEN, &parameter, headerNameAndValueList, HTTP_POST);
	Utility::Logger("Configuration::GetRefreshToken() response - " + response);
	int indexforFlowerBrace = response.find("{");
	string jsonString = response.substr(indexforFlowerBrace);
	json bearerTokenJson;
	try {
		bearerTokenJson = json::parse(jsonString);
	}
	catch (exception& e)
	{
		Utility::ErrorLogger("Configuration::CachePLMsettingsFromFile()::parsing bearerTokenJson exception - " + string(e.what()));
		throw e.what();
	}
	string finalBearerToken = bearerTokenJson["access_token"].dump();
	finalBearerToken = finalBearerToken.erase(0, 1);
	finalBearerToken = finalBearerToken.erase(finalBearerToken.size() - 1);
	Configuration::GetInstance()->SetBearerToken("Bearer " + finalBearerToken);
	Utility::CustomMessageBox("response" + response);
	Utility::Logger("Configuration::GetRefreshToken() Ended...");
}

string Configuration::GetUserId()
{
	return m_UserId;
}
void Configuration::SetUserId(string UserId)
{
	m_UserId = UserId;
}

string Configuration::GetRoleId()
{
	return m_roleId;
}
void Configuration::SetRoleId(string roleId)
{
	m_roleId = roleId;
}
string Configuration::GetUserGUID()
{
	return m_userGUID;
}
void Configuration::SetUserGUID(string userGUID)
{
	m_userGUID = userGUID;
	Utility::CustomMessageBox("m_userGUID:::" + m_userGUID);
}
string  Configuration::GetServerUserName()
{
	return m_serverUserName;
}
void Configuration::SetServerUserName(string serverUserName)
{
	m_serverUserName = serverUserName;
}

string  Configuration::GetServerUserPassword()
{
	return m_serverUserPassword;
}
void Configuration::SetServerUserPassword(string serverPassword)
{
	m_serverUserPassword = serverPassword;
}

string  Configuration::GetTenant()
{
	return m_tenant;
}
void Configuration::SetTenant(string tenant)
{
	m_tenant = tenant;
}

string  Configuration::GetschemaWithQuotes()
{
	return m_schemaWithQuotes;
}
void Configuration::SetschemaWithQuotes(string schemaWithQuotes)
{
	m_schemaWithQuotes = schemaWithQuotes;
}

string  Configuration::GetschemaWithoutQuotes()
{
	return m_schemaWithoutQuotes;
}
void Configuration::SetschemaWithoutQuotes(string schemaWithoutQuotes)
{
	m_schemaWithoutQuotes = schemaWithoutQuotes;
}

string  Configuration::GetPlmVersion()
{
	return m_PlmVersion;
}
void Configuration::SetPlmVersion(string PlmVersion)
{
	m_PlmVersion = PlmVersion;
}

string  Configuration::GetRedirectUrl()
{
	return m_RedirectUrl;
}
void Configuration::SetRedirectUrl(string redirectUrl)
{
	m_RedirectUrl = redirectUrl;
}

string  Configuration::GetCloPlugin()
{
	return m_CloPlugin;
}
void Configuration::SetCloPlugin(string CloPlugin)
{
	m_CloPlugin = CloPlugin;
}

string  Configuration::GetConnectionStatus()
{
	return m_ConnectionStatus;
}
void Configuration::SetConnectionStatus(string ConnectionStatus)
{
	m_ConnectionStatus = ConnectionStatus;
}
int  Configuration::GetMaxLogFileSize()
{
	return m_maxLogFileSize;
}
void Configuration::SetMaxLogFileSize(int logFileSize)
{
	m_maxLogFileSize = logFileSize;
}
/**
*\Caches all PLM Settings values from file.
*/
void Configuration::CachePLMsettingsFromFile()
{
	Utility::Logger("Configuration::CachePLMsettingsFromFile() Started..");
	string plmSettingsFilePath = DirectoryUtil::getPLMPluginDirectory() + PLMSETTINGS_FILE_NAME;
	try
	{
		json plmSettingsJSON = Utility::ReadJSONFile(plmSettingsFilePath);
		string selectedTenant = Utility::GetJSONValue<string>(plmSettingsJSON, SELECTEDTENANT_JSON_KEY, true);
		Utility::Logger("Configuration::CachePLMsettingsFromFile() selectedTenant - " + selectedTenant);

		if (selectedTenant == SELECT || selectedTenant.empty())
		{
			ClearPLMsettingsCache();
		}
		else
		{
			string selectedTenantDetails = Utility::GetJSONValue<string>(plmSettingsJSON, selectedTenant, false);
			json selectedTenantDetailsJSON;
			try {
				selectedTenantDetailsJSON = json::parse(selectedTenantDetails);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("Configuration::CachePLMsettingsFromFile()::parsing selectedTenantDetailsJSON exception - " + string(e.what()));
				throw e.what();
			}
			CachePLMsettings(selectedTenantDetailsJSON, selectedTenant);
		}		
	}
	catch (exception & e)
	{
		Utility::Logger("Configuration::CachePLMsettingsFromFile() exception - " + PLMSETTINGS_EXCEPTION_MSG);
		UTILITY_API->DisplayMessageBox(PLMSETTINGS_EXCEPTION_MSG);
	}
	Utility::Logger("Configuration::CachePLMsettingsFromFile() Ended..");
}
/**
*\Clears all PLM Settings values.
*/
void Configuration::ClearPLMsettingsCache()
{
	Utility::Logger("Configuration::ClearPLMsettingsCache() Started..");

	Configuration::GetInstance()->SetAuth1(BLANK);
	Configuration::GetInstance()->SetAuth2(BLANK);
	Configuration::GetInstance()->SetConsumerKey(BLANK);
	Configuration::GetInstance()->SetPLMUrl(BLANK);
	Configuration::GetInstance()->SetschemaWithQuotes(BLANK);
	Configuration::GetInstance()->SetschemaWithoutQuotes(BLANK);
	Configuration::GetInstance()->SetSecretKey(BLANK);
	Configuration::GetInstance()->SetServerUserPassword(BLANK);
	Configuration::GetInstance()->SetServerUserName(BLANK);
	Configuration::GetInstance()->SetTenant(BLANK);
	Configuration::GetInstance()->SetWebAppConsumerKey(BLANK);
	Configuration::GetInstance()->SetPlmVersion(BLANK);
	Configuration::GetInstance()->SetCloPlugin(BLANK);
	Configuration::GetInstance()->SetConnectionStatus(SERVER_NOTCONNECTED_STATUS);
	Configuration::GetInstance()->SetRedirectUrl(BLANK);
	Configuration::GetInstance()->SetCompanyName(BLANK);
	Configuration::GetInstance()->SetCompanyApiKey(BLANK);

	Utility::Logger("Configuration::ClearPLMsettingsCache() Ended..");
}
/**
*\Caches all PLM Settings values.
*/
void Configuration::CachePLMsettings(json selectedTenantDetails, string tenant)
{
	Utility::Logger("Configuration::CachePLMsettings() Started..");
	Utility::Logger("selected environment::");
	string plmSetting = Utility::GetJSONValue<string>(selectedTenantDetails, AUTH1_JSON_KEY, true);
	Configuration::GetInstance()->SetAuth1(plmSetting);

	plmSetting = Utility::GetJSONValue<string>(selectedTenantDetails, AUTH2_JSON_KEY, true);
	Configuration::GetInstance()->SetAuth2(plmSetting);

	plmSetting = Utility::GetJSONValue<string>(selectedTenantDetails, CONSUMERKEY_JSON_KEY, true);
	Configuration::GetInstance()->SetConsumerKey(plmSetting);

	plmSetting = Utility::GetJSONValue<string>(selectedTenantDetails, PLMSERVERURL_JSON_KEY, true);
	Configuration::GetInstance()->SetPLMUrl(plmSetting);

	plmSetting = Utility::GetJSONValue<string>(selectedTenantDetails, SECRETEKEY_JSON_KEY, true);
	Configuration::GetInstance()->SetSecretKey(plmSetting);

	plmSetting = Utility::GetJSONValue<string>(selectedTenantDetails, SERVERPASSWORD_JSON_KEY, true);
	Configuration::GetInstance()->SetServerUserPassword(plmSetting);

	plmSetting = Utility::GetJSONValue<string>(selectedTenantDetails, SERVERUSERNAME_JSON_KEY, true);
	Configuration::GetInstance()->SetServerUserName(plmSetting);

	Configuration::GetInstance()->SetTenant(tenant);

	plmSetting = Utility::GetJSONValue<string>(selectedTenantDetails, WEBAPPCONSUMERKEY_JSON_KEY, true);
	Configuration::GetInstance()->SetWebAppConsumerKey(plmSetting);

	plmSetting = Utility::GetJSONValue<string>(selectedTenantDetails, CLOPLMPLUGINVERSION_JSON_KEY, true);
	Configuration::GetInstance()->SetPlmVersion(plmSetting);

	plmSetting = Utility::GetJSONValue<string>(selectedTenantDetails, CLOPLUGINVERSION_JSON_KEY, true);
	Configuration::GetInstance()->SetCloPlugin(plmSetting);

	plmSetting = Utility::GetJSONValue<string>(selectedTenantDetails, REDIRECT_URL, true);
	Configuration::GetInstance()->SetRedirectUrl(plmSetting);

	plmSetting = Utility::GetJSONValue<string>(selectedTenantDetails, COMPANY_NAME, true);
	Configuration::GetInstance()->SetCompanyName(plmSetting);

	plmSetting = Utility::GetJSONValue<string>(selectedTenantDetails, COMPANY_API_KEY, true);
	Configuration::GetInstance()->SetCompanyApiKey(plmSetting);

	if (Configuration::GetInstance()->GetBearerToken().empty())
	{
		if (SERVER_CONNECTED_STATUS == Configuration::GetInstance()->GetConnectionStatus())
		{
			Configuration::GetInstance()->SetschemaWithQuotes(SCHEMA_RELOGIN_MSG);
			Configuration::GetInstance()->SetschemaWithoutQuotes(SCHEMA_RELOGIN_MSG);
		}
		else
		{
			Configuration::GetInstance()->SetschemaWithQuotes(SCHEMA_LOGIN_MSG);
			Configuration::GetInstance()->SetschemaWithoutQuotes(SCHEMA_LOGIN_MSG);
		}
		Configuration::GetInstance()->SetConnectionStatus(SERVER_NOTCONNECTED_STATUS);
	}
	else
	{
		Configuration::GetInstance()->SetConnectionStatus(SERVER_CONNECTED_STATUS);
	}
	Utility::Logger("Configuration::CachePLMsettings() Ended..");
}
void Configuration::CreateTemporaryFolderPath()
{
	string temporaryPath = UTILITY_API->GetCLOTemporaryFolderPath();
	MATERIALS_TEMP_DIRECTORY = temporaryPath + "TempMaterials\\";
	PRODUCTS_TEMP_DIRECTORY = temporaryPath + "TempProducts\\";
	TRIMS_TEMP_DIRECTORY = temporaryPath + "TempTrims\\";
	COLORS_TEMP_DIRECTORY = temporaryPath + "TempColors\\";
}
/**
* \brief Function is used to validate PLM Settings and return true or false
* \return Display Value
*/
bool Configuration::ValidatePLMSettings()
{
	bool validationPassed = false;
	if (!GetAuth1().empty() && !GetAuth2().empty() && !GetConsumerKey().empty() && !GetSecretKey().empty()
		&& !GetPLMUrl().empty() && !GetServerUserName().empty() && !GetServerUserPassword().empty() && !GetTenant().empty())
	{
		validationPassed = true;
	}
	return validationPassed;
}

