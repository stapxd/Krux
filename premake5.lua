include "Dependencies.lua"

workspace "Krux"
    architecture "x64"
    
    configurations { "Debug", "Release", "Dist"}
    startproject ("KruxEditor")

    multiprocessorcompile "on"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "Krux/vendor/GLFW"
    include "Krux/vendor/ImGui"
    include "Krux/vendor/Glad"
    include "Krux/vendor/ECS"
group ""

include "Krux"
include "KruxEditor"

include "Sandbox"


