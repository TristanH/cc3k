#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include "Entity.h"
#include "Display.h"
#include "Floor.h"
#include "Chamber.h"
#include "Player.h"
#include "Die.h"
#include "Cell.h"
#include "PRNG.h"
#include "Potion.h"
#include "Enemy.h"
#include "Dragon.h"
#include "DragonTreasure.h"

using namespace std;

void Floor::generateCells(string fileName, char playerType) {
    // generate the walls and shit.
    // initialize display->theDisplay simultaneously
    #ifdef DEBUG
    cout << "Generating floor cells from file " << fileName << endl;
    #endif
    ifstream f(fileName.c_str());
    string line;
    int r = 0;
    int c = 0;
    while(getline(f,line)) {
        #ifdef DEBUG
        cout << "Reading line " << r << endl;
        //cout << line;
        #endif
        if(f.fail()) break; //reached EOF
        istringstream ss(line);

        // create this line of the display first so cells
        // can interact with it later when they are created
        vector<char> theDisplay_column(line.begin(), line.end()); //column vector to be pused into display->theDisplay
        display->addColumn(theDisplay_column);
        cells.push_back(vector<Cell*>());
        
        // now parse the individual Cells
        char curr;
        while(ss.get(curr)) {
            Cell *cell = NULL;
            if(curr == ' ' || curr == '+' || curr == '|' || curr == '-' || curr == '#') 
                cell = new Cell(r, c, curr, this);
            else 
                cell = new Cell(r,c,'.',this);

            if(curr == '@'){
                Player* player = Player::getInstance(playerType, cell);
                cell->setEntity(player);
                playerSpawned = true;
            }
            else if(curr == '\\'){
                cell->makeStairway();
                stairsSpawned = true;
            }
            else if(curr == 'D'){
                Dragon* dragon = new Dragon(cell);
                Entity *dte = cell->findEntityInBounds('8');
                DragonTreasure *dt = dynamic_cast<DragonTreasure*>(dte);
                // only do this if the hoard already exists:
                if(dt){
                    dt->setDragon(dragon);
                    dragon->setTreasure(dt);
                }
                //otherwise weve just created the dragon and we wait till we find the hoard
                enemySpawnCount++;
                partialSpawn.push_back(dragon);
                cell->setEntity(dragon);
                display->notify(cell->getR(), cell->getC(), '.');
            }
            else if(curr == '8'){
                DragonTreasure *dt = new DragonTreasure(cell, 6, NULL);
                Entity *de = cell->findEntityInBounds('D');

                Dragon *dragon = dynamic_cast<Dragon*>(de);
                if(dragon){
                    dragon->setTreasure(dt);
                    dt->setDragon(dragon);
                }
                cell->setEntity(dt);
                treasureSpawnCount++;
                partialSpawn.push_back(dt);
            }
            else{
                // check for partially filled maps
                Entity *entity = Entity::getNewEntity(curr, cell);
                if(entity) {
                    if(dynamic_cast<Enemy *>(entity)){
                        enemySpawnCount++;
                        // Because of the way that the program is set up, it is easier to manually notify the display here to mask
                        // any partially spawned entities on the display.
                        if(curr != ' ' && curr != '+' && curr != '|' && curr != '-' && curr != '#')
                            display->notify(cell->getR(), cell->getC(), '.');
                    }
                    else if(dynamic_cast<Potion *>(entity)) potionSpawnCount++;
                    else if(dynamic_cast<Treasure *>(entity)) treasureSpawnCount++;
                    partialSpawn.push_back(entity);
                }
                cell->setEntity(entity);
            }

            cells[r].push_back(cell);
            c++;
        }
        c = 0;
        r++;
    }
    #ifdef DEBUG
    cout << "Map read generated" << endl;
    #endif
    // At this point, both the cells and display->theDisplay should be initialized
}

void Floor::notifyChambers() {
    //iterate through the vector of rooms and update them
    vector<Chamber*>::iterator it; //define iterator
    for(it = chambers.begin(); it != chambers.end(); ++it) { // iterators look weird but the are just glorified pointers
        (*it)->update(); //update the current chamber in the vector of chambers
    }
}

void Floor::randomFloorGeneration(char playerSpawnType) {
    // TODO: random floor generation. Can create temp file and then just use the generateCells function
    cerr << "random map generation still not implemented. please provide a map name as an arg." << endl;
    exit(1);
}

Floor::Floor(string fileName, char playerSpawnType) :
    enemySpawnCount(0),
    WIDTH(79), HEIGHT(25),
    playerSpawned(false), stairsSpawned(false){

    display = Display::getInstance();
    if(fileName != "") {
        #ifdef DEBUG
        cout << "generating floor from file" << endl;
        #endif 
        generateCells(fileName, playerSpawnType);
    }
    else {
        #ifdef DEBUG
        cout << "generating floor randomly" << endl;
        #endif
        randomFloorGeneration(playerSpawnType);
    }
    #ifdef DEBUG
    cout << "cells generated" << endl;
    #endif
    generateChambers();
    #ifdef DEBUG
    cout << "chambers generated" << endl;
    #endif
    createDies();
    #ifdef DEBUG
    cout << "dies created" << endl;
    #endif
    populate(playerSpawnType);
    #ifdef DEBUG
    cout << "floor populated" << endl;
    #endif
    Potion::setFloor(this);
}

Floor::~Floor() {
    // delete chambers
    chambers.erase(chambers.begin(), chambers.end());
    //TODO: make sure this isnt leaking memory
    // for(int i=0; i < chambers.size(); i++)
    //     delete chambers[i];

    #ifdef DEBUG
    cerr << "deleted chambers";
    #endif

    for(int i = 0; i < cells.size(); i++)
        for(int j=0; j < cells[i].size(); j++)
            delete cells[i][j];
    #ifdef DEBUG
    cerr << "deleted cells";
    #endif

    delete enemyDie;
    delete goldDie;
    delete potionDie;

    #ifdef DEBUG
    cerr << "Floor: Floor, chambers, dies and cells deleted" << endl;
    #endif
}

void Floor::updateGameStep() {
    // TODO: is the player implicitly updated before this????? I DUNNOOOOO BRAH
    notifyChambers();
}

void Floor::notifyDisplay(int i, int j, char newState) {
    // this should probably be called any time the floor is updated
    display->notify(i,j,newState);
}

void Floor::setDisplay(Display *d) {
    display = d;
}

void Floor::createDies() {
    // Enemy die has 18 sides because the lcd of the spawning probabilities is 18
    enemyDie = new Die(18); 
    // add sides to the die
    enemyDie->addSides(4, 'H');
    enemyDie->addSides(3, 'd');
    enemyDie->addSides(5, 'L');
    enemyDie->addSides(2, 'E');
    enemyDie->addSides(2, 'O');
    enemyDie->addSides(2, 'M');

    potionDie = new Die(6);
    potionDie->addSides(1, '0');
    potionDie->addSides(1, '1');
    potionDie->addSides(1, '2');
    potionDie->addSides(1, '3');
    potionDie->addSides(1, '4');
    potionDie->addSides(1, '5');

    goldDie = new Die(8);
    goldDie->addSides(5, '6');
    goldDie->addSides(2, '7');
    goldDie->addSides(1, '8');

}

void Floor::floodCreateChamber(int y, int x, bool** visited, Chamber *chamber){
    if(visited[y][x] || (cells[y][x]->getType() == '+' ||
                         cells[y][x]->getType() == '#' ||
                         cells[y][x]->getType() == '-' ||
                         cells[y][x]->getType() == '|'))
        return;
    chamber->addCell(cells[y][x]);
    visited[y][x] = true;
    floodCreateChamber(y+1,x,visited, chamber);
    floodCreateChamber(y,x+1,visited, chamber);
    floodCreateChamber(y-1,x,visited, chamber);
    floodCreateChamber(y,x-1,visited, chamber);
}

void Floor::generateChambers(){
    bool **visited;

    visited = new bool*[HEIGHT];
    for(int y=0; y < HEIGHT; y++){
        visited[y] = new bool[WIDTH];
        for(int x=0; x < WIDTH; x++){
            visited[y][x] = false;
        }
    }  

    for(int y =0; y < HEIGHT; y++){
        for(int x=0; x < WIDTH; x++){
            if(!visited[y][x] && cells[y][x]->getType() == '.'){
                Chamber* newChamber = new Chamber();
                floodCreateChamber(y, x, visited, newChamber);
                chambers.push_back(newChamber);
                #ifdef DEBUG
                cout << "chamber #" << chambers.size() - 1 << " created!" << endl;
                #endif
            }
        }
    }

}

Chamber *Floor::locateChamber(Cell *cell) {
    for(int i=0; i < chambers.size(); i++) {
        Chamber *curr = chambers[i];
        if(curr->hasCell(cell)) {
            return curr;
        }
    }
    return NULL; // Didn't find the coords in any chambers
}

void Floor::populate(char playerType) {
    #ifdef DEBUG
    cout << "populating" << endl;
    #endif

    /*************************
     * ORDER OF SPAWNING:    *
     *  1) Player            *
     *  2) Stairs            *
     *  3) Potions           *
     *  4) Gold              *
     *  5) Enemies           *
     ************************/
    if(!playerSpawned){
        Cell* playerCell = findUniqueCell();
        #ifdef DEBUG
        cout << "unique cell = [" << playerCell->getR() << "," << playerCell->getC() << "]" << endl;
        #endif

        Display::statusMessage += "Player character has spawned. ";
        // will only create a new player if its the first floor, which is what we want
        Player* player = Player::getInstance(playerType, playerCell);
        playerCell->setEntity(player);
    }
    if(!stairsSpawned){
        Cell *stairCell;

        do{
            stairCell = findUniqueCell();
        }while(sameChamber(Player::getInstance()->getCell(), stairCell));
        // avoid putting stairway in same chamber as player as per spec
        stairCell->makeStairway();
    }

    #ifdef DEBUG
    cout << "partial spawning..." << endl;
    #endif
    // spawn entites that were defined in the map file
    // TODO: we need to test that there partially spawned in enemies work!!! They may appear on the map but we need
    //       to make sure they can move and fight.
    for(int i=0; i < partialSpawn.size(); i++) {
        // TODO: not sure if there is anything else we need to do to add items that wasn't done in generateCells
        Enemy *curr = dynamic_cast<Enemy *>(partialSpawn[i]);
        if(curr) {
            Chamber *chamber = locateChamber(curr->getCell());
            chamber->addEnemy(curr);
            display->notify(curr->getR(), curr->getC(), curr->getDisplayChar());
        }
    }

    #ifdef DEBUG
    cout << "partial spawning done" << endl;
    #endif

    // spawn potions
    // every floor needs exactly 10 of them
    for(int i=potionSpawnCount; i < 10; i++){
        Cell *cell = findUniqueCell(); 
        char type = potionDie->rollDie();
        Entity *potion = Entity::getNewEntity(type, cell);
        cell->setEntity(potion);
    }

    // spawn gold.... gettin rich bitches
    for(int i=treasureSpawnCount; i < 10; i++){
        Chamber *randChamber = getRandChamber();
        Cell *cell = findUniqueCell(randChamber); 
        char type = goldDie->rollDie();
        #ifdef DEBUG
        cout << "Adding gold: " << type << endl;
        #endif

        //do special shit for dragons
        if(type == '8'){
            // we need a cell where a dragon can be in the gold's block radius
            while(cell->findNearbyEmpty() == NULL){
                randChamber = getRandChamber();
                cell = findUniqueCell(randChamber);
            }

            Entity *gold = Entity::getNewEntity(type, cell);
            cell->setEntity(gold);
            // we need to cast to get the treasure's dragon
            DragonTreasure *dt = dynamic_cast<DragonTreasure *>(gold);
            Dragon *dragon = dt->getDragon();
            dragon->getCell()->setEntity(dragon);
            dragon->setTreasure(dt);
            randChamber->addEnemy(dragon);
        }
        else{
            Entity *gold = Entity::getNewEntity(type, cell);
            cell->setEntity(gold);
        }
    }

    // spawn enemies
    // every floor needs exactly 20 of them
    for(int i=enemySpawnCount; i < 20; i++) {
        Chamber *randChamber = getRandChamber();
        Cell *cell = findUniqueCell(randChamber);
        char type = enemyDie->rollDie(); // Garunteed to return a type of enemy 
        Entity *entity = Entity::getNewEntity(type,cell); // TODO: we may need to cast this shit...
        cell->setEntity(entity); // make the cell point at the entity
        Enemy *enemy = dynamic_cast<Enemy *>(entity); // entity is known to be an enemy
        if(enemy) {
            randChamber->addEnemy(enemy); // finally, let the chamber know of the new enemy
            #ifdef DEBUG 
            cout << "spawned " << enemy->getDisplayChar() << endl;
            #endif 
        } else {
            cerr << "Floor: invalid cast from Entity* to Enemy*" << endl; 
        }
    }


    #ifdef DEBUG
    cout << "Floor: Floor populated" << endl;
    #endif
}


Chamber* Floor::getRandChamber() {
    Chamber *chamber;
    do{
        chamber = chambers[PRNG::random(chambers.size() - 1)];
        // dont try to spawn in a chamber thats already full
    }while(chamber->isFull());  
    return chamber;
}

Cell* Floor::findUniqueCell(Chamber *chamber) {
    if(!chamber) {
        chamber = getRandChamber();
    }
    Cell *cell;
    do{
        cell = chamber->getRandomCell();
        // dont spawn on a cell that already has an entity
    }while(cell->getEntity() != NULL);
    
    return cell;
}

bool Floor::sameChamber(Cell *a, Cell *b){
    for(int i=0;i<chambers.size();i++){
        if(chambers[i]->hasCell(a) && chambers[i]->hasCell(b))
            return true;
    }
    return false;
}

void Floor::notify(int i, int j, Cell *cell) {
    notifyDisplay(i,j,cell->getDisplayChar());
}

ostream &operator<<(ostream &out, Floor &f) {
    return out << *f.display;
}

Cell* Floor::getCell(int y, int x){
    if(y < 0 || y >= cells.size() || x < 0 || x>= cells[y].size()){
        #ifdef DEBUG
        cerr << "Invalid coordinates sent to floor.getCell" << endl;
        #endif
        return NULL;
    }
    else
        return cells[y][x];
}

void Floor::updatePotions(){
    // used potions will now have the right display chars,
    // we just need to update the display to show them
    for(int r=0; r<cells.size(); r++){
        for(int c=0; c<cells[r].size(); c++)
            notifyDisplay(r,c,cells[r][c]->getDisplayChar());
    }
}

