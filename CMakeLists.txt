cmake_minimum_required(VERSION 3.2)
project(aisd2_3)

add_executable(project ui/ui.cpp headers/Graph.h)

if (MSVC)
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	target_compile_options(project PRIVATE /W4)
else()
	target_compile_options(project PRIVATE -Wall -Wextra -pedantic -Werror)
endif()