#!/usr/bin/lua

solution "DL List"
project "dl_list"
	language "C"
	kind "ConsoleApp"
	location "src"
	targetdir "bin"
	objdir "obj"
	files {
		"src/main.c",
		"src/list.c",
		"src/list.h",
	}

	configurations { "Debug", "Release" }
	configuration "Debug"
		buildoptions { "-O0", "-g", "-Wall", "-D_GNU_SOURCE=1" }
		targetname "debug"

	configuration "Release"
		buildoptions { "-O3", "-Wall", "-D_GNU_SOURCE=1" }
		targetname "release"

