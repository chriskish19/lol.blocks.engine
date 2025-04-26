# 3.18 min version required
cmake_minimum_required(VERSION 3.18)

# set the name of the project
set(engine "lol.blocks.engine")
set(core "lol.blocks.core")

# create the main project
project(${core})

# using c++ 20 required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# check compiler version
set(MSVC_compiler_id "MSVC")
set(CLANG_compiler_id "Clang")
set(GCC_compiler_id "GNU")
set(is_using_MSVC_compiler OFF)
set(is_using_CLANG_compiler OFF)
set(is_using_GCC_compiler OFF)
string(COMPARE EQUAL ${CMAKE_CXX_COMPILER_ID} ${MSVC_compiler_id} is_using_MSVC_compiler)
string(COMPARE EQUAL ${CMAKE_CXX_COMPILER_ID} ${CLANG_compiler_id} is_using_CLANG_compiler)
string(COMPARE EQUAL ${CMAKE_CXX_COMPILER_ID} ${GCC_compiler_id} is_using_GCC_compiler)

# error on wrong compiler
if(NOT (is_using_MSVC_compiler OR is_using_CLANG_compiler OR is_using_GCC_compiler))
    message(FATAL_ERROR "Compiler not supported, You are using: ${CMAKE_CXX_COMPILER_ID}")
endif()

# set unicode globally
add_compile_definitions(-DUNICODE -D_UNICODE)

# get core source and header files
file(GLOB_RECURSE core_sf "../projects/core/*.cpp") # core_sf (core source files)
file(GLOB_RECURSE core_hf "../projects/core/*.hpp") # core_sf (core header files)

# engine is linked lib
# get engine source and header files
file(GLOB_RECURSE engine_sf "../projects/engine/*.cpp") # engine_sf (engine source files)
file(GLOB_RECURSE engine_hf "../projects/engine/*.hpp") # engine_hf (engine header files)

# build engine dll libs
add_library(${engine} SHARED ${engine_sf} ${engine_hf})

add_executable(${core} WIN32 ${core_sf} ${core_hf})
target_link_libraries(${core} engine d3d12 dxgi d3dcompiler)



