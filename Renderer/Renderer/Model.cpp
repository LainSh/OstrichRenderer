#include "Model.h"
#include "SkinnedMesh.h"

using namespace OST;

CModel::CModel(void) : m_pMesh(nullptr)
{
}


CModel::~CModel(void)
{
}

//******************************************************************
//FUNCTION:
bool CModel::loadModelFile(const std::string& vModelFilePath, bool vWithAdjacencies)
{
	m_pMesh = new CSkinnedMesh;
	
	if (!m_pMesh->loadMesh(vModelFilePath))
	{
		return false;
	}

	return true;
}

//******************************************************************
//FUNCTION:
void CModel::render()
{
	m_pMesh->render();
}
