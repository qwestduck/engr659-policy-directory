cmake_minimum_required(VERSION 2.4)

project(engr659-policy-directory)

include_directories(include)

#set(CMAKE_CXX_CLANG_TIDY
#  clang-tidy;
#  -header-filter=include;
#  -checks=*,-fuchsia-default-arguments,-clang-analyzer-cplusplus.NewDeleteLeaks;
#  -warnings-as-errors=*;
#)

include(CheckCXXSourceCompiles)
set(CMAKE_REQUIRED_FLAGS "-std=c++2a")
check_cxx_source_compiles(
    "
    #include <set>

    int main() {
        std::set<int> a;
        a.contains(0);

        return 0;
    }"

    HAVE_SETCONTAINS
)

add_executable(stats
    src/main.cpp
)

add_executable(perftest_tokenizer
    test/perf/tokenizer.cpp
)

add_executable(unittest_cppstandard
    test/unit/cppstandard.cpp
)

set(CMAKE_BUILD_TYPE Debug)

set_property(TARGET stats PROPERTY CXX_STANDARD 20)
set_property(TARGET perftest_tokenizer PROPERTY CXX_STANDARD 20)
set_property(TARGET unittest_cppstandard PROPERTY CXX_STANDARD 20)
