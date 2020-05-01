add_executable(perftest_tokenizer
    tokenizer.cpp
    ../../src/corpus.cpp
    ../../src/document.cpp
    ../../src/file.cpp
)

target_link_libraries(perftest_tokenizer Catch2)

add_test(tokenizer perftest_tokenizer)