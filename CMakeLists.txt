cmake_minimum_required(VERSION 3.21.2)
project(nsh VERSION 1.0 LANGUAGES CXX)

add_executable(main src/main.cpp)
add_library(lib STATIC 
    src/builtins.cpp 
    src/executer.cpp 
    src/main.cpp 
    src/parser.cpp
    src/support.cpp
    )

target_compile_options(lib PRIVATE -Wall)
target_compile_options(main PRIVATE -Wall -O2)
target_compile_features(lib PUBLIC cxx_std_17)

target_link_libraries(main PRIVATE lib)
target_include_directories(main PRIVATE include)
target_include_directories(lib PUBLIC include)
