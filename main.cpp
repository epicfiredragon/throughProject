#include <iostream>
#include <memory>
#include <vector>

class Reader {
public:
    virtual std::string ReadNextLine() = 0;
    virtual bool IsEnd() = 0;
};

class Writer {
public:
    virtual std::string WriteLine(const std::string&) = 0;
};

class ArithmeticSolver {
public:
    virtual std::string Solve(const std::string&) = 0;
};

class MyArithmeticSolver : public ArithmeticSolver {
public:
    std::string Solve(const std::string& str) override {
        /*
         * TODO : Dima
          * ебани сюда польскую обратную
         */
    }
};

struct markedSubstring {
    std::string str;
    bool is_arithmetic = false;
};

std::vector<markedSubstring> MarkArithmetic(const std::string& str) {
    /*
    * TODO : Dima
     * эта хуйня должна бить строку в подстроки, если это выражение, то кидай подстроку в структуру и ставь тру в is_arithmetic
    */
}

void HandleFile(const std::shared_ptr<Reader>& reader, const std::shared_ptr<Writer>& writer, const std::shared_ptr<ArithmeticSolver>& solver) {
    while (!reader->IsEnd()) {
        auto marked_substrings = MarkArithmetic(reader->ReadNextLine());
        std::string handled_string;
        for (const auto& i : marked_substrings) {
            if (i.is_arithmetic) {
                handled_string += solver->Solve(i.str);
            } else {
                handled_string += i.str;
            }
        }
        writer->WriteLine(handled_string);
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
