#ifndef __FLOOR_H__
#define __FLOOR_H__

//We do not have any stack allocated instances of Display
//so we don't need to include it. This reduces the chance of accidental
//circuluar dependencies
class Display;

class Chamber;

//ifstream needed to generate maps from file
#include <fstream>

//vector used to store enemies on floor
#include <vector>

//map used to define the probability of each entity spawning (enemies, potions, etc.)
#include <map>

class Floor{
	// fill in proper numbers later, maybe needs to be on heap?
	// cells[i][j] will be NULL if it is outside of a chamber
	std::vector<std::vector<Cell> > cells;
	Display *display; //map needs to notify dislpay
	std::vector<Chamber *> chambers;

	// maps the displayChar of an entity to its probability of spawnining.
	// this allows us to have different spawn probabilities for different floors.
	std::map<char, float> spawnRates;

	// keeps track of floor dimensions
	const int WIDTH;
	const int HEIGHT;

	// --Following 2 methods called by updateGameStep--
	//update enemies gives enemies a chance to move or attack player
	void updateEnemies();
	// the idea is that updateEnemies makes the enemies move their shit, then the enemies update their respective cells
	// and the cells notify the map of these updates

	// tells the display of all the updates after all the enemies are updated
	void notifyDisplay();

	void generateChambers();
	void floodCreateChamber(int y, int x, bool **visited, Chamber* chamber);

	public:
		// sets cells, spawns entities
		Floor(string fileName);
		void setDisplay(Display *display);
		void setSpawnRates(sed::map<char,float> mapping);
		void notify(/* TODO: we probably need to pass stuff into this */);

		//updating gamestep should move all the enemies and give them their chances to do combat
		void updateGameStep();

	friend std::ostream &operator<<(std::ostream &out, Floor &f);
};

#endif