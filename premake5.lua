workspace "Krux"
    architecture "x64"
    
    configurations { "Debug", "Release", "Dist"}
    startproject ("Sandbox")

    multiprocessorcompile "on"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Krux"
    location "Krux"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    buildoptions { "/utf-8" }

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "krxpch.h"
    pchsource "%{prj.name}/src/krxpch.cpp"

    local p = "%{prj.name}"

    files
    {
        p .. "/src/**.h",
        p .. "/src/**.cpp"
    }

    includedirs
    {
        p .. "/src",
        p .. "/vendor/spdlog/include"
    }

    links 
    {
    }

    libdirs 
    {
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "KRX_SYS_WINDOWS"
        }

    filter "configurations:Debug"
        defines "KRX_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "KRX_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "KRX_DIST"
        optimize "On"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    buildoptions { "/utf-8" }
    
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Krux/src",
        "Krux/vendor/spdlog/include"
    }

    links 
    {
        "Krux"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
        }

    filter "configurations:Debug"
        defines "KRX_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "KRX_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "KRX_DIST"
        optimize "On"
