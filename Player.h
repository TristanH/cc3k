#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"

class Player: public Character{
	Player *instance;
    void cleanup(); //passed into atexit()
    int gold; //keeps track of how much gold the player has

	//combat logic lives here
	public:
		// this fight is for the player attacking an enemy
		virtual void fight(Character *against);
		void *instance getInstance();
        void addGold(int amount); //just adds amount to current gold

};

#endif