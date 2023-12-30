#include <iostream>
#include <memory>
#include <vector>
#include "Writer.h"
#include "Reader.h"
#include "Solver.h"
#include "FileInfo.h"
#include "FileProcessor.h"

enum class ApplicationType {
    CMD, UI, WEB
};

const ApplicationType typeApp = ApplicationType::CMD;
const SolverType typeSolver = SolverType::My;

struct markedSubstring {
    std::string str;
    bool is_arithmetic = false;
};

std::vector<markedSubstring> MarkArithmetic(const std::string &str) {
    /*
    * TODO : Dima
     * эта хуйня должна бить строку в подстроки, если это выражение, то кидай подстроку в структуру и ставь тру в is_arithmetic, иначе просто кидай
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

void ProcessAndHandleFile(const FileInfo &info, SolverType typeSolver) {
    for (const auto& processor_step : info.pre_steps) {
        ChooseFileProcessor(processor_step)->Process(info.in_file_name);
    }
    HandleProcessedFile(ChooseReader(info.in_type, info.in_file_name),
                        ChooseWriter(info.out_type, info.out_file_name), ChooseSolver(typeSolver));
    for (const auto& processor_step : info.post_steps) {
        ChooseFileProcessor(processor_step)->Process(info.out_file_name);
    }
}

void mainCMD() {
    FileInfo info;
    /*
     * TODO : Dima
      * напиши тут ввод с консоли всей херни (имя вход выход, тип вход выход, как шифровали/архивировали, как надо на выходе)
      * и собери в FileInfo info
      * еще дай чек на несовпадение имен
     */
    ProcessAndHandleFile(info, typeSolver);
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
