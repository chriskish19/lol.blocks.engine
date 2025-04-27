# 3.18 min version required
cmake_minimum_required(VERSION 3.18)

# set the name of the project
set(engine "lol.blocks.engine")
set(core "lol.blocks.core")
set(gui "lol.blocks.gui")

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

# core exe
add_executable(${core} WIN32 ${core_sf} ${core_hf})

# core header file names
# creates macros for each hpp file include path
# very handy for name changes and file moves
foreach(HEADER_FILE ${core_hf})
    get_filename_component(FILE_NAME ${HEADER_FILE} NAME_WE)
    set(FILE_NAME_HPP "${FILE_NAME}_hpp")
    set(HEADER_FILE_PATH "\"${HEADER_FILE}\"")
    target_compile_definitions(${core} PRIVATE -D${FILE_NAME_HPP}=${HEADER_FILE_PATH})
    
    # for file name changes in the project
    # their is a file called names.hpp that manages all file name changes in the project
    if(${FILE_NAME} STREQUAL "names")
        target_compile_definitions(${core} PRIVATE -DNAMES_INCLUDE=${FILE_NAME_HPP})
    endif()
endforeach()



# engine is linked lib
# get engine source and header files
file(GLOB_RECURSE engine_sf "../projects/engine/*.cpp") # engine_sf (engine source files)
file(GLOB_RECURSE engine_hf "../projects/engine/*.hpp") # engine_hf (engine header files)

# build engine dll libs
add_library(${engine} SHARED ${engine_sf} ${engine_hf})

# engine header file names
# creates macros for each hpp file include path
# very handy for name changes and file moves
foreach(HEADER_FILE ${engine_hf})
    get_filename_component(FILE_NAME ${HEADER_FILE} NAME_WE)
    set(FILE_NAME_HPP "${FILE_NAME}_hpp")
    set(HEADER_FILE_PATH "\"${HEADER_FILE}\"")
    target_compile_definitions(${engine} PRIVATE -D${FILE_NAME_HPP}=${HEADER_FILE_PATH})
    
    # for file name changes in the project
    # their is a file called names.hpp that manages all file name changes in the project
    if(${FILE_NAME} STREQUAL "names")
        target_compile_definitions(${engine} PRIVATE -DNAMES_INCLUDE=${FILE_NAME_HPP})
    endif()
endforeach()

# link win32 and dx libraries to engine
target_link_libraries(${engine}
    PRIVATE
    user32
    gdi32
    shell32
    ole32
    oleaut32
    uuid
    comdlg32
    advapi32
    d3d12
    dxgi
    d3dcompiler
)



# gui is linked lib (dll)
# get gui source and headers
file(GLOB_RECURSE gui_sf "../projects/gui/*.cpp")
file(GLOB_RECURSE gui_hf "../projects/gui/*.hpp")

# build gui dll lib
add_library(${gui} SHARED ${gui_sf} ${gui_hf})

# gui header file names
# creates macros for each hpp file include path
# very handy for name changes and file moves
foreach(HEADER_FILE ${gui_hf})
    get_filename_component(FILE_NAME ${HEADER_FILE} NAME_WE)
    set(FILE_NAME_HPP "${FILE_NAME}_hpp")
    set(HEADER_FILE_PATH "\"${HEADER_FILE}\"")
    target_compile_definitions(${gui} PRIVATE -D${FILE_NAME_HPP}=${HEADER_FILE_PATH})
    
    # for file name changes in the project
    # their is a file called names.hpp that manages all file name changes in the project
    if(${FILE_NAME} STREQUAL "names")
        target_compile_definitions(${gui} PRIVATE -DNAMES_INCLUDE=${FILE_NAME_HPP})
    endif()
endforeach()

# Link Win32 libraries to gui
target_link_libraries(${gui}
    PRIVATE
    user32
    gdi32
    shell32
    ole32
    oleaut32
    uuid
    comdlg32
    advapi32
)



# link libs to core
target_link_libraries(${core} PUBLIC ${gui} ${engine})
target_include_directories(${core} PRIVATE "../projects/engine/include" "../projects/gui/include")


