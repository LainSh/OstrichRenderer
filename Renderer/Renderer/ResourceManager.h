#pragma once
#include "Singleton.h"
#include "Config.h"
#include "Resource.h"
#include <string>
#include <map>

namespace OST
{
	class CFBO;
	class CTexture;

	class CResourceManager : public CSingleton<CResourceManager>
	{
	public:
		virtual ~CResourceManager(void);

		bool startUp();
		bool shutDown();

		bool createAllResource(const CConfig* vResourceConfig);
		CResource* fetchResource(const std::string& vName);

	protected:
		CResourceManager(void);

	private:
		std::map<std::string, CResource*> m_ResourceSet;
		CConfig* m_pConfig;

	friend class CSingleton<CResourceManager>;
	};
}