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

TEST_CASE("ArithmeticSolver Test", "[ArithmeticSolver]") {
    std::string inputExpression = "444kld5+6";
    std::string expectedOutput = "444kld11";

    
    auto solver_type = SolverType::My;
    auto solver = ChooseSolver(solver_type);
    std::string result = solver->Solve(inputExpression);

    REQUIRE(result == expectedOutput);
}

