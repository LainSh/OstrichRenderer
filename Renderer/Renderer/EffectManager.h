#pragma once
#include "Singleton.h"
#include "Effect.h"
#include "Config.h"

namespace OST
{
	class CEffectManager : public CSingleton<CEffectManager>
	{
	public:
		virtual ~CEffectManager(void);

		bool startUp();
		bool shutDown();

		bool createAllEffect(const CConfig* vEffectConfig, std::map<std::string, CEffect*>& voEffectMap);

	private:
		CEffectManager(void);

	private:
		friend class CSingleton<CEffectManager>;
	};

}