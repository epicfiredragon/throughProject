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

TEST_CASE("ProcessAndHandleFile Test", "[ProcessAndHandleFile]") {
    { 
    FileInfo info;
    info.in_file_name = "test_input.txt";  
    info.out_file_name = "test_output.txt";  
    info.in_type = TypeFile::Text;
    info.out_type = TypeFile::Text;
    info.pre_steps = {};  
    info.post_steps = {}; 

    std::ofstream testInput(info.in_file_name);
    if (!testInput.is_open()) {
        FAIL("Failed to create test input file");
    }
    testInput << "444kld5+6" << std::endl;
    testInput.close();

    REQUIRE_NOTHROW(ProcessAndHandleFile(info, SolverType::My));

    std::ifstream testOutput(info.out_file_name);
    if (!testOutput.is_open()) {
        FAIL("Failed to open test output file");
    }

    std::string result;
    std::getline(testOutput, result);
    testOutput.close();

    REQUIRE(result == "444kld11");
    }
    {
        FileInfo info;
        info.in_file_name = "test_input2.txt";  
        info.out_file_name = "test_output2.txt";  
        info.in_type = TypeFile::Text;
        info.out_type = TypeFile::Text;
        info.pre_steps = {};  
        info.post_steps = {};  

       
        std::ofstream testInput(info.in_file_name);
        if (!testInput.is_open()) {
            FAIL("Failed to create test input file");
        }
        testInput << "3+5*2" << std::endl;
        testInput.close();

        
        REQUIRE_NOTHROW(ProcessAndHandleFile(info, SolverType::My));

        
        std::ifstream testOutput(info.out_file_name);
        if (!testOutput.is_open()) {
            FAIL("Failed to open test output file");
        }

        std::string result;
        std::getline(testOutput, result);
        testOutput.close();

        
        REQUIRE(result == "13");
    }
    {
        
        FileInfo info;
        info.in_file_name = "test_input2.txt";  
        info.out_file_name = "test_output2.txt";  
        info.in_type = TypeFile::Text;
        info.out_type = TypeFile::Text;
        info.pre_steps = {};  
        info.post_steps = {};  

         std::ofstream testInput(info.in_file_name);
        if (!testInput.is_open()) {
            FAIL("Failed to create test input file");
        }
        testInput << "ff" << std::endl;
        testInput.close();

        
        REQUIRE_NOTHROW(ProcessAndHandleFile(info, SolverType::My));

        
        std::ifstream testOutput(info.out_file_name);
        if (!testOutput.is_open()) {
            FAIL("Failed to open test output file");
        }

        std::string result;
        std::getline(testOutput, result);
        testOutput.close();

        
        REQUIRE(result == "ff");
    }
}


