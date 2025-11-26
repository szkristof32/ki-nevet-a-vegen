workspace "ki-nevet-a-vegen"
	architecture "x86_64"
	startproject "ki-nevet-a-vegen"

	configurations 	{ "Debug", "Release" }

	flags { "MultiProcessorCompile" }

	defines "NOMINMAX"

	filter "configurations:Debug"
		defines "IC_DEBUG"
		runtime "debug"
		symbols "on"

	filter "configurations:Release"
		defines "IC_RELEASE"
		runtime "release"
		optimize "full"

	filter "action:gmake"
		buildoptions { "-Wall", "-Werror" }

	filter "action:vs*"
		linkoptions { "/ignore:4006" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "infoc-engine"
	kind "StaticLib"
	language "C"
	cdialect "C11"
	staticruntime "off"

	location "infoc-engine"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"infoc-engine/src/**.c",
		"infoc-engine/src/**.h"
	}

	includedirs
	{
		"infoc-engine/src",
		"vendor/sdl/include"
	}

	libdirs
	{
		"vendor/sdl/lib/x64"
	}

	links
	{
		"SDL2",
		"SDL2_image",
		"SDL2_ttf"
	}

	filter "system:windows"
		systemversion "latest"

project "ki-nevet-a-vegen"
	kind "ConsoleApp"
	language "C"
	cdialect "C11"
	staticruntime "off"

	location "ki-nevet-a-vegen"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"ki-nevet-a-vegen/src/**.c",
		"ki-nevet-a-vegen/src/**.h"
	}

	includedirs
	{
		"ki-nevet-a-vegen/src",
		"infoc-engine/src",
		"vendor/sdl/include"
	}

	libdirs
	{
		"vendor/sdl/lib/x64"
	}

	links
	{
		"infoc-engine",
		"SDL2",
		"SDL2_image",
		"SDL2_ttf"
	}
	
	postbuildcommands
	{
		"{COPYFILE} \"%{wks.location}/vendor/sdl/lib/x64/SDL2.dll\" \"%{cfg.buildtarget.directory}\"",
		"{COPYFILE} \"%{wks.location}/vendor/sdl/lib/x64/SDL2_image.dll\" \"%{cfg.buildtarget.directory}\"",
		"{COPYFILE} \"%{wks.location}/vendor/sdl/lib/x64/SDL2_ttf.dll\" \"%{cfg.buildtarget.directory}\"",
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Release"
		kind "WindowedApp"
