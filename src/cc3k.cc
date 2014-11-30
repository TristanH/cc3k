#include "CmdInterpreter.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
	vector<string> args(argv, argv + argc);
    CmdInterpreter * ci = CmdInterpreter::getInstance(args);
    if(argc > 1) ci->setMapFile(argv[1]);
    #ifdef DEBUG
    cout << "cc3k.cc: instance of CmdInterpreter created; starting game..." << endl;
    #endif
    ci->start(); //terminates when game is done
}