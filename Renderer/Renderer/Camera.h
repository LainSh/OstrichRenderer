#pragma once
#include <glm/glm.hpp>

namespace OST
{
	class CCamera
	{
	public:
		CCamera();
		virtual ~CCamera();

		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();

	public:
		glm::vec3 m_Position;
		float	  m_FOV;
		glm::vec3 m_Target;
		float     m_Near;
		glm::vec3 m_Up;
		float     m_Far;

		unsigned int m_ViewportWidth;
		unsigned int m_ViewportHeight;
	};
}