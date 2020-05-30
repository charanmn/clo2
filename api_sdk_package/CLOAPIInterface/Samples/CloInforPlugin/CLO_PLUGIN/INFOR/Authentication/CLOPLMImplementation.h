#pragma once
#include <QDialog>
#include <string>
#include <iostream>

using namespace std;
/**
 * \Setting Search mode for PLM 
 */
namespace CLOPlugin
{ 
	enum SEARCH_ITEM_MODE
	{
		PLM_SEARCH
	};
	class CLOPLMImplementation : public QDialog 
	{
		Q_OBJECT
	
	public:
		CLOPLMImplementation(QWidget* parent = 0, Qt::WindowFlags flags = Qt::Dialog | Qt::FramelessWindowHint, SEARCH_ITEM_MODE mode= PLM_SEARCH);
		~CLOPLMImplementation();
		void SetSearchMode(SEARCH_ITEM_MODE searchMode);
		bool SigninPLM();
		bool SigninPLM(const string plmUserId, const string plmPassword, string bearerToken);		
		void SetUserIDConfiguration();
	private:
		SEARCH_ITEM_MODE m_searchMode;		
	};
}
