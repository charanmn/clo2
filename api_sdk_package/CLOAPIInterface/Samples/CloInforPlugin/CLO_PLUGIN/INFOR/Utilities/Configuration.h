#pragma once

#include <string>
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
using json = nlohmann::json;
using namespace std;
class Configuration
{
	static Configuration* _instance; // zero initialized by default
	string m_url;
	string m_auth1;
	string m_auth2;
	string m_consumerKey;
	string m_webAppConsumerKey;
	string m_secretKey;
	string m_bearerToken;
	string m_refreshToken;
	string m_logFileName;
	string m_UserId;
	string m_roleId;
	string m_userGUID;
	string m_serverUserName;
	string m_serverUserPassword;
	string m_tenant;
	string m_schemaWithQuotes;
	string m_schemaWithoutQuotes;
	string m_PlmVersion;
	string m_CloPlugin;
	string m_ConnectionStatus;
	string m_RedirectUrl;
	string m_errorLogFileName;
	int m_maxLogFileSize;
	string m_companyName;
	string m_companyApiKey;

public:


	string MATERIALS_TEMP_DIRECTORY;
	string PRODUCTS_TEMP_DIRECTORY;
	string TRIMS_TEMP_DIRECTORY;
	string COLORS_TEMP_DIRECTORY;

	static Configuration* GetInstance();
	static void	Destroy();

	void CachePLMsettingsFromFile();
	void GetRefreshToken();
	void ClearPLMsettingsCache();
	void CachePLMsettings(json selectedTenantDetails, string tenant);
	void CreateTemporaryFolderPath();
	bool ValidatePLMSettings();

	string GetPLMUrl();
	string GetAuth1();
	string GetAuth2();
	string GetConsumerKey();
	string GetWebAppConsumerKey();
	string GetSecretKey();
	string GetBearerToken();
	string GetRefreshTokenResponse();
	string GetLogFileName();
	string GetUserId();
	string GetRoleId();
	string GetUserGUID();
	string GetServerUserName();
	string GetServerUserPassword();
	string GetTenant();
	string GetschemaWithQuotes();
	string GetschemaWithoutQuotes();
	string GetPlmVersion();
	string GetCloPlugin();
	string GetConnectionStatus();
	string GetRedirectUrl();
	string GetErrorLogFileName();
	int GetMaxLogFileSize();
	string GetCompanyName();
	string GetCompanyApiKey();

	void SetBearerToken(string bearerToken);
	void SetPLMUrl(string str);
	void SetAuth1(string str);
	void SetAuth2(string str);
	void SetConsumerKey(string str);
	void SetWebAppConsumerKey(string str);
	void SetSecretKey(string str);
	void SetRefreshTokenResponse(string refreshToken);
	void SetLogFileName(string logFileName);
	void SetUserId(string UserId);
	void SetRoleId(string roleId);
	void SetUserGUID(string userGUID);
	void SetServerUserName(string UserId);
	void SetServerUserPassword(string UserId);
	void SetTenant(string tenant);
	void SetschemaWithQuotes(string schemaWithQuotes);
	void SetschemaWithoutQuotes(string schemaWithoutQuotes);
	void SetPlmVersion(string PlmVersion);
	void SetCloPlugin(string schemaWithoutQuotes);
	void SetConnectionStatus(string ConnectionStatus);
	void SetRedirectUrl(string retunrUrl);
	void SetErrorLogFileName(string errorLogFileName);
	void SetMaxLogFileSize(int maxLogFileSize);
	void SetCompanyName(string companyName);
	void SetCompanyApiKey(string companyApiKey);
};
