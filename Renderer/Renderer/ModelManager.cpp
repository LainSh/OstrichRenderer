#include "ModelManager.h"
#include "Model.h"
#include "Common.h"

using namespace OST;

CModelManager::CModelManager(void)
{
}


CModelManager::~CModelManager(void)
{
}

//******************************************************************
//FUNCTION:
bool OST::CModelManager::startUp()
{
	return true;
}

//******************************************************************
//FUNCTION:
bool OST::CModelManager::shutDown()
{
	return true;
}

//******************************************************************
//FUNCTION:
bool OST::CModelManager::createAllModel(const CConfig* vModelConfig)
{
	bool isAllCreated = true;
	for (unsigned int i=0; i<vModelConfig->getSubConfigNum(); i++)
	{
		CConfig* ModelConfig = vModelConfig->fetchSubConfigAt(i);
		std::string ModelSig = ModelConfig->getAttribute<std::string>(CONFIG_KEYWORD::MODEL_SIG);
		std::string ModelFile = ModelConfig->getAttribute<std::string>(CONFIG_KEYWORD::MODEL_FILE);
		CModel* pModel = new CModel;
		pModel->setModelSig(ModelSig);
		if (!pModel->loadModelFile(DEFAULT_CONFIG::MODEL_PATH + ModelFile))
		{
			//Log output warning...
			isAllCreated = false;
		}
		m_ModelSet.insert(std::make_pair(ModelSig, pModel));
	}
	return isAllCreated;
}

//******************************************************************
//FUNCTION:
CModel* CModelManager::fetchModel(const std::string& vModelSig)
{
	if (m_ModelSet.find(vModelSig) == m_ModelSet.end()) return nullptr;
	
	return m_ModelSet[vModelSig];
}

//******************************************************************
//FUNCTION:
bool CModelManager::loadModel(const std::string& vModelSig, const std::string& vModelPath, bool vWithAdjacencies)
{
	if (vModelPath.empty()) return false;

	CModel* pModel = new CModel;
	pModel->setModelSig(vModelSig);
	pModel->loadModelFile(vModelPath, vWithAdjacencies);

	m_ModelSet.insert(std::make_pair(vModelSig, pModel));

	return true;
}
