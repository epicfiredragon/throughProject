#include "ProcessAndHandleFile.h"
#include "exeptions.h"
#include <memory>
#include <utility>
#include <vector>
#include <regex>
#include "Writer.h"
#include "Reader.h"
#include "Solver.h"
#include "FileInfo.h"
#include "FileProcessor.h"
#include "key.h"
#include "TypeFile.h"
#include <Poco/StreamCopier.h>
#include <sstream>
#include <fstream>

struct markedSubstring {
    std::string str;

    bool is_arithmetic = false;

    explicit markedSubstring(std::string &&s, bool arithmetic = false)
            : str(s), is_arithmetic(arithmetic) {}
};

bool isValidExpression(const std::string &expression) {
    if (expression.size() < 3) {
        return false;
    }

    std::stack<char> parenthesesStack;

    for (char ch: expression) {
        if (std::isdigit(ch) || ch == '*' || ch == '+' || ch == '-' || ch == '/' || ch == '^') {
        } else if (ch == '(') {
            parenthesesStack.push(ch);
        } else if (ch == ')') {
            if (parenthesesStack.empty() || parenthesesStack.top() != '(') {
                return false;
            }
            parenthesesStack.pop();
        } else {
            return false;
        }
    }

    return parenthesesStack.empty() &&
           (std::isdigit(expression.back()) || expression.back() == ')');
}

std::vector<markedSubstring> MarkArithmetic(const std::string &str) {
    std::vector<markedSubstring> ret;
    std::vector<std::string> arithmetic_string;
    for (std::int64_t i = 0; i < str.size(); i++) {
        std::int64_t max_position = -1;
        for (std::int64_t j = 1; j <= str.size() - i; j++) {
            if (isValidExpression(str.substr(i, j))) {
                max_position = j;
            }
        }
        if (max_position != -1) {
            arithmetic_string.push_back(str.substr(i, max_position));
            if (i + max_position >= str.size()) {
                break;
            }
            i += max_position - 1;
        }
    }
    int64_t last_parsed_id = 0;
    size_t last_parsed_char = 0;
    if (arithmetic_string.empty()) {
        ret.emplace_back(str.substr(), false);
        return ret;
    } else {
        for (size_t i = 0; i < str.size(); i++) {
            if (str.substr(i, arithmetic_string[last_parsed_id].size()) ==
                arithmetic_string[last_parsed_id]) {
                ret.emplace_back(str.substr(last_parsed_char, i - last_parsed_char),
                                 false);
                ret.emplace_back(str.substr(i, arithmetic_string[last_parsed_id].size()),
                                 true);

                i += arithmetic_string[last_parsed_id].size();
                last_parsed_char = i;
                last_parsed_id++;
            }
            if (last_parsed_id == arithmetic_string.size()) {
                ret.emplace_back(str.substr(i, str.size() - i),
                                 false);
                break;
            }
        }
        return ret;
    }
}

//дальше не менял
void
HandleProcessedFile(const std::shared_ptr<Reader> &reader, const std::shared_ptr<Writer> &writer,
                    const std::shared_ptr<ArithmeticSolver> &solver) {
    while (!reader->IsEnd()) {
        auto marked_substrings = MarkArithmetic(reader->ReadNextLine());
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
    auto reader = ChooseReader(info.in_type, from);
    auto writer = ChooseWriter(info.out_type, to);
    HandleProcessedFile(reader, writer, ChooseSolver(typeSolver));
    reader.reset();
    writer.reset();
    for (const auto &processor_step: info.post_steps) {
        ChooseFileProcessor(processor_step)->Step(to);
    }
    std::ofstream out(info.out_file_name, std::ios::binary);
    if (!out.is_open()) {
        throw FileCreationError(info.in_file_name);
    }
    Poco::StreamCopier::copyStream(to, out);
}
