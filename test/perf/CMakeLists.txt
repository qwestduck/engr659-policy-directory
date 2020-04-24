add_executable(perftest_tokenizer
    EXCLUDE_FROM_ALL
    tokenizer.cpp
    ../../src/corpus.cpp
    ../../src/document.cpp
    ../../src/file.cpp
)

add_dependencies(test perftest_tokenizer)