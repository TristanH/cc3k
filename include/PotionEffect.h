#ifndef __POTION_EFFECT_H__
#define __POTION_EFFECT_H__
#include "Player.h"
#include <string>

class PotionEffect : public Player {
public:
    PotionEffect(Player *base);
    ~PotionEffect();
    virtual int getAttack() = 0;
    virtual int getDefence() = 0;
    Player *unpack();

    // Need to give an implementation or I get an error
    bool notify(); 
    std::string raceStr();
protected:
    Player *base;
};

#endif