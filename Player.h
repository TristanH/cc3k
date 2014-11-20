#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"

class Player: public Character{
	Player *instance;
    static void cleanup(); //passed into atexit()
    int gold; //keeps track of how much gold the player has

	//combat logic lives here
	public:
        virtual Player() = 0;
        virtual Player(){};
		// this fight is for the player attacking an enemy
		virtual void fight(Entity *against); // TODO: we changed this to fight Entity so that we don't have to check if Character. Need to implement properly so attacking an Item just logs something.
		static void *instance getInstance(char race);
        void addGold(int amount); //just adds amount to current gold
        void move(string direction);
};

#endif