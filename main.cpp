#include <iostream>
#include <Poco/JSON/JSONException.h>
#include <Poco/XML/XMLException.h>
#include "SolverType.h"
#include "ProcessAndHandleFile.h"
#include "FileInfo.h"
#include "exeptions.h"
#include "MagicWiget.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>

enum class ApplicationType {
    CMD, UI
};

const ApplicationType typeApp = ApplicationType::UI;
const SolverType typeSolver = SolverType::Library;

void mainCMD() {
    FileInfo info;
    info.in_file_name = "in.txt";
    info.out_file_name = "out.txt";
    info.in_type = TypeFile::Text;
    info.out_type = TypeFile::Text;
    info.pre_steps.push_back(FileProcessingStep::AES);
    info.post_steps.push_back(FileProcessingStep::Zip);
    
    std::cout << "Name input file : ";
    std::cin >> info.in_file_name;
    std::cout << "Name output file : ";
    std::cin >> info.out_file_name;
    
    std::string typestring;
    std::cout << "Name type of input file : ";
    std::cin >> typestring;
    if(typestring == "Text"){
        info.in_type = TypeFile::Text;
    }
    else{
        if(typestring == "XML") {
            info.in_type = TypeFile::XML;
        }
        else {
           info.in_type = TypeFile::JSON;
        }
    }             
    std::cout << "Name type of output file : ";
    std::cin >> typestring;
    if(typestring == "Text"){
        info.out_type = TypeFile::Text;
    }
    else{
        if(typestring == "XML") {
            info.out_type = TypeFile::XML;
        }
        else {
           if(typestring == "JSON"){
               info.out_type = TypeFile::JSON;
           }
        }
    }
    
    std::vector<std::string> proceestypestrings;
    int count;
    std::cin >> count;
    std::cout << "Name type of input process : ";
    for (int i = 0; i < count; ++i) {

    std::cin >> proceestypestrings[i];
    if(proceestypestrings[i] == "Zip"){
        info.pre_steps.push_back(FileProcessingStep::Zip);
    }
    else{
        if(proceestypestrings[i] == "AES"){
            info.pre_steps.push_back(FileProcessingStep::AES);
        }
    }   
    }
    proceestypestrings.clear();
    std::cout << "Name type of output process : ";
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
       std::cin >> proceestypestrings[i];
    if(proceestypestrings[i] == "Zip"){
        info.post_steps.push_back(FileProcessingStep::Zip);
    }
    else{
        if(proceestypestrings[i] == "AES"){
            info.post_steps.push_back(FileProcessingStep::AES);
        }
    }  
    }
    try {
        ProcessAndHandleFile(info, typeSolver);
    }
    catch (FileOpenError &) {
        std::cout << "No such file";
        std::exit(0);
    }
    catch (FileCreationError &) {
        std::cout << "File creation error";
        std::exit(0);
    }
    catch (BadFileSyntaxError &) {
        std::cout << "Syntax error";
        std::exit(0);
    }
    catch (Poco::JSON::JSONException &) {
        std::cout << "Syntax error";
        std::exit(0);
    }
    catch (Poco::XML::XMLException &) {
        std::cout << "Syntax error";
        std::exit(0);
    }

}

int mainUI() {
    int zero = 0;
    char ** ch;
    QApplication app(zero, ch);

    MagicWidget magicWidget;
    magicWidget.show();

    return app.exec();
}

int main() {
    switch (typeApp) {
        case ApplicationType::CMD:
            mainCMD();
            break;
        case ApplicationType::UI:
            return mainUI();
    }
}
