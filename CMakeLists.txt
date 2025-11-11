cmake_minimum_required(VERSION 3.28)
project(CSV_Editor_For_MZ_Matcher_Results)

set(CMAKE_CXX_STANDARD 20)

add_executable(CSV_Editor_For_MZ_Matcher_Results main.cpp
        CSV_Editor.cpp
        CSV_Editor.h)
