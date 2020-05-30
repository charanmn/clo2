#pragma once

#include <vector>

#include "DefineDllForWin.h"

using namespace std;

namespace CLOAPI
{
	class MV_CLO_INTERFACE_API WebAPIInterface {
	public:
		/*
		// At the moment, we support to open a web browser and to get the current URL for the web browser.
		*/


		// Open a web brower on CLO
		/*
		@param url : e.g. https://clo3d.com
		@param fp : call back function pointer for a void function with parameters (int, char**).
		@return bool = success or fail to open the web browser in CLO
		*/
		virtual bool OpenWebBrowserAPI(const string& url, void(*fp)(int argc, char** argv) = NULL) { return true; }

		// Get the current URL from CLO web browser
		/*
		@return string = current URL on the web browser in CLO
		*/
		virtual string GetCurrentURLOnWebkit() { return ""; }
	};
}
