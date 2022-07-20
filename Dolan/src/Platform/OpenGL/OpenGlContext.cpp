#include "dnpch.h"
#include "OpenGlContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Dolan {

	OpenGlContext::OpenGlContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		DN_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGlContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		DN_CORE_ASSERT(status, "Failed to initialise Glad");

		DN_CORE_INFO("OpenGL info:");
		DN_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		DN_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		DN_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGlContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}