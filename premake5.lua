local component = dofile("component.lua")

workspace "citizen-scripting-cpp"
        configurations { "Debug", "Release" }
        architecture "x86_64"
        language "C++"
        cppdialect "C++23"
        location "build"

project "citizen-scripting-cpp"
        kind "SharedLib"
        targetname "citizen-scripting-cpp"
        targetprefix "lib"
        files {
                "src/CppScriptRuntime.cpp",
                "src/Component.cpp",
        }
        includedirs { "." }
        component()

        filter "configurations:Debug"
                symbols "On"
                optimize "Off"

        filter "configurations:Release"
                optimize "On"
