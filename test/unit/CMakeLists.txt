add_executable(unittest_cppstandard
    EXCLUDE_FROM_ALL
    cppstandard.cpp
)

add_executable(unittest_buildVectors
    EXCLUDE_FROM_ALL
    buildVectors.cpp
    ../../src/corpus.cpp
    ../../src/document.cpp
)

add_dependencies(test unittest_cppstandard unittest_buildVectors)