#include <iostream>
#include "SolverType.h"
#include "ProcessAndHandleFile.h"

enum class ApplicationType {
    CMD, UI, WEB
};

const ApplicationType typeApp = ApplicationType::CMD;
const SolverType typeSolver = SolverType::My;

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
