#include "catch2/catch_test_macros.hpp"
#include "Solver.h"

TEST_CASE("Test1") {
    auto solver_type = SolverType::My;
    auto solver = ChooseSolver(solver_type);
    REQUIRE(solver->Solve("5+1") == "6");
}

TEST_CASE("Test2") {
    auto solver_type = SolverType::My;
    auto solver = ChooseSolver(solver_type);
    REQUIRE(solver->Solve("(2+25*2-1^0)/2") == "25.500000");
}

TEST_CASE("Test3") {
    auto solver_type = SolverType::My;
    auto solver = ChooseSolver(solver_type);
    REQUIRE(solver->Solve("1/0") == "inf");
}

TEST_CASE("Test4") {
    auto solver_type = SolverType::My;
    auto solver = ChooseSolver(solver_type);
    REQUIRE(solver->Solve("5-10") == "-5");
}

TEST_CASE("Test5") {
    auto solver_type = SolverType::My;
    auto solver = ChooseSolver(solver_type);
    REQUIRE(solver->Solve("2147483646+1") == "2147483647");
}