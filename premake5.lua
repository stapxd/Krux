workspace "Krux"
    architecture "x64"
    
    configurations { "Debug", "Release", "Dist"}
    startproject ("Sandbox")

    multiprocessorcompile "on"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs['GLFW']  = "Krux/vendor/GLFW/include"
IncludeDirs['ImGui'] = "Krux/vendor/ImGui"
IncludeDirs['Glad'] = "Krux/vendor/Glad/include"

group "Dependencies"
    include "Krux/vendor/GLFW"
    include "Krux/vendor/ImGui"
    include "Krux/vendor/Glad"
group ""

project "Krux"
    location "Krux"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    characterset "Unicode"

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
        p .. "/vendor/spdlog/include",
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.ImGui}",
        "%{IncludeDirs.Glad}"
    }

    links 
    {
        "GLFW",
        "Glad",
        "ImGui"
    }

    libdirs 
    {
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        staticruntime "On"
    
        buildoptions { "/utf-8" }

        defines
        {
            "KRX_SYS_WINDOWS",
            "GLFW_INCLUDE_NONE",
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

    characterset "Unicode"
    
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
        "Krux/vendor/spdlog/include",
        "%{IncludeDirs.ImGui}"
    }

    links 
    {
        "Krux"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        staticruntime "On"

        buildoptions { "/utf-8" }

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
