#pragma once
#include "CameraManipulator.h"
#include <string>

namespace OST
{
	class CManualManipulator : public CManualManipulator
	{
	public:
		CManualManipulator();
		virtual ~CManualManipulator();

	protected:
		virtual void _UpdateCameraV() override;

	private:
		float m_Yaw;
		float m_Pitch;
		float m_Speed;
		float m_Sensitivity;
		float m_Zoom;
	};
}

