#ifndef __DIE_H__
#define __DIE_H__

// used for probabilities of enemies spawning
class Die {

	//number of sides on the die
	int numSides;

	// number of sides we have a result for
	int sidesWithResult;

	int* sides;

public:
	Die(int numSides);
	~Die();
	void addSides(int number, char result);
	char rollDie();
};

#endif