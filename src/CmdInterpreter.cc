#include "CmdInterpreter.h"
#include "Die.h"
#include "Player.h"
#include "Cell.h"
#include <iostream> //for NULL and cerr
#include <string>
using namespace std;

// Static stuff
CmdInterpreter *CmdInterpreter::instance = NULL; //by default

void CmdInterpreter::cleanup() {
    delete instance;
}

CmdInterpreter *CmdInterpreter::getInstance(vector<string> args) {
    if(!instance) {
        instance = new CmdInterpreter(args);
        atexit(cleanup);
    }
    return instance;
}


// Methods
CmdInterpreter::CmdInterpreter(vector<string> args) :
    isFinished(false),
    shouldRestart(false),
    floor(NULL),
    player(NULL),
    state(0){
        this->args = args;
    }


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
    #ifdef DEBUG
    cout << "CmdInterpreter.cc: game loop terminated" << endl;
    #endif
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

    #ifdef DEBUG
    cout << "CmdInterpreter.cc: program state = " << state << "; cmd = " << cmd << endl;
    #endif
    if(state == 1) {
        bool validCmd = false;
        if(cmd == "u") {
            string dir;
            cin >> dir;
            //TODO: pickup thing in that dir
            cerr << "This isn't implemented yet :(" << endl; 
            validCmd = true;
        } else if(cmd == "a") {
            string dir;
            cin >> dir;
            Cell *otherCell = (player->getCell())->getAdjacentCell(dir);
            Entity *otherEntity = otherCell->getEntity();
            player->fight(otherEntity); // At this point we know    
            validCmd = true; 
        } else if(cmd == "r") {
            restart();
            // Don't set validCmd becaues we don't want a game step to happen after we decide to restart
            cerr << "This isn't implemented yet :(" << endl; 
        } else if(Cell::isValidDirection(cmd)) {
            player->move(cmd);
            validCmd = true;
        }

        if(validCmd) {
            // Player has done his shit so update everything else.
            #ifdef DEBUG
            cout << "CmdInterpreter.cc: updating game step..." << endl;
            #endif
            floor->updateGameStep();
        }

    } else {
        if(cmd == "s" || cmd == "d" || cmd == "v" || cmd == "g" || cmd == "t") {
            
            // we need to generate the player. it can be acessed later by using Player::getInstance again (from any module that includes Player.h)
            player = Player::getInstance(cmd[0]);

            // Die has 18 sides because the lcd of the spawning probabilities is 18
            Die *spawnDie = new Die(18); 

            // add sides to the die
            spawnDie->addSides(4, 'H');
            spawnDie->addSides(3, 'D');
            spawnDie->addSides(5, 'L');
            spawnDie->addSides(2, 'E');
            spawnDie->addSides(2, 'O');
            spawnDie->addSides(2, 'M');

            // get the name of the file to generate map from
            // TODO: remove temporary fix and actually use cmd line args
            string filename = "maps/normal_format.data";
            floor = new Floor(filename);
            floor->setSpawnRates(spawnDie);
            floor->populate();

            state = 1; // we should now start reading commands related to the "playing" state
        }
    }
}
