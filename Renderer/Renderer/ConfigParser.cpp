#include "ConfigParser.h"
#include <boost/tokenizer.hpp>
#include <glm/glm.hpp>

using namespace OST;

CConfigParser::CConfigParser(void)
{
}


CConfigParser::~CConfigParser(void)
{
}

//******************************************************************
//FUNCTION:
void CConfigParser::parseXMLFile(const std::string& vFileName, CConfig* voConfig)
{
	_ASSERT(!vFileName.empty() && voConfig);

	boost::property_tree::ptree Ptree;
	boost::property_tree::read_xml(vFileName, Ptree, boost::property_tree::xml_parser::trim_whitespace);

	voConfig->__extractXMLAttributes(Ptree);
}

//******************************************************************
//FUNCTION:
void OST::CConfigParser::parseINIFile(const std::string& vFileName, CConfig* voConfig)
{

}
