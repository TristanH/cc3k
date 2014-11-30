#include "PotionEffect.h"
#include "Player.h"
#include <string>
using namespace std;

PotionEffect::PotionEffect(Player *base) : 
    base(base),
    Player(base->getCell(), base->getAttack(), base->getDefence(), base->getHP(), base->getGold(), base->getFloorNum()){}

PotionEffect::~PotionEffect() { delete base; }

Player *PotionEffect::unpack() {
    return base->unpack();
}

bool PotionEffect::notify() {
    base->notify();
}

string PotionEffect::raceStr() {
    return base->raceStr();
}