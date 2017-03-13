#include "Entity.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace OST;

CEntity::CEntity(void)
{
}


CEntity::~CEntity(void)
{
}

//******************************************************************
//FUNCTION:
void OST::CEntity::render()
{
	_renderV();
}

//******************************************************************
//FUNCTION:
const glm::mat4& OST::CEntity::getModelMatrix() const
{
	
	glm::mat4 TranslateMat = glm::translate(glm::mat4(1.0), m_StateSet.m_Position);
	glm::quat RotateQuat = glm::quat(m_StateSet.m_EulerAngle); 
	glm::mat4 RotateMat = glm::toMat4(RotateQuat);
	glm::mat4 ScaleMat = glm::scale(glm::mat4(1.0), m_StateSet.m_Scale);

	return (TranslateMat * RotateMat * ScaleMat);
}

//******************************************************************
//FUNCTION:
const glm::vec3& OST::CEntity::getPosition() const
{
	return m_StateSet.m_Position;
}

//******************************************************************
//FUNCTION:
const glm::vec3& OST::CEntity::getEulerAngle() const
{
	return m_StateSet.m_EulerAngle;
}

//******************************************************************
//FUNCTION:
const glm::vec3& OST::CEntity::getScale() const
{
	return m_StateSet.m_Scale;
}
