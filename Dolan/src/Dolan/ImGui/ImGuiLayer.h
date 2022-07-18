#pragma once

#include "Dolan/Layer.h"

#include "Dolan/Events/ApplicationEvent.h"
#include "Dolan/Events/KeyEvent.h"
#include "Dolan/Events/MouseEvent.h"

namespace Dolan {

	class DOLAN_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}
