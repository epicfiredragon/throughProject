#include <iostream>
#include <memory>
#include <vector>
#include "Writer.h"
#include "Reader.h"
#include "Solver.h"
#include "FileInfo.h"

enum class ApplicationType {
    CMD, UI, WEB
};

enum class SolverType {
    My, Library
};

const ApplicationType typeApp = ApplicationType::CMD;
const SolverType typeSolver = SolverType::My;

class ArithmeticSolver {
public:
    virtual std::string Solve(const std::string &) = 0;
};

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

struct markedSubstring {
    std::string str;
    bool is_arithmetic = false;
};

std::vector<markedSubstring> MarkArithmetic(const std::string &str) {
    /*
    * TODO : Dima
     * эта хуйня должна бить строку в подстроки, если это выражение, то кидай подстроку в структуру и ставь тру в is_arithmetic
    */
}

void
HandleProcessedFile(const std::shared_ptr<Reader> &reader, const std::shared_ptr<Writer> &writer,
                    const std::shared_ptr<ArithmeticSolver> &solver) {
    while (!reader->IsEnd()) {
        auto marked_substrings = MarkArithmetic(reader->ReadNextLine());
        /*
         * TODO : exceptions
         */
        std::string handled_string;
        for (const auto &i: marked_substrings) {
            if (i.is_arithmetic) {
                handled_string += solver->Solve(i.str);
            } else {
                handled_string += i.str;
            }
        }
        writer->WriteLine(handled_string);
    }
}

std::shared_ptr<ArithmeticSolver> ChooseSolver() {
    switch (typeSolver) {
        case SolverType::My:
            return std::make_shared<MyArithmeticSolver>();
        case SolverType::Library:
            return std::make_shared<LibraryArithmeticSolver>();
    }
}

void ProcessAndHandleFile(const FileInfo &info) {

    HandleProcessedFile(ChooseReader(info.in_type, info.in_file_name),
                        ChooseWriter(info.out_type, info.out_file_name), ChooseSolver());
}

void mainCMD() {
    FileInfo info;
    /*
     * TODO : Dima
      * напиши тут ввод с консоли всей херни (имя вход выход, тип вход выход, как шифровали/архивировали, как надо на выходе)
      * и собери в FileInfo
     */
    ProcessAndHandleFile(info);
}

void mainUI() {

}

void mainWEB() {

}

int main() {
    switch (typeApp) {
        case ApplicationType::CMD:
            mainCMD();
            break;
        case ApplicationType::UI:
            mainUI();
            break;
        case ApplicationType::WEB:
            mainWEB();
            break;
    }
}
