#ifndef __FLOOR_H__
#define __FLOOR_H__

#include <fstream>

class Floor{
	// fill in proper numbers later, maybe needs to be on heap?
	// cells[i][j] will be NULL if it is outside of a chamber
	Cell cells[100][100];
	Display *display; //map needs to notify dislpay

	// this looks right?
	Vector<Enemy> enemies;


	public:
		// sets cells, spawns entities
		Floor(string fileName);
		void notify();

		//updating gamestep should move all the enemies and give them their chances to do combat
		void updateGameStep();
		// the following 2 are called by updateGameStep():

		//update enemies gives enemies a chance to move or attack player
		void updateEnemies();
		// the idea is that updateEnemies makes the enemies move their shit, then the enemies update their respective cells
		// and the cells notify the map of these updates

		// tells the display of all the updates after all the enemies are updated
		void notifyDisplay();

	friend std::ostream &operator<<(std::ostream &out, Floor &f);
};

#endif