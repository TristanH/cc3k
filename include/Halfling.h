#ifndef __HALFLING_H__
#define __HALFLING_H__

#include "Enemy.h"

class Cell;

class Halfling : public Enemy {

    public:
    	Halfling(Cell *cell);

};

#endif