#include "DefencePotionEffect.h"
#include "Player.h"
#include "PotionEffect.h"
using namespace std;

DefencePotionEffect::DefencePotionEffect(Player *base, int amount) :
    PotionEffect(base), amount(amount) {}

int DefencePotionEffect::getAttack() { // Doesn't effect attack
    return base->getAttack();
}

int DefencePotionEffect::getDefence() { 
    return base->getDefence() + amount;
}