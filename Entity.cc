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