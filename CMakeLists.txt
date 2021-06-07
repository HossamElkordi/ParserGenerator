cmake_minimum_required(VERSION 3.15.3   )
project(ParserGenerator)

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(ParserGenerator main.cpp CFGFileParser.cpp CFGFileParser.h AmbiguitySolver.cpp AmbiguitySolver.h FollowSetGenerator.cpp FollowSetGenerator.h FirstSetGenerator.cpp FirstSetGenerator.h TableGenerator.cpp TableGenerator.h InputChecker.cpp InputChecker.h LexicalAnalyzer.cpp LexicalAnalyzer.h)

include(FindPkgConfig)
find_package(LexicalAnalyzerGenerator REQUIRED)
include_directories(${LEXICALANALYZERGENERATOR_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${LEXICALANALYZERGENERATOR_LIBRARY})