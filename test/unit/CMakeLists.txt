add_executable(unit_catch2
    catch2.cpp
)

add_executable(unittest_cppstandard
    cppstandard.cpp
)

add_executable(unittest_buildVectors
    buildVectors.cpp
    ../../src/corpus.cpp
    ../../src/document.cpp
)

target_link_libraries(unit_catch2 Catch2)
target_link_libraries(unittest_cppstandard Catch2)
target_link_libraries(unittest_buildVectors Catch2)

add_test(catch2 unit_catch2)
add_test(cppstandard unittest_cppstandard)
add_test(buildVectors unittest_buildVectors)