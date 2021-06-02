cmake_minimum_required(VERSION 3.19)
project(ParserGenerator)

set(CMAKE_CXX_STANDARD 14)

add_executable(ParserGenerator main.cpp CFGFileParser.cpp CFGFileParser.h AmbiguitySolver.cpp AmbiguitySolver.h)