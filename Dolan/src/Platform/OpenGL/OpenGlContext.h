#pragma once

#include "Dolan/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Dolan {
	class OpenGlContext : public GraphicsContext
	{
	public:
		OpenGlContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}