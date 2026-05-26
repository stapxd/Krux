project "Krux"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    characterset "Unicode"
    buildoptions { "/utf-8" }

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "krxpch.h"
    pchsource "src/krxpch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",

        "vendor/stb/include/stb/**.h",
        "vendor/stb/include/stb/**.cpp",
        "vendor/glm/glm/**.hpp",
        "vendor/glm/glm/**.inl",

        "vendor/ImGuizmo/src/ImGuizmo.h",
        "vendor/ImGuizmo/src/ImGuizmo.cpp"
    }

    includedirs
    {
       "src",
    }
    externalincludedirs 
    {
        "vendor/spdlog/include",
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.ImGui}",
        "%{IncludeDirs.Glad}",
        "%{IncludeDirs.glm}",
        "%{IncludeDirs.stb}",
        "%{IncludeDirs.ECS}",
        "%{IncludeDirs.ImGuizmo}"
    }
    externalwarnings "Off"

    links 
    {
        "GLFW",
        "Glad",
        "ImGui",
        "ECS",
    }

    libdirs 
    {
    }

    filter "files:vendor/stb/include/stb/**.cpp"
        enablepch "Off"

    filter "files:vendor/ImGuizmo/src/ImGuizmo.cpp"
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