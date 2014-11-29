#ifndef __CMD_INTERPRETER_H__
#define __CMD_INTERPRETER_H__

#include "Floor.h" // I have to include this or the compiler keeps giving warnings (cause I delete floor)
class Player;

#include <iostream>
#include <string>

// Singleton class, receives input from cin and interprets commands
class CmdInterpreter{
    static CmdInterpreter* instance;
    static void cleanup();
    bool isFinished;
    bool shouldRestart;

    // keeps track of current state of the game:
    // 0 -> race selection
    // 1 -> playing
    //TODO: instead of using a int to represent a state we should have a state object and have a stack of states in the CmdInterpreter class
    int state;

    // this is an observer of the cmd interpreter
    Floor *floor;
    int floorNum;

    Player *player;
    
    CmdInterpreter(std::vector<std::string> args = std::vector<std::string>());
    ~CmdInterpreter();

    void executeCmd(std::string cmd);

    // these are all called by notifyEntities
    void notifyPlayer();

    // since the floor is responsible for spawning enemies
    // it should also be responsible for doing all the updates for
    // enemies, environment and such
    void updateFloor();
    // we have to update the player first, because the enemies won't move if he goes near them

    // Print stuff that is supposed to go underneath the map
    void printInfo();

    // Command line argument stuff
    std::vector<std::string> args;


    public:

        // The use of optional params means we can still just call CmdInterpreter::getInstance()
        static CmdInterpreter* getInstance(std::vector<std::string> args = std::vector<std::string>());
        
        //contains main game loop
        void start();

        // called when user wants to restart game, deletes and recreates everything
        void restart();

        //finishes game, deletes everything and quits
        void end();

};

#endif