#ifndef __DEFENCE_POTION_EFFECT__
#define __DEFENCE_POTION_EFFECT__
#include "PotionEffect.h"

class Player;

class DefencePotionEffect : public PotionEffect {
    int amount;
    public:
        DefencePotionEffect(Player *base, int amount);
        int getAttack();
        int getDefence();
        int getHP();
        void changeHP(int amount);
};

#endif