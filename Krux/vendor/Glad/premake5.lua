project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "on"
	warnings "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/glad.c",
        "include/glad/glad.h",
        "include/KHR/khrplatform.h"
	}

    includedirs
    {
        "include"
    }

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
        symbols "off"

    filter "configurations:Dist"
		runtime "Release"
		optimize "on"
        symbols "off"