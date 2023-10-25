cmake_minimum_required(VERSION 3.18)

set(TARGET CrabChampionsUtils)
project(${TARGET})

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

add_library(${TARGET} SHARED ${SOURCES} ${HEADERS})
target_include_directories(${TARGET} PRIVATE .)
target_link_libraries(${TARGET} PUBLIC UE4SS)

# Organize source files in Visual Studio filters without considering project folder name
foreach(_source IN ITEMS ${SOURCES} ${HEADERS})
    get_filename_component(_source_name "${_source}" NAME)
    get_filename_component(_source_path "${_source}" PATH)

    # Handle the special case for dllmain.cpp
    if (${_source_name} STREQUAL "dllmain.cpp")
        source_group("" FILES "${_source}")
    else ()
        string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" _group_path "${_source_path}")
        source_group("${_group_path}" FILES "${_source}")
    endif ()
endforeach()