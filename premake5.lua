workspace "Chunky"
    architecture "x64"
    startproject "Example"

    configurations
    {
        "Debug",
        "Release"
    }

output_directory = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

thirdparty = {}
thirdparty["glad"] = "Engine/thirdparty/glad"
thirdparty["glfw"] = "Engine/thirdparty/glfw"

project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. output_directory .. "/%{prj.name}")
    objdir ("bin_int/" .. output_directory .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",

        -- Third Party
        "%{thirdparty.glad}/**.h",
        "%{thirdparty.glad}/**.c"
    }

    includedirs
    {
		"%{prj.name}/src",

        -- Third Party
        "%{thirdparty.glad}/include",
        "%{thirdparty.glfw}/include",
    }

    libdirs
    {
        "%{thirdparty.glfw}/lib",
    }

    links
    {
        "glfw3_mt.lib",
        "opengl32.lib",
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

project "Example"
    location "Example"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. output_directory .. "/%{prj.name}")
    objdir ("bin_int/" .. output_directory .. "/%{prj.name}")

	files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
		"%{prj.name}/src",
        "Engine/src",
    }

    links
    {
        "Engine"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"