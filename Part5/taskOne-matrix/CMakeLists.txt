cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

set(NAMESPACE taskOne)
set(COMPONENT matrix)
project(${NAMESPACE}-${COMPONENT})

add_executable(${PROJECT_NAME} main.cpp)
add_executable(${NAMESPACE}::${COMPONENT} ALIAS ${PROJECT_NAME})

find_package(taskOne-smi)
target_link_libraries(${PROJECT_NAME} PRIVATE taskOne::smi)

#target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)
