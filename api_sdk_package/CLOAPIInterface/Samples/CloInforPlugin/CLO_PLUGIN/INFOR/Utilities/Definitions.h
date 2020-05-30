#pragma once

#include <QString>
#include <QVariant>
#include <string>

using namespace std;
const int iconHieght = 18;
const int iconWidth = 18;
const QString inputStyle = "font: 75 8pt \"Tahoma\";";
const QString inputFont = "font: 75 8pt \"Tahoma\";";
const QString buttonFont = "font: 75 8pt \"Tahoma\";";

#define UPLOAD_FILE_SIZE 5242880 //5MB 
#define USER_INPUT_WIDTH 210
#define SEARCH_LABEL_WIDTH 195
#define FONT_SIZE 16
#define TABLE_WIDTH 425
#define TABLE_HEIGHT 500
#define TEXTEDIT_SIZE_WIDTH 190
#define TEXTEDIT_SIZE_HEIGHT 80
#define DLTYPECODE_STYLE_IMAGES 11
#define PAGE_SIZE 40
#define RESULT_TABLE_WIDTH 1250
#define RESULT_TABLE_HEIGHT 500
#define BUTTON_WIDTH_1 112
#define BUTTON_WIDTH_2 120
#define BUTTON_WIDTH_3 130
#define BUTTON_HEIGHT 30

const string DATE_TEXT = "date";
const string TEXT_FILE_EXTENSION = ".log";
const string BASIC = "Basic ";
const string AUTHORIZATION = "Authorization";
const string CLIENT_VERSION = "x-fplm-client-version";
const string INFOR_TENANT = "x-infor-tenant";
const string INFOR_USER = "x-infor-user";
const string INFOR_SCHEMA = "x-fplm-schema";
const string CONTENTTYPE = "content-Type";
const string CHARSET_UTF8 = "charset: utf-8";
const string FORM_ENCODED_TYPE = "application/x-www-form-urlencoded";
const string INFOR_TYPE = "application/json";
const string HTTP_POST = "HTTP Post";
const string RESPONSE_200 = "200";
const string isFileExists = "file_already_exists";
const string paletteFields = "Color Palette";
const string COLOR_PALETTE = "Color Palette";
const string UNAUTHORIZED = "Unauthorized";
const string INTERNAL_SERVER_ERROR = "500 Internal Server";
const string TIMEOUT_ERROR = "504 Gateway Timeout";
const string REQUEST_TIMEOUT = "Request Timeout";
const string TIMEOUT_ERROR_MESSAGE = "Request aborted after target server failed to respond within configured timeout";
const string NETWORK_ERROR_MESSAGE = "Please check your Network connection and try again";
const string LICENSE_ERROR_CODE_101 = "{\"result_code\": 101}";
const string LICENSE_ERROR_CODE_102 = "{\"result_code\": 102}";
const string LICENSE_ERROR_CODE_101_MSG = "Company name is missing. Please verify PLM settings or contact your system administrator.";
const string LICENSE_ERROR_CODE_102_MSG = "Company Api Key is missing. Please verify PLM settings or contact your system administrator.";
const string LICENSE_LOGOUT_MSG = "User logged out successfully.";
const string BASE64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/* PLM Settings functionality Constants Start. */
const string AUTH1_JSON_KEY = "auth1";
const string AUTH2_JSON_KEY = "auth2";
const string CONSUMERKEY_JSON_KEY = "consumerKey";
const string PLMSERVERURL_JSON_KEY = "plmServerUrl";
const string SECRETEKEY_JSON_KEY = "secrteKey";
const string SERVERPASSWORD_JSON_KEY = "serverPassword";
const string SERVERUSERNAME_JSON_KEY = "serverUserName";
const string WEBAPPCONSUMERKEY_JSON_KEY = "webAppConsumerKey";
const string CLOPLMPLUGINVERSION_JSON_KEY = "plmClientVersion";
const string CLOPLUGINVERSION_JSON_KEY = "cloViseVersion";
const string AVAILABLETENANTS_JSON_KEY = "availableTenants";
const string SELECTEDTENANT_JSON_KEY = "selectedTenant";
const string SERVER_CONNECTED_STATUS = "Connected";
const string SERVER_NOTCONNECTED_STATUS = "Not Connected";
const string PLMSETTINGS_FILE_NAME = "PLMSettings.json";
const string SELECT = "SELECT";
const string BLANK = "";
const string SCHEMA_RELOGIN_MSG = "Not Available";
const string SCHEMA_LOGIN_MSG = "Not Available";
const string RESTARTCLO_MSG = "Please logout from CLO-Vise for changes to take Effect!";
const string PLMSETTINGS_EXCEPTION_MSG = "Something went wrong! Please verify PLM Settings/File. If problem still persists, please contact your System Adminastrator.";
const string LICENSE_NOT_VALID_MSG = "You are not authorized to access CLO-Vise. Please contact your system administrator.";
const string LOGOUT_UNSUCCESSFUL_MSG = "You don't have active session.";
const string USER_ALREADY_ACTIVE = "License limit exceeded. Please log out of the CLO-Vise on other devices. If license is currently not active on other devices, please try again in ten minutes. If you continue to have issues or cannot log out of other devices, please contact The CLO Support Team.";
const string SUPPORTED_TRIM_FILE_FORMATS = "trm,btn,obj,zpac,sst,zsd,zip,bth,zpl";
const string REDIRECT_URL = "redirectUrl";
const string COMPANY_NAME = "companyName";
const string COMPANY_API_KEY = "companyApiKey";
const string INVALID_USER = "Incorrect user ID or password";
const string TENANT_QAC_COOKIE = "tenant_cookie_qac=";
const string TENANT_COOKIE = "tenant_cookie=";
const int SAML_QAC_REQUEST_NUM = 444;
const int SAML_MINGLE_REQUEST_NUM = 452;
const string INVALID_FILENAME_CHARS = "\\/:?\"<>|";
/* PLM Settings functionality Constants End. */