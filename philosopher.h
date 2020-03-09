#include "fork.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <random>
#include <string>

class philosopher
{
	int id;

	std::shared_ptr<fork> right, left;
	void think();
	void eat();

public:

	std::string status = "start";
	void operator()()
	{
		this->dine();
	}

	void execute();
	philosopher(int id, std::shared_ptr<fork> left, std::shared_ptr<fork> right);
	~philosopher();
	void dine();
};

