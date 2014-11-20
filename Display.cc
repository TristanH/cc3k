#include <iostream>
#include "Display.h"
using namespace std;

void Display::notify(int i, int j, char newState) {
    theDisplay[i][j] = newState; //TODO: maybe we should use .get() because [] syntax doesn't have range check.
}

char Display::getState(int i, int j) {
    return theDisplay[i][j];
}

ostream &operator<<(ostream &out, Display &d) {
    for(int i=0; i < theDisplay.size(); i++) {
        for(int j=0; j < theDisplay[i].size(); j++) {
            out << theDisplay[i][j];
        }
        out << endl;
    }
    return out;
}