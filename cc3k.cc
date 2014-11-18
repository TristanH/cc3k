#include "CmdInterpreter.h"
using namespace std;

int main(int argc, char* argv[]) {
    CmdInterpreter ci;
    ci.start(); //terminates when game is done
    cout << "Game exited: thanks for playing!" << endl;
}