#pragma once
#include "Camera.h"
#include <string>

namespace OST
{
	class CCameraManipulator
	{
	public:
		CCameraManipulator();
		virtual ~CCameraManipulator();

		CCameraManipulator(const CCameraManipulator& vCM);

		void assignCamera(CCamera* vCamera);
		void updateCamera();

	protected:
		virtual void _UpdateCameraV() {};


	private:
		std::string m_Sig;

		CCamera* m_Camera;
	};
}