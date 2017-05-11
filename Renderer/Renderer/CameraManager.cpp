#include "CameraManager.h"
#include "Common.h"

using namespace OST;

CCameraManager::CCameraManager()
{
}


CCameraManager::~CCameraManager()
{
}

//******************************************************************
//FUNCTION:
bool OST::CCameraManager::createCameraManipulator(CConfig* vCameraConfig)
{
	_ASSERT(vCameraConfig);
	bool isAllCreated = true;
	for (unsigned int i=0; i<vCameraConfig->getSubConfigNum(); i++)
	{
		CConfig* pCameraConfig = vCameraConfig->fetchSubConfigAt(i);
		std::string ManipulatorSig = m_DefaultManipulatorSig;
		if (pCameraConfig->isAttributeExisted(CONFIG_KEYWORD::CAMERA_MANIPULATOR_SIG))
		{
			ManipulatorSig = pCameraConfig->getAttribute<std::string>(CONFIG_KEYWORD::CAMERA_MANIPULATOR_SIG);
		}

		CCameraManipulator* pManipulator = 
		
	}
}

//******************************************************************
//FUNCTION:
bool OST::CCameraManager::activateCameraManipulator(const std::string& vManipulatorSig)
{

}

//******************************************************************
//FUNCTION:
OST::CCameraManipulator* OST::CCameraManager::fetchActivatedManipulator()
{

}

//******************************************************************
//FUNCTION:
OST::CCameraManipulator* OST::CCameraManager::fetchManipulatorBySig(const std::string& vSig)
{

}

//******************************************************************
//FUNCTION:
void OST::CCameraManager::initAllManipulator()
{

}

//******************************************************************
//FUNCTION:
CCameraManipulator* OST::CCameraManager::__createDefaultManipulator()
{
	
}

//******************************************************************
//FUNCTION:
CCameraManipulator* OST::CCameraManager::__createManipulator(const std::string& vSig)
{
	CCameraManipulator* pManipulator = nullptr;

	if (m_CameraManipulatorSet.find(vSig) != m_CameraManipulatorSet.end())
	{
		pManipulator = new CCameraManipulator(*m_CameraManipulatorSet[vSig]);
	}

	return pManipulator;
}
