#include "Player.h"
#include "Shade.h"
#include "Drow.h"
#include "Vampire.h"
#include "Goblin.h"
#include "Troll.h"
#include "Cell.h"
#include "Character.h"
#include "Display.h"
#include "AttackPotionEffect.h"
#include "DefencePotionEffect.h"
#include "Treasure.h"
#include "Merchant.h"
#include "Dragon.h"

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
    floorNum(1), // TODO: increment when going to another floor
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

void Player::addPotion(char type, int amount) {
    if(instance) {
        if(type == '1' || type == '4') {
            instance = new AttackPotionEffect(instance,amount);
        } else if(type == '2' || type == '5') { 
            #ifdef DEBUG
            cout << "Player: defence potion" << endl;
            #endif
            instance = new DefencePotionEffect(instance,amount);
            #ifdef DEBUG
            cout << "Player: instance decorated" << endl;
            #endif
        } else if(type == '0' || type == '3') { // health potions
            instance->changeHP(amount);
        } // else, don't modify instance
    } else {
        cerr << "Player: no instance of Player to decorate" << endl;
    }
}

Player *Player::unpack() { 
    #ifdef DEBUG
    cout << "Player: reached decorator base-case" << endl;
    #endif
    return this; 
}

void Player::removePotions() {
    if(instance) {
        #ifdef DEBUG
        cout << "Player: removing potions" << endl;
        #endif
        instance = instance->unpack();
    } else {
        cerr << "Player: no instance of Player to remove decorations from" << endl;
    }
}

void Player::addGold(int amount) {
    gold += amount;
}


int Player::getGold() {
    return gold;
}

int Player::getFloorNum() {
    return floorNum;
}

void Player::nextFloor() {
    floorNum++;
}

bool Player::move(string direction){
    if(tryMove(direction)) { // Implemented in Character.h
        Display::statusMessage += "PC moved " + Character::dirFull(direction) + ". "; // TODO: have to add the "and sees a..." portion
        return true;
    }

    // TODO: check gold collecting here
    Display::statusMessage += "PC can't move " + Character::dirFull(direction) + ". ";
    return false;
}

void Player::fight(Entity *against) {
    //if we check to make sure the entity's not an item, we can safely cast to a character
    // we need this to get access to the Character specific functions
    Character *cAgainst = dynamic_cast<Character*>(against);

    if(!cAgainst){
        Display::statusMessage+= "Player tried to attack non-enemy, nothing happens! ";
        #ifdef DEBUG
        cout << "Player tried to fight non-character!! returning" << endl;
        #endif
        return;
    }
    
    int damage = ceil((100.0/(100 + cAgainst->getDefence()))*this->getAttack());
    cAgainst->changeHP(-damage);
    #ifdef DEBUG
    cout << "Dealt " << damage << " damage. " << endl;
    cout << "Enemy's HP is now " << cAgainst->getHP() << endl;
    #endif
    //specialFightEffect is used so subclasses can have their special powers in combat
    specialFightEffect(cAgainst, damage);

    // cover special merchant and dragon aggression case
    if(against->getDisplayChar() == 'M')
        Merchant::makeHostile();
    else if(against->getDisplayChar() == 'D'){
        Dragon *dragon = dynamic_cast<Dragon*>(cAgainst);
        dragon->makeHostile();
    }
    // we will deal with enemy onDeath and such when we update it from chamber
}

void Player::specialFightEffect(Character *against, int damage){
    // do nothing for standard player, subclasses CAN but don't have to overwrite
    ;
}

void Player::onDeath(){
    ; //This doesnt need to be implemented, cmdinterpreter will check for player death
}

bool Player::notify(){
    return true;
}