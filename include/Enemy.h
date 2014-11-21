#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Character.h"

// this should be abstract, with the diff enemy types extending it
class Enemy: public Character{

	int dropValue;

    public:
    	// this is only for the step of enemies attacking the player
    	// this will be concrete, then enemies with special attack effects can overwrite it
    	void fight(Character *against);

    	void updateMove();
};

#endif