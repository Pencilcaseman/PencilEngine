workspace "PencilEngine"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "PencilEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "PencilEngine/vendor/Glad/include"

include "PencilEngine/vendor/GLFW"
include "PencilEngine/vendor/Glad"

project "PencilEngine"
    location "PencilEngine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pcpch.h"
    pchsource "PencilEngine/src/pcpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}"
    }
    
    links {
        "GLFW",
        "Glad",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "c++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "PC_PLATFORM_WINDOWS",
            "PC_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "PC_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "PC_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "PC_DIST"
        buildoptions "/MD"
        optimize "On"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"

    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "PencilEngine/vendor/spdlog/include",
        "PencilEngine/src"
    }

    links {
        "PencilEngine"
    }

    filter "system:windows"
        cppdialect "c++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "PC_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "PC_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "PC_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "PC_DIST"
        buildoptions "/MD"
        optimize "On"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"
