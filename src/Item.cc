#include "Item.h"

Item::Item(Cell *cell, char displayChar):
	Entity(cell, displayChar){}

bool Item::notify(){
	return true;// no implementation needed... i think
}
