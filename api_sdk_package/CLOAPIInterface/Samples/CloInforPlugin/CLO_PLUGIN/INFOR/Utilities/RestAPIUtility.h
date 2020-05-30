#pragma once

#include <string>
#include <QString>
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
#include "CLO_PLUGIN/INFOR/Utilities/Definitions.h"
#include "CLO_PLUGIN/INFOR/Libraries/curl/include/curl/curl.h"
#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "ws2_32.lib")

using namespace std;

using json = nlohmann::json;

const string COLOR_SEARCH_API = "/view/api/view/layout/data/get";
const string COLOR_PALETTE_SEARCH_API = "/view/api/view/layout/data/get";
const string COLOR_DETAILS_API = "/view/api/view/layout/data/get";
const string GET_USER_INFO_API = "/security/api/security/user/getinfo/";
const string GET_ATTACHMENT_INFO_API = "/view/api/view/layout/data/get";
const string FABRIC_SEARCH_API = "/view/api/view/layout/data/get";
const string FABRIC_GET_DEPENDENCIES_API = "/view/api/view/layout/data/get";
const string FABRIC_DETAILS_API = "/view/api/view/layout/data/get";
const string TRIMS_DEPENDENCY_API = "/view/api/view/layout/data/get";
const string TRIMS_SEARCH_API = "/view/api/view/layout/data/get";

const string PRODUCT_DEPENDENCIES_API = "/view/api/view/layout/data/get";
const string PRODUCT_DETAILS_API = "/view/api/view/layout/data/get";
const string PRODUCT_CREATE_API = "/pdm/api/pdm/style/save";
const string PRODUCT_SEARCH_API = "/view/api/view/layout/data/get";
const string PRODUCT_ATTCHMENT_API = "/view/api/view/layout/data/get";
const string PRODUCT_UPDATE_API = "/pdm/api/pdm/style/save";
const string PRODUCT_UNLINK_ATTACHMENT_API = "/documents/api/document/DeleteObjectsMetadata";
const string PRODUCT_DELETE_ATTACHMENT_API = "/documents/api/document/doclib/delete";
const string PRODUCT_GET_ATTCHMENT_API = "/view/api/view/layout/data/get";
const string PRODUCT_GET_STYLECODE_GENERATOR_SETTINGS = "/library/api/library/tools/idgenerator/get";

const string UPLOAD_FILE = "/documents/api/document/UploadFile";
const string LINK_ATTACHMENT = "/documents/api/document/SaveMetadata";
const string GET_TOKEN = "/token.oauth2";
const string VALIDATE_CREDENTIALS = "/authorization.oauth2?client_id=";
const string GET_REFRESH_TOKEN = "/token.oauth2";
const string SAML2 = "/idp/SSO.saml2";
const string KEY_VALUE_PAIR = "/view/api/view/locale/keyvalpair";
const string AUTHORIZATION_PING_URL = "resume/as/authorization.ping";
const string MS_FORM_LOGIN_URL = "https://sso.lcwaikiki.com/adfs/ls/";
const string MS_LOGIN_URL = "http://sso.lcwaikiki.com/adfs/services/trust";
const string MINGLE_LOGIN_FORM_URL = "https://mingle-bridge.eu1.inforcloudsuite.com/RedirectToIdp";
const string LICENSE_LOGIN_API = "http://_clovise.clo3d.com/plugin/govise/login";
const string LICENSE_LOGOUT_API = "http://_clovise.clo3d.com/plugin/govise/logout";

inline string LegacyRestCall(string parameter, string api, string contentType)
{
	vector<pair<string, string>> headerNameAndValueList;
	headerNameAndValueList.push_back(make_pair(CONTENTTYPE, contentType));
	headerNameAndValueList.push_back(make_pair(AUTHORIZATION, Configuration::GetInstance()->GetBearerToken()));
	headerNameAndValueList.push_back(make_pair(CLIENT_VERSION, Configuration::GetInstance()->GetPlmVersion()));
	headerNameAndValueList.push_back(make_pair(INFOR_TENANT, Configuration::GetInstance()->GetTenant()));
	headerNameAndValueList.push_back(make_pair(INFOR_USER, Configuration::GetInstance()->GetUserGUID()));
	string response = REST_API->CallRESTPost(Configuration::GetInstance()->GetPLMUrl() + api, &parameter, headerNameAndValueList, HTTP_POST);
	return response;
}

/**
* Method is used to write result data
*/
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* userp) {
	userp->append((char*)contents, size * nmemb);
	return size * nmemb;
}

/**
* Method is used to monitor rest call progress
*/
static int progress_callback(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow) {

	if (((double)dltotal) == 0 && ((double)ulnow) != ((double)ultotal)) {
		UTILITY_API->SetProgress("Uploading. Please wait...", (((double)ulnow) / ((double)ultotal) * 100));
	}
	else {
		UTILITY_API->SetProgress("Loading data...", (((double)dlnow) / ((double)dltotal) * 100));
	}

	return 0;
}

/**
* Rest call method
*/
static string RestCall(string parameter, string api, string contentType)
{
	UTILITY_API->CreateProgressBar();
	CURL* RESTAPI;
	CURLcode res_code;
	string* data;
	string config;
	string response;
	curl_version_info_data* vinfo = curl_version_info(CURLVERSION_NOW);
	if (vinfo->features & CURL_VERSION_SSL) {
		printf("CURL: SSL enabled" + '\n');
	}
	else {
		printf("CURL: SSL not enabled\n");
	}

	RESTAPI = curl_easy_init();

	if (RESTAPI)
	{
		
		string acceptHeader = "Accept: " + INFOR_TYPE;
		string authorization = AUTHORIZATION + ": " + Configuration::GetInstance()->GetBearerToken();
		string clinetVersion = CLIENT_VERSION + ": " + Configuration::GetInstance()->GetPlmVersion();
		string tenant = INFOR_TENANT + ": " + Configuration::GetInstance()->GetTenant();
		string userId = INFOR_USER + ": " + Configuration::GetInstance()->GetUserGUID();
		string url = Configuration::GetInstance()->GetPLMUrl() + api;

		struct curl_slist* headers = NULL;
		if (contentType == "application/json") {
			string contentTypee = CONTENTTYPE + ": " + INFOR_TYPE + "; " + CHARSET_UTF8;
			headers = curl_slist_append(headers, contentTypee.c_str());
		}
		else if(!contentType.empty()) {
			string contentTypee = CONTENTTYPE + ": " + contentType;
			headers = curl_slist_append(headers, contentTypee.c_str());
		}
		headers = curl_slist_append(headers, acceptHeader.c_str());
		headers = curl_slist_append(headers, authorization.c_str());
		headers = curl_slist_append(headers, clinetVersion.c_str());
		headers = curl_slist_append(headers, tenant.c_str());
		headers = curl_slist_append(headers, userId.c_str());
		
		curl_easy_setopt(RESTAPI, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(RESTAPI, CURLOPT_URL, url.c_str());
		curl_easy_setopt(RESTAPI, CURLOPT_CAINFO, "./ca-bundle.crt");
		curl_easy_setopt(RESTAPI, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(RESTAPI, CURLOPT_SSL_VERIFYHOST, false);
		curl_easy_setopt(RESTAPI, CURLOPT_POSTFIELDS, parameter.c_str());
		curl_easy_setopt(RESTAPI, CURLOPT_POSTFIELDSIZE, parameter.size());
		curl_easy_setopt(RESTAPI, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(RESTAPI, CURLOPT_TIMEOUT, 600L);

		curl_easy_setopt(RESTAPI, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(RESTAPI, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(RESTAPI, CURLOPT_NOPROGRESS, 0);
		curl_easy_setopt(RESTAPI, CURLOPT_XFERINFOFUNCTION, progress_callback);

		res_code = curl_easy_perform(RESTAPI);
		
		if (res_code != CURLE_OK) {
			stringstream errorMsg;
			errorMsg << "Curl response msg CURLOPT_WRITEDATA: " << curl_easy_strerror(res_code) << " respose :" << response;
			response = errorMsg.str();
		}
	}
	// Clean up the resources
	curl_easy_cleanup(RESTAPI);
	UTILITY_API->DeleteProgressBar(false);

	return response;
}

/**
* Method is used call REST API
*/
inline string RestCall(string parameter, string api)
{
	return RestCall(parameter, api, INFOR_TYPE);
}
