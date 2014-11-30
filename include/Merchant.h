#ifndef __MERCHANT_H__
#define __MERCHANT_H__

#include "Enemy.h"

class Cell;
class Entity;

class Merchant : public Enemy {
    
    // True if the player previously attacked any merchant.
    // In this case, all merchants are hostile.
    static bool hostile;

    public:
    	Merchant(Cell *cell);
    	~Merchant();
    	void fight(Entity *against);
    	bool notify();
    	static void makeHostile();

};

#endif