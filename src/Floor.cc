#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include "Display.h"
#include "Floor.h"
#include "Player.h"
#include "Die.h"
using namespace std;

void Floor::generateCells(string filename) {
    // generate the walls and shit.
    // initialize display->theDisplay simultaneously
    ifstream f(fileName.c_str());
    string line;
    int r = 0;
    int c = 0;
    while(getline(f,line)) {
        if(f.fail()) break; //reached EOF
        istringstream ss(line);
        char curr;
        vector<Cell> column; //column vector to be pushed into cells (the vector of vectors of Cells)
        vector<char> theDisplay_column; //column vector to be pused into display->theDisplay
        while(ss.getchar(curr)) {
            Entity *entity = Entity::getNewEntity(curr);
            Cell cell = new Cell(r, c, curr, entity);
            column.push_back(cell);
            theDisplay_column.push_back(curr);
            c++;
        }
        cells.push_back(column);
        display->theDisplay.push_back(theDisplay_column);
        c = 0;
        r++;
    }
    // At this point, both the cells and display->theDisplay should be initialized
}

void Floor::notifyChambers() {
    //iterate through the vector of rooms and update them
    vector<Chamber>::iterator it; //define iterator
    for(it = v.begin(); it != v.end(); ++i) { // iterators look weird but the are just glorified pointers
        it->update(); //update the current chamber in the vector of chambers
    }
}

Floor::Floor(string fileName) : display(NULL){
    generateCells(filename);
    generateChambers();
    player = Player::getInstance();
}

Floor::~Floor() {

    // delete enemies
    for(int i=0; i < enemies.size(); i++)
        for(int j=0; j < enemies[i].size(); j++)
            delete enemies[i][j];

    // delete chambers
    for(int i=0; i < chambers.size(); j++)
        delete chambers[i];
}

void Floor::updateGameStep() {
    // TODO: is the player implicitly updated before this????? I DUNNOOOOO BRAH
    updateRooms();
    notifyDisplay();
}

void Floor::notifyDisplay(int i, int j, char newState) {
    // this should probably be called any time the floor is updated
    display->notify(i,j,newState);
}

void Floor::setDisplay(Display *d) {
    display = d;
}

void Floor::setSpawnRates(Die sr) {
    spawnRates = sr;
}

void Floor::floodCreateChamber(int y, int x, bool** visited, Chamber *chamber){
    if(visited[y][x] || cells[y][x].getType() != '.')
        return;
    chamber.addCell(cells[y][x]);
    visited[y][x] = true;
    floodCreateChamber(y+1,x,visited, chamber);
    floodCreateChamber(y,x+1,visited, chamber);
    floodCreateChamber(y-1,x,visited, chamber);
    floodCreateChamber(y,x-1,visited, chamber);
}

void Floor::generateChambers(){
    bool **visited;

    visted = new int*[HEIGHT];
    for(int y=0; y < HEIGHT; y++){
        visited[y][x] = new int[WIDTH];
        for(int x=0; x < WIDTH; x++){
            visited[y][x] = false;
        }
    }  

    for(int y =0; y < 25; y++){
        for(int x=0; x<79; x++){
            if(!visited[y][x] && cells[y][x].getType() == '.'){
                Chamber* newChamber = new Chamber();
                floodCreateChamber(y, x, visited, newChamber);
                chambers.push(newChamber);
            }
        }
    }

}

void Floor::populate() {
    // TODO: add this funcitonality. We just want shit to compiles so we can leave it blank for now.
}

void Floor::notify(int i, int j, Entity *entity) {
    display->notify(i,j,entity->displayChar);
}

ostream &operator<<(ostream &out, Floor &f) {
    return out << f.display;
}

Cell* Floor::getCell(int y, int x){
    if(y < 0 || y >= HEIGHT || x < 0 || x>= WIDTH){
        cerr << "Invalid coordinates sent to floor.getCell"
        return NULL;
    }
    else
        return cells[y][x];
}