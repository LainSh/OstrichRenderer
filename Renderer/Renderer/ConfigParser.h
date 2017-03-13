#pragma once
#include "Singleton.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/any.hpp>
#include <map>
#include "Config.h"

namespace OST
{
	class CConfig;

	class CConfigParser : public CSingleton<CConfigParser>
	{
	public:
		enum EConfigDataType
		{
			VELA_CONFIG_UNKNOWN =0,
			VELA_CONFIG_INT,
			VELA_CONFIG_FLOAT,
			VELA_CONFIG_DOUBLE,
			VELA_CONFIG_BOOL,
			VELA_CONFIG_STRING,
			VELA_CONFIG_VEC2,
			VELA_CONFIG_VEC3,
			VELA_CONFIG_VEC4,
			VELA_CONFIG_SUBCONFIG
		};

	public:
		CConfigParser(void);
		~CConfigParser(void);

		void parseXMLFile(const std::string& vFileName, CConfig* voConfig);
		void parseINIFile(const std::string& vFileName, CConfig* voConfig);

	friend class CSingleton<CConfigParser>;
	};

}