#include "ProductFactoryData.h"
#include "BaseProduct.h"

namespace OST
{
	template<typename TDerivedProduct>
	class CProductFactory
	{
	public:
		CProductFactory(const std::string& vSig);
		~CProductFactory(void){}

	protected:
		virtual CBaseProduct* _createProductV() {return new TDerivedProduct;}

	private:

		friend class CProductFactoryData;
	};

	template class OST_DLL_EXPORT CProductFactory<CBaseProduct>;

	template<class TDerivedProduct>
	CProductFactory<TDerivedProduct>::CProductFactory(const	std::string& vSig)
	{
		CProductFactoryData::getInstance()->registerProductFactory(reinterpret_cast<CProductFactory<CBaseProduct>*>(this), vSig);
	}
}