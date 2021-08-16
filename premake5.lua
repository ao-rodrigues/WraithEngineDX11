workspace "WraithEngine"
	architecture "x64"
	configurations {
		"Debug",
		"Release"
	}

	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "WraithEngine"
	location "WraithEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	pchheader "wrpch.h"
	pchsource "%{prj.name}/src/wrpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"vendor/spdlog/include"
	}

	buildoptions { "/W3", "/MP" }
	flags { "MultiProcessorCompile" }

	filter "system:windows"
		systemversion "latest"
		characterset "MBCS"
		defines { "WR_PLATFORM_WINDOWS" }
		links { 
			"d3d11.lib",
			"dxguid.lib"
		}

	filter "configurations:Debug"
		defines { "DEBUG", "WR_DEBUG" }
		symbols "on"

	filter "configurations:Release"
		defines { "NDEBUG", "WR_RELEASE" }
		optimize "on"

	filter { "system:windows", "configurations:Debug" }
		buildoptions "/MTd"

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"WraithEngine/src",
		"vendor/spdlog/include"
	}

	buildoptions { "/W3", "/MP" }

	links {
		"WraithEngine"
	}

	filter "system:windows"
		systemversion "latest"
		characterset "MBCS"
		defines { "WR_PLATFORM_WINDOWS" }

	filter "configurations:Debug"
		defines { "DEBUG", "WR_DEBUG" }
		symbols "on"

	filter "configurations:Release"
		defines { "NDEBUG", "WR_RELEASE" }
		optimize "on"

	filter { "system:windows", "configurations:Debug" }
		buildoptions "/MTd"

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"