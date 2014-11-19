#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include "Display.h"
#include "Floor.h"
using namespace std;

void Floor::generate

void Floor::generateCells(string filename) {
    // generate the walls and shit.
    ifstream f(fileName.c_str());
    string line;
    int r = 0;
    int c = 0;
    while(getline(f,line)) {
        if(f.fail()) break; //reached EOF
        istringstream ss(line);
        char curr;
        vector<Cell> column; //column vector to be pushed into cells (the vector of vectors of Cells)
        while(ss.getchar(curr)) {
            Cell cell(r,c,curr);
            column.push_back(cell);
            c++;
        }
        cells.push_back(column);
        c = 0;
        r++;
    }
}

void Floor::updateRooms() {
    //iterate through the vector of rooms and update them
    vector<Chamber>::iterator it; //define iterator
    for(it = v.begin(); it != v.end(); ++i) {
        it->update();
    }
}

Floor::Floor(string fileName) : display(NULL){
    generateCells(filename);
    generateChambers();
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

void Floor::setSpawnRates(map<char,float> sr) {
    spawnRates = sr;
}

ostream &operator<<(ostream &out, Floor &f) {
    return out << f.display;
}