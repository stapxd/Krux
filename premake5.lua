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
IncludeDirs['glm'] = "Krux/vendor/glm"
IncludeDirs['stb'] = "Krux/vendor/stb/include"

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
    buildoptions { "/utf-8" }

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "krxpch.h"
    pchsource "%{prj.name}/src/krxpch.cpp"

    local p = "%{prj.name}"

    files
    {
        p .. "/src/**.h",
        p .. "/src/**.cpp",
        
        p .. "/vendor/stb/include/stb/**.h",
		p .. "/vendor/stb/include/stb/**.cpp",
		p .. "/vendor/glm/glm/**.hpp",
		p .. "/vendor/glm/glm/**.inl",
    }

    includedirs
    {
        p .. "/src",
    }
    externalincludedirs 
    {
        p .. "/vendor/spdlog/include",
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.ImGui}",
        "%{IncludeDirs.Glad}",
        "%{IncludeDirs.glm}",
        "%{IncludeDirs.stb}"
    }
    externalwarnings "Off"

    links 
    {
        "GLFW",
        "Glad",
        "ImGui"
    }

    libdirs 
    {
    }

    filter "files:Krux/vendor/stb/include/stb/**.cpp"
        enablepch "Off"

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        staticruntime "On"

        defines
        {
            "KRX_SYS_WINDOWS",
            "GLFW_INCLUDE_NONE",
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter "configurations:Debug"
        defines {
            "KRX_DEBUG"
        }
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
    buildoptions { "/utf-8" }
    
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
    
    }
    externalincludedirs 
    {
        "Krux/src",
        "Krux/vendor/spdlog/include",
        "Krux/vendor/stb/include",
        "%{IncludeDirs.ImGui}",
        "%{IncludeDirs.glm}",
    }
    externalwarnings "Off"

    links 
    {
        "Krux",
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        staticruntime "On"


        defines
        {
            "KRX_SYS_WINDOWS",
            "_CRT_SECURE_NO_WARNINGS"
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
