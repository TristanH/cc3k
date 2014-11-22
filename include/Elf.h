#ifndef __ELF_H__
#define __ELF_H__

#include "Enemy.h"

class Cell;

class Elf : public Enemy {

    public:
    	Elf(Cell* cell);

};

#endif