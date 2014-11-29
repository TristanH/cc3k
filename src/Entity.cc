#include "Entity.h"
#include "Cell.h"
#include "Human.h"
#include "Dwarf.h"
#include "Halfling.h"
#include "Elf.h"
#include "Orc.h"
#include "Merchant.h"
#include "Dragon.h"

#include "HealthPotion.h"
#include "AttackPotion.h"
#include "DefencePotion.h"

#include <iostream>

using namespace std;

Entity::Entity(Cell* cell, char displayChar):
    cell(cell), displayChar(displayChar){
        if(cell != NULL){
            cell->setEntity(this);
        }
        else{
            cerr << "Warning: entity constructed with NULL cell";
        }
    }

Entity * Entity::getNewEntity(char type, Cell *cell) {
    if(type == 'H') {
        return new Human(cell);
    } else if(type == 'd') {
        return new Dwarf(cell);
    } else if(type == 'L') {
        return new Halfling(cell);
    } else if(type == 'E') {
        return new Elf(cell);
    } else if(type == 'O') {
        return new Orc(cell);
    } else if(type == 'M') {
        return new Merchant(cell);
    } else if(type == 'D') {
        return new Dragon(cell);
    } else if(type == '0') {
        return new HealthPotion(cell, 10);
    } else if(type == '1') {
        return new AttackPotion(cell, 10); 
    } else if(type == '2') {
        return new DefencePotion(cell, 10); 
    } else if(type == '3') {
        return new HealthPotion(cell, -10); 
    } else if(type == '4') {
        return new AttackPotion(cell, -10); 
    } else if(type == '5') {
        return new DefencePotion(cell, -10); 
    }
    #ifdef DEBUG
    cout << "Entity: returning NULL enemy!!" << endl;
    #endif
    return NULL; // Not provided with valid enemy type
}

int Entity::getR() { return cell->getR(); }
int Entity::getC() { return cell->getC(); }
Cell *Entity::getCell() { return cell; }
char Entity::getDisplayChar(){ return displayChar; }
void Entity::setCell(Cell *newCell) {
    cell = newCell;
}