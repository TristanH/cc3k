#include "AttackPotionEffect.h"
#include "Player.h"
#include "PotionEffect.h"
using namespace std;

AttackPotionEffect::AttackPotionEffect(Player *base, int amount) :
    PotionEffect(base), amount(amount) {}

int AttackPotionEffect::getAttack() {
    return base->getAttack() + amount;
}

int AttackPotionEffect::getDefence() { // Doesn't effect defence
    return base->getDefence();
}

int AttackPotionEffect::getHP() {
    return base->getHP();
}

void AttackPotionEffect::changeHP(int amount) {
    base->changeHP(amount);
}