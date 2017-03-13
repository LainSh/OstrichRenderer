#pragma once
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/any.hpp>
#include <vector>
#include <iostream>
#include "Platform.h"

namespace OST
{
	class OST_DLL_EXPORT CConfig
	{
	public:
		enum EConfigDataType
		{
			OST_CONFIG_UNKNOWN =0,
			OST_CONFIG_INT,
			OST_CONFIG_FLOAT,
			OST_CONFIG_DOUBLE,
			OST_CONFIG_BOOL,
			OST_CONFIG_STRING,
			OST_CONFIG_VEC2,
			OST_CONFIG_VEC3,
			OST_CONFIG_VEC4,
			OST_CONFIG_SUBCONFIG
		};

	public:
		CConfig(void);
		virtual ~CConfig(void);

		bool isAttributeExisted(const std::string& vAttributeName) const;
		void parseXMLFile(const std::string& vFileName);
		void addSubConfig(CConfig* vConfig); 
		CConfig* cloneConfig() const;
		void setName(const std::string& vName);
		void setSig(const std::string& vSig);
		void setAttribute(const std::string& vAttributeName, boost::any vAttributeValue);

		CConfig* fetchSubConfigByName(const std::string& vName) const;
		CConfig* fetchSubConfigAt(unsigned int vIndex) const;

		unsigned int getSubConfigNum() const {return m_SubConfigSet.size();}
		std::string getConfigSig() const { return m_Sig; }
		std::string getConfigName() const { return m_Name; }

		template<class T>
		void getVecAttribute(const std::string& vAttributeName, std::vector<T>& voAttribute)
		{
			std::map<std::string, boost::any>::const_iterator itr;
			for (itr=m_AttributesMap.begin(); itr!=m_AttributesMap.end(); itr++)
			{
				if (itr->first == vAttributeName)
				{
					T Value = boost::any_cast<T>(itr->second);
					voAttribute.push_back(Value);
				}
			}
		}

		template<class T>
		T getAttribute(const std::string& vAttributeName) const
		{
			std::map<std::string, boost::any>::const_iterator itr = m_AttributesMap.find(vAttributeName);
			_ASSERT(itr != m_AttributesMap.end());
			T Value;
			bool Success;
			try
			{
				Value = boost::any_cast<T>(itr->second);
				Success =  true;
			}
			catch (boost::bad_any_cast e)
			{
#ifdef _DEBUG
				std::cout << "Bad boost::any_cast." << std::endl;
#endif
				Success = false;
			}
			_ASSERT(Success);
			return Value;
		}
	private:
		void __extractXMLAttributes(const boost::property_tree::ptree& vPropertyTree);
		void __defineTypeMap();

	private:
		std::map<std::string, EConfigDataType> m_PreDefinedTypeMap;
		std::map<std::string, boost::any> m_AttributesMap;
		std::vector<CConfig*> m_SubConfigSet;
		CConfig* m_pParentConfig;
		std::string m_Name;
		std::string m_Sig;

	friend class CConfigParser;
	};

}