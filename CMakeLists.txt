cmake_minimum_required(VERSION 3.15.3)
project(ParserGenerator)

set(CMAKE_CXX_STANDARD 14)

add_executable(ParserGenerator main.cpp CFGFileParser.cpp CFGFileParser.h AmbiguitySolver.cpp AmbiguitySolver.h FollowSetGenerator.cpp FollowSetGenerator.h FirstSetGenerator.cpp FirstSetGenerator.h)