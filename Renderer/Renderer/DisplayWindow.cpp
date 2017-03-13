#include "DisplayWindow.h"

using namespace OST;

CDisplayWindow::CDisplayWindow(void) : m_WindowInstance(nullptr), m_FullMode(false)
{
}


CDisplayWindow::~CDisplayWindow(void)
{
	if (!m_WindowInstance)
	{
		glfwDestroyWindow(m_WindowInstance);
		m_WindowInstance = nullptr;
	}
}

//******************************************************************
//FUNCTION:
bool OST::CDisplayWindow::createWindowInstance(const std::string& vWindowName, unsigned int vWidth, unsigned int vHeight)
{
	if (!glfwInit()) return false;

	m_WindowInstance = glfwCreateWindow(vWidth, vHeight, vWindowName.c_str(), NULL, NULL);

	if (!m_WindowInstance)
	{
		glfwTerminate();
		return false;
	}

	return true;
}

//******************************************************************
//FUNCTION:
int CDisplayWindow::windowShouldClose()
{
	return glfwWindowShouldClose(m_WindowInstance);
}
