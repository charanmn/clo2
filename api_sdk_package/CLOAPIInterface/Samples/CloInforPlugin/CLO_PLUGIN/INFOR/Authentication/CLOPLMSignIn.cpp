#pragma once
#include "CLOPLMSignIn.h"
#include <QDebug>
#include "CLOAPIInterface.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"
#include "CLO_PLUGIN/INFOR/Utilities/Definitions.h"
#include "CLO_PLUGIN/INFOR/Utilities/Configuration.h"
#include <Qt/qtextstream.h>
#include <Qt/qfileinfo.h>
#include <Qt/qimagereader.h>
#include <Qt/qhttpmultipart.h>
#include <errno.h>
#include <sys/types.h>
/*
*OnAccept() method is doing the  authontication of the user.
*readJsonFile() method is provideing the url to login the user.
*/
namespace CLOPlugin {
	/**
	 * \brief constructor to singleton instance
	 */ 
	PLMSignin* PLMSignin::_instance = NULL;
	PLMSignin* PLMSignin::GetInstance()
	{
		if (_instance == NULL) {
			_instance = new PLMSignin();
		}
		return _instance;
	}
	/**
	 * \brief destructor to destroy singleton instance
	 */
	void PLMSignin::Destroy()
	{
		if (_instance) {
			delete _instance;
			_instance = NULL;
		}
	}
	/**
	 * \brief constructor to Set SignInPLM
	 */
	void PLMSignin::SetSignInPLM(bool b)
	{
		m_isSignInPLMEnabled = b;
	}
	/**
	 * \brief constructor to Get SignInPLM
	 */
	bool PLMSignin::GetSignInPLM()
	{
		return m_isSignInPLMEnabled;
	}
	CLOPLMSignIn* CLOPLMSignIn::_instance = NULL;
	CLOPLMSignIn* CLOPLMSignIn::GetInstance()
	{
		if (_instance == NULL) {
			_instance = new CLOPLMSignIn();
		}
		return _instance;
	}
	/**
	 * \brief destructor to destroy CLOPLMSignIn
	 */
	void CLOPLMSignIn::Destroy()
	{
		if (_instance) {
			delete _instance;
			_instance = NULL;
		}
	}
	CLOPLMSignIn::CLOPLMSignIn(QWidget* parent, Qt::WindowFlags flags)
		: QDialog(parent, flags)
	{
		Utility::Logger("CLOPLMSignIn::CLOPLMSignIn() Started...");
		setupUi(this);
		
		PLMInputPwd->setEchoMode(QLineEdit::Password);
		loginButton->setIcon(QIcon(":/CLO_PLUGIN/INFOR/images/icon_ok_over.svg"));
		loginButton->setIconSize(QSize(iconHieght, iconWidth));
				
		QObject::connect(closeWindow, SIGNAL(clicked()), this, SLOT(cancel_Clicked()));
		QObject::connect(loginButton, SIGNAL(clicked()), this, SLOT(ValidateLoginCredentials()));
		Utility::Logger("CLOPLMSignIn::CLOPLMSignIn() Ended...");
	}
	CLOPLMSignIn::~CLOPLMSignIn()
	{

	}
	/**
	 * \brief  Setting DefaultUserName 
	 */
	void CLOPLMSignIn::SetDefaultID(QString userId)
	{
		PLMInputId->setText(m_plmLoginId);
	}
	/**
	 * \brief Setting DefaultPassword 
	 */
	void CLOPLMSignIn::SetDefaultPassword(QString password)
	{
		PLMInputPwd->setText(m_plmLoginPassword);
	}
	/**
	 * \brief  Get CLOPLMSignIn ID
	 */
	const QString& CLOPLMSignIn::GetUserID()
	{
		return m_plmLoginId;
	}
	 /**
	  * \brief  Get Password
	  */
	const QString& CLOPLMSignIn::GetPassword()
	{
		return m_plmLoginPassword;
	}
	
	static std::string GetToken() 
	{
		Utility::Logger("CLOPLMSignIn::GetToken() Started...");
		string id = Configuration::GetInstance()->GetConsumerKey();
		string pw = Configuration::GetInstance()->GetSecretKey();
		string basicAuthorizationString = BASIC + Utility::ConvertToBase64(id + ":" + pw); ////Converting Id and Password to Base64 @To-Do
		vector<pair<string, string>> headerNameAndValueList;
		headerNameAndValueList.push_back(make_pair(AUTHORIZATION, basicAuthorizationString));
		headerNameAndValueList.push_back(make_pair("Content-Type", "application/x-www-form-urlencoded"));
		string parameter = "grant_type=password";
		parameter += "&username=" + Configuration::GetInstance()->GetServerUserName();
		parameter += "&password=" + Configuration::GetInstance()->GetServerUserPassword();
		string response = REST_API->CallRESTPost(Configuration::GetInstance()->GetAuth2() + GET_TOKEN, &parameter, headerNameAndValueList, HTTP_POST);
		Utility::Logger("authorization response::" + response);
		//If Response conaitans string "invalid_grant" or "invalid_client", assumed some thing wrong with entered PLM Settings
		if (response.find("invalid_grant") == string::npos && response.find("invalid_client") == string::npos)
		{
			int indexforFlowerBrace = response.find("{");
			string jsonString = response.substr(indexforFlowerBrace);
			json bearerTokenJson;
			try {
				bearerTokenJson = json::parse(jsonString);
			}
			catch (exception & e)
			{
				Utility::ErrorLogger("CLOPLMSignIn::GetToken()::parsing bearerTokenJson exception - " + string(e.what()));
				throw e.what();
			}
			string finalBearerToken = bearerTokenJson["access_token"].dump();
			finalBearerToken = finalBearerToken.erase(0, 1);
			finalBearerToken = finalBearerToken.erase(finalBearerToken.size() - 1);
			string refreshToken= bearerTokenJson["refresh_token"].dump();
			refreshToken = refreshToken.erase(0, 1);
			refreshToken = refreshToken.erase(refreshToken.size() - 1);
			Configuration::GetInstance()->SetRefreshTokenResponse(refreshToken);
			Utility::Logger("refresh token::" + refreshToken);
			return finalBearerToken;
			
			
		}
		else {
			Configuration::GetInstance()->SetRefreshTokenResponse("");
			return "";
		}
		Utility::Logger("CLOPLMSignIn::GetToken() Ended...");
	}	
	/**
	 * \brief Method checks for Validate Login Credentials
	 * \param response 
	 */
	void CLOPLMSignIn::ValidateLoginCredentials()
	{	   
		Utility::Logger("CLOPLMSignIn::ValidateLoginCredentials() Started...");
		hide();
		m_plmLoginId = PLMInputId->text();
		m_plmLoginPassword = PLMInputPwd->text();
		m_UserID = m_plmLoginId.toStdString();
		string userName = m_plmLoginId.toStdString();
		string password = m_plmLoginPassword.toStdString();
		if (Configuration::GetInstance()->GetPLMUrl().find(Configuration::GetInstance()->GetTenant()) == string::npos)
		{
			UTILITY_API->DisplayMessageBox("Unable to login. Please verify PLM settings!");
			show();
		}
		else if ((userName.empty()) || (password.empty()))
		{
			UTILITY_API->DisplayMessageBox("Unable to login. Please verify login credentials!");
			show();
			return;
		}
		else 
		{ 
			if (!REST_API) 
			{
				show();
				return;
			}
			
			bool loggedIn = false;
			//json resJson = Utility::ValidateUserLicense(LICENSE_LOGIN_API, m_UserID);
			int resultCode = 1;// resJson["result_code"].get<int>();
			if (resultCode == 0) {
				UTILITY_API->DisplayMessageBox(LICENSE_NOT_VALID_MSG);
				Utility::Logger(LICENSE_NOT_VALID_MSG);
			}
			else if (resultCode == 1) {
				loggedIn = true;
			}
			else if (resultCode == 2) {
				UTILITY_API->DisplayMessageBox(USER_ALREADY_ACTIVE);
				Utility::Logger(USER_ALREADY_ACTIVE);
			}
			else if (resultCode == 101) {
				UTILITY_API->DisplayMessageBox(LICENSE_ERROR_CODE_101_MSG);
				Utility::Logger(LICENSE_ERROR_CODE_101_MSG);
			}
			else if (resultCode == 102) {
				UTILITY_API->DisplayMessageBox(LICENSE_ERROR_CODE_102_MSG);
				Utility::Logger(LICENSE_ERROR_CODE_102_MSG);
			}

			if (!loggedIn) {
				return;
			}

			vector<pair<string, string>> headerNameAndValueList;
			headerNameAndValueList.push_back(make_pair("Content-Type", "text/html"));
			string tenant = Configuration::GetInstance()->GetTenant();
			headerNameAndValueList.push_back(make_pair(INFOR_TENANT, tenant));
			string response = REST_API->CallRESTGet(Configuration::GetInstance()->GetAuth2() + VALIDATE_CREDENTIALS + Configuration::GetInstance()->GetWebAppConsumerKey() + "&response_type=code&redirect_uri="+Configuration::GetInstance()->GetRedirectUrl()+"&response_mode=query", headerNameAndValueList, "HTTP Get");
			Utility::Logger("authorization response::" + response);
			//If Response conaitans string "Something is not right", assumed some thing wrong with entered PLM Settings
			bool isAuthenticated = false;
			int samlRequestChars = SAML_QAC_REQUEST_NUM;
			string cookieType = TENANT_QAC_COOKIE;
			if (response.find("Choose Authentication") != string::npos) {
				isAuthenticated = ValidateOrgUser(response, userName, password);
				if (!isAuthenticated) {
					samlRequestChars = SAML_MINGLE_REQUEST_NUM;
					cookieType = TENANT_COOKIE;
					string auth1Str = Configuration::GetInstance()->GetAuth1().substr(8, Configuration::GetInstance()->GetAuth1().length() - 1);
					string subStringRes = response.substr(response.find(AUTHORIZATION_PING_URL) - 9, AUTHORIZATION_PING_URL.length() + 9);

					string auth1String = Configuration::GetInstance()->GetAuth1();
					auth1String.replace(4, 1, "");

					string chooseAuthUrl = Configuration::GetInstance()->GetAuth2().substr(0,
						Configuration::GetInstance()->GetAuth2().find_last_of(":")) + "/sp/startSSO.ping?";
					chooseAuthUrl += "PartnerIdpId=" + auth1String;
					chooseAuthUrl += "&TargetResource" + Configuration::GetInstance()->GetAuth2().substr(0,
						Configuration::GetInstance()->GetAuth2().find(Configuration::GetInstance()->GetTenant())) + subStringRes;

					vector<pair<string, string>> authChooserHeader;
					authChooserHeader.push_back(make_pair(INFOR_TENANT, Configuration::GetInstance()->GetTenant()));

					response = REST_API->CallRESTGet(chooseAuthUrl, authChooserHeader, "Http Get");
					Utility::Logger("response----------" + response);
				}
				
			}

			if (!isAuthenticated) {
				if (response.find("Something is not right") != string::npos)
				{
					UTILITY_API->DisplayMessageBox("Unable to login. Please verify PLM settings!");
					Utility::Logger("Unable to Login. Please Verify PLM Settings!");
				}
				else
				{
					string samlRequest = response.substr(response.find("SAMLRequest") + 20, samlRequestChars);
					string relayState = response.substr(response.find("RelayState") + 19, 30);
					vector<pair<string, string>> samlRequestHeader;
					string tenant = Configuration::GetInstance()->GetTenant();
					samlRequestHeader.push_back(make_pair(INFOR_TENANT, tenant));
					samlRequestHeader.push_back(make_pair("Content-Type", "application/x-www-form-urlencoded"));
					string samlRequestParam = "SAMLRequest=" + QUrl::toPercentEncoding(QString::fromStdString(samlRequest));
					samlRequestParam += "&RelayState=" + relayState;
					unsigned char* postField = new unsigned char[samlRequestParam.length() + 1];
					std::strcpy((char*)postField, samlRequestParam.c_str());
					unsigned int size = (unsigned int)(samlRequestParam.length()) + 1;
					string samlBeforeResponse = REST_API->CallRESTPost2(Configuration::GetInstance()->GetAuth1() + SAML2, postField, size, samlRequestHeader, HTTP_POST);
					//UTILITY_API->DisplayMessageBox("samlBeforeResponse -> ValidateLoginCredentials():: " + samlBeforeResponse);
					//If Response conaitans string "", assumed some thing wrong with entered PLM Settings or
					//If Response conaitans string "Unexpected System Error", assumed some thing wrong with entered PLM Settings
					//UTILITY_API->DisplayMessageBox("samlBeforeResponse.size() -> ValidateLoginCredentials():: " + samlBeforeResponse.length());
					Utility::Logger("server response::" + samlBeforeResponse);
					if (samlBeforeResponse.find("200 OK") == string::npos)
					{
						UTILITY_API->DisplayMessageBox("Unable to login. Please verify PLM settings!");
						Utility::ErrorLogger("CLOPLMSignIn::ValidateLoginCredentials() Unable to Login.Please Verify PLM Settings!");
					}
					else
					{
						if (response.find("Unexpected System Error") != string::npos)
						{
							UTILITY_API->DisplayMessageBox("Unable to login. Please verify PLM settings!");
							Utility::ErrorLogger("CLOPLMSignIn::ValidateLoginCredentials() Unexpected System Error Unable to Login.Please Verify PLM Settings!");
						}
						else
						{
							string actionKeywordSearch = "resumeSAML20";
							string cookie = "Set-Cookie: PF";
							size_t actionKeyworkIndex = samlBeforeResponse.find(actionKeywordSearch);
							size_t cookieIndex = samlBeforeResponse.find(cookie);
							string urlSubString = samlBeforeResponse.substr(actionKeyworkIndex - 11, 36);
							string cookieStr = samlBeforeResponse.substr(cookieIndex + 12, 47);
							string tenant = Configuration::GetInstance()->GetTenant();
							string cookieHeader = cookieType + tenant + "; " + cookieStr;
							vector<pair<string, string>> authCodeHeader;
							authCodeHeader.push_back(make_pair(INFOR_TENANT, tenant));
							authCodeHeader.push_back(make_pair("Content-Type", "application/x-www-form-urlencoded"));
							authCodeHeader.push_back(make_pair("Cookie", cookieHeader));
							string loginRequestParam = "pf.username=" + userName;
							loginRequestParam += "&pf.pass=" + password;
							const std::string finalUrl = Configuration::GetInstance()->GetAuth1() + urlSubString;

							string loginResponse = REST_API->CallRESTPost(finalUrl, &loginRequestParam, authCodeHeader, HTTP_POST);
							Utility::Logger("use login response::" + loginResponse);
							if (loginResponse.find("200 OK") != string::npos &&
								loginResponse.find("We did not recognize the user name or password that you entered") == string::npos)
							{
								string bearerString = GetToken();
								if (!bearerString.empty())
								{
									string requestToken = "Bearer " + bearerString;
									Configuration::GetInstance()->SetBearerToken(requestToken);
									Utility::Logger("user name::" + userName);
									Utility::Logger("password::" + password);
									Utility::Logger("authorization token::" + requestToken);
									Configuration::GetInstance()->SetConnectionStatus("Connected");
									m_isAuthenticated = true;
									accept();
								}
								else
								{
									UTILITY_API->DisplayMessageBox("Unable to login. Please verify PLM settings!");
									Utility::ErrorLogger("CLOPLMSignIn::ValidateLoginCredentials() Unable to Login.Please Verify PLM Settings!");
								}
							}
							else
							{
								UTILITY_API->DisplayMessageBox("Unable to login. Please verify login credentials!");
								Utility::ErrorLogger("CLOPLMSignIn::ValidateLoginCredentials() Unable to Login. Please Verify Login Credentials!");
							}
						}
					}
				}
			}
		}	
		Utility::Logger("CLOPLMSignIn::ValidateLoginCredentials() Ended...");
	}

	bool CLOPLMSignIn::ValidateOrgUser(string& response, string& username, string& password) {

		bool isauthenticated = false;
		size_t authPingIndex = response.find(AUTHORIZATION_PING_URL) - 6;
		string urlKey = response.substr(authPingIndex, 5);
		string tenant = Configuration::GetInstance()->GetTenant();

		string internalUserLoginParams = "id=" + QUrl::toPercentEncoding(QString::fromStdString(MS_LOGIN_URL));
		internalUserLoginParams += "&identityProviderType=OnPremise";
		internalUserLoginParams += "&resume=" + QUrl::toPercentEncoding(QString::fromStdString("/as/" + urlKey + "/"+ AUTHORIZATION_PING_URL));
		internalUserLoginParams += "&displayValue=" + QUrl::toPercentEncoding(QString::fromStdString("LCWaikiki User"));
		internalUserLoginParams += "&rememberMe=false";
		internalUserLoginParams += "&tenantInfo=" + tenant;
		internalUserLoginParams += "&sl=0";

		vector<pair<string, string>> internalUserLoginHeader;
		internalUserLoginHeader.push_back(make_pair(INFOR_TENANT, tenant));
		internalUserLoginHeader.push_back(make_pair(CONTENTTYPE, FORM_ENCODED_TYPE));
		internalUserLoginHeader.push_back(make_pair("Cookie", "tenant_cookie="+ tenant));

		unsigned char* internalUserLoginField = new unsigned char[internalUserLoginParams.length() + 1];
		std::strcpy((char*)internalUserLoginField, internalUserLoginParams.c_str());
		unsigned int sizee = (unsigned int)(internalUserLoginParams.length()) + 1;
		string internalUserLoginResponse = REST_API->CallRESTPost2("https://mingle-bridge.eu1.inforcloudsuite.com/RedirectToIdp", internalUserLoginField, sizee, internalUserLoginHeader, HTTP_POST);

		//Utility::Logger("internalUserLoginResponse----------" + internalUserLoginResponse);

		size_t actionIndex = internalUserLoginResponse.find(" action=") + 9;
		size_t actionUrlIndex = internalUserLoginResponse.find("idp/samlSSO") + 11;
		string actionUrl = internalUserLoginResponse.substr(actionIndex, actionUrlIndex - actionIndex);

		string samlRequest = internalUserLoginResponse.substr(internalUserLoginResponse.find("SAMLRequest") + 20, 636);
		string relayState = internalUserLoginResponse.substr(internalUserLoginResponse.find("RelayState") + 19, 30);
		vector<pair<string, string>> samlRequestHeader;
		
		samlRequestHeader.push_back(make_pair(INFOR_TENANT, tenant));
		samlRequestHeader.push_back(make_pair(CONTENTTYPE, FORM_ENCODED_TYPE));
		string samlRequestParam = "SAMLRequest=" + QUrl::toPercentEncoding(QString::fromStdString(samlRequest));
		samlRequestParam += "&RelayState=" + relayState;
		unsigned char* postField = new unsigned char[samlRequestParam.length() + 1];
		std::strcpy((char*)postField, samlRequestParam.c_str());
		unsigned int size = (unsigned int)(samlRequestParam.length()) + 1;
		string samlBeforeResponse = REST_API->CallRESTPost2(actionUrl, postField, size, samlRequestHeader, HTTP_POST);
		//Utility::Logger("samlBeforeResponse ::" + samlBeforeResponse);

		samlRequest = samlBeforeResponse.substr(samlBeforeResponse.find("SAMLRequest") + 39, 1024);
		relayState = samlBeforeResponse.substr(samlBeforeResponse.find("RelayState") + 37, 48);

		string samlRequestParam2 = "SAMLRequest=" + QUrl::toPercentEncoding(QString::fromStdString(samlRequest));
		samlRequestParam2 += "&RelayState=" + relayState;
		unsigned char* postField2 = new unsigned char[samlRequestParam2.length() + 1];
		std::strcpy((char*)postField2, samlRequestParam2.c_str());
		unsigned int size2 = (unsigned int)(samlRequestParam2.length()) + 1;
		string samlAfterResponse = REST_API->CallRESTPost2(MS_FORM_LOGIN_URL, postField2, size2, samlRequestHeader, HTTP_POST);
	
		//Utility::Logger("samlAfterResponse ::" + samlAfterResponse);

		string stsCookie = samlAfterResponse.substr(samlAfterResponse.find("Set-Cookie: MSISSamlRequest") + 28, 1664);
		string loginUrl = samlAfterResponse.substr(samlAfterResponse.find("client-request-id"), 54);

		vector<pair<string, string>> authCodeHeader;
		authCodeHeader.push_back(make_pair(INFOR_TENANT, tenant));
		authCodeHeader.push_back(make_pair(CONTENTTYPE, FORM_ENCODED_TYPE));
		authCodeHeader.push_back(make_pair("Cookie", "MSISSamlRequest=" + stsCookie));
		string loginRequestParam = "UserName=" + username;
		loginRequestParam += "&Password=" + password;

		string loginResponse = REST_API->CallRESTPost(MS_FORM_LOGIN_URL+"?"+loginUrl, &loginRequestParam, authCodeHeader, HTTP_POST);

		Utility::Logger("Org user loginResponse ::" + loginResponse);
		if (loginResponse.find("200 OK") != string::npos && loginResponse.find(INVALID_USER) == string::npos)
		{
			string bearerString = GetToken(); 
			if (!bearerString.empty())
			{
				string requestToken = "Bearer " + bearerString;
				Configuration::GetInstance()->SetBearerToken(requestToken);
				Configuration::GetInstance()->SetConnectionStatus("Connected");
				m_isAuthenticated = true;
				isauthenticated = true;
				accept();
			}
		}

		return isauthenticated;
	}

	/**
	 * \brief Method checks for Login cancel 
	 * \param response 
	 */
	void CLOPLMSignIn::cancel_Clicked() 
	{
		PLMInputId->clear();
		PLMInputPwd->clear();;
		this->close();
	}
}
	