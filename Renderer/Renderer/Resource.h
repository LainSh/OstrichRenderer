#pragma once
#include <string>
#include "BaseProduct.h"
#include "Common.h"
#include "Config.h"

namespace OST
{
	class CResource : public CBaseProduct
	{
	public:
		CResource();
		virtual ~CResource();

		const std::string& getSig() const { return m_Sig; }
		const std::string& getName() const { return m_Name; }

		void setSig(const std::string& vSig);
		void setName(const std::string& vName);

		virtual void initWithConfig(const CConfig* vConfig);

	protected:
		virtual void _initResourceV() {}
		const CConfig* _getConfig() const { return m_pConfig; }

	private:
		std::string m_Sig;
		std::string m_Name;
		CConfig* m_pConfig;
	};

}
