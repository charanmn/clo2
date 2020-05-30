#include "PLMSettingsSample.h"
#include "PLMSettingDataSample.h"
#include "CLO_PLUGIN/INFOR/Utilities/Definitions.h"
#include <QDebug>
#include <QFileDialog>
#include "CLO_PLUGIN/INFOR/Utilities/Configuration.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"
#include <fstream>
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
#include "CLO_PLUGIN/INFOR/Utilities/DirectoryUtil.h"

using json = nlohmann::json;

namespace CLOAPISample
{
	PLMSettingsSample::PLMSettingsSample(QWidget* parent)
		: QWidget(parent)
	{
		setupUi(this);
		//Generates PLM Settings UI, reading PLM Settings JSON File.
		GeneratePLMSettingsUIFromFile();
		//This is a slot, which triggers on change of PLM Environment value.
		QObject::connect(comboBox_PLMTenant, SIGNAL(currentIndexChanged(const QString&)), this,
			SLOT(CurrentTenantChanged(const QString&)));
	}

	PLMSettingsSample::~PLMSettingsSample()
	{
		//DESTROY_PLM_SETTING_DATA_SAMPLE 
		// do not use this here. please release plm setting data when unloading the library windows sample plug-in dll.
		//Update PLM Settings JSON File, on change of PLM Environment value.
		UpdatePLMSettingsFileWithSelectedTenant();
	}

	void PLMSettingsSample::Reset()
	{
		// re-create the PLM settings data instance
		DESTROY_PLM_SETTING_DATA_SAMPLE;
	}
	/**
	*\reading the PLMSettings.json display inPLMSettingsUI.
	*/
	void PLMSettingsSample::GeneratePLMSettingsUIFromFile()
	{
		Utility::Logger("PLMSettingsSample::GeneratePLMSettingsUIFromFile() Started..");
		string plmSettingsFilePath = DirectoryUtil::getPLMPluginDirectory() + PLMSETTINGS_FILE_NAME;
		try
		{
			json plmSettingsJSON = Utility::ReadJSONFile(plmSettingsFilePath);
			string availableTenants = plmSettingsJSON[AVAILABLETENANTS_JSON_KEY].dump();
			json availableTenantsJSON = json::parse(availableTenants);
			Utility::Logger("PLMSettingsSample::GeneratePLMSettingsUIFromFile() availableTenantsJSON - " + to_string(availableTenantsJSON));
			string selectedTenant =  Utility::GetJSONValue<string>(plmSettingsJSON, SELECTEDTENANT_JSON_KEY, true);
			Utility::Logger("PLMSettingsSample::GeneratePLMSettingsUIFromFile() selectedTenant - " + selectedTenant);
			QStringList availableTenantsList = Utility::ConvertJSONArrayQStringList(availableTenantsJSON);
			int selectedTenantIndex = availableTenantsList.indexOf(QString::fromStdString(selectedTenant));
			
			comboBox_PLMTenant->addItems(availableTenantsList);
			comboBox_PLMTenant->setCurrentIndex(selectedTenantIndex);
			
			ShowOrHidePLMSettingsOfSelectedTenant(selectedTenant);
		}
		catch (exception& e)
		{
			Utility::Logger("PLMSettingsSample::GeneratePLMSettingsUIFromFile() exception - "+string(e.what()));
			UTILITY_API->DisplayMessageBox(PLMSETTINGS_EXCEPTION_MSG);
		}
		Utility::Logger("PLMSettingsSample::GeneratePLMSettingsUIFromFile() Ended..");
	}
	/**
	*\Checks for current environment change and generates back PLM Settings UI.
	* \param changedServerName
	*/
	void PLMSettingsSample::CurrentTenantChanged(const QString& changedTenant)
	{
		Utility::Logger("PLMSettingsSample::CurrentTenantChanged() Started..");
		string plmSettingsFilePath = DirectoryUtil::getPLMPluginDirectory() + PLMSETTINGS_FILE_NAME;
		try 
		{
			json plmSettingsJSON = Utility::ReadJSONFile(plmSettingsFilePath);
			string selectedTenant = Utility::GetJSONValue<string>(plmSettingsJSON, SELECTEDTENANT_JSON_KEY, true);
			Utility::Logger("PLMSettingsSample::CurrentTenantChanged() changedTenant - " + changedTenant.toStdString());
			Utility::Logger("PLMSettingsSample::CurrentTenantChanged() selectedTenant - " + selectedTenant);
			if (changedTenant == QString::fromStdString(SELECT))
			{
				HidePLMSettingsOfSelectedTenant();
			}
			else
			{
				string plmSettingsDetails =  Utility::GetJSONValue<string>(plmSettingsJSON, changedTenant.toStdString(), false);
				json plmSettingsDetailsJSON = json::parse(plmSettingsDetails);
				
				if (selectedTenant != changedTenant.toStdString())
				{
					label_ConsumerKey_Value->setText(QString::fromStdString(Utility::GetJSONValue<string>(plmSettingsDetailsJSON, CONSUMERKEY_JSON_KEY, true)));
					label_WebAppConsumerKey_Value->setText(QString::fromStdString(Utility::GetJSONValue<string>(plmSettingsDetailsJSON, WEBAPPCONSUMERKEY_JSON_KEY, true)));
					label_ServerUser_Value->setText(QString::fromStdString(Utility::GetJSONValue<string>(plmSettingsDetailsJSON, SERVERUSERNAME_JSON_KEY, true)));
					label_PlmServer_Value->setText(QString::fromStdString(Utility::GetJSONValue<string>(plmSettingsDetailsJSON, PLMSERVERURL_JSON_KEY, true)));
					if (Configuration::GetInstance()->GetBearerToken().empty())
					{
						label_PlmSchema_Value->setText(QString::fromStdString(SCHEMA_LOGIN_MSG));
					}
					else
					{
						label_PlmSchema_Value->setText(QString::fromStdString(SCHEMA_RELOGIN_MSG));
					}
					label_Cloplugin_Value->setText(QString::fromStdString(Utility::GetJSONValue<string>(plmSettingsDetailsJSON, CLOPLUGINVERSION_JSON_KEY, true)));
					lable_PlmVersion_Value->setText(QString::fromStdString(Utility::GetJSONValue<string>(plmSettingsDetailsJSON, CLOPLMPLUGINVERSION_JSON_KEY, true)));
					label_ConnectionStatus_Value->setText(QString::fromStdString(SERVER_NOTCONNECTED_STATUS));
					label_CompanyName_Value->setText(QString::fromStdString(Utility::GetJSONValue<string>(plmSettingsDetailsJSON, COMPANY_NAME, true)));
				}
				else
				{
					SetPLMSettingsOfSelectedTenant();
				}
				ShowPLMSettingsOfSelectedTenant();
			}
		}
		catch (exception& e)
		{
			Utility::Logger("PLMSettingsSample::CurrentTenantChanged() exception - " + string(e.what()));
			UTILITY_API->DisplayMessageBox(PLMSETTINGS_EXCEPTION_MSG);
		}
		Utility::Logger("PLMSettingsSample::CurrentTenantChanged() Ended..");
	}
	/**
	*\Shows or Hide PLM Settings values on PLM Settings UI.
	* \param selectedEnvironment, plmSettingsJSON
	*/
	void PLMSettingsSample::ShowOrHidePLMSettingsOfSelectedTenant(string selectedTenant)
	{
		Utility::Logger("PLMSettingsSample::ShowOrHidePLMSettingsOfSelectedTenant() Started..");
		if (selectedTenant == SELECT)
		{
			HidePLMSettingsOfSelectedTenant();
		}
		else
		{
			SetPLMSettingsOfSelectedTenant();
			ShowPLMSettingsOfSelectedTenant();
		}
		Utility::Logger("PLMSettingsSample::ShowOrHidePLMSettingsOfSelectedTenant() Ended..");
	}
	/**
	*\Set all PLM Settings values on PLM Settings UI.
	*/
	void PLMSettingsSample::SetPLMSettingsOfSelectedTenant()
	{
		Utility::Logger("PLMSettingsSample::SetPLMSettingsOfSelectedTenant() Started..");

		label_ConsumerKey_Value->setText(QString::fromStdString(Configuration::GetInstance()->GetConsumerKey()));
		label_WebAppConsumerKey_Value->setText(QString::fromStdString(Configuration::GetInstance()->GetWebAppConsumerKey()));
		label_ServerUser_Value->setText(QString::fromStdString(Configuration::GetInstance()->GetServerUserName()));
		label_PlmServer_Value->setText(QString::fromStdString(Configuration::GetInstance()->GetPLMUrl()));
		label_PlmSchema_Value->setText(QString::fromStdString(Configuration::GetInstance()->GetschemaWithoutQuotes()));
		label_Cloplugin_Value->setText(QString::fromStdString(Configuration::GetInstance()->GetCloPlugin()));
		lable_PlmVersion_Value->setText(QString::fromStdString(Configuration::GetInstance()->GetPlmVersion()));
		label_ConnectionStatus_Value->setText(QString::fromStdString(Configuration::GetInstance()->GetConnectionStatus()));
		label_CompanyName_Value->setText(QString::fromStdString(Configuration::GetInstance()->GetCompanyName()));
		
		Utility::Logger("PLMSettingsSample::SetPLMSettingsOfSelectedTenant() Ended..");
	}
	/**
	*\Shows all PLM Settings values on PLM Settings UI.
	*/
	void PLMSettingsSample::ShowPLMSettingsOfSelectedTenant()
	{
		Utility::Logger("PLMSettingsSample::ShowPLMSettingsOfSelectedTenant() Started..");

		label_ConsumerKey_Value->show();
		label_BackendConsumer_Key->show();

		label_WebAppConsumerKey_Value->show();
		label_WebAppConsumer_Key->show();

		label_ServerUser_Value->show();
		label_ServerUserName_Key->show();

		label_PlmServer_Value->show();
		label_PlmServer_Key->show();

		label_PlmSchema_Value->show();
		label_PlmSchema_Key->show();

		lable_PlmVersion_Value->show();
		lable_PLMVersion_Key->show();

		label_Cloplugin_Value->show();
		label_CloPlugin_Key->show();

		label_ConnectionStatus_Value->show();
		label_ConnectionStatus_key->show();

		label_CompanyName_Key->show();
		label_CompanyName_Value->show();

		Utility::Logger("PLMSettingsSample::ShowPLMSettingsOfSelectedTenant() Ended..");
	}
	/**
	*\Hides all PLM Settings values on PLM Settings UI.
	*/
	void PLMSettingsSample::HidePLMSettingsOfSelectedTenant()
	{
		Utility::Logger("PLMSettingsSample::HidePLMSettingsOfSelectedTenant() Started..");

		label_WebAppConsumerKey_Value->hide();
		label_WebAppConsumer_Key->hide();

		label_ConsumerKey_Value->hide();
		label_BackendConsumer_Key->hide();

		label_ServerUser_Value->hide();
		label_ServerUserName_Key->hide();

		label_PlmSchema_Value->hide();
		label_PlmSchema_Key->hide();

		label_PlmServer_Value->hide();
		label_PlmServer_Key->hide();

		label_ConnectionStatus_Value->hide();
		label_ConnectionStatus_key->hide();

		lable_PlmVersion_Value->hide();
		lable_PLMVersion_Key->hide();

		label_Cloplugin_Value->hide();
		label_CloPlugin_Key->hide();

		label_CompanyName_Key->hide();
		label_CompanyName_Value->hide();

		Utility::Logger("PLMSettingsSample::HidePLMSettingsOfSelectedTenant() Ended..");
	}
	/**
	*\Updates selected environment on PLM Settings UI to File.
	*/
	void PLMSettingsSample::UpdatePLMSettingsFileWithSelectedTenant()
	{
		Utility::Logger("PLMSettingsSample::UpdatePLMSettingsFileWithSelectedTenant() Started..");
		string plmSettingsFilePath = DirectoryUtil::getPLMPluginDirectory() + PLMSETTINGS_FILE_NAME;
		try
		{
			json plmSettingsJSON = Utility::ReadJSONFile(plmSettingsFilePath);
			string selectedTenant = Utility::GetJSONValue<string>(plmSettingsJSON, SELECTEDTENANT_JSON_KEY, true);
			Utility::Logger("PLMSettingsSample::UpdatePLMSettingsFileWithSelectedTenant() selectedTenant - " + selectedTenant);
			string changedTenant = comboBox_PLMTenant->currentText().toStdString();
			
			if (selectedTenant != changedTenant)
			{
				if (!Configuration::GetInstance()->GetUserId().empty())
				{
					UTILITY_API->DisplayMessageBox(RESTARTCLO_MSG);
				}
				plmSettingsJSON[SELECTEDTENANT_JSON_KEY] = changedTenant;
				Utility::WriteJSONFile(plmSettingsFilePath, true, plmSettingsJSON);
				Configuration::GetInstance()->SetConnectionStatus(SERVER_NOTCONNECTED_STATUS);
				Configuration::GetInstance()->SetschemaWithoutQuotes(SCHEMA_RELOGIN_MSG);
				Configuration::GetInstance()->SetschemaWithQuotes(SCHEMA_LOGIN_MSG);
				Configuration::GetInstance()->SetBearerToken(BLANK);
			}
			Configuration::GetInstance()->CachePLMsettingsFromFile();
		}
		catch (exception& e)
		{
			Utility::Logger("PLMSettingsSample::UpdatePLMSettingsFileWithSelectedTenant() exception - " + string(e.what()));
			UTILITY_API->DisplayMessageBox(PLMSETTINGS_EXCEPTION_MSG);
		}
		Utility::Logger("PLMSettingsSample::UpdatePLMSettingsFileWithSelectedTenant() Ended..");

	}
}