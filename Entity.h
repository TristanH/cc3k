#ifndef __ENTITY_H__
#define __ENTITY_H__

class Entity{
	Cell *cell;
	char displayChar;

	public:
		virtual void notify() = 0;
		virtual Entity() = 0;
		virtual ~Entity(){};
};

#endif