#include "Cell.h"
#include "Map.h"
#include "PRNG.h"

#include <ctime>

using namespace std;

Cell::Cell(int y, int x, char type): 
	entity(NULL), y(y), x(x), type(type){
	floor = Floor.getInstance();
	directions = {}
}

//make this const?
string Cell::directions[] = {"no", "ne", "ea", "se", "so", "sw", "we", "nw"};

void Cell::notifyFloor(){
	//idk how to do this

	// what i think we want is to print this->type if entity is null
	// otherwise print the entity.displayChar
	// but what actually needs to be done by the map? I can't think of anything
	// the display char just needs to update..
}

void Cell::setEntity(const Entity *newEntity){
	entity = newEntity;
	notifyFloor();
}

Entity* Cell::getEntity(){
	return entity;
}

bool Cell::isWalkable(){
	return type == '.' && entity == NULL;
}

char Cell::getType(){
	return type;
}

Cell* Cell::getAdjacentCell(string direction){
	if(direction == "no")
		return Floor.getCell(y-1,x);
	else if(direction == "ne")
		return Floor.getCell(y-1, x+1);
	else if(direction == "ea")
		return Floor.getCell(y, x+1);
	else if(direction == "se")
		return Floor.getCell(y+1, x+1);
	else if(direction == "so")
		return Floor.getCell(y+1, x);
	else if(direction == "sw")
		return Floor.getCell(y+1, x-1);
	else if(direction == "we")
		return Floor.getCell(y, x-1);
	else if(direction == "nw")
		return Floor.getCell(y-1, x-1);

	cerr << "ERROR: Invalid direciton given to getAdjacentCell" << endl;
	return NULL;
}

Player* Cell::findPlayerInBounds(){
	for(int i=0;i<7;i++){
		Cell *checkCell = getAdjacentCell(directions[i]);
		if(*checkCell.getEntity() == Player.getInstance())
			return checkCell.getEntity();
	}
	// return NULL if the player's not in a block radius
	return NULL;
}

string Cell::getRandomDirection(){
	prng random(time(NULL));
	return directions[random(7)];
}


