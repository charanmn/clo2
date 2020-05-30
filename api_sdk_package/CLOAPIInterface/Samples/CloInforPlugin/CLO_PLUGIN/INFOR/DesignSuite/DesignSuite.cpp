#pragma once
#include "DesignSuite.h"
#include <QDebug>
#include <qmessagebox.h>
#include "CLO_PLUGIN/INFOR/Materials/Fabrics/FabricsSearchDialog.h"
#include "CLO_PLUGIN/INFOR/Products/createproduct.h"
#include "CLO_PLUGIN/INFOR/Products/ProductSearch.h"
#include "CLO_PLUGIN/INFOR/Products/UpdateProduct.h"
#include <exception>
#include "CLO_PLUGIN/INFOR/Utilities/Definitions.h"
#include "CLO_PLUGIN/INFOR/Materials/Trims/TrimsSearch.h"
#include "CLO_PLUGIN/INFOR/Colors/ColorSearch.h"
#include "CLO_PLUGIN/INFOR/Authentication/CLOPLMSignIn.h"

using namespace std;
/*
*brief having the methods for navigating all the functions for (product,material,color)related.
*getInstance and destroy methods for making the classs as a singleton 
*/

namespace CLOPlugin
{
	DesignSuite* DesignSuite::_instance = NULL;

	DesignSuite* DesignSuite::GetInstance()
	{
		Utility::Logger("DesignSuite -> GetInstance() -> Start");
		if (_instance == NULL) {
			_instance = new DesignSuite();
		}
		Utility::Logger("DesignSuite -> GetInstance() -> End");
		return _instance;
	}

	void DesignSuite::Destroy()
	{
		Utility::Logger("DesignSuite -> Destroy() -> Start");
		if (_instance) {
			delete _instance;
			_instance = NULL;
		}
		Utility::Logger("DesignSuite -> Destroy() -> End");
	}

	DesignSuite::DesignSuite(QWidget* parent, Qt::WindowFlags flags)
		: QDialog(parent, flags)
	{
		Utility::Logger("DesignSuite -> Constructor() -> Start");
		setupUi(this);
		int iconHieghtonButton = 24;
		int iconWidthonButton = 24;

		gridLayout->setVerticalSpacing(-1);
		gridLayout->setContentsMargins(0, -1, 0, -1);
		Configuration::GetInstance()->CreateTemporaryFolderPath();

		Cancel->setIconSize(QSize(iconHieght, iconWidth));

		QObject::connect(Cancel, SIGNAL(clicked()), this, SLOT(closeWindow()));
		QObject::connect(ShMaterial, SIGNAL(clicked()), this, SLOT(materialSearch()));
		QObject::connect(CreateProduct, SIGNAL(clicked()), this, SLOT(clickedCreatProd()));
		QObject::connect(searchProducts, SIGNAL(clicked()), this, SLOT(clickedSearchProd()));
		QObject::connect(UpdateProduct, SIGNAL(clicked()), this, SLOT(clickedUpdateProd()));
		QObject::connect(ShColor, SIGNAL(clicked()), this, SLOT(clickedSearchColors()));
		QObject::connect(trimsSearch, SIGNAL(clicked()), this, SLOT(clickedSearchTrims()));	
		QObject::connect(logout, SIGNAL(clicked()), this, SLOT(clickedLogout()));
		Utility::Logger("DesignSuite -> Constructor() -> End");
	}

	DesignSuite::~DesignSuite()
	{

	}
	/*
	*brief usign try catch for through the exception.
	*clickedSearchColors for execute the functionality when the clike of search Color button.
	*Clear all fields items in the ColorSearch UI.
	*/
	void DesignSuite::clickedSearchColors()
	{
		Utility::Logger("DesignSuite -> clickedSearchColors() -> Start");
		this->hide();
		try
		{
			ColorSearch::GetInstance()->setModal(true);
			ColorSearch::GetInstance()->setWindowTitle("Color Search Criteria");
			ColorSearch::GetInstance()->ClearAllFields();
			ColorSearch::GetInstance()->exec();
		}

		catch (exception & e)
		{
			UTILITY_API->DisplayMessageBox("Exception!!" + string(e.what()));
			Utility::Logger("DesignSuite::clickedSearchColors()::  exception - " + string(e.what()));
		}
		catch (const char* msg)
		{  
			UTILITY_API->DisplayMessageBox("Exception :: " + string(msg));
			Utility::Logger("DesignSuite::clickedSearchColors()::  exception - " + string(msg));
		}
		Utility::Logger("DesignSuite -> clickedSearchColors() -> End");
	}
	/*
	*brief usign try catch for through the exception.
	*clickedSearchTrims for execute the functionality when the clike of Search Material-Trims button.
	*Clear all fields items in the TrimsSearch UI.
	*/
	void DesignSuite::clickedSearchTrims()
	{
		Utility::Logger("DesignSuite -> clickedSearchTrims() -> Start");
		this->hide();
		try
		{
			TrimsSearch::GetInstance()->setModal(true);
			TrimsSearch::GetInstance()->setWindowTitle("Trims Search Criteria");
			TrimsSearch::GetInstance()->ClearAllFields();
			TrimsSearch::GetInstance()->exec();
		}
		catch (exception & e)
		{
			UTILITY_API->DisplayMessageBox("Exception!!" + string(e.what()));
			Utility::Logger("DesignSuite::clickedSearchTrims()::  exception - " + string(e.what()));
		}
		catch (const char* msg)
		{
			UTILITY_API->DisplayMessageBox("Exception :: " + string(msg));
			Utility::Logger("DesignSuite::clickedSearchTrims()::  exception - " + string(msg));
		}
		Utility::Logger("DesignSuite -> clickedSearchTrims() -> End");
	}

	/*
	*brief usign try catch for through the exception.
	*clickedSearchTrims for execute the functionality when the clike of Search Material-Fabrics button.
	*Clear all fields items in the MaterialSearchDialog UI.
	*/
	void DesignSuite::materialSearch()
	{
		Utility::Logger("DesignSuite -> materialSearch() -> Start");
		this->hide();
		try
		{
			MaterialSearchDialog::GetInstance()->setModal(true);
			MaterialSearchDialog::GetInstance()->ClearAllFields();
			MaterialSearchDialog::GetInstance()->exec();
		}
		catch (exception & e)
		{
			UTILITY_API->DisplayMessageBox("Exception!!" + string(e.what()));
			Utility::Logger("DesignSuite::materialSearch()::  exception - " + string(e.what()));
		}
		catch (const char* msg)
		{
			UTILITY_API->DisplayMessageBox("Exception :: " + string(msg));
			Utility::Logger("DesignSuite::materialSearch()::  exception - " + string(msg));
		}
		Utility::Logger("DesignSuite -> materialSearch() -> End");
	}

	/*
	*brief usign try catch for through the exception.
	*clickedCreatProd for execute the functionality when the clike of create product button.
	*Clear all fields items in createProduct UI, when the user donsn't save&close button .
	*/

	void DesignSuite::clickedCreatProd()
	{		
		Utility::Logger("DesignSuite -> clickedCreatProd() -> Start");
		this->hide();
		try
		{
			createProduct::GetInstance()->setModal(true);
			if(createProduct::GetInstance()->IsSaveClicked() == false)
			{
				createProduct::GetInstance()->ClearAllFields();
			}
			createProduct::GetInstance()->exec();
		}
		catch (exception & e)
		{
			UTILITY_API->DisplayMessageBox("Exception!!" + string(e.what()));
			Utility::Logger("DesignSuite::clickedCreatProd()::  exception - " + string(e.what()));
		}
		catch (const char* msg)
		{
			UTILITY_API->DisplayMessageBox("Exception :: " + string(msg));
			Utility::Logger("DesignSuite::clickedCreatProd()::  exception - " + string(msg));
		}
		Utility::Logger("DesignSuite -> clickedCreatProd() -> End");
	}
	/*
	*brief usign try catch for through the exception.
	*clickedSearchProd for execute the functionality when the clike of Search product button.
	*Clear all fields items in the ProductSearch UI.
	*/
	void DesignSuite::clickedSearchProd()
	{
		Utility::Logger("DesignSuite -> clickedSearchProd() -> Start");
		this->hide();
		try
		{
			ProductSearch::GetInstance()->setModal(true);
			ProductSearch::GetInstance()->ClearAllFields();
			ProductSearch::GetInstance()->exec();
		}
		catch (exception& e)
		{
			UTILITY_API->DisplayMessageBox("Exception!!" + string(e.what()));
			Utility::Logger("DesignSuite::clickedSearchProd()::  exception - " + string(e.what()));
		}
		catch (const char* msg)
		{
			UTILITY_API->DisplayMessageBox("Exception :: " + string(msg));
			Utility::Logger("DesignSuite::clickedSearchProd()::  exception - " + string(msg));
		}
		Utility::Logger("DesignSuite -> clickedSearchProd() -> End");
	}
	/*
	*brief usign try catch for through the exception.
	*clickedUpdateProd() for execute the functionality when the clike of Update product button.
	*Clear all fields items in the ProductSearch UI.
	*/
	void DesignSuite::clickedUpdateProd()
	{
		Utility::Logger("DesignSuite -> clickedUpdateProd() -> Start");
		this->hide();
		try
		{
			if (UpdateProduct::GetInstance()->IsValidProductForUpdate()) {
				UpdateProduct::GetInstance()->setModal(true);
				if (UpdateProduct::GetInstance()->IsSaveClicked() == false)
				{
					UpdateProduct::GetInstance()->ClearAllFields();
				}
				UpdateProduct::GetInstance()->SetAllFields();
				UpdateProduct::GetInstance()->exec();
			}
			else {
				UTILITY_API->DisplayMessageBox("No active product to update.");
				this->show();
			}
			
		}
		catch (exception & e)
		{
			UTILITY_API->DisplayMessageBox("Exception!!" + string(e.what()));
			Utility::Logger("DesignSuite::clickedUpdateProd()::  exception - " + string(e.what()));
		}
		catch (const char* msg)
		{
			UTILITY_API->DisplayMessageBox("Exception :: " + string(msg));
			Utility::Logger("DesignSuite::clickedUpdateProd()::  exception - " + string(msg));
		}
		Utility::Logger("DesignSuite -> clickedUpdateProd() -> End");
	}
	/*
	*brief closeWindow to close the designSuite UI.
	*/
	void DesignSuite::closeWindow()
	{
		Utility::Logger("DesignSuite -> closeWindow() -> Start");
		close();
		Utility::Logger("DesignSuite -> closeWindow() -> End");
	}
	/*
	*brief logout from PLM.
	*/
	void DesignSuite::clickedLogout()
	{
		bool loggedOut = false;
		//json resJson = Utility::ValidateUserLicense(LICENSE_LOGOUT_API, CLOPLMSignIn::GetInstance()->m_UserID);
		int resultCode = 1; //resJson["result_code"].get<int>();
		if (resultCode == 0) {
			UTILITY_API->DisplayMessageBox(LOGOUT_UNSUCCESSFUL_MSG);
			Utility::Logger(LOGOUT_UNSUCCESSFUL_MSG);
		}
		else if (resultCode == 1) {
			loggedOut = true;
			Utility::Logger(LICENSE_LOGOUT_MSG);
		}
		else if (resultCode == 101) {
			UTILITY_API->DisplayMessageBox(LICENSE_ERROR_CODE_101_MSG);
			Utility::Logger(LICENSE_ERROR_CODE_101_MSG);
		}
		else if (resultCode == 102) {
			UTILITY_API->DisplayMessageBox(LICENSE_ERROR_CODE_102_MSG);
			Utility::Logger(LICENSE_ERROR_CODE_102_MSG);
		}
		
		if (loggedOut) {
			Destroy();
			PLMSignin::Destroy();
			CLOPLMSignIn::Destroy();
			ColorSearch::Destroy();
			MaterialSearchDialog::Destroy();
			TrimsSearch::Destroy();
			createProduct::Destroy();
			ProductSearch::Destroy();
			UpdateProduct::Destroy();
		}
	}
}

