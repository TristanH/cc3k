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
};

#endif