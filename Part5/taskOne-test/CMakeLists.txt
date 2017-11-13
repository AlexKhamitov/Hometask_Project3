cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

set(NAMESPACE taskOne)
set(COMPONENT test)
project(${NAMESPACE}-${COMPONENT})

add_executable(${PROJECT_NAME} test.cpp)
add_executable(${NAMESPACE}::${SOMPONENT} ALIAS ${PROJECT_NAME})

find_package(taskOne-smi)
target_link_libraries(${PROJECT_NAME} PRIVATE taskOne::smi)


