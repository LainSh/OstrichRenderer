#pragma once
#include "Platform.h"
#include <string>
#include <boost/any.hpp>
#include <gl/glew.h>

namespace OST
{
	class CModel;
	class CFBO;
	class CTexture;

	OST_DLL_EXPORT CModel* OSTFetchModel(const std::string& vModelSig);
	OST_DLL_EXPORT CTexture* OSTFetchTexture(const std::string& vTexSig);
	OST_DLL_EXPORT CFBO*   OSTFetchFBO(const std::string& vFBOSig);

	template<class T>
	bool OSTInterpretString2GraphicsEnum(const std::string& vInput, T& voResult)
	{
		boost::any ValueHolder;

		if ("TEX1D" == vInput) { ValueHolder = GL_TEXTURE_1D; voResult = boost::any_cast<T>(ValueHolder); return true; }
		if ("TEX2D" == vInput) { ValueHolder = GL_TEXTURE_2D; voResult = boost::any_cast<T>(ValueHolder); return true; }
		if ("TEX3D" == vInput) { ValueHolder = GL_TEXTURE_3D; voResult = boost::any_cast<T>(ValueHolder); return true; }

		ValueHolder = GL_INVALID_ENUM;
		return false;
	};

}