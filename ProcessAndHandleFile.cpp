#include "ProcessAndHandleFile.h"
#include "exeptions.h"
#include <memory>
#include <vector>
#include <sstream>
#include <fstream>
#include "Writer.h"
#include "Reader.h"
#include "Solver.h"
#include "FileInfo.h"
#include "FileProcessor.h"
#include <Poco/StreamCopier.h>

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
    std::ifstream in(info.in_file_name, std::ios::binary);
    if (!in.is_open()) {
        throw FileOpenError(info.in_file_name);
    }
    std::stringstream from;
    Poco::StreamCopier::copyStream(in, from);
    std::stringstream to;
    for (const auto &processor_step: info.pre_steps) {
        ChooseFileProcessor(processor_step)->Restep(from);
    }
    HandleProcessedFile(ChooseReader(info.in_type, from),
                        ChooseWriter(info.out_type, to), ChooseSolver(typeSolver));
    for (const auto &processor_step: info.post_steps) {
        ChooseFileProcessor(processor_step)->Step(to);
    }
    std::ofstream out(info.out_file_name, std::ios::binary);
    if (!out.is_open()) {
        throw FileCreationError(info.in_file_name);
    }
    Poco::StreamCopier::copyStream(to, out);
}
