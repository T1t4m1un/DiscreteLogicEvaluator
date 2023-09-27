cmake_minimum_required(VERSION 3.20)

# 使用bison和flex工具生成解析器和词法分析器
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

bison_target(Parser yacc.y ${CMAKE_CURRENT_BINARY_DIR}/yacc.tab.cpp)
flex_target(Scanner lex.l ${CMAKE_CURRENT_BINARY_DIR}/lex.cpp)
add_flex_bison_dependency(Scanner Parser)

add_library(parser STATIC ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS} ast.cpp)