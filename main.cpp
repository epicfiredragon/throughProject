#include <iostream>
#include <fstream>
#include "SolverType.h"
#include "ProcessAndHandleFile.h"
#include "FileInfo.h"
#include <Poco/Zip/Compress.h>
#include <Poco/StreamCopier.h>
#include <sstream>

enum class ApplicationType {
    CMD, UI, WEB
};

const ApplicationType typeApp = ApplicationType::CMD;
const SolverType typeSolver = SolverType::My;

void mainCMD() {
    FileInfo info;
    info.in_file_name = "in.txt";
    info.out_file_name = "out.txt";
    info.in_type = TypeFile::Text;
    info.out_type = TypeFile::Text;
    info.pre_steps.push_back(FileProcessingStep::Zip);

    std::fstream stream("in.txt");
    std::stringstream zip;
    Poco::Zip::Compress compressor(zip, true);
    std::stringstream from("22 0+5");
    compressor.addFile(from, Poco::DateTime(), Poco::Path(".file"));
    compressor.close();
    stream.clear();
    Poco::StreamCopier::copyStream(zip, stream);
    stream.close();

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
