#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <GLFW/glfw3.h>
#include <string>

namespace OST
{
	class CDisplayWindow
	{
	public:
		CDisplayWindow(void);
		~CDisplayWindow(void);

		bool createWindowInstance(const std::string& vWindowName, unsigned int vWidth, unsigned int vHeight);
		int windowShouldClose();

	protected:
		GLFWwindow* fetchWindowInstance() const {return m_WindowInstance;}

	private:
		GLFWwindow *m_WindowInstance;

		bool	     m_FullMode;
		unsigned int m_WindowWidth;
		unsigned int m_WindowHeight;

		friend class CRenderer;
	};

}