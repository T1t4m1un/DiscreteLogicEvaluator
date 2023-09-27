cmake_minimum_required(VERSION 3.20)

project(FormulaEvaluator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(parser)
add_subdirectory(analyze)
add_subdirectory(execution)

add_executable(FormulaEvaluator main.cpp)
target_link_libraries(FormulaEvaluator parser analyzer)