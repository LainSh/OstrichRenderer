#include "RenderState.h"

using namespace OST;

CRenderState::CRenderState(void)
{
	__defaultState();
}


CRenderState::~CRenderState(void)
{
}

//******************************************************************
//FUNCTION:
void CRenderState::__defaultState()
{
	m_ClearBufferState = V_CLEAR_COLOR_BUFFER | V_CLEAR_DEPTH_BUFFER;

	m_DepthTest = false;
	m_DepthFunc = V_TEST_FUNC_LESS;
	m_DepthMask = true;

	m_StencilTest = false;
	m_StencilSeparate = false;
	m_StencilMask = true;
	m_StencilBackFunc = V_TEST_FUNC_ALWAYS;
	m_StencilBackOp = ((unsigned int)V_OP_KEEP << 6) | ((unsigned int)V_OP_KEEP << 3) | ((unsigned int)V_OP_KEEP);
	m_StencilFrontFunc = V_TEST_FUNC_ALWAYS;
	m_StencilFrontOp = ((unsigned int)V_OP_KEEP << 6) | ((unsigned int)V_OP_KEEP << 3) | ((unsigned int)V_OP_KEEP);

	m_CullFaceEnable = false;
	m_CullFaceOption = V_BACK_FACE;
}
