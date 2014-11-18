#include "CmdInterpreter.h"
#include <iostream> //for NULL
using namespace std;

// Static stuff
CmdInterpreter *CmdInterpreter::instance = NULL; //by default

void CmdInterpreter::cleanup() {
    delete instance;
}

void CmdInterpreter::getInstance() {
    if(!instance) {
        instance = new CmdInterpreter();
        atexit(cleanup);
    }
    return instance;
}


// Methods
CmdInterpreter::CmdInterpreter() :
    isFinished(false),
    shouldRestart(false),
    floor(NULL),
    player(NULL),
    state(0) {}


CmdInterpreter::~CmdInterpreter() {
    delete floor;
    delete player;
}

void CmdInterpreter::start() {
    string cmd;
    while(!isFinished && cin >> cmd) {
        executeCmd(cmd);
    }
    if(shouldRestart) {
        //TODO: restart shit
    } //TODO: else, just exit the game
}

void CmdInterpreter::end() {
    isFinished = true;
}

void CmdInterpreter::restart() {
    shouldRestart = true;
    end();
}

void CmdInterpreter::executeCmd(string cmd) {
    if(state == 1) {
        if(cmd == "u") {
            string dir;
            cin >> dir;
            //TODO: move player in that dir
        } else if(cmd == "a") {
            string dir;
            cin >> dir;
            //TODO: attack character in that dir
        } else if(cmd == "r") {
            restart();
        }
    } else {
        if(cmd == "s" || cmd == "d" || cmd == "v" || cmd == "g" || cmd == "t") {
            //create new player with race corresponding to cmd
        }
    }
}
