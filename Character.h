#ifndef __CHARACTER_H__
#define __CHARACTER_H__

class Character: public Entity{

	int attack;
	int defence;
	int HP;

	public:
		// fight can be called by players on enemies and enemies on players
		virtual void fight(Character *against) = 0;
		// character tries to move in this direction, returns true if they did, false if they couldn't
		// if it does, it will remove itself from the cell it's on (has a cell from entity) and set itself on the adjacent one
		// the old cell and the new cell with both notify map
		bool tryMove(string direction);
};

#endif