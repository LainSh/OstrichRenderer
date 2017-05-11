#include "ManualManipulator.h"

using namespace OST;

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 3.0f;
const float SENSITIVITY = 0.25f;
const float ZOOM = 45.0f;

CManualManipulator::CManualManipulator() : m_Yaw(YAW), m_Pitch(PITCH), m_Speed(SPEED), m_Sensitivity(SENSITIVITY), m_Zoom(ZOOM)
{
}


CManualManipulator::~CManualManipulator()
{
}

//******************************************************************
//FUNCTION:
void OST::CManualManipulator::_UpdateCameraV()
{

}
