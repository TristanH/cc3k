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
    const int FLOORS_TO_WIN;
    std::string mapFile;

    // keeps track of current state of the game:
    // 0 -> race selection
    // 1 -> playing
    int state;

    bool didWin;
    int finalScore;

    // this is an observer of the cmd interpreter
    Floor *floor;
    
    CmdInterpreter(std::vector<std::string> args = std::vector<std::string>());
    ~CmdInterpreter();

    void executeCmd(std::string cmd);

    void nextFloor();
    void loopDone();
    void won();
    // we have to update the player first, because the enemies won't move if he goes near them

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

        void setMapFile(std::string filename);

};

#endif