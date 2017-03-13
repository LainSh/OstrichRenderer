#pragma once
#include <boost/algorithm/string.hpp>
#include "Platform.h"

namespace OST
{
	class OST_DLL_EXPORT CBaseProduct
	{
	public:
		CBaseProduct(){}
		virtual ~CBaseProduct(){}

		const std::string& getProductCreationSig() const {return m_ProductCreationSig;}

	private:
		void __setProductCreationSig(const std::string& vSig) {m_ProductCreationSig = boost::algorithm::to_upper_copy(vSig);}

		std::string m_ProductCreationSig;
	
	friend class CProductFactoryData;
	};
}