#include "Chamber.h"
#include <vector>
using namespace std;

void Chamber::updateEnemies() {
	//iterate through the vector of enemies and update them
    vector<Enemy *>::iterator it; //define iterator
    for(it = enemies.begin(); it != enemies.end(); ++it) { // iterators look weird but the are just glorified pointers
        // enemies need to first check if the player is in fighting range.
        // if the player can't be attacked, move in a random direction (unless enemy is a dragon)
        // all of this should be taken care by the enemy (which will call some cell function)
    	it->updateMove();
    }
}

void Chamber::addEnemy(Enemy *e) {
    enemies.push_back(e);
}

void Chamber::update() {
    updateEnemies();
}

void Chamber::addCell(Cell *newCell){
	// we want to insert cells in the order they should be updated, eg starting at top then left to right
	int y = newCell.getY();
	int x = newCell.getX();
	for(int i=0; i < cells.size(); i++){
		// if we've found the right place to insert this cell
		if(y < cells[i].getY() || (y == cells[i].getY() && x < cells[i].getX())){
			cells.insert(i, newCell);
			return;
		}
	}
	// if we get here aka we haven't found a spot for the new Cell yet, put it at the back of the list
	// this covers the empty list case too
	cells.push_back(newCell);
}