#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace OST;

CCamera::CCamera()
{
}


CCamera::~CCamera()
{
}

//******************************************************************
//FUNCTION:
glm::mat4 OST::CCamera::getViewMatrix()
{
	glm::mat4 ViewMatrix = glm::lookAt(m_Position, m_Target, m_Up);

	return ViewMatrix;
}

//******************************************************************
//FUNCTION:
glm::mat4 OST::CCamera::getProjectionMatrix()
{
	glm::mat4 ProjectionMatrix = glm::perspective(m_FOV, (float)m_ViewportWidth / m_ViewportHeight, m_Near, m_Far);

	return ProjectionMatrix;
}
