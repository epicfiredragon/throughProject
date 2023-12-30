#include "Solver.h"

class MyArithmeticSolver : public ArithmeticSolver {
public:
    std::string Solve(const std::string &str) override {
        /*
         * TODO : Dima
          * ебани сюда польскую обратную
         */
    }
};

class LibraryArithmeticSolver : public ArithmeticSolver {
public:
    std::string Solve(const std::string &str) override {
        /*
         * TODO : найти библу
         */
    }
};

std::shared_ptr<ArithmeticSolver> ChooseSolver(SolverType typeSolver) {
    switch (typeSolver) {
        case SolverType::My:
            return std::make_shared<MyArithmeticSolver>();
        case SolverType::Library:
            return std::make_shared<LibraryArithmeticSolver>();
    }
}
