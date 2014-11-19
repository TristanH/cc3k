#include "Chamber.h"
using namespace std;

void Chamber::Chamber(int y, int x): cornerY(y), cornerX(x){}


void Chamber::updateEnemies() {

}

void Chamber::addEnemy(Enemy *e) {
    enemies.push_back(e);
}

void Chamber::update() {
    updateEnemies();
}

void Chamber::addCell(){
	// TODO: Figure out adding cells so they can be processed in the correct order
	// Correct order: top row the second top row, left to right..
}