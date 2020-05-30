#pragma once
#include <QDialog>
#include <string>
#include <iostream>
#include "GeneratedFiles/ui_CLOPLMSignIn.h"
using namespace std;
/**
 * \ Singin to CLO plugin  
 */
namespace CLOPlugin 
{
	class PLMSignin
	{
	private:
		static PLMSignin* _instance;
		bool m_isSignInPLMEnabled;

		PLMSignin()
		{
			m_isSignInPLMEnabled = false;
		} 
		~PLMSignin()
		{
		}
	public:
		static PLMSignin*	GetInstance();
		static void			Destroy();
		void SetSignInPLM(bool b);
		bool GetSignInPLM();
	};
	class CLOPLMSignIn : public QDialog, public Ui::CLOPLMSignIn
	{
		Q_OBJECT
	private:
		bool m_isSignInSuccessful = false;
		static CLOPLMSignIn* _instance;
		QString m_plmLoginId;
		QString m_plmLoginPassword;

	public:
		static CLOPLMSignIn* GetInstance();
		static void	Destroy();
		CLOPLMSignIn(QWidget* parent = 0, Qt::WindowFlags flags = Qt::Dialog | Qt::FramelessWindowHint);
		~CLOPLMSignIn();
		void SetDefaultID(QString userId);
		void SetDefaultPassword(QString password);
		const QString& GetUserID();
		const QString& GetPassword();
		bool ValidateOrgUser(string& response, string& username, string& password);
		bool m_isAuthenticated;
		string m_UserID;
	private slots:
		void ValidateLoginCredentials();
		void cancel_Clicked();
	};
}

