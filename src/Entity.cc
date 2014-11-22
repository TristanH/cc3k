Entity * Entity::getNewEntity(char type) {
    if(type == "H") {
        return new Human();
    } else if(type == "D") {
        return new Dwarf();
    } else if(type == "L") {
        return new Halfling();
    } else if(type == "E") {
        return new Elf();
    } else if(type == "O") {
        return new Orc();
    } else if(type == "M") {
        return new Merchant();
    }
}

int Entity::getR() { return cell->getR(); }
int Entity::getC() { return cell->getC(); }
Cell *Entity::getCell() { return cell; }