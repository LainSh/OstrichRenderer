#include "DeferredEffect.h"
#include "../../Renderer/Renderer/ProductFactory.h"
#include "../../Renderer/Renderer/Interface.h"
#include "../../Renderer/Renderer/Shader.h"
#include "../../Renderer/Renderer/Texture.h"
#include "../../Renderer/Renderer/Model.h"
#include <gl/freeglut.h>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

OST::CProductFactory<DeferredEffect> theCreater("Deferred_Shading");

DeferredEffect::DeferredEffect(void)
{
}


DeferredEffect::~DeferredEffect(void)
{
}

//******************************************************************
//FUNCTION:
void DeferredEffect::_loadEffectV()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	__geometryPass();
	__deferredPass();
	__copyPass();
}

//******************************************************************
//FUNCTION:
void DeferredEffect::__geometryPass()
{
	OST::CFBO* pFBO = OST::OSTFetchFBO("fbo");
	OST::CShader* pShader = _fetchShader("GeometryPass");
	pFBO->bindFBO();
	pShader->enable();
	glUniformMatrix4fv(pShader->getUniformLocation("uWVPTransformMat"), 1, GL_FALSE, glm::value_ptr(m_ProjectionMat* m_ViewMat * m_WorldMat));
	glUniformMatrix4fv(pShader->getUniformLocation("uWTransformMat"), 1, GL_FALSE, glm::value_ptr(m_WorldMat));
	glUniformMatrix4fv(pShader->getUniformLocation("uNormalMat"), 1, GL_FALSE, glm::value_ptr(m_NormalMat));
	m_pModel->render();
	pShader->disable();
	pFBO->banFBO();
}

//******************************************************************
//FUNCTION:
void DeferredEffect::__deferredPass()
{
	OST::CShader* pShader = _fetchShader("DeferredPass");
	pShader->enable();
	OST::CTexture* pPosTex = OST::OSTFetchTexture("texpos");
	OST::CTexture* pNormalTex = OST::OSTFetchTexture("texnormal");
	pPosTex->bind(GL_TEXTURE0);
	pNormalTex->bind(GL_TEXTURE1);
	pShader->setUniformInt("uPositionSampler", 0);
	pShader->setUniformInt("uNormalSampler", 1);
	m_pScreenQuad->render();
	pShader->disable();
}

//******************************************************************
//FUNCTION:
void DeferredEffect::__copyPass()
{
	OST::CShader* pShader = _fetchShader("CopyPass");
	pShader->enable();
	OST::CTexture* pTex = OST::OSTFetchTexture("texnormal");
	pTex->bind(GL_TEXTURE0);
	pShader->setUniformInt("uTexSampler", 0);
	m_pScreenQuad->render();
	pShader->disable();
}

//******************************************************************
//FUNCTION:
void DeferredEffect::_initEffectV()
{
	m_pModel = OST::OSTFetchModel("teapot");

	m_pScreenQuad = new OST::CQuad;
	m_pScreenQuad->setFullScreenQuad(1024, 768);

	m_WorldMat = glm::scale(glm::mat4(1.0),glm::vec3(10.0, 10.0, 10.0));
	m_ViewMat = glm::lookAt(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, -10.0), glm::vec3(0.0, 1.0, 0.0));
	m_ProjectionMat = glm::perspective(glm::radians(60.0f), (float)1024 / 768, 0.1f, 1000.0f);
	m_NormalMat = glm::transpose(glm::inverse(m_WorldMat));
}
