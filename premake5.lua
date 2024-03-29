workspace "Dolan"
	architecture "x86_64"
	startproject "Dolan-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Dolan/vendor/GLFW/include"
IncludeDir["Glad"] = "Dolan/vendor/Glad/include"
IncludeDir["ImGui"] = "Dolan/vendor/imgui"
IncludeDir["glm"] = "Dolan/vendor/glm"
IncludeDir["stb_image"] = "Dolan/vendor/stb_image"
IncludeDir["entt"] = "Dolan/vendor/entt/include"
IncludeDir["yaml_cpp"] = "Dolan/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "Dolan/vendor/ImGuizmo"

group "Dependencies"
	include "Dolan/vendor/GLFW"
	include "Dolan/vendor/Glad"
	include "Dolan/vendor/imgui"
	include "Dolan/vendor/yaml-cpp"
group ""

project "Dolan"
	location "Dolan"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "dnpch.h"
	pchsource "Dolan/src/dnpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
		"opengl32.lib"
	}

	filter "files:vendor/ImGuizmo/**.cpp"
	flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"DN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "DN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DN_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
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
		"Dolan/src",
		"Dolan/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Dolan"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"DN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "DN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DN_DIST"
		runtime "Release"
		optimize "on"

project "Dolan-Editor"
	location "Dolan-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
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
		"Dolan/src",
		"Dolan/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
	}

	links
	{
		"Dolan"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"DN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "DN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DN_DIST"
		runtime "Release"
		optimize "on"