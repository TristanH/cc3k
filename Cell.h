#ifndef __CELL_H__
#define __CELL_H__

//We do not have any stack allocated instances of Entity or Map
//so we don't need to include them. This reduces the chance of accidental
//circuluar dependencies
class Entity;
class Map;

class Cell{
	// the entity on this cell
	Entity *entity;
	// Can be floor, wall, passage, stairway
	const char type;
	Map *map;

	void notifyMap();

	public:
		void setEntity(const Entity *newEntity);
		Entity *getEntity();
		bool isWalkable();
};

#endif