#include "philosopher.h"



void philosopher::execute(){
	dine();
}

void philosopher::think()
{
	int thinking_time = rand() % 1000 + 1500;

	status = "mysli";
	std::this_thread::sleep_for(std::chrono::milliseconds(thinking_time));
}

void philosopher::eat()
{
	int eating_time = rand() % 1000 + 1500;


	std::unique_lock<std::mutex> l1(left->availability, std::defer_lock);
	std::unique_lock<std::mutex> l2(right->availability, std::defer_lock);
	
	status = "czeka";
	
	std::lock(l1, l2);
	
	status = "je   ";
	std::this_thread::sleep_for(std::chrono::milliseconds(eating_time));
}

philosopher::philosopher(int id, std::shared_ptr<fork> left, std::shared_ptr<fork> right)
{
	this->id = id;
	this->right = right;
	this->left = left;

	// if (left->getId() < right->getId()) {
	// 	this->second = left;
	// 	this->first = right;
	// }
	// else {
	// 	this->second = right;
	// 	this->first = left;
	// }
}


philosopher::~philosopher()
{
}

void philosopher::dine()
{
	while (true) {
		this->eat();
		this->think();
	}
}
