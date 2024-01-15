#include "ProcessAndHandleFile.h"
#include "exeptions.h"
#include <memory>
#include <vector>
#include <regex>
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
struct markedSubstring {
      std::string str;
      bool is_arithmetic = false;
       markedSubstring(const std::string& s, bool is_arith) : str(s), is_arithmetic(is_arith) {}
};
bool isValidExpression(const std::string& expression) {
    if(expression.size() < 3){
        return false;
    }
    std::stack<char> parenthesesStack;
    for (char ch : expression) {
        if (std::isdigit(ch) || ch == '*' || ch == '+' || ch == '-' || ch == '/' || ch == '^'){
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
    return parenthesesStack.empty();
}
std::vector<markedSubstring> MarkArithmetic(const std::string &str){
    std::vector<std::string> arithmeticstring;
    std::int64_t mxpos = -1;
    for(std::int64_t i = 0 ; i < str.size() ; i++){
        for(std::int64_t j = 1 ; j <= str.size() - i ; j++){
            if(isValidExpression(str.substr(i , j)))mxpos = j;
        }
        if(mxpos != -1){
            arithmeticstring.push_back(str.substr(i , mxpos));
            if(i + mxpos >= str.size())break;
            i += mxpos;
        }
        mxpos = -1;
    }
    std::int64_t temp = 0;
    mxpos = 0;
    bool badalloc = false;
    for(std::int64_t i = 0 ; i < str.size() ; i++){
        if(str.substr(i , arithmeticstring[temp].size()) == arithmeticstring[t]){
           markedSubstring(str.substr(mxpos , i - mxpos + 1) , false);
           mxpos = i;
           markedSubstring(str.substr(i , arithmeticstring[temp].size()) , true);
           if(i + arithmeticstring[temp].size() >= str.size()){
              badalloc = true;
              break;
           }
           i += arithmeticstring[temp].size();
           temp++;
        }
    }
    if(!badalloc){
       markedSubstring(str.substr(mxpos + arithmeticstring.back().size() + 1 , str.size() - mxpos + 1) , false);
    }
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
