#include "CmdInterpreter.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
	vector<string> args(argv, argv + argc);
    CmdInterpreter * ci = CmdInterpreter::getInstance(args);
    ci->setMapFile("maps/full_map.data"); // TODO: replace with cmd line args
    #ifdef DEBUG
    cout << "cc3k.cc: instance of CmdInterpreter created; starting game..." << endl;
    #endif
    ci->start(); //terminates when game is done
}