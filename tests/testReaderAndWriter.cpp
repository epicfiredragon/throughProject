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
    std::shared_ptr<Reader> reader = ChooseReader(TypeFile::Text , input);
     
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
   
    std::shared_ptr<Writer> writer = ChooseWriter(TypeFile::Text , output);
     
    SECTION("WriteLine()") {
        writer->WriteLine("Line 1");
        writer->WriteLine("Line 2");
        writer->WriteLine("Line 3");

        std::string expectedOutput = "Line 1\nLine 2\nLine 3\n";
        REQUIRE(output.str() == expectedOutput);
    }
}
TEST_CASE("XmlReader Test", "[XmlReader]") {
    std::istringstream input("<xml>\n<a>aa</a>\n<b>55+99</b>\n<c>599+6666</c>\n<d>hsdjhjsjds</d>\n</xml>");
    std::shared_ptr<Reader> reader = ChooseReader(TypeFile::XML, input);

    SECTION("ReadNextNode()") {
        REQUIRE(reader->ReadNextLine() == "aa");
        REQUIRE(reader->ReadNextLine() == "55+99");
        REQUIRE(reader->ReadNextLine() == "599+6666");
        REQUIRE(reader->ReadNextLine() == "hsdjhjsjds");
    }

    SECTION("IsEnd()") {
        REQUIRE_FALSE(reader->IsEnd());

        while (!reader->IsEnd()) {
            reader->ReadNextLine();
        }
        REQUIRE(reader->IsEnd());
    }
}

TEST_CASE("XmlWriter Test", "[XmlWriter]") {

    SECTION("WriteNode()") {
        std::ostringstream output;
        std::shared_ptr<Writer> writer = ChooseWriter(TypeFile::XML, output);
        writer->WriteLine("aa");
        writer->WriteLine("55+99");
        writer->WriteLine("599+6666");
        writer->WriteLine("hsdjhjsjds");
        writer.reset();


        std::string expectedOutput = "<xml>\n<res>aa</res>\n<res>55+99</res>\n<res>599+6666</res>\n<res>hsdjhjsjds</res>\n</xml>\n";
        REQUIRE(output.str() == expectedOutput);
    }
}

TEST_CASE("JsonReader Test", "[JsonReader]") {
    std::istringstream input(R"(["aa","55+99","599+6666","hsdjhjsjds"])");
    std::shared_ptr<Reader> reader = ChooseReader(TypeFile::JSON, input);

    SECTION("ReadNextNode()") {
        REQUIRE(reader->ReadNextLine() == "aa");
        REQUIRE(reader->ReadNextLine() == "55+99");
        REQUIRE(reader->ReadNextLine() == "599+6666");
        REQUIRE(reader->ReadNextLine() == "hsdjhjsjds");
    }

    SECTION("IsEnd()") {
        REQUIRE_FALSE(reader->IsEnd());
        while (!reader->IsEnd()) {
            reader->ReadNextLine();
        }
        REQUIRE(reader->IsEnd());
    }
}

TEST_CASE("JsonWriter Test", "[JsonWriter]") {
    SECTION("WriteNode()") {
        std::ostringstream output;
        std::shared_ptr<Writer> writer = ChooseWriter(TypeFile::JSON, output);
        writer->WriteLine("aa");
        writer->WriteLine("55+99");
        writer->WriteLine("599+6666");
        writer->WriteLine("hsdjhjsjds");
        std::cout << output.str();
        writer.reset();

        std::string expectedOutput = R"(["aa","55+99","599+6666","hsdjhjsjds"])";
        REQUIRE(output.str() == expectedOutput);
    }
}


