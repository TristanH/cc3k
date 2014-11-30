#include "Shade.h"
#include "Cell.h"
#include "Entity.h"
#include <string>
using namespace std;

Shade::Shade(Cell *cell) : 
	Player(cell, 25, 25, 125) {}

Shade::~Shade(){

}


string Shade::raceStr() {
    return "Shade";
}