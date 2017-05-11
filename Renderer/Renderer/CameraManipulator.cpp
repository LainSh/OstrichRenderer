#include "CameraManipulator.h"

using namespace OST;

CCameraManipulator::CCameraManipulator() : m_Camera(nullptr)
{
}


CCameraManipulator::~CCameraManipulator()
{
}

CCameraManipulator::CCameraManipulator(const CCameraManipulator& vCM)
{
	m_Camera = new CCamera(*(vCM.m_Camera));
}

//******************************************************************
//FUNCTION:
void OST::CCameraManipulator::assignCamera(CCamera* vCamera)
{
	m_Camera = vCamera;
}

//******************************************************************
//FUNCTION:
void OST::CCameraManipulator::updateCamera()
{

	_UpdateCameraV();
}
