#pragma once

#include "Dolan/Core/Layer.h"

#include "Dolan/Events/ApplicationEvent.h"
#include "Dolan/Events/KeyEvent.h"
#include "Dolan/Events/MouseEvent.h"

namespace Dolan {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;
		
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}
