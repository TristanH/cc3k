#include "CmdInterpreter.h"
#include "Die.h"
#include "Player.h"
#include "Cell.h"
#include "Display.h"
#include "Item.h"
#include "Shade.h"
#include "Potion.h"
#include "Treasure.h"
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
    state(0),
    mapFile(""),
    didWin(false),
    finalScore(0),
    FLOORS_TO_WIN(5) { //TODO: make cmd line arg to alter this
        this->args = args;
    }


CmdInterpreter::~CmdInterpreter() {
    delete floor;
}

void CmdInterpreter::setMapFile(string filename) {
    mapFile = filename;
}

void CmdInterpreter::loopDone() {
    if(shouldRestart) {
        shouldRestart = false;
        didWin = false;
        isFinished = false;
        state = 0;
        finalScore = 0;
        delete floor;
        floor = NULL;
        Player::restart();
        Display::restart();
        Cell::newFloor();
        Display::statusMessage = "";
        start();
    } else {
        if(didWin) {
            cout << "Congratulations! You beat the final floor!" << endl;
        } else {
            finalScore = Player::getInstance()->getGold();
            cout << "Game over." << endl;
        }
        ostringstream ss;
        ss << "Final Score: " << finalScore;
        cout << ss.str() << endl;
    }
}

void CmdInterpreter::start() {
    string cmd;
    cout << "Pick your race: " << endl;
    cout << "s - Shade, d - Drow, v - Vampire, g - Goblin, t - Troll" << endl;
    while(!isFinished && cin >> cmd) {
        executeCmd(cmd);
    }
    loopDone();
}

void CmdInterpreter::end() {
    isFinished = true;
}

void CmdInterpreter::restart() {
    shouldRestart = true;
    end();
}

void CmdInterpreter::won() {
    finalScore = Player::getInstance()->getGold();
    if(Player::getInstance()->raceStr() == "Shade") finalScore += finalScore * 0.5;
    isFinished = true;
    didWin = true;
}

void CmdInterpreter::nextFloor() {
    #ifdef DEBUG
    cerr<< "nextFloor called " <<endl;
    #endif
    Player *player = Player::getInstance();
    if(player->getFloorNum() == FLOORS_TO_WIN) {
        isFinished = true;
        didWin = true;
    } else {
        Player::removePotions(); // remove temp potion decorators
        player = Player::getInstance(); // replace player with undecorated instance
        player->nextFloor(); // increment floor count
        Display::getInstance()->reset();
        delete floor;
        Cell::newFloor();
        // doesn't matter what playerSpawn char is, it already exists
        floor = new Floor(mapFile, '!');
        ostringstream ss;
        ss << "Welcome to floor " << player->getFloorNum();   
        Display::statusMessage += ss.str();
        cout << *floor;
    }
}

void CmdInterpreter::executeCmd(string cmd) {
    if(state == 1) {
        Display::statusMessage = ""; // So messages can be appended.
        #ifdef DEBUG
        cout << "cmd = " << cmd << endl;
        #endif
        Player *player = Player::getInstance();

        bool validCmd = false;
        if(cmd == "u") {
            string dir;
            cin >> dir;
            if(Cell::isValidDirection(dir)){
                Entity *entity = player->getCell()->getAdjacentCell(dir)->getEntity();
                if(entity) {
                    Potion *potion = dynamic_cast<Potion *>(entity);
                    if(potion) {
                        potion->collect(player);
                        Cell *cell = potion->getCell();
                        cell->setEntity(NULL);
                        player = Player::getInstance();
                        delete potion;
                    } else {
                        Display::statusMessage += "That isn't a usable item";
                    }
                } else {
                    Display::statusMessage += "Nothing to use!";
                }
                validCmd = true;
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
        } else if(cmd == "e") {
            end();
        } else if(Cell::isValidDirection(cmd)) {
            #ifdef DEBUG
            cout << "Cmd:Interpreter: moving to " << cmd << " with "<< player->getCell()->getAdjacentCell(cmd)->getDisplayChar() << endl;
            #endif
            Cell *goTo = player->getCell()->getAdjacentCell(cmd);
            if(cmd == "ea" && goTo->getDisplayChar() == '\\') {
                nextFloor();                
            } else {
                Treasure *treasure = dynamic_cast<Treasure *>(goTo->getEntity());
                if(treasure && treasure->collect(player)) {
                    goTo->setEntity(NULL);
                    delete treasure;
                }
                player->move(cmd);
            }
            validCmd = true;
        }
        #ifdef DEBUG
        else if(cmd == "add") {
            char type = '5';
            int amount = -10;
            Player::addPotion(type, amount);
            validCmd = true;
        } else if(cmd == "remove") {
            Player::removePotions();
            player = Player::getInstance();
            validCmd = true;
        }
        #endif

        if(validCmd) {
            // Player has done his shit so update everything else.
            #ifdef DEBUG
            cout << "CmdInterpreter.cc: updating game step..." << endl;
            #endif
            Player::getInstance()->gameTick();
            floor->updateGameStep();
            if(player->getHP() <= 0){
                cout << "Your HP has dropeed below 0! " << endl;
                end();
            }
        } 
        else
            Display::statusMessage+= "Invalid command supplied. ";
        if(!isFinished) cout << *floor;

    } else {
        if(cmd == "s" || cmd == "d" || cmd == "v" || cmd == "g" || cmd == "t") {

            floor = new Floor(mapFile, cmd[0]);
            #ifdef DEBUG
            cout << "floor made" << endl;
            #endif
            Display::statusMessage += "Player character has spawned. ";
            cout << *floor;
            state = 1; // we should now start reading commands related to the "playing" state
        }
        else
            Display::statusMessage+= "Invalid command supplied. ";
    }
}
