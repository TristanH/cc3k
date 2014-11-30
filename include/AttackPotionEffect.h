#ifndef __ATTACK_POTION_EFFECT_H__
#define __ATTACK_POTION_EFFECT_H__
#include "PotionEffect.h"

class Player;

class AttackPotionEffect : public PotionEffect {
    int amount;
    public:
        AttackPotionEffect(Player *base, int amount);
        int getAttack();
        int getDefence();
        int getHP();
        void changeHP(int amount);
};

#endif