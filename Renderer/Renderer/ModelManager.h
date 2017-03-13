#pragma once
#include "Singleton.h"
#include "Config.h"
#include <map>

namespace OST
{
	class CModel;

	class CModelManager : public CSingleton<CModelManager>
	{
	public:
		virtual ~CModelManager(void);

		bool startUp();
		bool shutDown();

		bool createAllModel(const CConfig* vModelConfig);

		bool loadModel(const std::string& vModelSig, const std::string& vModelPath, bool vWithAdjacencies = false);

		CModel* fetchModel(const std::string& vModelSig);

	protected:
		CModelManager(void);

	private:
		std::map<std::string, CModel*> m_ModelSet;

		friend class CSingleton<CModelManager>;
	};
}