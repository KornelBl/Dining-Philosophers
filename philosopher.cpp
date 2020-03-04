#include "pch.h"
#include "philosopher.h"





void philosopher::think()
{
	int thinking_time = rand() % 1000 + 1500;

	std::cout << "Filozof nr " << this->id << " zaczal myslec" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(thinking_time));
	std::cout << "Filozof nr " << this->id << " skonczyl myslec" << std::endl;
}

void philosopher::eat()
{
	int eating_time = rand() % 1000 + 1500;

	//if (first->availability.try_lock() == false) {
	//	std::cout << "Filozof nr " << this->id << " czeka na pierwszy widelec" << std::endl;
	//	first->availability.lock();
	//}
	//if (second->availability.try_lock() == false){
	//	std::cout << "Filozof nr " << this->id << " czeka na drugi widelec" << std::endl;
	//	second->availability.lock();
	//}

	std::unique_lock<std::mutex> l1(first->availability, std::defer_lock);
	std::unique_lock<std::mutex> l2(second->availability, std::defer_lock);

	std::lock(l1, l2);
	
	std::cout << "Filozof nr " << this->id << " zaczal jesc" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(eating_time));
	std::cout << "Filozof nr " << this->id << " skonczyl jesc" << std::endl;

}

philosopher::philosopher(int id, std::shared_ptr<fork> left, std::shared_ptr<fork> right)
{
	this->id = id;
	if (left->getId() < right->getId()) {
		this->second = left;
		this->first = right;
	}
	else {
		this->second = right;
		this->first = left;
	}
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
