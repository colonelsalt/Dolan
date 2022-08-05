#pragma once

#include "Dolan/Core/Base.h"
#include "Dolan/Events/Event.h"
#include "Dolan/Core/Timestep.h"

namespace Dolan {
	class Layer
	{
	public:
		Layer(const std::string name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return m_DebugName; }
	
	protected:
		const std::string m_DebugName;

	};
}