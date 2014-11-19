#include <iostream>
#include <map>
#include "Display.h"
#include "Floor.h"
using namespace std;

Floor::Floor(string fileName) : display(NULL){
    // generate the walls and shit.
    // determine where the rooms are and put them into the rooms vector
}



void Floor::notify() {
    //what are we notifying the display of??
}

void Floor::updateGameStep() {
    // TODO: is the player implicitly updated before this????? I DUNNOOOOO BRAH
    updateRooms();
    notifyDisplay();
}

void Floor::updateRooms() {
    //iterate through the vector of rooms and update them
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