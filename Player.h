#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"

class Player: public Character{
	Player *instance;

	//combat logic lives here
	public:
		void fight(Character *against);
		void *instance getInstance();

};

#endif