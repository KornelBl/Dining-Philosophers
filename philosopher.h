#include "fork.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <random>
#include <string>

class philosopher
{
	int id;

	bool active = true;
	std::shared_ptr<fork> right, left;
	void think();
	void eat();

public:
	std::string status = "start";

	int getID();
	void execute();
	void disactivate();
	philosopher(int id, std::shared_ptr<fork> left, std::shared_ptr<fork> right);
	~philosopher();
	void dine();
};
