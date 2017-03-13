#pragma once
#include "../../Renderer/Renderer/Effect.h"
#include "../../Renderer/Renderer/Shape.h"
#include "../../Renderer/Renderer/Model.h"
#include "../../Renderer/Renderer/FBO.h"
#include <glm/glm.hpp>

class DeferredEffect : public OST::CEffect
{
public:
	DeferredEffect(void);
	virtual ~DeferredEffect(void);

protected:
	virtual void _loadEffectV() override;
	virtual void _initEffectV() override;

private:
	void __geometryPass();
	void __deferredPass();
	void __copyPass();

private:
	OST::CQuad*  m_pScreenQuad;
	OST::CModel* m_pModel;

	glm::mat4 m_WorldMat;
	glm::mat4 m_ViewMat;
	glm::mat4 m_ProjectionMat;
	glm::mat4 m_NormalMat;
};
