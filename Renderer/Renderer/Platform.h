#pragma once
#pragma warning(disable: 4251)
#ifdef OST_EXPORT
#define OST_DLL_EXPORT __declspec(dllexport)
#else
#define OST_DLL_EXPORT __declspec(dllimport)
#endif