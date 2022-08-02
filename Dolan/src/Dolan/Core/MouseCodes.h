#pragma once

namespace Dolan
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define DN_MOUSE_BUTTON_0      ::Dolan::Mouse::Button0
#define DN_MOUSE_BUTTON_1      ::Dolan::Mouse::Button1
#define DN_MOUSE_BUTTON_2      ::Dolan::Mouse::Button2
#define DN_MOUSE_BUTTON_3      ::Dolan::Mouse::Button3
#define DN_MOUSE_BUTTON_4      ::Dolan::Mouse::Button4
#define DN_MOUSE_BUTTON_5      ::Dolan::Mouse::Button5
#define DN_MOUSE_BUTTON_6      ::Dolan::Mouse::Button6
#define DN_MOUSE_BUTTON_7      ::Dolan::Mouse::Button7
#define DN_MOUSE_BUTTON_LAST   ::Dolan::Mouse::ButtonLast
#define DN_MOUSE_BUTTON_LEFT   ::Dolan::Mouse::ButtonLeft
#define DN_MOUSE_BUTTON_RIGHT  ::Dolan::Mouse::ButtonRight
#define DN_MOUSE_BUTTON_MIDDLE ::Dolan::Mouse::ButtonMiddle