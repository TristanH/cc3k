#include "PotionEffect.h"
#include "Player.h"
#include <string>
using namespace std;

PotionEffect::PotionEffect(Player *base) : 
    base(base),
    Player(base->getCell(), base->getAttack(), base->getDefence(), base->getHP(), base->getGold(), base->getFloorNum(), base->getMaxHP()){}

PotionEffect::~PotionEffect() { delete base; }

Player *PotionEffect::unpack() {
    #ifdef DEBUG
    cerr << "PotionEffect: unpacking..." << endl;
    #endif
    return base->unpack();
}

bool PotionEffect::notify() { // TODO: does this need to be bool??
    base->notify();
}

void PotionEffect::gameTick() {
    #ifdef DEBUG
    cout << "calling super gameTick()" << endl; 
    #endif
    base->gameTick();
}

string PotionEffect::raceStr() {
    return base->raceStr();
}