#include "catch2/catch_test_macros.hpp"
#include "Solver.h"

TEST_CASE("Simple") {
    auto solver_type = SolverType::My;
    auto solver = ChooseSolver(solver_type);
    REQUIRE(solver->Solve("25+25") == "50");
    REQUIRE(solver->Solve("599+6666") == "154");
}
