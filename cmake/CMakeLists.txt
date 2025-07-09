# 3.18 min version required
cmake_minimum_required(VERSION 3.18)

# set the name of the project
set(engine "lol.blocks.engine")
set(core "lol.blocks.core")
set(gui "lol.blocks.gui")
set(logs "lol.blocks.logger")
set(tests "lol.blocks.tests")

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
set(UNICODE_DEFINED ON)

#############################
# Core exe
#############################

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
    set(FILE_NAME_HPP "CORE_${FILE_NAME}_hpp")
    set(HEADER_FILE_PATH "\"${HEADER_FILE}\"")
    target_compile_definitions(${core} PRIVATE -D${FILE_NAME_HPP}=${HEADER_FILE_PATH})
    
    # for file name changes in the project
    # their is a file called names.hpp that manages all file name changes in the project
    if(${FILE_NAME} STREQUAL "names")
        target_compile_definitions(${core} PRIVATE -DCORE_NAMES_INCLUDE=${FILE_NAME_HPP})
    endif()
endforeach()
#############################
# End of Core exe
#############################




#############################
# Logger library
#############################

# logger is linked lib (dll)
# get logger source and headers
file(GLOB_RECURSE logger_sf "../projects/logger/*.cpp")
file(GLOB_RECURSE logger_hf "../projects/logger/*.hpp")

# build logger dll lib
add_library(${logs} SHARED ${logger_sf} ${logger_hf})

# linker settings
target_compile_definitions(${logs} PRIVATE -DLOGS_EXPORTS)

# logger header file names
# creates macros for each hpp file include path
# very handy for name changes and file moves
foreach(HEADER_FILE ${logger_hf})
    get_filename_component(FILE_NAME ${HEADER_FILE} NAME_WE)
    set(FILE_NAME_HPP "LOGGER_${FILE_NAME}_hpp")
    set(HEADER_FILE_PATH "\"${HEADER_FILE}\"")
    target_compile_definitions(${logs} PUBLIC -D${FILE_NAME_HPP}=${HEADER_FILE_PATH})
    
    # for file name changes in the project
    # their is a file called names.hpp that manages all file name changes in the project
    if(${FILE_NAME} STREQUAL "names")
        target_compile_definitions(${logs} PUBLIC -DLOGGER_NAMES_INCLUDE=${FILE_NAME_HPP})
    endif()
endforeach()

# Link Win32 libraries to gui
target_link_libraries(${logs}
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
#############################
# End of Logger library
#############################



#############################
# Engine library
#############################

# directx toolkit
find_package(directxtk CONFIG REQUIRED)

# assimp loader
find_package(assimp CONFIG REQUIRED)


# engine is linked lib
# get engine source and header files
file(GLOB_RECURSE engine_sf "../projects/engine/*.cpp") # engine_sf (engine source files)
file(GLOB_RECURSE engine_hf "../projects/engine/*.hpp") # engine_hf (engine header files)

# build engine dll libs
add_library(${engine} SHARED ${engine_sf} ${engine_hf})

# linker settings
target_compile_definitions(${engine} PRIVATE -DENGINE_EXPORTS)

# engine header file names
# creates macros for each hpp file include path
# very handy for name changes and file moves
foreach(HEADER_FILE ${engine_hf})
    get_filename_component(FILE_NAME ${HEADER_FILE} NAME_WE)
    set(FILE_NAME_HPP "ENGINE_${FILE_NAME}_hpp")
    set(HEADER_FILE_PATH "\"${HEADER_FILE}\"")
    target_compile_definitions(${engine} PUBLIC -D${FILE_NAME_HPP}=${HEADER_FILE_PATH})
    
    # for file name changes in the project
    # their is a file called names.hpp that manages all file name changes in the project
    if(${FILE_NAME} STREQUAL "names")
        target_compile_definitions(${engine} PUBLIC -DENGINE_NAMES_INCLUDE=${FILE_NAME_HPP})
    endif()
endforeach()


# for DX11 DEMOS
# creates macros for each resource (full file path)
file(GLOB_RECURSE ed_dx11_rs "../projects/engine/demos/dx11/resources/*")
foreach(ENGINE_RESOURCE ${ed_dx11_rs})
    # gets the name from ENGINE_RESOURCE, ENGINE_RESOURCE is the full path from C:
    get_filename_component(FILE_NAME ${ENGINE_RESOURCE} NAME_WE)
    
    # gets the extension from ENGINE_RESOURCE
    get_filename_component(FILE_EXT ${ENGINE_RESOURCE} EXT)
    
    if(UNICODE_DEFINED AND NOT (${FILE_EXT} STREQUAL ".h" OR ${FILE_EXT} STREQUAL ".hpp"))
        # full file path in the variable ENGINE_RESOURCE_FILE_PATH
        set(ENGINE_RESOURCE_FILE_PATH "L\"${ENGINE_RESOURCE}\"")
    else()
        # full file path in the variable ENGINE_RESOURCE_FILE_PATH
        set(ENGINE_RESOURCE_FILE_PATH "\"${ENGINE_RESOURCE}\"")
    endif()

    # get rid of the dot and replace it with _
    string(REPLACE "." "_" FILE_EXT ${FILE_EXT})

    # the macro name
    set(ENGINE_RESOURCE_NAME "ENGINE_${FILE_NAME}${FILE_EXT}")
    
    # set the macro to the file path
    target_compile_definitions(${engine} PUBLIC -D${ENGINE_RESOURCE_NAME}=${ENGINE_RESOURCE_FILE_PATH})
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
    d3d11
    dxgi
    d3dcompiler
    Microsoft::DirectXTK
    runtimeobject
    ${logs}
    assimp::assimp
)
#############################
# End of Engine library
#############################



#############################
# Gui library
#############################

# gui is linked lib (dll)
# get gui source and headers
file(GLOB_RECURSE gui_sf "../projects/gui/*.cpp")
file(GLOB_RECURSE gui_hf "../projects/gui/*.hpp")

# build gui dll lib
add_library(${gui} SHARED ${gui_sf} ${gui_hf})

# linker settings
target_compile_definitions(${gui} PRIVATE -DGUI_EXPORTS)

# gui header file names
# creates macros for each hpp file include path
# very handy for name changes and file moves
foreach(HEADER_FILE ${gui_hf})
    get_filename_component(FILE_NAME ${HEADER_FILE} NAME_WE)
    set(FILE_NAME_HPP "GUI_${FILE_NAME}_hpp")
    set(HEADER_FILE_PATH "\"${HEADER_FILE}\"")
    target_compile_definitions(${gui} PUBLIC -D${FILE_NAME_HPP}=${HEADER_FILE_PATH})
    
    # for file name changes in the project
    # their is a file called names.hpp that manages all file name changes in the project
    if(${FILE_NAME} STREQUAL "names")
        target_compile_definitions(${gui} PUBLIC -DGUI_NAMES_INCLUDE=${FILE_NAME_HPP})
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
    ${logs}
)

#############################
# End of Gui library
#############################



#############################
# Test library
#############################

# tests is linked lib
# get tests source and header files
file(GLOB_RECURSE tests_sf "../projects/unit-tests/*.cpp") # tests_sf (tests source files)
file(GLOB_RECURSE tests_hf "../projects/unit-tests/*.hpp") # tests_hf (tests header files)

# build engine dll libs
add_library(${tests} SHARED ${tests_sf} ${tests_hf})

# linker settings
target_compile_definitions(${tests} PRIVATE -DTEST_EXPORTS)

# tests header file names
# creates macros for each hpp file include path
# very handy for name changes and file moves
foreach(HEADER_FILE ${tests_hf})
    get_filename_component(FILE_NAME ${HEADER_FILE} NAME_WE)
    set(FILE_NAME_HPP "TEST_${FILE_NAME}_hpp")
    set(HEADER_FILE_PATH "\"${HEADER_FILE}\"")
    target_compile_definitions(${tests} PUBLIC -D${FILE_NAME_HPP}=${HEADER_FILE_PATH})
    
    # for file name changes in the project
    # their is a file called names.hpp that manages all file name changes in the project
    if(${FILE_NAME} STREQUAL "names")
        target_compile_definitions(${tests} PUBLIC -DTEST_NAMES_INCLUDE=${FILE_NAME_HPP})
    endif()
endforeach()

# link win32 and dx libraries to engine
target_link_libraries(${tests}
    PRIVATE
    user32
    gdi32
    shell32
    ole32
    oleaut32
    uuid
    comdlg32
    advapi32
    d3d11
    dxgi
    d3dcompiler
    Microsoft::DirectXTK
    runtimeobject
    ${logs}
    ${engine}
    ${gui}
)

#############################
# End of Test library
#############################

# link libs to core
target_link_libraries(${core} PUBLIC 
${gui} 
${engine} 
${logs} 
${tests}
Microsoft::DirectXTK
runtimeobject)

