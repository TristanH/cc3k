#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player{
    Player *instance;
    void cleanup();
//combat logic lives here
	public:
		void fight(Character *against);
		void *instance getInstance();

};

#endif