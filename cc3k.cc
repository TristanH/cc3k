#include "CmdInterpreter.h"
using namespace std;

int main(int argc, char* argv[]) {
    CmdInterpreter ci;
    //TODO: we need to specify the floor file in a cmd line arg so we should pass in cmd line args into start()
    ci.start(); //terminates when game is done
    cout << "Game exited: thanks for playing!" << endl;
}