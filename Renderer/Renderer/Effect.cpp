#include "Effect.h"
#include "Common.h"

using namespace OST;

CEffect::CEffect(void) : m_pEffectConfig(nullptr), m_EffectState(OST_EFFECT_ON), m_EffectType(OST_EFFECT_DEFAULT)
{
}


CEffect::~CEffect(void)
{
}

//******************************************************************
//FUNCTION:
bool CEffect::__initEffectShader()
{
	if (!m_pEffectConfig) return false;

	for (unsigned int i=0; i<m_pEffectConfig->getSubConfigNum(); i++)
	{
		CConfig* pShaderConfig = m_pEffectConfig->fetchSubConfigAt(i);
		CShader* pShader = new CShader;
		pShader->addShader(GL_VERTEX_SHADER, pShaderConfig->getAttribute<std::string>(CONFIG_KEYWORD::VERTEX_SHADER));
		pShader->addShader(GL_FRAGMENT_SHADER, pShaderConfig->getAttribute<std::string>(CONFIG_KEYWORD::FRAGMENT_SHADER));
		pShader->compileShader();
		std::string ShaderName = pShaderConfig->getAttribute<std::string>(CONFIG_KEYWORD::SHADER_NAME);
		m_ShaderMap.insert(std::make_pair(ShaderName, pShader));
	}

	return true;
}

//******************************************************************
//FUNCTION:
void CEffect::loadEffect()
{
	if (m_EffectState == OST_EFFECT_OFF) return;

	_loadEffectV();
}

//******************************************************************
//FUNCTION:
bool CEffect::initEffectWithConfig(const CConfig* vEffectConfig)
{
	if (!vEffectConfig) return false;
	m_pEffectConfig = vEffectConfig->cloneConfig();
	m_EffectSig = m_pEffectConfig->getAttribute<std::string>(CONFIG_KEYWORD::EFFECT_SIG);

	if (!__initEffectShader()) return false;
	_initEffectV();

	return true;
}

//******************************************************************
//FUNCTION:
void OST::CEffect::enableEffect()
{
	m_EffectState = OST_EFFECT_ON;
}

//******************************************************************
//FUNCTION:
void OST::CEffect::disableEffect()
{
	m_EffectState = OST_EFFECT_OFF;
}

//******************************************************************
//FUNCTION:
bool OST::CEffect::_enableShader(const std::string& vShaderName)
{
	if (m_ShaderMap.find(vShaderName) == m_ShaderMap.end()) return false;

	m_ShaderMap[vShaderName]->enable();

	return true;
}

//******************************************************************
//FUNCTION:
bool OST::CEffect::_disableShader(const std::string& vShaderName)
{
	if (m_ShaderMap.find(vShaderName) == m_ShaderMap.end()) return false;

	m_ShaderMap[vShaderName]->disable();

	return true;
}

//******************************************************************
//FUNCTION:
CShader* OST::CEffect::_fetchShader(const std::string& vShaderName)
{
	if (m_ShaderMap.find(vShaderName) == m_ShaderMap.end()) return nullptr;

	return m_ShaderMap[vShaderName];
}
