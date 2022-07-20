#include "dnpch.h"
#include "OpenGlContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Dolan {

	OpenGlContext::OpenGlContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		DN_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
	}

	void OpenGlContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		DN_CORE_ASSERT(status, "Failed to initialise Glad");
	}

	void OpenGlContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}