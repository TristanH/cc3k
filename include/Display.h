#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include <iostream>
#include <vector>

class Display {

    // Will be initialized simultaneously with the cells vector in Floor
    std::vector<std::vector<char> > theDisplay;
    static void cleanup();
    static Display *instance;

	public:

		static Display* getInstance();
		// notifys theDisplay at (i,j) with new state
		void notify(int i, int j, char newState);
		char getState(int i, int j);
		void addColumn(std::vector<char> col);
        static std::string statusMessage;

	friend std::ostream &operator<<(std::ostream &out, Display &d);

};


#endif