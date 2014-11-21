#ifndef __ITEM_H__
#define __ITEM_H__

#include "Entity.h"

class Item: public Entity{
	
	public:
		// returns true if it was able to be collected
		virtual bool collect(Player* player) = 0;
};

#endif
