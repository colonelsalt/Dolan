#pragma once

#include "Dolan/Core.h"
#include "Dolan/Events/Event.h"

namespace Dolan {
	class DOLAN_API Layer
	{
	public:
		Layer(const std::string name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return m_DebugName; }
	
	protected:
		const std::string m_DebugName;

	};
}