#ifndef __CMD_INTERPRETER_H__
#define __CMD_INTERPRETER_H__

//We do not have any stack allocated instances of Floor or Player
//so we don't need to include them. This reduces the chance of accidental
//circuluar dependencies
class Floor;
class Player;

//for ostream
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

    //we notify the relevant entities from the given command 
    // the map is then notified by the entitys of their changes and itself updates
    void notifyEntitys();


    // these are all called by notifyEntities
    void notifyPlayer();
    void updateEnemies();
    void updateEnvironment();
    void updateCombat(); 

    public:
        CmdInterpreter *getInstance();
        
        //contains main game loop
        void start();

        void restart();
        void end();

};

#endif