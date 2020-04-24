cmake_minimum_required(VERSION 2.4)

project(engr659-policy-directory)

include_directories(include)

include(UseLATEX.cmake)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#enable_testing()

#set(CMAKE_CXX_CLANG_TIDY
#  clang-tidy;
#  -fix;
#  -header-filter=include;
#  -checks=*,-fuchsia-default-arguments,-fuchsia-default-arguments-calls,-fuchsia-trailing-return,-clang-analyzer-cplusplus.NewDeleteLeaks;
#  -warnings-as-errors=*;
#)

add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(test)