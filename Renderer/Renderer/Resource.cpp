#include "Resource.h"

using namespace OST;

CResource::CResource()
{
}


CResource::~CResource()
{
}

//******************************************************************
//FUNCTION:
void CResource::setSig(const std::string& vSig)
{
	m_Sig = vSig;
}

void CResource::setName(const std::string& vName)
{
	m_Name = vName;
}

//******************************************************************
//FUNCTION:
void OST::CResource::initWithConfig(const CConfig* vConfig)
{
	m_pConfig = vConfig->cloneConfig();
	_initResourceV();
}
