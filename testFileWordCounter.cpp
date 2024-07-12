#define CATCH_CONFIG_MAIN
#include <string>
#include <exception>
#include <stdexcept>
#include "catch.hpp"
#include "fileWordCounter.hpp"

TEST_CASE("Using FileWordCounter to count words from \"testFile.txt\"", "[count]") {
    FileWordCounter fwc("testFile.txt");

    CHECK(fwc.totalWordsCounted() == 29);

    // Based on list from https://en.wikipedia.org/wiki/Punctuation
    SECTION("Checking certain characters are ignored") {
        CHECK(fwc.count("'") == 0);
        CHECK(fwc.count("\"") == 0);
        CHECK(fwc.count("!") == 0);
        CHECK(fwc.count("?") == 0);
        CHECK(fwc.count(",") == 0);
        CHECK(fwc.count(".") == 0);
        CHECK(fwc.count("(") == 0);
        CHECK(fwc.count(")") == 0);
        CHECK(fwc.count("[") == 0);
        CHECK(fwc.count("]") == 0);
        CHECK(fwc.count("{") == 0);
        CHECK(fwc.count("}") == 0);
        CHECK(fwc.count("<") == 0);
        CHECK(fwc.count(">") == 0);
        CHECK(fwc.count("_") == 0);
        CHECK(fwc.count("/") == 0);
        CHECK(fwc.count(":") == 0);
        CHECK(fwc.count(";") == 0);
    }

    SECTION("Checking word frequencies are counted correctly") {
        CHECK(fwc.count("0") == 1);
        CHECK(fwc.count("12") == 1);
        CHECK(fwc.count("345") == 1);
        CHECK(fwc.count("6789") == 1);

        CHECK(fwc.count("abcdefg") == 2);
        CHECK(fwc.count("hijklmnop") == 2);
        CHECK(fwc.count("qrs") == 2);
        CHECK(fwc.count("tuv") == 2);
        CHECK(fwc.count("wx") == 2);
        CHECK(fwc.count("yz") == 2);

        CHECK(fwc.count("she") == 1);
        CHECK(fwc.count("will") == 1);
        CHECK(fwc.count("shell") == 2);

        CHECK(fwc.count("solar-powered") == 1);
        CHECK(fwc.count("solar") == 2);
        CHECK(fwc.count("powered") == 2);

        CHECK(fwc.count("hello") == 5);

        CHECK(fwc.count("integer") == 6);
        CHECK(fwc.count("long") == 6);
        CHECK(fwc.count("float") == 7);
        CHECK(fwc.count("double") == 7);

        CHECK(fwc.count("the") == 19);
        CHECK(fwc.count("quick") == 17);
        CHECK(fwc.count("brown") == 17);
        CHECK(fwc.count("fox") == 14);
        CHECK(fwc.count("jumped") == 13);
        CHECK(fwc.count("over") == 11);
        CHECK(fwc.count("lazy") == 10);
        CHECK(fwc.count("dog") == 9);
    }
}

TEST_CASE("Using FileWordCounter on \"testFile.txt\" to get the top N most used words", "[rank]") {
    FileWordCounter fwc("testFile.txt");

    SECTION("Checking the top 10 most used words (in decending order)") {
        std::vector<FWCPair> top10 = fwc.topNWords(10);

        CHECK_FALSE(top10.empty());
        CHECK(top10.size() == 13);

        std::vector<FWCPair>::iterator it = top10.begin();
        CHECK(it->first == "the"); CHECK(it->second == 19); it++;    // 1
        CHECK(it->first == "brown"); CHECK(it->second == 17); it++;  // 2
        CHECK(it->first == "quick"); CHECK(it->second == 17); it++;  // 2
        CHECK(it->first == "fox"); CHECK(it->second == 14); it++;    // 3
        CHECK(it->first == "jumped"); CHECK(it->second == 13); it++; // 4
        CHECK(it->first == "over"); CHECK(it->second == 11); it++;   // 5
        CHECK(it->first == "lazy"); CHECK(it->second == 10); it++;   // 6
        CHECK(it->first == "dog"); CHECK(it->second == 9); it++;     // 6
        CHECK(it->first == "double"); CHECK(it->second == 7); it++;  // 8
        CHECK(it->first == "float"); CHECK(it->second == 7); it++;   // 8
        CHECK(it->first == "integer"); CHECK(it->second == 6); it++; // 9
        CHECK(it->first == "long"); CHECK(it->second == 6); it++;    // 9
        CHECK(it->first == "hello"); CHECK(it->second == 5); it++;   // 10
    }
}

TEST_CASE("Checking exceptions thrown by FileWordCounter", "[exception]") {
    REQUIRE_THROWS_AS(FileWordCounter("nonExistentFile.txt"), std::runtime_error);
}
