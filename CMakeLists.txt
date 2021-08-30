cmake_minimum_required(VERSION 3.13)
project(hill_climbing)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES solve.cpp)
install(FILES input.txt DESTINATION ./)

add_executable(solve ${SOURCE_FILES})