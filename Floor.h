#ifndef __FLOOR_H__
#define __FLOOR_H__

//We do not have any stack allocated instances of Display
//so we don't need to include it. This reduces the chance of accidental
//circuluar dependencies
class Display;

//ifstream needed to generate maps from file
#include <fstream>


class Floor{
	// fill in proper numbers later, maybe needs to be on heap?
	Cell cells[100][100]; 
	Display *dislpay; //map needs to notify dislpay

	public:
		Floor(string fileName);
	friend std::ostream &operator<<(std::ostream &out, Floor &f);
};

#endif