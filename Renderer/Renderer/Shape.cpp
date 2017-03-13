#include "Shape.h"

using namespace OST;

//******************************************************************
//FUNCTION:
void CShape::render()
{
	//GL_Triangle is default 
	GLenum DrawType = (m_Type == SHAPE_UNKNOWN_TYPE) ? GL_TRIANGLES : m_DrawTypeMap[m_Type];
	_render(DrawType);
}

//******************************************************************
//FUNCTION:
void CShape::_render(GLenum vDrawType)
{
	_ASSERT(m_Type);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(vDrawType, 0, m_VerticesNum);
	glDisableVertexAttribArray(0);
}

//******************************************************************
//FUNCTION:
void CShape::__initDrawMap()
{
	m_DrawTypeMap[SHAPE_POINT]    = GL_POINTS;
	m_DrawTypeMap[SHAPE_LINE]     = GL_LINES;
	m_DrawTypeMap[SHAPE_TRIANGLE] = GL_TRIANGLES;
	m_DrawTypeMap[SHAPE_TRIANGLE_FAN] = GL_TRIANGLE_FAN;
	m_DrawTypeMap[SHAPE_QUAD]     = GL_QUADS;
}

//******************************************************************
//FUNCTION:
void CShape::_initShapeObject()
{
	glGenBuffers(1, &m_VBO);
	__initDrawMap();
}

//******************************************************************
//FUNCTION:
void CShape::_attachVertices2ShapeObject()
{
	_ASSERT(m_VerticesNum);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* m_VerticesNum, &m_Vertices[0], GL_STATIC_DRAW);
}


/************************************************************************/
/* QUAD IMPLEMENT                                                       */
/************************************************************************/
CQuad::CQuad(void)
{
	_initShapeObject();
	_setType(SHAPE_QUAD);
}

//******************************************************************
//FUNCTION:
void CQuad::setFullScreenQuad(int vScreenWidth, int vScreenHeight)
{
	_clearVertices();
	_addVertex(glm::vec3(-1.0, -1.0, 0.0));
	_addVertex(glm::vec3(1.0, -1.0, 0.0));
	_addVertex(glm::vec3(1.0, 1.0, 0.0));
	_addVertex(glm::vec3(-1.0, 1.0, 0.0));

	_attachVertices2ShapeObject();
}
