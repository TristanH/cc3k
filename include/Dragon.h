#ifndef __DRAGON_H__
#define __DRAGON_H__

#include "Enemy.h"

class Dragon : public Enemy {

	DragonTreasure *treasure;
    
    public:
    	Dragon(DragonTreasure* dt);
    	// needs a specific implementation to not be aggresive
    	void updateMove();
    	

};

#endif