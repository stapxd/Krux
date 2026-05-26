project "KruxEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    characterset "Unicode"
    buildoptions { "/utf-8" }
    
    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    includedirs
    {
        "src",
    }
    externalincludedirs 
    {
        "%{wks.location}/Krux/src",
        "%{wks.location}/Krux/vendor/spdlog/include",
        "%{wks.location}/Krux/vendor/stb/include",
        "%{IncludeDirs.Glad}",
        "%{IncludeDirs.ImGui}",
        "%{IncludeDirs.glm}",
        "%{IncludeDirs.ECS}",
        "%{IncludeDirs.ImGuizmo}"
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