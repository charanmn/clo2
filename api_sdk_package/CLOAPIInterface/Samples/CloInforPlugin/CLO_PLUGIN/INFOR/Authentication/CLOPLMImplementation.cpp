#include "CLOPLMImplementation.h"
#include "CLOAPIInterface/CLOAPIInterface.h"
#include "LibraryWindowImplPlugin.h"
#include "CLOPLMSignIn.h"
#include "CLO_PLUGIN/INFOR/DesignSuite/DesignSuite.h"
#include "CLO_PLUGIN/INFOR/Utilities/Configuration.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
#include "CLO_PLUGIN/INFOR/Utilities/RestAPIUtility.h"

/**
 * \ Setting Search mode for PLM 
 */
namespace CLOPlugin
{
	CLOPLMImplementation::CLOPLMImplementation(QWidget* parent, Qt::WindowFlags flags, SEARCH_ITEM_MODE searchMode) : QDialog(parent, flags)
	{
		m_searchMode = searchMode;

	}
	CLOPLMImplementation::~CLOPLMImplementation()
	{

	} 
	/**
	 * \brief Method to Set Search Mode
	 * \param response 
	 */
	void CLOPLMImplementation::SetSearchMode(SEARCH_ITEM_MODE searchMode)
	{
		Utility::Logger("CLOPLMImplementation::SetSearchMode() Started...");
	    const string plmUserId, plmPassword;
		string token;
		m_searchMode = searchMode;
		if (m_searchMode == PLM_SEARCH)
		{
			bool isAccepted = SigninPLM();
			if (isAccepted)
			{
				SetUserIDConfiguration();
				DesignSuite::GetInstance()->setModal(true);
				DesignSuite::GetInstance()->exec();
			}
		}
		Utility::Logger("CLOPLMImplementation::SetSearchMode() Ended...");
	}
	/*Brief: This method gets the user ID correspondng to the User who logged into the CLO.
	Input Params: void
	return: Returns a string
	*/
	void CLOPLMImplementation::SetUserIDConfiguration()
	{
		Utility::Logger("CLOPLMImplementation::SetUserIDConfiguration() Started...");
		string userID;
		string userIdstr, roleIdstr, userGUID, activeSchema;
		userID = CLOPLMSignIn::GetInstance()->m_UserID;
		Utility::Logger("connected user ID::" + userID);
		json paramJson = json::object();
		//paramJson["Schema"] = Configuration::GetInstance()->GetschemaWithoutQuotes();
		Utility::Logger("connected schema::" +to_string(paramJson));
		string response = RestCall(to_string(paramJson), GET_USER_INFO_API + userID);

		Utility::Logger("CLOPLMImplementation::SetUserIDConfiguration() response - " + response);
		string errorResponse = Utility::CheckErrorDescription(response);
		string completeDependencies;
		json userIdJson; 
		if (errorResponse.empty() && (errorResponse.length() == 0))
		{
			try
			{
				userIdJson = json::parse(response);
				userIdstr = userIdJson["userId"].dump();
				Configuration::GetInstance()->SetUserId(userIdstr);
				Utility::CustomMessageBox("connected user ID::" + userIdstr);
				roleIdstr = userIdJson["activeRoleId"].dump();
				Utility::Logger("connected roleId::" + roleIdstr);
				Configuration::GetInstance()->SetRoleId(roleIdstr);
				userGUID = userIdJson["userGuid"].dump();
				userGUID = userGUID.erase(0, 1);
				userGUID = userGUID.erase(userGUID.size() - 1);
				Configuration::GetInstance()->SetUserGUID(userGUID);
				Utility::Logger("connected userGUID::" + userGUID);
				activeSchema = Utility::GetJSONValue<string>(userIdJson, "activeSchema", false);
				Configuration::GetInstance()->SetschemaWithQuotes(activeSchema);
				activeSchema = Utility::GetJSONValue<string>(userIdJson, "activeSchema", true);
				Configuration::GetInstance()->SetschemaWithoutQuotes(activeSchema);
			}
			catch (exception& e)
			{
				Utility::ErrorLogger("CLOPLMImplementation::SetUserIDConfiguration() exception - " + string(e.what()));
				throw e.what();
			}
		}
		else
		{
			UTILITY_API->DisplayMessageBox(errorResponse);
			Utility::Logger("CLOPLMImplementation::SetUserIDConfiguration() errorResponse - " + errorResponse);
		}
		Utility::Logger("CLOPLMImplementation::SetUserIDConfiguration() Ended...");
	}
	/**
	 * \brief Sign in to PLM
	 * \param response 
	 */
	bool CLOPLMImplementation::SigninPLM()
	{
		Utility::Logger("CLOPLMImplementation::SigninPLM()) Started...");

		if (PLMSignin::GetInstance()->GetSignInPLM())
			return true;
		CLOPLMSignIn::GetInstance()->exec(); // make this a single ton and get instance
		if (CLOPLMSignIn::GetInstance()->result() == QDialog::Accepted)
		{
			QString getId = CLOPLMSignIn::GetInstance()->GetUserID();
			QString getPassword = CLOPLMSignIn::GetInstance()->GetPassword();
			PLMSignin::GetInstance()->SetSignInPLM(true);
		}
		else
		{
			PLMSignin::GetInstance()->SetSignInPLM(false);
		}
		Utility::Logger("CLOPLMImplementation::SigninPLM()) Ended...");
		return PLMSignin::GetInstance()->GetSignInPLM();
	}
	bool CLOPLMImplementation::SigninPLM(const string userId, const string password, string bearerToken)
	{
		return false;
	}
}