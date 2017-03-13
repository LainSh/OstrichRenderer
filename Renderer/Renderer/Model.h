#pragma once
#include "Platform.h"
#include <string>
#include "Entity.h"

namespace OST
{
	class CSkinnedMesh;

	class OST_DLL_EXPORT CModel
	{
	public:
		CModel(void);
		virtual ~CModel(void);

		bool loadModelFile(const std::string& vModelFilePath, bool vWithAdjacencies = false);
		void render();

		void setModelSig(const std::string& vSig) { m_ModelSig = vSig;}

	private:
		std::string m_ModelSig;
		CSkinnedMesh *m_pMesh;
	};
}
