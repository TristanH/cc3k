#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Entity.h"
#include <string>

class Character: public Entity{

	protected:
		Character(Cell *cell, char dc, int atk, int def, int hp, int maxHP = -1);
		int attack;
		int defence;
		int HP;
		int maxHP;
	public:
		// fight can be called by players on enemies and enemies on players
		virtual void fight(Entity *against) = 0;
		virtual int specialFightEffect(Character *against, int damageDone) = 0;
		//virtual void notify() = 0;
		virtual ~Character(){}

		// character tries to move in this direction, returns true if they did, false if they couldn't
		// if it does, it will remove itself from the cell it's on (has a cell from entity) and set itself on the adjacent one
		// the old cell and the new cell with both notify map
		bool tryMove(std::string direction);

		virtual int getDefence();
		virtual int getAttack();
		int getHP();
		int getMaxHP();
		void changeHP(int amount);
		virtual void onDeath() = 0;

		static std::string dirFull(std::string shortDir);

};

#endif