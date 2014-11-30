#include "CmdInterpreter.h"
#include "Die.h"
#include "Player.h"
#include "Cell.h"
#include "Display.h"
#include "Item.h"
#include <iostream> //for NULL and cerr
#include <string>
#include <sstream>
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
    mapFile(""),
    FLOORS_TO_WIN(5) { //TODO: make cmd line arg to alter this
        this->args = args;
    }


CmdInterpreter::~CmdInterpreter() {
    delete floor;
    //delete player; TODO: do we explicitly delete singleton or does atexit do this??
}

void CmdInterpreter::setMapFile(string filename) {
    mapFile = filename;
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

void CmdInterpreter::nextFloor() {
    Player *player = Player::getInstance();
    if(player->getFloorNum() == FLOORS_TO_WIN) {

    } else {
        // Player::removePotions(); // remove temp potion decorators
        // player = Player::getInstance(); // replace player with undecorated instance
        // player->nextFloor(); // increment floor count
        // delete floor;
        // floor = new Floor(mapFile);
        // ostringstream ss;
        // ss << "Welcome to floor " << player->getFloorNum();   
        // Display::statusMessage += ss.str();
        // cout << *floor;
    }
}

void CmdInterpreter::executeCmd(string cmd) {

    if(state == 1) {
        Display::statusMessage = ""; // So messages can be appended.
        bool validCmd = false;
        if(cmd == "u") {
            string dir;
            cin >> dir;
            if(Cell::isValidDirection(dir)){
                Entity *entity = player->getCell()->getAdjacentCell(dir)->getEntity();
                if(entity) {
                    Item *item = dynamic_cast<Item *>(entity);
                    if(item) {
                        item->collect(player);
                        Cell *cell = item->getCell();
                        cell->setEntity(NULL);
                        // TODO: set entity to '.'
                        delete item;
                        validCmd = true;
                    } else {
                        Display::statusMessage += "That isn't a usable item";
                    }
                } else {
                    Display::statusMessage += "Nothing to use!";
                }
            }
        } else if(cmd == "a") {
            string dir;
            cin >> dir;
            if(Cell::isValidDirection(dir)){
                #ifdef DEBUG
                cout << "Player is attempting to fight" << endl;
                #endif
                Cell *otherCell = (player->getCell())->getAdjacentCell(dir);
                Entity *otherEntity = otherCell->getEntity();
                player->fight(otherEntity); // At this point we know    
                validCmd = true; 
            }
        } else if(cmd == "r") {
            restart();
            // Don't set validCmd becaues we don't want a game step to happen after we decide to restart
            cerr << "This isn't implemented yet :(" << endl; //TODO: remove this line when this is implemented
        } else if(cmd == "e") {
            end();
        } else if(Cell::isValidDirection(cmd)) {
            #ifdef DEBUG
            cout << "Cmd:Interpreter: moving to " << cmd << endl;
            #endif
            Cell *goTo = player->getCell()->getAdjacentCell(cmd);
            if(cmd == "ea" && goTo->getDisplayChar() == '\\') {
                nextFloor();
            } else {
                player->move(cmd);
                validCmd = true;
            }
        }
        #ifdef DEBUG
        else if(cmd == "add") {
            char type = '5';
            int amount = -10;
            Player::addPotion(type, amount);
            validCmd = true;
        } else if(cmd == "remove") {
            Player::removePotions();
            validCmd = true;
        }
        #endif

        if(validCmd) {
            // Player has done his shit so update everything else.
            #ifdef DEBUG
            cout << "CmdInterpreter.cc: updating game step..." << endl;
            #endif
            floor->updateGameStep();
            cout << *floor;
        }

    } else {
        if(cmd == "s" || cmd == "d" || cmd == "v" || cmd == "g" || cmd == "t") {

            // get the name of the file to generate map from
            // TODO: remove temporary fix and actually use cmd line args
            string filename = "maps/full_map.data";
            floor = new Floor(filename, cmd[0]);
            player = Player::getInstance();
            cout << *floor;
            state = 1; // we should now start reading commands related to the "playing" state
        }
    }
}
