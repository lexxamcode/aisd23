cmake_minimum_required(VERSION 3.2)
project(aisd2_3)

<<<<<<< HEAD
add_executable(project ui/ui.cpp headers/Graph.h)
=======
add_executable(project ui/ui.cpp headers/Graph.h headers/City.h headers/Road.h)
>>>>>>> 36d8e48bc7099286b9db818178c5107a5359f43c

if (MSVC)
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	target_compile_options(project PRIVATE /W4)
else()
	target_compile_options(project PRIVATE -Wall -Wextra -pedantic -Werror)
endif()