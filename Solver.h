#ifndef THROUGH_SOLVER_H
#define THROUGH_SOLVER_H

#include <iostream>
#include <memory>
#include <vector>
#include "SolverType.h"

class ArithmeticSolver {
public:
    virtual std::string Solve(const std::string &) = 0;
};

std::shared_ptr<ArithmeticSolver> ChooseSolver(SolverType typeSolver);

#endif //THROUGH_SOLVER_H
