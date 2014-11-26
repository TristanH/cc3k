#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

#include "Display.h"
#include "Floor.h"
#include "Chamber.h"
#include "Player.h"
#include "Die.h"
#include "Cell.h"
#include "PRNG.h"
#include "Potion.h"

using namespace std;

void Floor::generateCells(string fileName) {
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
        
        // now parse the individual Cells
        char curr;
        vector<Cell*> column; //column vector to be pushed into cells (the vector of vectors of Cells)
        while(ss.get(curr)) {
            Cell *cell = new Cell(r, c, curr, this);
            Entity *entity = Entity::getNewEntity(curr, cell); // TODO: we should move this before the cell ctor and just include it as a parameter as defined in the cell ctor
            cell->setEntity(entity);
            column.push_back(cell);
            c++;
        }
        cells.push_back(column);
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

Floor::Floor(string fileName) :
    WIDTH(79), HEIGHT(25){
    display = Display::getInstance();
    generateCells(fileName);
    generateChambers();
}

Floor::~Floor() {
    // delete chambers
    for(int i=0; i < chambers.size(); i++)
        delete chambers[i];
    for(int i = 0; i < cells.size(); i++)
        for(int j=0; j < cells[i].size(); j++)
            delete cells[i][j];
    #ifdef DEBUG
    cout << "Floor: Floor, chambers, and cells deleted" << endl;
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

void Floor::setSpawnRates(Die *sr) {
    spawnRates = sr;
}

void Floor::floodCreateChamber(int y, int x, bool** visited, Chamber *chamber){
    if(visited[y][x] || cells[y][x]->getType() != '.')
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

void Floor::populate() {
    // The player should already be placed from CmdInterpreter
    
    // First put stairway somewhere on the map
    Cell *stairCell;

    do{
        stairCell = findUniqueCell();
    }while(sameChamber(Player::getInstance()->getCell(), stairCell));
    // avoid putting stairway in same chamber as player as per spec
    stairCell->makeStairway();

    // spawn potions
    // every floor needs exactly 10 of them
    for(int i=0; i < 10; i++){
        Cell *cell = findUniqueCell();
        // make potion here, add to cell

    }


    #ifdef DEBUG
    cout << "Floor populated: " << endl;
    cout << *display;
    #endif
}

Cell* Floor::findUniqueCell() {
    Chamber *chamber;
    do{
        chamber = chambers[PRNG::random(chambers.size() - 1)];
        // dont try to spawn in a chamber thats already full
    }while(chamber->isFull());  

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
    if(y < 0 || y >= HEIGHT || x < 0 || x>= WIDTH){
        cerr << "Invalid coordinates sent to floor.getCell";
        return NULL;
    }
    else
        return cells[y][x];
}