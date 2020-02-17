cmake_minimum_required(VERSION 2.4)

project(engr659-policy-directory)

include_directories(include)

#set(CMAKE_CXX_CLANG_TIDY
#  clang-tidy;
#  -header-filter=include;
#  -checks=*,-fuchsia-default-arguments,-clang-analyzer-cplusplus.NewDeleteLeaks;
#  -warnings-as-errors=*;
#)

add_executable(tokenize
    src/main.cpp
)

set_property(TARGET tokenize PROPERTY CXX_STANDARD 20)
