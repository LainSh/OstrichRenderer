#pragma once
#include "Platform.h"
#include "Common.h"
#include "DisplayWindow.h"
#include "Effect.h"
#include "Config.h"
#include <map>

namespace OST
{
	class OST_DLL_EXPORT CRenderer
	{
	public:
		CRenderer(void);
		~CRenderer(void);

		bool initRenderer();
		void run();
		

	protected:
		virtual void _renderV() {}
		virtual void _initSceneV() {}

		bool _loadEffect(const std::string& vEffectSig);


	private:
//		bool __initAllModelObject();
		bool __initAllResource();
		bool __initAllEffect();
		bool __initEnvironment();
		bool __initScene();
		void __loadConfig();
		void __destroy();

	private:
		CDisplayWindow *m_pDisplayWindow;

		std::string m_WindowTitle;
		unsigned int m_WinWidth;
		unsigned int m_WinHeight;

		std::map<std::string, CEffect*> m_EffectMap;

		CConfig* m_pSceneConfig;
		CConfig* m_pEffectConfig;
		CConfig* m_pResourceConfig;
	};
}
