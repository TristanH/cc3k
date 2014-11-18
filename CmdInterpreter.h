#ifndef __CMD_INTERPRETER_H__
#define __CMD_INTERPRETER_H__

#include <iostream>

// Singleton class, receives input from cin and interprets commands
class CmdInterpreter{
    CmdInterpreter* instance;
    bool isFinished;

    // this is an observer of the cmd interpreter
    Floor *floor;

    Player *player;
    
    CmdInterpreter();
    void cleanup();

    void readCommand();

    // these are all called by notifyEntities
    void notifyPlayer();

    // since the floor is responsible for spawning enemies
    // it should also be responsible for doing all the updates for
    // enemies, environment and such
    void updateFloor();
    // we have to update the player first, because the enemies won't move if he goes near them


    public:
        CmdInterpreter *getInstance();
        
        //contains main game loop
        void start();

        // called when user wants to restart game, deletes and recreates everything
        void restart();

        //finishes game, deletes everything and quits
        void end();

};

#endif