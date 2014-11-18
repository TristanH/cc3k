#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include <iostream>

class Display {

	char theDisplay[100][100];
	public:
		//notifys theDisplay at (i,j) with new state
		void notify(int i, int j, char state);
		char getState(int i, int j);

	friend std::ostream &operator<<(std::ostream &out, Display &d);

};


#endif