#include "Player.h"

class Shade;
class Drow;
class Vampire;
class Goblin;
class Troll;

using namesapce std;

void Player::cleanup() {
    delete instance;
}

Player *Player::getInstance(char cmd = 's') {
    if(!instance) {
        if(cmd == 's') {
            instance = new Shade();
        } else if(cmd == 'd') {
            instance = new Drow();
        } else if(cmd == 'v') {
            instance = new Vampire();
        } else if(cmd == 'g') {
            instance = new Goblin();
        } else if(cmd == 't') {
            instance = new Troll();
        }
        atexit(cleanup);
    }
    return instance;
}

void Player::addGold(int amount) {
    gold += amount;
}

void Player::fight(Entity *against) {
    // TODO: implement fighting. Maybe it can call a takeDamage function on against which can be overriden
    //       such that if a player attacks a potion then it inidcates to the player that they can't attack
    //       a potion.
}