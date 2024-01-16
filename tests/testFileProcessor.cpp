#include "FileProcessor.h"
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

TEST_CASE("ZipFileProcessor Test", "[ZipFileProcessor]") {
    {

        std::stringstream stream;
        stream << "This is a test input for ZipFileProcessor.";
        std::shared_ptr<FileProcessor> zipProcessor = ChooseFileProcessor(FileProcessingStep::Zip);


        REQUIRE_NOTHROW(zipProcessor->Step(stream));
        REQUIRE_NOTHROW(zipProcessor->Restep(stream));


        REQUIRE(stream.str() == "This is a test input for ZipFileProcessor.");
    }
    {

        std::stringstream stream;
        stream << "";
        std::shared_ptr<FileProcessor> zipProcessor = ChooseFileProcessor(FileProcessingStep::Zip);


        REQUIRE_NOTHROW(zipProcessor->Step(stream));
        REQUIRE_NOTHROW(zipProcessor->Restep(stream));


        REQUIRE(stream.str().empty());
    }

}

TEST_CASE("AESFileProcessor Test", "[AESFileProcessor]") {
    {
        std::stringstream stream;
        stream << "This is a test input for AESFileProcessor.";
        std::shared_ptr<FileProcessor> aesProcessor = ChooseFileProcessor(FileProcessingStep::AES);

        REQUIRE_NOTHROW(aesProcessor->Step(stream));
        REQUIRE_NOTHROW(aesProcessor->Restep(stream));

        REQUIRE(stream.str() == "This is a test input for AESFileProcessor.");
    }
    {
        std::stringstream stream;
        stream << "";
        std::shared_ptr<FileProcessor> aesProcessor = ChooseFileProcessor(FileProcessingStep::AES);

        REQUIRE_NOTHROW(aesProcessor->Step(stream));
        REQUIRE_NOTHROW(aesProcessor->Restep(stream));

        REQUIRE(stream.str().empty());
    }

}