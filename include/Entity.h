#ifndef __ENTITY_H__
#define __ENTITY_H__

//We do not have any stack allocated instances of Cell
//so we don't need to include it. This reduces the chance of accidental
//circuluar dependencies
class Cell;

//for ostream
#include <iostream>

class Entity{

    protected:
        //all entities are aware of the cell they occupy and they must be able to
        //notify the cells they move to of their presence
        Cell *cell;

        //actual character array that will be displayed to stdout.
        //This will be set when the Entity is spawned (in the case of an enemy)
        //or created at the start of the game (in the case of the player)
        char displayChar;
        Entity(Cell* cell, char displayChar);

	public:
        int getR();
        int getC();
        Cell *getCell();
        void setCell(Cell *newCell);
        char getDisplayChar();
		virtual void notify() = 0;
		virtual ~Entity(){};
        
        // This creates and returns a pointer to a new Enemy of the corresponding type of "type".
        static Entity *getNewEntity(char type, Cell* cell);

};

#endif