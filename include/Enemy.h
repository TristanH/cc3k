#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Character.h"

// this should be abstract, with the diff enemy types extending it
class Enemy: public Character{
	protected:	
		Enemy(Cell *cell, char dc, int atk, int def, int hp);
        void move();

    public:
    	// this is only for the step of enemies attacking the player
    	// this will be concrete, then enemies with special attack effects can overwrite it
    	void fight(Entity *against);
    	void specialFightEffect(Character *against, int damageDone);
    	bool notify();
    	void onDeath();
};


#endif