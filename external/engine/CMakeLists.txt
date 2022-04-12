cmake_minimum_required(VERSION 3.13.0)

project("Engine")
set(ENGINE_NAME "Engine")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_DEBUG_POSTFIX "d")
set(ENGINE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ENGINE_LINK_LIBS ${ENGINE_NAME} PARENT_SCOPE)
configure_file(engine_config.h.in engine_config.h @ONLY)

file(GLOB engine_src_files "*.cpp")
file(GLOB engine_include_files 
	"include/*.h" 
	"include/*.hpp" 
	"include/interfaces/*.h"
	"include/engine/*"
	"include/engine/interface/*"
)

add_library(Glad glad.c include/glad/glad.h)
target_include_directories(Glad PRIVATE include)

add_library(${ENGINE_NAME}
	${engine_src_files} ${engine_include_files}
)
target_link_directories( ${ENGINE_NAME} PRIVATE lib )
target_include_directories(${ENGINE_NAME}
	PRIVATE "${CMAKE_SOURCE_DIR}/include"
	PRIVATE include
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(${ENGINE_NAME} Glad)

if (MSVC)
	target_link_libraries(${ENGINE_NAME}
		opengl32
		debug Debug/glfw3d optimized Release/glfw3
		debug Debug/freetyped optimized Release/freetype
	)
	include(CPack)
elseif (UNIX)
    target_link_libraries(${ENGINE_NAME}
        glfw
        GL
        X11
        pthread
        Xrandr
        Xi
        dl
        m
        z
		freetype
    )
endif()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "Header Files" FILES ${engine_include_files})
