#include "Interface.h"
#include "ModelManager.h"
#include "ResourceManager.h"
#include "FBO.h"
#include "Texture.h"
#include "Common.h"

using namespace OST;

//******************************************************************
//FUNCTION:
CModel* OST::OSTFetchModel(const std::string& vModelSig)
{
	return CModelManager::getInstance()->fetchModel(vModelSig);
}

//******************************************************************
//FUNCTION:
CTexture* OST::OSTFetchTexture(const std::string& vTexSig)
{
	CResource* pResource = CResourceManager::getInstance()->fetchResource(vTexSig);
	if (pResource->getSig() == RESOURCE_SIG::RS_TEXTURE) return (dynamic_cast<CTexture*>(pResource));

	return nullptr;
}

//******************************************************************
//FUNCTION:
CFBO* OST::OSTFetchFBO(const std::string& vFBOSig)
{
	CResource* pResource = CResourceManager::getInstance()->fetchResource(vFBOSig);
	if (pResource->getSig() == RESOURCE_SIG::RS_FBO) return (dynamic_cast<CFBO*>(pResource));

	return nullptr;
}

