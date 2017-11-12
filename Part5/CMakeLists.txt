cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
project(taskOne)

set(SUBPROJECTS
    ${PROJECT_NAME}-smi
    ${PROJECT_NAME}-test
    )

macro(find_package)
    if(NOT "${ARGV0}" IN_LIST SUBPROJECTS)
        _find_package(${ARGV})
    endif()
endmacro()

foreach(subproj IN LISTS SUBPROJECTS)
    add_subdirectory(${subproj})
endforeach()