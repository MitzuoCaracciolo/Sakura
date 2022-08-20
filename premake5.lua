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

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SAKURA_PLATFORM_WINDOWS"
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