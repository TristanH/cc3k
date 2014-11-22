#ifndef __DRAGON_H__
#define __DRAGON_H__

#include "Enemy.h"
Class cell;

class Dragon : public Enemy {
    
    public:
    	Dragon(Cell *cell);
    	// needs a specific implementation to not be aggresive
    	void updateMove();
    	

};

#endif