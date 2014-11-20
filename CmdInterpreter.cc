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
        bool validCmd = false;
        if(cmd == "u") {
            string dir;
            cin >> dir;
            //TODO: pickup thing in that dir
            cer << "This isn't implemented yet :(" << endl; 
            validCmd = true;
        } else if(cmd == "a") {
            string dir;
            cin >> dir;
            Cell *otherCell = player->cell->getAdjacentCell(dir);
            Entity *otherEntity = otherCell->getEntity();
            player->fight(otherEntity); // At this point we know    
            validCmd = true; 
        } else if(cmd == "r") {
            restart();
            // Don't set validCmd becaues we don't want a game step to happen after we decide to restart
            cer << "This isn't implemented yet :(" << endl; 
        } else if(Cell::isValidDirection(cmd)) {
            player->move(cmd);
            validCmd = true;
        }

        if(validCmd) {
            // Player has done his shit so update everything else.
            floor->updateGameStep();
        }

    } else {
        if(cmd == "s" || cmd == "d" || cmd == "v" || cmd == "g" || cmd == "t") {
            
            // we need to generate the player. it can be acessed later by using Player::getInstance again (from any module that includes Player.h)
            player = Player::getInstance(cmd);

            // generate the first floor
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

            state = 1; // we should now start reading commands related to the "playing" state
        }
    }
}
