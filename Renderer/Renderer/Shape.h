#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include "Platform.h"

namespace OST
{
	class OST_DLL_EXPORT CShape
	{
	public:
		enum EShapeType
		{
			SHAPE_UNKNOWN_TYPE = 0,
			SHAPE_POINT,
			SHAPE_LINE,
			SHAPE_TRIANGLE,
			SHAPE_TRIANGLE_FAN,
			SHAPE_QUAD
		};

	public:
		CShape(void) {}
		virtual ~CShape(void) {}

		void render();

	protected:
		void _initShapeObject();
		void _attachVertices2ShapeObject();
		void _setType(EShapeType vType) { m_Type = vType;}

		void _clearVertices() { m_Vertices.clear(); m_VerticesNum = 0; }
		void _addVertex(const glm::vec3& vVertex) { m_Vertices.push_back(vVertex); m_VerticesNum++; }

		virtual void _render(GLenum vDrawType);

	private:
		GLuint m_VBO;
		unsigned int m_VerticesNum;
		std::vector<glm::vec3> m_Vertices;
		EShapeType m_Type;
		std::map<EShapeType, GLenum> m_DrawTypeMap;

		void __initDrawMap();
	};

	/************************************************************************/
	/* QUAD CLASS                                                           */
	/************************************************************************/
	class OST_DLL_EXPORT CQuad : public CShape
	{
	public:
		CQuad(void);
		virtual ~CQuad(void) {}

		void setFullScreenQuad(int vScreenWidth, int vScreenHeight);
	};
}

