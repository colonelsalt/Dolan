#pragma once

#ifdef DN_PLATFORM_WINDOWS
	#ifdef DN_BUILD_DLL
		#define DOLAN_API __declspec(dllexport)
	#else
		#define DOLAN_API __declspec(dllimport)
	#endif // DN_BUILD_DLL
#else
	#error Dolan only supports Windows!
#endif // DN_PLATFORM_WINDOWS

#define BIT(x) (1 << x)