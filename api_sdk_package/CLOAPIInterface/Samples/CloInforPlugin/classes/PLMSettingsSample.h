#pragma once

#include <QDialog>

#include <string>
#include <iostream>

#include "ui_PLMSettingsSample.h"
#include "CLO_PLUGIN/INFOR/Libraries/json.h"
using json = nlohmann::json;

using namespace std;

namespace CLOAPISample
{

	class PLMSettingsSample : public QWidget, public Ui::PLMSettings
	{
		Q_OBJECT
			
	public:
		PLMSettingsSample(QWidget* parent = 0);
		~PLMSettingsSample();		

		void Reset();

	private:
		string m_serverName = "";
		void UpdatePLMSettingsFileWithSelectedTenant();
		void GeneratePLMSettingsUIFromFile();
		void ShowOrHidePLMSettingsOfSelectedTenant(string selectedTenant);
		void SetPLMSettingsOfSelectedTenant();
		void ShowPLMSettingsOfSelectedTenant();
		void HidePLMSettingsOfSelectedTenant();
		
	private slots:
		void CurrentTenantChanged(const QString& changedServerName);
	};
}