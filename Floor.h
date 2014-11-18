#ifndef __FLOOR_H__
#define __FLOOR_H__

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