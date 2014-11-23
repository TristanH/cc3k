#include "CmdInterpreter.h"

#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
	vector<string> args(argv, argv + argc);
    CmdInterpreter * ci = CmdInterpreter::getInstance(args);
    ci->start(); //terminates when game is done
    // TODO: do we need to delete a singleton or does atexit() cover that??
    cout << "Game exited: thanks for playing!" << endl;
}