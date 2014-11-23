#include "Player.h"
#include "Shade.h"
#include "Drow.h"
#include "Vampire.h"
#include "Goblin.h"
#include "Troll.h"
#include "Cell.h"

using namespace std;

Player *Player::instance = NULL;

// We declared the dtor to be pure virtual because we need Player to not be instantiated. This causes issues though because all subclasses
// will implicitly called Player::~Player() when being destroyed but it doesn't have an implementation when it is pure virtual. This is why
// we simply implement it as an empty function here. It is pure virtual but also has a concrete (empty) implementation. Black magic brah.
Player::~Player(){}

Player::Player(Cell *cell, int atk, int def, int HP):
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

bool Player::move(string direction){
    if(tryMove(direction))
        return true;

    // TODO: check gold collecting here
    return false;
}

void Player::fight(Entity *against) {
    // TODO: implement fighting. Maybe it can call a takeDamage function on against which can be overriden
    //       such that if a player attacks a potion then it inidcates to the player that they can't attack
    //       a potion.
}