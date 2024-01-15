#include "Solver.h"
#include <cmath>
#include <stack>
#include <string>

int getPriority(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0; 
}

std::string applyOperation(const std::string& a, const std::string& b, char op) {
    double operand1 = stod(a);
    double operand2 = stod(b);
    double result;

    switch (op) {
        case '+': result = operand1 + operand2; break;
        case '-': result = operand1 - operand2; break;
        case '*': result = operand1 * operand2; break;
        case '/': result = operand1 / operand2; break;
        case '^': result = pow(operand1, operand2); break;
        default: return a + op + b;
    }

    if (result == floor(result)) {
        return std::to_string(static_cast<int>(result));
    } else {
        return std::to_string(result);
    }
}

std::string evaluateExpression(const std::string& expression) {
    std::stack<std::string> values;
    std::stack<char> operators;

    for (char token : expression) {
        if (isdigit(token)) {
            values.push(std::string(1, token));
        } else if (token == '(') {
            operators.push(token);
        } else if (token == ')') {
            while (!operators.empty() && operators.top() != '(') {
                std::string b = values.top(); values.pop();
                std::string a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOperation(a, b, op));
            }
            operators.pop(); 
        } else {
            while (!operators.empty() && getPriority(operators.top()) >= getPriority(token)) {
                std::string b = values.top(); values.pop();
                std::string a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOperation(a, b, op));
            }
            operators.push(token); 
        }
    }

    while (!operators.empty()) {
        std::string b = values.top(); values.pop();
        std::string a = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        values.push(applyOperation(a, b, op));
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
    }
}
