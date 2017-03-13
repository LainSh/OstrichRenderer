#pragma once
#include <glm/glm.hpp>

namespace OST
{
	class CModel;

	struct SEntityStateSet
	{
		glm::vec3 m_Position;
		glm::vec3 m_EulerAngle;
		glm::vec3 m_Scale;
	};

	class CEntity
	{
	public:
		CEntity(void);
		virtual ~CEntity(void);

		void render();

		const glm::vec3& getPosition() const;
		const glm::vec3& getEulerAngle() const;
		const glm::vec3& getScale() const;

		const glm::mat4& getModelMatrix() const;

	protected:
		virtual void _renderV() {}

	private:
		CModel* m_pModel;
		SEntityStateSet m_StateSet;
	};

}