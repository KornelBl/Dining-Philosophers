#include "fork.h"


int fork::getId()
{
	return id;
}

fork::fork(int id)
{
	this->id = id;
}


fork::~fork()
{
}
