#include "Config.h"
#include "ConfigParser.h"
#include <boost/tokenizer.hpp>
#include <glm/glm.hpp>

using namespace OST;

CConfig::CConfig(void) : m_pParentConfig(nullptr)
{
	__defineTypeMap();
}

CConfig::~CConfig(void)
{
}

//******************************************************************
//FUNCTION:
bool CConfig::isAttributeExisted(const std::string& vAttributeName) const
{
	std::map<std::string, boost::any>::const_iterator itr = m_AttributesMap.find(vAttributeName);

	if (itr != m_AttributesMap.end()) return true;

	return false;
}

//******************************************************************
//FUNCTION:
void CConfig::parseXMLFile(const std::string& vFileName)
{
	CConfigParser::getInstance()->parseXMLFile(vFileName, this);
}

//******************************************************************
//FUNCTION:
void CConfig::addSubConfig(CConfig* vConfig)
{
	if (!vConfig) return;

	CConfig* Temp = vConfig->cloneConfig();
	Temp->m_pParentConfig = this;
	m_SubConfigSet.push_back(Temp);
}

//******************************************************************
//FUNCTION:
CConfig* CConfig::cloneConfig() const
{
	return new CConfig(*this);
}

//******************************************************************
//FUNCTION:
void OST::CConfig::setName(const std::string& vName)
{
	m_Name = vName;
}

//******************************************************************
//FUNCTION:
void OST::CConfig::setSig(const std::string& vSig)
{
	m_Sig = vSig;
}

//******************************************************************
//FUNCTION:
void OST::CConfig::__defineTypeMap()
{
	m_PreDefinedTypeMap.insert(std::make_pair("int", OST_CONFIG_INT));
	m_PreDefinedTypeMap.insert(std::make_pair("float", OST_CONFIG_FLOAT));
	m_PreDefinedTypeMap.insert(std::make_pair("double", OST_CONFIG_DOUBLE));
	m_PreDefinedTypeMap.insert(std::make_pair("bool", OST_CONFIG_BOOL));
	m_PreDefinedTypeMap.insert(std::make_pair("string", OST_CONFIG_STRING));
	m_PreDefinedTypeMap.insert(std::make_pair("vec2", OST_CONFIG_VEC2));
	m_PreDefinedTypeMap.insert(std::make_pair("vec3", OST_CONFIG_VEC3));
	m_PreDefinedTypeMap.insert(std::make_pair("vec4", OST_CONFIG_VEC4));
	m_PreDefinedTypeMap.insert(std::make_pair("subconfig", OST_CONFIG_SUBCONFIG));
}

//******************************************************************
//FUNCTION:
void OST::CConfig::setAttribute(const std::string& vAttributeName, boost::any vAttributeValue)
{
	m_AttributesMap.insert(std::make_pair(vAttributeName, vAttributeValue));
}

//******************************************************************
//FUNCTION:
CConfig* OST::CConfig::fetchSubConfigByName(const std::string& vName) const
{
	for (auto iter : m_SubConfigSet)
	{
		if (iter->m_Name == vName) return iter;
	}

	return nullptr;
}

//******************************************************************
//FUNCTION:
CConfig* OST::CConfig::fetchSubConfigAt(unsigned int vIndex) const
{
	return (vIndex >= m_SubConfigSet.size()) ? nullptr : m_SubConfigSet[vIndex];
}

//******************************************************************
//FUNCTION:
void CConfig::__extractXMLAttributes(const boost::property_tree::ptree& vPropertyTree)
{
	for (auto iter : vPropertyTree)
	{
		std::string Prefix = iter.first;
		if (Prefix == "<xmlattr>") continue;

		std::string TempTypeStr = Prefix + "." + "<xmlattr>" + "." + "type";
		std::string Type = vPropertyTree.get<std::string>(TempTypeStr,"subconfig");
		std::string TempNameStr = Prefix + "." + "<xmlattr>" + "." + "name";
		std::string AttributeName = vPropertyTree.get<>(TempNameStr, "");

		_ASSERT(m_PreDefinedTypeMap.find(Type) != m_PreDefinedTypeMap.end());

		std::string PropertyKeyFullName = iter.first;

		switch (m_PreDefinedTypeMap.find(Type)->second)
		{
		case EConfigDataType::OST_CONFIG_INT:
			setAttribute(PropertyKeyFullName, iter.second.get_value<int>());
			break;
		case EConfigDataType::OST_CONFIG_FLOAT:
			setAttribute(PropertyKeyFullName, iter.second.get_value<float>());
			break;
		case EConfigDataType::OST_CONFIG_DOUBLE:
			setAttribute(PropertyKeyFullName, iter.second.get_value<double>());
			break;
		case EConfigDataType::OST_CONFIG_BOOL:
			setAttribute(PropertyKeyFullName, iter.second.get_value<bool>());
			break;
		case EConfigDataType::OST_CONFIG_STRING:
			setAttribute(PropertyKeyFullName, iter.second.data());
			break;
		case EConfigDataType::OST_CONFIG_VEC2:
			{
				std::string Str = iter.second.get_value<std::string>();
				boost::char_separator<char> Sep(" ");

				boost::tokenizer<boost::char_separator<char>> Token(Str, Sep);
				std::vector<float> Vec;
				for (auto TokenIter : Token)
				{
					std::string Temp = TokenIter;
					Vec.push_back(std::atof(Temp.c_str()));
				}

				glm::vec2 TokenValue;
				for (unsigned int i=0; i<Vec.size(); i++)
				{
					TokenValue[i] = Vec[i];
				}

				setAttribute(PropertyKeyFullName, TokenValue);
				break;
			}
		case EConfigDataType::OST_CONFIG_VEC3:
			{
				std::string Str = iter.second.get_value<std::string>();
				boost::char_separator<char> Sep(" ");

				boost::tokenizer<boost::char_separator<char>> Token(Str, Sep);
				std::vector<float> Vec;
				for (auto TokenIter : Token)
				{
					std::string Temp = TokenIter;
					Vec.push_back(std::atof(Temp.c_str()));
				}

				glm::vec2 TokenValue;
				for (unsigned int i=0; i<Vec.size(); i++)
				{
					TokenValue[i] = Vec[i];
				}

				setAttribute(PropertyKeyFullName, TokenValue);
				break;
			}
		case EConfigDataType::OST_CONFIG_VEC4:
			{
				std::string Str = iter.second.get_value<std::string>();
				boost::char_separator<char> Sep(" ");

				boost::tokenizer<boost::char_separator<char>> Token(Str, Sep);
				std::vector<float> Vec;
				for (auto TokenIter : Token)
				{
					std::string Temp = TokenIter;
					Vec.push_back(std::atof(Temp.c_str()));
				}

				glm::vec2 TokenValue;
				for (unsigned int i=0; i<Vec.size(); i++)
				{
					TokenValue[i] = Vec[i];
				}

				setAttribute(PropertyKeyFullName, TokenValue);
				break;
			}
		case EConfigDataType::OST_CONFIG_SUBCONFIG:
			{
				std::string SubConfigName = AttributeName;
				std::string SubConfigSig = PropertyKeyFullName;
				CConfig* pSubConfig = new CConfig;
				pSubConfig->setName(SubConfigName);
				pSubConfig->setSig(SubConfigSig);
				pSubConfig->__extractXMLAttributes(iter.second);
				addSubConfig(pSubConfig);
				break;
			}
		default:
			break;
		}
	}
}