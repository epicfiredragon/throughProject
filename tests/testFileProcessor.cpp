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
        
        std::stringstream input;
        input << "This is a test input for ZipFileProcessor.";
        std::shared_ptr<FileProcessor> zipProcessor = ChooseFileProcessor(FileProcessingStep::Zip);

        
        REQUIRE_NOTHROW(zipProcessor->Step(input));

        
        std::stringstream output;
        REQUIRE_NOTHROW(zipProcessor->Restep(output));

        
        REQUIRE(output.str() == "This is a test input for ZipFileProcessor.");
    }
   {
        
        std::stringstream input;
        input << "";
        std::shared_ptr<FileProcessor> zipProcessor = ChooseFileProcessor(FileProcessingStep::Zip);

        
        REQUIRE_NOTHROW(zipProcessor->Step(input));

        
        std::stringstream output;
        REQUIRE_NOTHROW(zipProcessor->Restep(output));

        
        REQUIRE(output.str() == "");
    }
    
}

TEST_CASE("AESFileProcessor Test", "[AESFileProcessor]") {
    {
        std::stringstream input;
        input << "This is a test input for AESFileProcessor.";
        std::shared_ptr<FileProcessor> aesProcessor = ChooseFileProcessor(FileProcessingStep::AES);

        REQUIRE_NOTHROW(aesProcessor->Step(input));

        std::stringstream output;
        REQUIRE_NOTHROW(aesProcessor->Restep(output));

        REQUIRE(output.str() == "This is a test input for AESFileProcessor.");
    }
    {
        std::stringstream input;
        input << "";
        std::shared_ptr<FileProcessor> aesProcessor = ChooseFileProcessor(FileProcessingStep::AES);

        REQUIRE_NOTHROW(aesProcessor->Step(input));

        std::stringstream output;
        REQUIRE_NOTHROW(aesProcessor->Restep(output));

        REQUIRE(output.str() == "");
    }

}