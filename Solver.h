#ifndef THROUGH_SOLVER_H
#define THROUGH_SOLVER_H

#include <iostream>
#include <memory>
#include <vector>

enum class SolverType {
    My, Library
};

class ArithmeticSolver {
public:
    virtual std::string Solve(const std::string &) = 0;
};

std::shared_ptr<ArithmeticSolver> ChooseSolver(SolverType typeSolver);

#endif //THROUGH_SOLVER_H
