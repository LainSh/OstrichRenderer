#pragma once

namespace OST
{
	enum EClearBufferState
	{
		V_CLEAR_COLOR_BUFFER = 1,
		V_CLEAR_DEPTH_BUFFER = 2,
		V_CLEAR_STENCIL_BUFFER = 4
	};

	enum ETestFunc
	{
		V_TEST_FUNC_LESS = 0,
		V_TEST_FUNC_EQUAL,
		V_TEST_FUNC_GREATER,
		V_TEST_FUNC_LEQUAL,
		V_TEST_FUNC_GEQUAL,
		V_TEST_FUNC_NOTEQUAL,
		V_TEST_FUNC_ALWAYS,
		V_TEST_FUNC_NEVER
	};

	enum EStencilOp
	{
		V_OP_KEEP = 0,
		V_OP_ZERO,
		V_OP_REPLACE,
		V_INCR,
		V_INCR_WRAP,
		V_DECR,
		V_DECR_WRAP,
		V_INVERT
	};

	enum ECullFaceOp
	{
		V_BACK_FACE = 0,
		V_FRONT_FACE
	};

	class CRenderState
	{
	public:
		CRenderState(void);
		~CRenderState(void);

	private:
		void __defaultState();

	private:
		unsigned int m_ClearBufferState;

		bool m_DepthTest;
		unsigned int m_DepthFunc;
		bool m_DepthMask;

		bool m_StencilTest;
		bool m_StencilSeparate;
		unsigned int m_StencilBackFunc;
		unsigned int m_StencilBackOp;
		unsigned int m_StencilFrontFunc;
		unsigned int m_StencilFrontOp;
		bool m_StencilMask;

		bool m_CullFaceEnable;
		bool m_CullFaceOption;
	};
}