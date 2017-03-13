#include "ResourceManager.h"
#include "ModelManager.h"
#include "FBO.h"
#include "Texture.h"
#include "ProductFactoryData.h"

using namespace OST;

CResourceManager::CResourceManager(void)
{
}


CResourceManager::~CResourceManager(void)
{
}

//******************************************************************
//FUNCTION:
bool CResourceManager::startUp()
{

	return true;
}

//******************************************************************
//FUNCTION:
bool CResourceManager::shutDown()
{

	return true;
}

//******************************************************************
//FUNCTION:
bool CResourceManager::createAllResource(const CConfig* vResourceConfig)
{
	_ASSERT(vResourceConfig);
	m_pConfig = vResourceConfig->cloneConfig();

	for (unsigned int i=0; i<m_pConfig->getSubConfigNum(); i++)
	{
		CConfig* pConfig = m_pConfig->fetchSubConfigAt(i);
//		_ASSERT(!ResourceName.empty()); Resource must have a name
		CResource* pResource = dynamic_cast<CResource*>(CProductFactoryData::getInstance()->createProduct(pConfig->getConfigSig()));
		_ASSERT(pResource);
		pResource->initWithConfig(pConfig);
		std::string ResourceName = pResource->getName();
		_ASSERT(!ResourceName.empty());
		m_ResourceSet.insert(std::make_pair(ResourceName, pResource));
	}

	return true;
}

//******************************************************************
//FUNCTION:
CResource* CResourceManager::fetchResource(const std::string& vName)
{
	if (m_ResourceSet.find(vName) == m_ResourceSet.end()) return nullptr;
	
	return m_ResourceSet[vName];
}
