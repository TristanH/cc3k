#include "CmdInterpreter.h"
#include "Die.h"
#include <iostream> //for NULL
#include <string>
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
    }
}

void CmdInterpreter::end() {
    isFinished = true;
}

void CmdInterpreter::restart() {
    shouldRestart = true;
    end();
}

void CmdInterpreter::printLog(string str) {
    // TODO: we should figure out how to make this always print in a designated area underneath the game display
    cout << str << endl; 
}

void CmdInterpreter::executeCmd(string cmd) {
    if(state == 1) {
        if(cmd == "u") {
            string dir;
            cin >> dir;
            //TODO: pickup thing in that dir
        } else if(cmd == "a") {
            string dir;
            cin >> dir;
            Cell *otherCell = player->cell->getAdjacentCell(dir);
            Entity *otherEntity = otherCell->getEntity();
            player->fight(otherEntity); // At this point we know     
        } else if(cmd == "r") {
            restart();
        } else if(Cell::isValidDirection(cmd)) {
            player->move(cmd);
        }
    } else {
        if(cmd == "s" || cmd == "d" || cmd == "v" || cmd == "g" || cmd == "t") {
            // generate the first floor
            // create new player with race corresponding to cmd

            // generating/populating floor 
            Die spawnDie(18); 

            // Initialize the probability mapping. mapping[X][0]->numerator, mapping[X][1]->denominator
            // TODO: read in cmd line argument for file to override the mapping if
            spawnDie.addSides(4, 'H');
            spawnDie.addSides(3, 'D');
            spawnDie.addSides(5, 'L');
            spawnDie.addSides(2, 'E');
            spawnDie.addSides(2, 'O');
            spawnDie.addSides(2, 'M');


            floor = new Floor();
            floor->setSpawnRates(mapping);
            floor->populate();

            //creating player
            player = getInstance(cmd);
        }
    }
    floor->updateGameStep();
}
