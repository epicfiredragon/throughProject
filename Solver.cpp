#include "Solver.h"
#include <cmath>
#include <stack>
#include <string>

int getPriority(char operand) {
    switch (operand) {
        case '^' :
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

std::string applyOperation(const std::string &first, const std::string &second, char operand) {
    double operand1 = stod(first);
    double operand2 = stod(second);
    double result;

    switch (operand) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            result = operand1 / operand2;
            break;
        case '^':
            result = pow(operand1, operand2);
            break;
        default:
            return first + operand + second;
    }

    if (result == floor(result)) {
        return std::to_string(static_cast<int>(result));
    } else {
        return std::to_string(result);
    }
}

std::string evaluateExpression(const std::string &expression) {
    std::stack<std::string> values;
    std::stack<char> operators;

    for (char token: expression) {
        if (isdigit(token)) {
            values.emplace(1, token);
        } else if (token == '(') {
            operators.push(token);
        } else if (token == ')') {
            while (!operators.empty() && operators.top() != '(') {
                std::string second = values.top();
                values.pop();
                std::string first = values.top();
                values.pop();
                char operand = operators.top();
                operators.pop();
                values.push(applyOperation(first, second, operand));
            }
            operators.pop();
        } else {
            while (!operators.empty() && getPriority(operators.top()) >= getPriority(token)) {
                std::string second = values.top();
                values.pop();
                std::string first = values.top();
                values.pop();
                char operand = operators.top();
                operators.pop();
                values.push(applyOperation(first, second, operand));
            }
            operators.push(token);
        }
    }

    while (!operators.empty()) {
        std::string second = values.top();
        values.pop();
        std::string first = values.top();
        values.pop();
        char operand = operators.top();
        operators.pop();
        values.push(applyOperation(first, second, operand));
    }
    return values.top();
}


class MyArithmeticSolver : public ArithmeticSolver {
public:
    std::string Solve(const std::string &str) override {
        return evaluateExpression(str);
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
        default:
            throw std::system_error();
    }
}
