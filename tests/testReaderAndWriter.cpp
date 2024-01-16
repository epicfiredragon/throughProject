#include "catch2/catch_test_macros.hpp"
#include "ProcessAndHandleFile.h"
#include "exeptions.h"
#include <memory>
#include <utility>
#include <vector>
#include <regex>
#include "Writer.h"
#include "Reader.h"
#include "Solver.h"
#include "FileInfo.h"
#include "FileProcessor.h"
#include "key.h"
#include "TypeFile.h"
#include <Poco/StreamCopier.h>
#include <sstream>
#include <fstream>

TEST_CASE("TextReader Test", "[TextReader]") {
    std::istringstream input("Line 1\nLine 2\nLine 3");
    auto reader = std::make_shared<TextReader>(input);

    SECTION("ReadNextLine()") {
        REQUIRE(reader->ReadNextLine() == "Line 1");
        REQUIRE(reader->ReadNextLine() == "Line 2");
        REQUIRE(reader->ReadNextLine() == "Line 3");
    }

    SECTION("IsEnd()") {
        REQUIRE_FALSE(reader->IsEnd());
        reader->ReadNextLine();
        reader->ReadNextLine();
        reader->ReadNextLine();
        REQUIRE(reader->IsEnd());
    }
}


TEST_CASE("TextWriter Test", "[TextWriter]") {
    std::ostringstream output;
    auto writer = std::make_shared<TextWriter>(output);

    SECTION("WriteLine()") {
        writer->WriteLine("Line 1");
        writer->WriteLine("Line 2");
        writer->WriteLine("Line 3");

        std::string expectedOutput = "Line 1\nLine 2\nLine 3\n";
        REQUIRE(output.str() == expectedOutput);
    }
}

