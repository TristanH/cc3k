#include "Drow.h"
#include "Cell.h"
#include "Entity.h"
#include <string>
using namespace std;

Drow::Drow(Cell *cell) 
	: Player(cell,25,15,150) {}

Drow::~Drow() {

}


string Drow::raceStr() {
    return "Drow";
}