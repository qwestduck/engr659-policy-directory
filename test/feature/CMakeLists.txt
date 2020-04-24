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