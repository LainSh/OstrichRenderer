#pragma once
#include "Singleton.h"
#include "CameraManipulator.h"
#include "Camera.h"
#include "Config.h"
#include <map>

namespace OST
{
	class CCameraManager : public CSingleton<CCameraManager>
	{
	public:
		~CCameraManager();

		bool createCameraManipulator(CConfig* vCameraConfig);
		bool activateCameraManipulator(const std::string& vManipulatorSig);

		CCameraManipulator* fetchActivatedManipulator();
		CCameraManipulator* fetchManipulatorBySig(const std::string& vSig);

	protected:
		CCameraManager();

	private:

		/*All camera manipulators are build-in with unique signatures*/
		void initAllManipulator();

		CCameraManipulator* __createDefaultManipulator();
		CCameraManipulator* __createManipulator(const std::string& vSig);

	private:
		CCameraManipulator* m_ActivatedManipulator;
		std::map<std::string, CCameraManipulator*> m_CameraManipulatorSet;

		const std::string m_DefaultManipulatorSig;
	};

}