#ifndef __FLOOR_H__
#define __FLOOR_H__

//We do not have any stack allocated instances of Display
//so we don't need to include it. This reduces the chance of accidental
//circuluar dependencies
class Display;
class Cell;
class Chamber;
class Entity;
class Die;

//ifstream needed to generate maps from file
#include <fstream>

//vector used to store enemies on floor
#include <vector>

//map used to define the probability of each entity spawning (enemies, potions, etc.)
#include <map>

#include <string>

class Floor{
	// cells[i][j] will be NULL if it is outside of a chamber
	std::vector<std::vector<Cell *> > cells;
	Display *display; //map needs to notify dislpay - TODO: where do we delete this??
	std::vector<Chamber *> chambers; // TODO: should we maybe make these stack-allocated so they die with the floor?

	// maps the displayChar of an entity to its probability of spawnining.
	// this allows us to have different spawn probabilities for different floors.
	Die *enemyDie;
	// TODO: add dice for potions and gold piles (if needed)

	// keeps track of floor dimensions
	const int WIDTH;
	const int HEIGHT;

	void generateCells(std::string filename);

	// --Following 2 methods called by updateGameStep--
	//update enemies gives enemies a chance to move or attack player
	void updateEnemies();
	// the idea is that updateEnemies makes the enemies move their shit, then the enemies update their respective cells
	// and the cells notify the map of these updates

	void notifyDisplay(int i, int j, char newState);
	void notifyChambers();

	void generateChambers();
	void floodCreateChamber(int y, int x, bool **visited, Chamber* chamber);

	bool sameChamber(Cell *a, Cell *b);

	public:
		// sets cells, spawns entities
		Floor(std::string fileName);

		// Since the floor owns its cells and chambers, it will delete all cells and chambers
		~Floor();
		void setDisplay(Display *display);
		void setEnemyDie(Die *sr);
		// TODO: add other setters for other dice if needed (potions, gold, random events, etc.)

		//updating gamestep should move all the enemies and give them their chances to do combat
		void updateGameStep();

		Cell *getCell(int y, int x);

		// this will use the spawnRates to populate the already generate map
		void populate();

		// simply tells the floor that this entity has just occupied it's space and the display should be updated
		void notify(int i, int j, Cell *cell);

		Cell* findUniqueCell();

	friend std::ostream &operator<<(std::ostream &out, Floor &f);
};

#endif