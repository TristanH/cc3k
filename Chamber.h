/************************************************************************
 * Chambers are only valid if they are fully enclosed with walls/doors. *
 * Invalid chambers will break map generation!                          *
 ************************************************************************/

#ifndef __CHAMBER_H__
#define __CHAMBER_H__

#include "Cell.h"
#include <vector>

class Enemy;

class Chamber {

    // we should keep track of enemies per room even though they are orginally spawned and distributed by the
    // floor. This way we can know if a room is clear. This could lead to us creating rooms that only unlock after
    // you have defeated all the enemies. DAT DLC THO!!!
    std::vector<Enemy *> enemies;

    std::vector<Cell *> cells;
 
    void updateEnemies();

    public:
    	Chamber();
        void update();
        void addCell(Cell *cell);

};
#endif