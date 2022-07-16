workspace "Dolan"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Dolan/vendor/GLFW/include"
IncludeDir["Glad"] = "Dolan/vendor/Glad/include"
IncludeDir["ImGui"] = "Dolan/vendor/imgui"

include "Dolan/vendor/GLFW"
include "Dolan/vendor/Glad"
include "Dolan/vendor/imgui"

project "Dolan"
	location "Dolan"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "dnpch.h"
	pchsource "Dolan/src/dnpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"DN_PLATFORM_WINDOWS",
			"DN_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"IMGUI_IMPL_OPENGL_LOADER_CUSTOM"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "DN_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "DN_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "DN_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Dolan/vendor/spdlog/include",
		"Dolan/src"
	}

	links
	{
		"Dolan"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"DN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DN_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "DN_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "DN_DIST"
		runtime "Release"
		optimize "On"