#include <iostream>
#include "SolverType.h"
#include "ProcessAndHandleFile.h"
#include "FileInfo.h"
#include "exeptions.h"

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
    /*
     * TODO : Dima
      * напиши тут ввод с консоли всей херни (имя вход выход, тип вход выход, как шифровали/архивировали, как надо на выходе)
      * и собери в FileInfo info
      * еще дай чек на несовпадение имен
     */
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
