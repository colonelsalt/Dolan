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
		virtual void OnEvent(Event& e) override;
		
		void Begin();
		void End();

		void SetEventBlock(bool shouldBlock) { m_ShouldBlockEvents = shouldBlock; }
		void SetDarkThemeColors();
	private:
		bool m_ShouldBlockEvents = true;
		float m_Time = 0.0f;
	};

}
