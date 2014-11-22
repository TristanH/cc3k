#include <iostream>
#include <vector>
#include "Display.h"
using namespace std;

void Display::notify(int i, int j, char newState) {
    theDisplay[i][j] = newState; //TODO: maybe we should use .get() because [] syntax doesn't have range check.
}

char Display::getState(int i, int j) {
    return theDisplay[i][j];
}

void Display::addColumn(vector<char> col){
	theDisplay.push_back(col);
}

ostream &operator<<(ostream &out, Display &d) {
    for(int i=0; i < d.theDisplay.size(); i++) {
        for(int j=0; j < d.theDisplay[i].size(); j++) {
            out << d.theDisplay[i][j];
        }
        out << endl;
    }
    return out;
}