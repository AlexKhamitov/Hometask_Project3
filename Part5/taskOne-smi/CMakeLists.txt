cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

set(NAMESPACE taskOne)
set(COMPONENT smi)
project(${NAMESPACE}-${COMPONENT})

add_library(${PROJECT_NAME} smi.cpp)
add_library(${NAMESPACE}::${COMPONENT} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)
