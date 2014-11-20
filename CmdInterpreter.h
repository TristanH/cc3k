#ifndef __CMD_INTERPRETER_H__
#define __CMD_INTERPRETER_H__

//We do not have any stack allocated instances of Floor or Player
//so we don't need to include them. This reduces the chance of accidental
//circuluar dependencies
class Floor;
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

    Player *player;
    
    CmdInterpreter();

    void executeCmd(std::string cmd);

    // these are all called by notifyEntities
    void notifyPlayer();

    // since the floor is responsible for spawning enemies
    // it should also be responsible for doing all the updates for
    // enemies, environment and such
    void updateFloor();
    // we have to update the player first, because the enemies won't move if he goes near them

    void printLog(std::string str);


    public:
        static CmdInterpreter *getInstance();
        
        //contains main game loop
        void start();

        // called when user wants to restart game, deletes and recreates everything
        void restart();

        //finishes game, deletes everything and quits
        void end();

};

#endif