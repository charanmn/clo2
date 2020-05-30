#pragma once

#include <vector>

#include "DefineDllForWin.h"

using namespace std;

namespace CLOAPI
{
	class MV_CLO_INTERFACE_API PatternAPIInterface {
	public:

		/*
			Get the number of patterns
			@return return the number of patterns on the pattern editor and avatar window
		*/
		virtual int GetPatternSize() { return 0; } // deprecated. please use 'GetPatternCount()' function

		/*
			Get the pattern index which is using the pattern name
			@return pattern index
		*/
		virtual int GetPatternIndex(const string& patternName) { return 0; }
		virtual int GetPatternIndexW(const wstring& patternName) { return 0; }
		
		/*
			Get the pattern information which is using for pattern index
			@return json string for pattern information
		*/
		virtual string GetPatternInformation(int patternIndex) { return ""; }
		virtual wstring GetPatternInformationW(int patternIndex) { return L""; }

		/*
			Get the number of patterns
			@return return the number of patterns on the pattern editor and avatar window
		*/
		virtual int GetPatternCount() { return 0; }
	};
}
