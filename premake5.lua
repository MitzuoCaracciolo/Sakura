workspace "Sakura"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release"
	}

	startproject "Sandbox"

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Sakura"
	location "Sakura"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17" 
	staticruntime "on"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "skpch.h"
	pchsource "Sakura/src/skpch.cpp"

	files
	{
		"%{prj.name}/src/Sakura.h",
		"%{prj.name}/src/skpch.h",
		"%{prj.name}/src/skpch.cpp",
		"%{prj.name}/src/Sakura/**.h",
		"%{prj.name}/src/Sakura/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/stb_image"
	}

	links
	{
		"d3d11.lib",
		"d3dcompiler.lib",
		"dxguid.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SAKURA_PLATFORM_WINDOWS"
		}

		files
		{
			"%{prj.name}/src/Platform/Windows/**.h",
			"%{prj.name}/src/Platform/Windows/**.cpp",
			"%{prj.name}/src/Platform/DirectX/**.h",
			"%{prj.name}/src/Platform/DirectX/**.cpp"
		}

project "Sandbox"
	location "Sandbox"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Sakura/vendor/spdlog/include",
		"Sakura/src"
	}

	links
	{
		"Sakura"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SAKURA_PLATFORM_WINDOWS"
		}