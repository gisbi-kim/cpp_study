cmake_minimum_required(VERSION 3.26)
project(my_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(main hello.cpp main.cpp)
target_compile_features(main PRIVATE cxx_std_20)
target_compile_options(main PRIVATE -fmodules-ts)
