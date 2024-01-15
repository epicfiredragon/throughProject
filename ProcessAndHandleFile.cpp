#include "ProcessAndHandleFile.h"
#include <memory>
#include <vector>
#include <regex>
#include "Writer.h"
#include "Reader.h"
#include "Solver.h"
#include "FileInfo.h"
#include "FileProcessor.h"

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
    std::vector<std::string> temp;
    std::int64_t mx = -1;
    for(std::int64_t i = 0 ; i < str.size() ; i++){
        for(std::int64_t j = 1 ; j <= str.size() - i ; j++){
            if(isValidExpression(str.substr(i , j)))mx = j;
        }
        if(mx != -1){
            temp.push_back(str.substr(i , mx));
            if(i + mx >= str.size())break;
            i += mx;
        }
        mx = -1;
    }
    std::int64_t k = 0 , t = 0;
    std::vector<std::string> ans;
    std::vector<bool> q;
    bool flag = false;
    for(std::int64_t i = 0 ; i < str.size() ; i++){
        if(str.substr(i , temp[t].size()) == temp[t]){
           markedSubstring(str.substr(k , i - k + 1) , false);
           k = i;
           markedSubstring(str.substr(i , temp[t].size()) , true);
           if(i + temp[t].size() >= str.size()){
              flag = true;
              break;
           }
           i += temp[t].size();
           t++;
        }
    }
    if(!flag){
       markedSubstring(str.substr(k + temp.back().size() + 1 , str.size() - k + 1) , false);
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
    for (const auto &processor_step: info.pre_steps) {
        ChooseFileProcessor(processor_step)->Process(info.in_file_name);
    }
    HandleProcessedFile(ChooseReader(info.in_type, info.in_file_name),
                        ChooseWriter(info.out_type, info.out_file_name), ChooseSolver(typeSolver));
    for (const auto &processor_step: info.post_steps) {
        ChooseFileProcessor(processor_step)->Process(info.out_file_name);
    }
}
