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
	Display *display; //map needs to notify dislpay
	std::vector<Chamber *> chambers;

	// keeps track of floor dimensions
	const int WIDTH;
	const int HEIGHT;

	std::vector<Entity *> partialSpawn; // Keeps track of the entities spawned from the map file
	int enemySpawnCount;
	int potionSpawnCount;
	int treasureSpawnCount;
	bool playerSpawned;
	bool stairsSpawned;

	// maps the displayChar of an entity to its probability of spawnining.
	// this allows us to have different spawn probabilities for different floors.
	Die *enemyDie;
	Die *potionDie;
	Die *goldDie;

	void generateCells(std::string filename, char playerType);

	// --Following 2 methods called by updateGameStep--
	//update enemies gives enemies a chance to move or attack player
	void updateEnemies();
	// the idea is that updateEnemies makes the enemies move their shit, then the enemies update their respective cells
	// and the cells notify the map of these updates

	void notifyDisplay(int i, int j, char newState);
	void notifyChambers();

	void generateChambers();
	void randomFloorGeneration(char playerSpawnType);
	void floodCreateChamber(int y, int x, bool **visited, Chamber* chamber);

	bool sameChamber(Cell *a, Cell *b);
	Chamber *locateChamber(Cell *cell);

	void createDies();

	public:
		// sets cells, spawns entities
		Floor(std::string fileName, char playerSpawnType);

		// Since the floor owns its cells and chambers, it will delete all cells and chambers
		~Floor();
		void setDisplay(Display *display);

		//updating gamestep should move all the enemies and give them their chances to do combat
		void updateGameStep();

		Cell *getCell(int y, int x);

		// this will use the spawnRates to populate the already generate map
		void populate(char playerType);

		// simply tells the floor that this entity has just occupied it's space and the display should be updated
		void notify(int i, int j, Cell *cell);

		Chamber *getRandChamber();
		// If no chamber is given, this function will operate the same as before and just get a random cell on the
		// floor. I needed to add a (optional) intermediate step so that enemies can be added to a chambers enemy vector
		Cell* findUniqueCell(Chamber *chamber = NULL);

		void updatePotions();
	friend std::ostream &operator<<(std::ostream &out, Floor &f);
};

#endif