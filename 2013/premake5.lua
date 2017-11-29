
solution "Google Code Jam 2013 Round 1A"
    configurations  { "Debug", "Release" }
    startproject    "q-unittest"

    location "build"

project "techdevguide"
    kind      "StaticLib"
    language  "C++"
    targetdir "build/bin/%{cfg.buildcfg}"

    files { "src/**.h", 
            "src/**.cpp" }

    includedirs { "src" }
    filter "configurations:Debug"
    	defines {"DEBUG"}
    	symbols "On"
    
    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"
    
    configuration "gmake"
        buildoptions {
            "-std=c++14"
        }

project "GoogleTest"
    kind      "StaticLib"
    language  "C++"
    targetdir "build/bin/%{cfg.buildcfg}"

    files { "../3rd/gtest-1.7.0/src/gtest_main.cc", 
            "../3rd/gtest-1.7.0/src/gtest-all.cc" }

    libdirs { "../3rd/" }
    includedirs {"../3rd/gtest-1.7.0", "../3rd/gtest-1.7.0/include"}

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"
 
    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"

    configuration "gmake"
        buildoptions {
            "-std=c++14"
        }

project "techdevguide-unittest"
    kind      "ConsoleApp"
    language  "C++"
    targetdir "build/bin/%{cfg.buildcfg}"

    files { "test/**.h", 
            "test/**.cpp" }

    links {"techdevguide", "GoogleTest"}
    libdirs { "../3rd/" }
    includedirs {"../3rd/gtest-1.7.0", "../3rd/gtest-1.7.0/include", "src" }
    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"
    
    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"

    configuration "gmake"
        buildoptions {
            "-std=c++14"
        }
        linkoptions {
            "-pthread"
        }

--[[
project "GoogleBenchmark"
    kind      "StaticLib"
    language  "C++"
    targetdir "build/bin/%{cfg.buildcfg}"

    files { "../3rd/google-benchmark/src/*" } 

    libdirs { "../3rd/" }
    includedirs {"../3rd/google-benchmark", "../3rd/google-benchmark/include"}

    filter "configurations:Debug"
        defines {"DEBUG", "HAVE_STD_REGEX" }
        symbols "On"
    
    filter "configurations:Release"
        defines {"NDEBUG", "HAVE_STD_REGEX" }
        optimize "On"

    configuration "gmake"
        buildoptions {
            "-std=c++14"
        }

project "techdevguide-benchmark"
    kind      "ConsoleApp"
    language  "C++"
    targetdir "build/bin/%{cfg.buildcfg}"

    files { "benchmark/**.cpp" }

    links {"techdevguide", "GoogleBenchmark"}
    libdirs { "../3rd/" }
    includedirs {"../3rd/google-benchmark", "../3rd/google-benchmark/include", "src" }
    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"
    
    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"

    configuration "gmake"
        buildoptions {
            "-std=c++14"
        }
        linkoptions {
            "-pthread"
        }
]]

