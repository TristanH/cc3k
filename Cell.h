#ifndef __CELL_H__
#define __CELL_H__


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
		// gets the cell from eg no, nw, sw used for enemy attacking, potions, moving
		Entity *getAdjacentCell(string direction);

};

#endif