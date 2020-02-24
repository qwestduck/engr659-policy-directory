cmake_minimum_required(VERSION 2.4)

project(engr659-policy-directory)

include_directories(include)

#set(CMAKE_CXX_CLANG_TIDY
#  clang-tidy;
#  -header-filter=include;
#  -checks=*,-fuchsia-default-arguments,-fuchsia-default-arguments-calls,-fuchsia-trailing-return,-clang-analyzer-cplusplus.NewDeleteLeaks;
#  -warnings-as-errors=*;
#)

include(UseLATEX.cmake)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

## Feature testing
#include(CheckCXXSourceCompiles)
#set(CMAKE_REQUIRED_FLAGS "-std=c++17")

#check_cxx_source_compiles(
#    "
#    #include <set>
#
#    int main() {
#        std::set<int> a;
#        a.contains(0);
#
#        return 0;
#    }"
#
#    HAVE_SETCONTAINS
#)

add_executable(stats
    src/main.cpp
    src/corpus.cpp
    src/document.cpp
)

add_executable(perftest_tokenizer
    test/perf/tokenizer.cpp
    src/corpus.cpp
    src/document.cpp
)

add_executable(unittest_cppstandard
    test/unit/cppstandard.cpp
)

add_latex_document(doc/assignment-template.tex)
