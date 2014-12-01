#include <iostream>
#include <vector>
#include "Display.h"
#include "Player.h"
#include <iomanip>
using namespace std;

Display* Display::instance = NULL;
string Display::statusMessage = "";

void Display::cleanup() {
    delete instance;
    instance = NULL;
}

Display* Display::getInstance(){
    if(!instance){
        instance = new Display;
        atexit(cleanup);
    }
    return instance;
}

void Display::restart() {
    Display::cleanup();
}

void Display::notify(int i, int j, char newState) {
    theDisplay[i][j] = newState; //TODO: maybe we should use .get() because [] syntax doesn't have range check.
}

char Display::getState(int i, int j) {
    return theDisplay[i][j];
}

void Display::addColumn(vector<char> col){
	theDisplay.push_back(col);
}

void Display::reset(){
    theDisplay.erase(theDisplay.begin(), theDisplay.end());
}

ostream &operator<<(ostream &out, Display &d) {
    for(int i=0; i < d.theDisplay.size(); i++) {
        for(int j=0; j < d.theDisplay[i].size(); j++) {
            out << d.theDisplay[i][j];
        }
        out << endl;
    }
    Player *p = Player::getInstance();
    cout << "Race:  " << p->raceStr() << " Gold: " << p->getGold();
    cout << setw(55) << right << "Floor: " << p->getFloorNum() << left << endl;
    cout << "HP: " << p->getHP() << endl;
    cout << "Atk: " << p->getAttack() << endl;
    cout << "Def: " << p->getDefence() << endl;
    cout << "Action: " << Display::statusMessage << endl; // TODO: add action shit!
    return out;
}
