#pragma once
#include "fork.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <random>

class philosopher
{
	int id;

	//first,second instead of left, right to avoid deadlock, a fork with higher id number will be taken assign as first
	std::shared_ptr<fork> first, second;
	void think();
	void eat();

public:
	void operator()()
	{
		this->dine();
	}
	philosopher(int id, std::shared_ptr<fork> left, std::shared_ptr<fork> right);
	~philosopher();
	void dine();
};

