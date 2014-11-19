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

void Floor::floodCreateChamber(int y, int x, bool** visited, Chamber *chamber){
    if(visited[y][x])
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
                Chamber* newChamber = new Chamber(y, x);
                floodCreateChamber(y, x, visited, newChamber);
                chambers.push(newChamber);
            }
        }
    }

}

ostream &operator<<(ostream &out, Floor &f) {
    return out << f.display;
}