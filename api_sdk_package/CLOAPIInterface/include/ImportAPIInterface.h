#pragma once

#include <vector>

#include "DefineDllForWin.h"

#include "CloApiData.h"

using namespace std;

namespace Marvelous
{
	class View3DBase;
	class SceneGraph;
	class PatternEditor;
	class Library;
}

namespace CLOAPI
{
	class MV_CLO_INTERFACE_API ImportAPIInterface {
	public:
		/*
		Load File (zprj, zpac, avt, obj, fbx, zcmr)
		*/
		virtual bool ImportFile(const string& filePath) { return true; }
		virtual bool ImportFileW(const wstring& filePath) { return true; }

		/*
		Load File (zprj)
		*/
		virtual bool ImportZprj(const string& filePath, const Marvelous::ImportZPRJOption& loadOption) { return true; }
		virtual bool ImportZprjW(const wstring& filePath, const Marvelous::ImportZPRJOption& loadOption) { return true; }
	};
}