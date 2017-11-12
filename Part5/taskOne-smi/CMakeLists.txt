cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

set(NAMESPACE taskOne)
set(COMPONENT smi)
project(${NAMESPACE}-${COMPONENT})

add_executable(${PROJECT_NAME} main.cpp)
add_executable(${NAMESPACE}::${COMPONENT} ALIAS ${PROJECT_NAME}

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
