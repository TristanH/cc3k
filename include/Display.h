#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include <iostream>

class Display {

    // Will be initialized simultaneously with the cells vector in Floor
    std::vector<std::vector<char> > theDisplay;
    
	public:
		// notifys theDisplay at (i,j) with new state
		void notify(int i, int j, char newState);
		char getState(int i, int j);

	friend std::ostream &operator<<(std::ostream &out, Display &d);

};


#endif