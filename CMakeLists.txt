# Copyright (c) 2026 Klumzy Duk Gamez.
# See LICENSE.md for full terms.

cmake_minimum_required(VERSION 3.25)
project(
	crossyroad-clone
	VERSION 0.1.0
	LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD            23)
set(CMAKE_CXX_STANDARD_REQUIRED   ON)
set(CMAKE_CXX_EXTENSIONS          OFF)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/build_out" CACHE PATH "" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32 AND MINGW)
    set(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
endif()

set(CR_THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party")
set(CR_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(CR_ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")

set(SDL_STATIC ON  CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)

add_subdirectory("${CR_THIRD_PARTY_DIR}/SDL" EXCLUDE_FROM_ALL SYSTEM)
# add_subdirectory("${CR_THIRD_PARTY_DIR}/glad" EXCLUDE_FROM_ALL SYSTEM)

add_executable(cr)
set_target_properties(
	cr PROPERTIES
	OUTPUT_NAME "crossyroad-clone"
)
file(
	GLOB_RECURSE CR_SOURCES CONFIGURE_DEPENDS
	"${CR_SOURCE_DIR}/*.cpp"
)
target_sources(
	cr PRIVATE
	${CR_SOURCES}
)
target_include_directories(
	cr PRIVATE
	"${CR_SOURCE_DIR}"
)
target_link_libraries(
	cr PRIVATE
	SDL3::SDL3
	# glad
)
target_compile_options(
	cr PRIVATE
	"-O3"
	"--embed-dir=${CR_ASSETS_DIR}"
)

install(
	FILES
	$<TARGET_FILE:cr>
	DESTINATION "."
)

