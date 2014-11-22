#include "CmdInterpreter.h"
using namespace std;

int main(int argc, char* argv[]) {
    CmdInterpreter * ci = CmdInterpreter::getInstance(argc, argv);
    //TODO: we need to specify the floor file in a cmd line arg so we should pass in cmd line args into start()
    ci->start(); //terminates when game is done
    // TODO: do we need to delete a singleton or does atexit() cover that??
    cout << "Game exited: thanks for playing!" << endl;
}