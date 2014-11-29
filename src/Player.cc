#include "Player.h"
#include "Shade.h"
#include "Drow.h"
#include "Vampire.h"
#include "Goblin.h"
#include "Troll.h"
#include "Cell.h"
#include "Character.h"

#include <math.h>

using namespace std;

Player *Player::instance = NULL;

// We declared the dtor to be pure virtual because we need Player to not be instantiated. This causes issues though because all subclasses
// will implicitly called Player::~Player() when being destroyed but it doesn't have an implementation when it is pure virtual. This is why
// we simply implement it as an empty function here. It is pure virtual but also has a concrete (empty) implementation. Black magic brah.
Player::~Player(){
    #ifdef DEBUG
    cout << "Player: Player destroyed" << endl;
    #endif
}

Player::Player(Cell *cell, int atk, int def, int HP):
    gold(0),
    action("Player character has spawned."),
    Character(cell, '@', atk, def, HP){}

void Player::cleanup() {
    delete instance;
}

// After the player has been initialy created, you can get it by simply calling getInstance (no params).
// cmd defaults to 's' (see Player.h)
Player *Player::getInstance(char cmd, Cell *cell) {
    if(!instance) {
        if(cmd == 's') {
            instance = new Shade(cell);
        } else if(cmd == 'd') {
            instance = new Drow(cell);
        } else if(cmd == 'v') {
            instance = new Vampire(cell);
        } else if(cmd == 'g') {
            instance = new Goblin(cell);
        } else if(cmd == 't') {
            instance = new Troll(cell);
        }
        atexit(cleanup);
    }
    return instance;
}

void Player::addGold(int amount) {
    gold += amount;
}

int Player::getGold() {
    return gold;
}

string Player::getAction() {
    return action;
}

bool Player::move(string direction){
    if(tryMove(direction)) { // Implemented in Character.h
        #ifdef DEBUG
        cout << "Player: tryMove returned true" << endl;
        #endif
        action = "PC moved " + Character::dirFull(direction); // TODO: have to add the "and sees a..." portion
        return true;
    }

    // TODO: check gold collecting here
    action = "PC can't move " + Character::dirFull(direction);
    return false;
}

void Player::fight(Entity *against) {
    //TODO: item check
    //if Item
    //   return;
    
    //if we check to make sure the entity's not an item, we can safely cast to a character
    // we need this to get access to the Character specific functions
    Character *cAgainst = static_cast<Character*>(against);
    
    int damage = ceil((100/(100 + cAgainst->getDefence()))*attack);
    cAgainst->changeHP(-damage);
    //specialFightEffect is used so subclasses can have their special powers in combat
    specialFightEffect(cAgainst, damage);
}

void Player::specialFightEffect(Character *against, int damage){
    // do nothing for standard player, subclasses CAN but don't have to overwrite
    ;
}