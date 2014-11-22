#ifndef __CELL_H__
#define __CELL_H__

//We do not have any stack allocated instances of Entity or Map
//so we don't need to include them. This reduces the chance of accidental
//circuluar dependencies
class Entity;
class Map;
class Player;
class Floor;

#include <string>

class Cell{
	// the entity on this cell
	Entity *entity;
	int r, c; // row, column
	// Can be floor, wall, passage, stairway
	// will not change when entity is on it
	const char type;
	Floor *floor;
	static const std::string directions[8];

	void notifyFloor();

	public:
		// If the cell being created doesn't have an entity on it, the entity
		// field is just NULL
		Cell(int r, int c, char type, Floor *floor, Entity *entity = NULL);
		void setEntity(Entity *newEntity);
		Entity *getEntity();
		bool isWalkable();
		int getR();
		int getC();
		char getType();
		char getDisplayChar();
		// gets the cell from eg no, nw, sw used for enemy attacking, potions, moving
		Cell *getAdjacentCell(std::string direction);

		Player *findPlayerInBounds();
		static std::string getRandomDirection();
		static bool isValidDirection(std::string direction);

};

#endif