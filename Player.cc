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

bool Player::move(string direction){
    if(tryMove(direction))
        return true;

    // TODO: check gold collecting here
    return false;
}