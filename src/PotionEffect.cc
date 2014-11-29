#include "PotionEffect.h"
#include "Player.h"
#include <string>
using namespace std;

PotionEffect::PotionEffect(Player *base) : 
    base(base),
    Player(base->getCell(), base->getAttack(), base->getDefence(), base->getHP()){}

PotionEffect::~PotionEffect() { delete base; }

Player *PotionEffect::unpack() {
    #ifdef DEBUG
    cout << "PotionEffect: returning " << base->unpack() << endl;
    #endif
    return base->unpack();
}

void PotionEffect::notify() {
    base->notify();
}

string PotionEffect::raceStr() {
    return base->raceStr();
}