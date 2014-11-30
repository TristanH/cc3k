#include "Chamber.h"
#include "Enemy.h"
#include "Cell.h"
#include "PRNG.h"
#include <vector>
#include <iterator>
using namespace std;

Chamber::Chamber(){}

void Chamber::updateEnemies() {
	//iterate through the vector of enemies and update them
    for(int i=0; i < enemies.size(); i++) { // was using an iterator here before but fuck that shit
        // notify the enemy that its time to update
        #ifdef DEBUG
        //cout << "updating " << *enemies[i] << endl;
        #endif
    	bool isDead = !enemies[i]->notify();
    	if(isDead){
            // TODO: make sure memory is not leaked here
    		//delete enemies[i];
    		enemies.erase(enemies.begin() + i);
    		#ifdef DEBUG
    		cout << "Enemy at index " << i << " deleted, " << enemies.size() << " enemies left in chamber" << endl;
    		#endif
    		i--;
    	}
    }
}

// Uses the same logic as the below addCell funciton 
void Chamber::addEnemy(Enemy *e) {
    int r = e->getR();
    int c = e->getC();
    vector<Enemy *>::iterator it;
    for(it = enemies.begin(); it != enemies.end(); it++) {
    	Enemy *curr = *it;
    	if(r < curr->getR() || (r == curr->getR() && c < curr->getC())) {
    		enemies.insert(it, e);
    		return;
    	}
    }
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

Cell* Chamber::getRandomCell(){
	return cells[PRNG::random(cells.size() - 1)];
}

bool Chamber::isFull(){
	for(int i=0; i < cells.size(); i++){
		if(cells[i]->getEntity() == NULL)
			return false;
	}
	return true;
}

bool Chamber::hasCell(Cell *cell){
	for(int i=0; i < cells.size(); i++){
		if(cells[i] == cell) {
            return true;
        }
	}
	return false;
}

Chamber::~Chamber(){
	for(int i=0;i<enemies.size();i++)
		delete enemies[i];
}
