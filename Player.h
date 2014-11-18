#ifndef __PLAYER_H__
#define __PLAYER_H__


class Player: public Character{
	Player *instance;

	//combat logic lives here
	public:
		void fight(Character *against);
		void *instance;

};

#endif
