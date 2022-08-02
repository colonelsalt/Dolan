#pragma once

namespace Dolan
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define DN_KEY_SPACE           ::Dolan::Key::Space
#define DN_KEY_APOSTROPHE      ::Dolan::Key::Apostrophe    /* ' */
#define DN_KEY_COMMA           ::Dolan::Key::Comma         /* , */
#define DN_KEY_MINUS           ::Dolan::Key::Minus         /* - */
#define DN_KEY_PERIOD          ::Dolan::Key::Period        /* . */
#define DN_KEY_SLASH           ::Dolan::Key::Slash         /* / */
#define DN_KEY_0               ::Dolan::Key::D0
#define DN_KEY_1               ::Dolan::Key::D1
#define DN_KEY_2               ::Dolan::Key::D2
#define DN_KEY_3               ::Dolan::Key::D3
#define DN_KEY_4               ::Dolan::Key::D4
#define DN_KEY_5               ::Dolan::Key::D5
#define DN_KEY_6               ::Dolan::Key::D6
#define DN_KEY_7               ::Dolan::Key::D7
#define DN_KEY_8               ::Dolan::Key::D8
#define DN_KEY_9               ::Dolan::Key::D9
#define DN_KEY_SEMICOLON       ::Dolan::Key::Semicolon     /* ; */
#define DN_KEY_EQUAL           ::Dolan::Key::Equal         /* = */
#define DN_KEY_A               ::Dolan::Key::A
#define DN_KEY_B               ::Dolan::Key::B
#define DN_KEY_C               ::Dolan::Key::C
#define DN_KEY_D               ::Dolan::Key::D
#define DN_KEY_E               ::Dolan::Key::E
#define DN_KEY_F               ::Dolan::Key::F
#define DN_KEY_G               ::Dolan::Key::G
#define DN_KEY_H               ::Dolan::Key::H
#define DN_KEY_I               ::Dolan::Key::I
#define DN_KEY_J               ::Dolan::Key::J
#define DN_KEY_K               ::Dolan::Key::K
#define DN_KEY_L               ::Dolan::Key::L
#define DN_KEY_M               ::Dolan::Key::M
#define DN_KEY_N               ::Dolan::Key::N
#define DN_KEY_O               ::Dolan::Key::O
#define DN_KEY_P               ::Dolan::Key::P
#define DN_KEY_Q               ::Dolan::Key::Q
#define DN_KEY_R               ::Dolan::Key::R
#define DN_KEY_S               ::Dolan::Key::S
#define DN_KEY_T               ::Dolan::Key::T
#define DN_KEY_U               ::Dolan::Key::U
#define DN_KEY_V               ::Dolan::Key::V
#define DN_KEY_W               ::Dolan::Key::W
#define DN_KEY_X               ::Dolan::Key::X
#define DN_KEY_Y               ::Dolan::Key::Y
#define DN_KEY_Z               ::Dolan::Key::Z
#define DN_KEY_LEFT_BRACKET    ::Dolan::Key::LeftBracket   /* [ */
#define DN_KEY_BACKSLASH       ::Dolan::Key::Backslash     /* \ */
#define DN_KEY_RIGHT_BRACKET   ::Dolan::Key::RightBracket  /* ] */
#define DN_KEY_GRAVE_ACCENT    ::Dolan::Key::GraveAccent   /* ` */
#define DN_KEY_WORLD_1         ::Dolan::Key::World1        /* non-US #1 */
#define DN_KEY_WORLD_2         ::Dolan::Key::World2        /* non-US #2 */

/* Function keys */
#define DN_KEY_ESCAPE          ::Dolan::Key::Escape
#define DN_KEY_ENTER           ::Dolan::Key::Enter
#define DN_KEY_TAB             ::Dolan::Key::Tab
#define DN_KEY_BACKSPACE       ::Dolan::Key::Backspace
#define DN_KEY_INSERT          ::Dolan::Key::Insert
#define DN_KEY_DELETE          ::Dolan::Key::Delete
#define DN_KEY_RIGHT           ::Dolan::Key::Right
#define DN_KEY_LEFT            ::Dolan::Key::Left
#define DN_KEY_DOWN            ::Dolan::Key::Down
#define DN_KEY_UP              ::Dolan::Key::Up
#define DN_KEY_PAGE_UP         ::Dolan::Key::PageUp
#define DN_KEY_PAGE_DOWN       ::Dolan::Key::PageDown
#define DN_KEY_HOME            ::Dolan::Key::Home
#define DN_KEY_END             ::Dolan::Key::End
#define DN_KEY_CAPS_LOCK       ::Dolan::Key::CapsLock
#define DN_KEY_SCROLL_LOCK     ::Dolan::Key::ScrollLock
#define DN_KEY_NUM_LOCK        ::Dolan::Key::NumLock
#define DN_KEY_PRINT_SCREEN    ::Dolan::Key::PrintScreen
#define DN_KEY_PAUSE           ::Dolan::Key::Pause
#define DN_KEY_F1              ::Dolan::Key::F1
#define DN_KEY_F2              ::Dolan::Key::F2
#define DN_KEY_F3              ::Dolan::Key::F3
#define DN_KEY_F4              ::Dolan::Key::F4
#define DN_KEY_F5              ::Dolan::Key::F5
#define DN_KEY_F6              ::Dolan::Key::F6
#define DN_KEY_F7              ::Dolan::Key::F7
#define DN_KEY_F8              ::Dolan::Key::F8
#define DN_KEY_F9              ::Dolan::Key::F9
#define DN_KEY_F10             ::Dolan::Key::F10
#define DN_KEY_F11             ::Dolan::Key::F11
#define DN_KEY_F12             ::Dolan::Key::F12
#define DN_KEY_F13             ::Dolan::Key::F13
#define DN_KEY_F14             ::Dolan::Key::F14
#define DN_KEY_F15             ::Dolan::Key::F15
#define DN_KEY_F16             ::Dolan::Key::F16
#define DN_KEY_F17             ::Dolan::Key::F17
#define DN_KEY_F18             ::Dolan::Key::F18
#define DN_KEY_F19             ::Dolan::Key::F19
#define DN_KEY_F20             ::Dolan::Key::F20
#define DN_KEY_F21             ::Dolan::Key::F21
#define DN_KEY_F22             ::Dolan::Key::F22
#define DN_KEY_F23             ::Dolan::Key::F23
#define DN_KEY_F24             ::Dolan::Key::F24
#define DN_KEY_F25             ::Dolan::Key::F25

/* Keypad */
#define DN_KEY_KP_0            ::Dolan::Key::KP0
#define DN_KEY_KP_1            ::Dolan::Key::KP1
#define DN_KEY_KP_2            ::Dolan::Key::KP2
#define DN_KEY_KP_3            ::Dolan::Key::KP3
#define DN_KEY_KP_4            ::Dolan::Key::KP4
#define DN_KEY_KP_5            ::Dolan::Key::KP5
#define DN_KEY_KP_6            ::Dolan::Key::KP6
#define DN_KEY_KP_7            ::Dolan::Key::KP7
#define DN_KEY_KP_8            ::Dolan::Key::KP8
#define DN_KEY_KP_9            ::Dolan::Key::KP9
#define DN_KEY_KP_DECIMAL      ::Dolan::Key::KPDecimal
#define DN_KEY_KP_DIVIDE       ::Dolan::Key::KPDivide
#define DN_KEY_KP_MULTIPLY     ::Dolan::Key::KPMultiply
#define DN_KEY_KP_SUBTRACT     ::Dolan::Key::KPSubtract
#define DN_KEY_KP_ADD          ::Dolan::Key::KPAdd
#define DN_KEY_KP_ENTER        ::Dolan::Key::KPEnter
#define DN_KEY_KP_EQUAL        ::Dolan::Key::KPEqual

#define DN_KEY_LEFT_SHIFT      ::Dolan::Key::LeftShift
#define DN_KEY_LEFT_CONTROL    ::Dolan::Key::LeftControl
#define DN_KEY_LEFT_ALT        ::Dolan::Key::LeftAlt
#define DN_KEY_LEFT_SUPER      ::Dolan::Key::LeftSuper
#define DN_KEY_RIGHT_SHIFT     ::Dolan::Key::RightShift
#define DN_KEY_RIGHT_CONTROL   ::Dolan::Key::RightControl
#define DN_KEY_RIGHT_ALT       ::Dolan::Key::RightAlt
#define DN_KEY_RIGHT_SUPER     ::Dolan::Key::RightSuper
#define DN_KEY_MENU            ::Dolan::Key::Menu