#pragma once
#include "Platform.h"
#include "BaseProduct.h"
#include "Shader.h"
#include "Config.h"
#include <map>

namespace OST
{
	class OST_DLL_EXPORT CEffect : public CBaseProduct
	{
	public:
		enum EEffectType
		{
			OST_EFFECT_DEFAULT,
			OST_EFFECT_BUILT_IN
		};

		enum EEffectState
		{
			OST_EFFECT_OFF = 0,
			OST_EFFECT_ON
		};

	public:
		CEffect(void);
		virtual ~CEffect(void);

		void enableEffect();
		void disableEffect();

		bool initEffectWithConfig(const CConfig* vEffectConfig);
		void loadEffect();

		CConfig* fetchEffectConfig() const { return m_pEffectConfig;}
		void setEffectState(EEffectState vState) { m_EffectState = vState;}
		void setEffectType(EEffectType vType) { }
		void setEffectSig(const std::string& vSig) { m_EffectSig = vSig;}

	protected:
		virtual void _loadEffectV() {}
		virtual void _initEffectV() {}

		bool _enableShader(const std::string& vShaderName);
		bool _disableShader(const std::string& vShaderName);

		CShader* _fetchShader(const std::string& vShaderName);

	private:
		bool __initEffectShader();

	private:
		EEffectState m_EffectState;
		EEffectType m_EffectType;
		std::string m_EffectSig;
		
		std::map<std::string, CShader*> m_ShaderMap;
		CConfig* m_pEffectConfig;

	friend class CEffectManager;
	};

}