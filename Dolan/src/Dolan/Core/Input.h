#pragma once

#include "Dolan/Core/Base.h"
#include "Dolan/Core/KeyCodes.h"
#include "Dolan/Core/MouseCodes.h"

namespace Dolan {
	
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}