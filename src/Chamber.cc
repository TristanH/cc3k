#include "Chamber.h"
#include "Enemy.h"
#include "Cell.h"
#include <vector>
#include <iterator>
using namespace std;

void Chamber::updateEnemies() {
	//iterate through the vector of enemies and update them
    int enemiesSize = enemies.size();
    for(int i=0; i < enemiesSize; i++) { // was using an iterator here before but fuck that shit
    	enemies[i]->updateMove();
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
	int r = newCell->getR();
	int c = newCell->getC();
	vector<Cell *>::iterator it;
	for(it = cells.begin(); it != cells.end(); it++){
		Cell *curr = *it;
		// if we've found the right place to insert this cell
		if(r < curr->getR() || (r == curr->getR() && c < curr->getC())){
			cells.insert(it, newCell);
			return;
		}
	}
	// if we get here aka we haven't found a spot for the new Cell yet, put it at the back of the list
	// this covers the empty list case too
	cells.push_back(newCell);
}