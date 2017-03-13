#include "EffectManager.h"
#include "ProductFactoryData.h"
#include "Common.h"
#include "Effect.h"

using namespace OST;

CEffectManager::CEffectManager(void)
{
}


CEffectManager::~CEffectManager(void)
{
}

//******************************************************************
//FUNCTION:
bool OST::CEffectManager::startUp()
{

	return true;
}

//******************************************************************
//FUNCTION:
bool OST::CEffectManager::shutDown()
{

	return true;
}

//******************************************************************
//FUNCTION:
bool OST::CEffectManager::createAllEffect(const CConfig* vEffectConfig, std::map<std::string, CEffect*>& voEffectMap)
{
	_ASSERT(vEffectConfig);
	for (unsigned int i=0; i<vEffectConfig->getSubConfigNum(); i++)
	{
		CConfig* pConfig = vEffectConfig->fetchSubConfigAt(i);
		std::string EffectSig = pConfig->getAttribute<std::string>(CONFIG_KEYWORD::EFFECT_SIG);
		CEffect* pEffect = dynamic_cast<CEffect*>(OST::CProductFactoryData::getInstance()->createProduct(EffectSig));
		_ASSERT(pEffect);
		if (!pEffect->initEffectWithConfig(pConfig)) continue;
		voEffectMap.insert(std::make_pair(EffectSig, pEffect));
	}
	return true;
}
