#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "File.hpp"

TEST_CASE( "String Streams handled correctly", "[File]" ) {
    REQUIRE( File::streamContentToWString(new std::wistringstream(L"")) == L"" );
    REQUIRE( File::streamContentToWString(new std::wistringstream(L"Cats are cool")) == L"Cats are cool" );
}

TEST_CASE( "File Streams handled correctly", "[File]") {
    REQUIRE( File::streamContentToWString(new std::wifstream("../data/corpus-metadata.csv")) ==
        std::wstring(
            L"10643075_active_20070313.txt 10643075\n"
            L"10643076_active_20060117.txt 10643076\n"
            L"10643077_active_20151012.txt 10643077\n"
            L"10643078_active_20100303.txt 10643078\n"
        )
    );
}