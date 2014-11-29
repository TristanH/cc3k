#include "CmdInterpreter.h"
#include "Die.h"
#include "Player.h"
#include "Cell.h"
#include <iostream> //for NULL and cerr
#include <string>
#include <iomanip>
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
    state(0),
    floorNum(0){
        this->args = args;
    }


CmdInterpreter::~CmdInterpreter() {
    delete floor;
    //delete player; TODO: do we explicitly delete singleton or does atexit do this??
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

void CmdInterpreter::printInfo() {
    Player *p = Player::getInstance();
    cout << "Race: " << p->raceStr() << " Gold: " << p->getGold();
    cout << setw(56) << right << "Floor: " << floorNum << left << endl;
    cout << "HP: " << p->getHP() << endl;
    cout << "Atk: " << p->getAttack() << endl;
    cout << "Def: " << p->getDefence() << endl;
    cout << "Action: " << p->getAction() << endl; // TODO: add action shit!
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
            cerr << "This isn't implemented yet :(" << endl; //TODO: remove this line when this is implemented
        } else if(Cell::isValidDirection(cmd)) {
            #ifdef DEBUG
            cout << "Cmd:Interpreter: moving to " << cmd << endl;
            #endif
            player->move(cmd);
            validCmd = true;
        }

        if(validCmd) {
            // Player has done his shit so update everything else.
            #ifdef DEBUG
            cout << "CmdInterpreter.cc: updating game step..." << endl;
            #endif
            floor->updateGameStep();
            cout << *floor;
            printInfo();
        }

    } else {
        if(cmd == "s" || cmd == "d" || cmd == "v" || cmd == "g" || cmd == "t") {

            // get the name of the file to generate map from
            // TODO: remove temporary fix and actually use cmd line args
            string filename = "maps/normal_format.data";
            floor = new Floor(filename);

            // we need to generate the player. it can be acessed later by using Player::getInstance again (from any module that includes Player.h)
            // make a floor function to first find a random chamber, then a random spot in that chamber for the player
            // maybe reuse it for stairs?
            Cell* playerCell = floor->findUniqueCell();
            player = Player::getInstance(cmd[0], playerCell);

            floor->populate();

            floorNum++; // should increment any time a new floor is traveled to (using stairs)
            state = 1; // we should now start reading commands related to the "playing" state
        }
    }
}
