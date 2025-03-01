project "ATGE"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
	  "Source"
   }

   forceincludes { "_WORKING_DIR/MemTracker/Framework.h" }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
   
   characterset ("MBCS")

   filter "system:windows"
	   systemversion "latest"
	   defines 
	   {
			"WINDOWS_TARGET_PLATFORM="$(TargetPlatformVersion)"",
			"MEMORY_LOGS_DIR=R"($(SolutionDir))"" 
	   }

   filter "configurations:Debug"
	   defines { "DEBUG" }
	   runtime "Debug"
	   symbols "On"

   filter "configurations:Release"
	   defines { "RELEASE" }
	   runtime "Release"
	   optimize "On"
	   symbols "On"

   filter "configurations:Dist"
	   defines { "DIST" }
	   runtime "Release"
	   optimize "On"
	   symbols "Off"
