#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"
#include <string>
#include <iostream> // for NULL

class Cell;
class Entity;

class Player: public Character{
	static Player *instance;
    static void cleanup(); //passed into atexit()
    int gold; //keeps track of how much gold the player has
    int floorNum;

	//combat logic lives here
	public:
        virtual ~Player() = 0; // Nothing else here is pure virtual so we need this to be or else people can instantiate Player (this means we need to also create an empty implementation of the dtor in Player.cc)
		// this fight is for the player attacking an enemy
		void fight(Entity *against); // TODO: we changed this to fight Entity so that we don't have to check if Character. Need to implement properly so attacking an Item just logs something.
        void specialFightEffect(Character *against, int damageDone);
        static  Player *getInstance(char race = 's', Cell *cell = NULL);
        static void addPotion(char type, int amount);
        static void removePotions();
        void addGold(int amount); //just adds amount to current gold
        bool move(std::string direction);
        virtual std::string raceStr() = 0;
        int getGold();
        int getFloorNum();
        void onDeath();
        bool notify();
        virtual Player *unpack();
    protected:
    	Player(Cell *cell, int atk, int def, int HP);
};

#endif