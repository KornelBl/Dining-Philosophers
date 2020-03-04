// Dining_Philosophers.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include "philosopher.h"
#include "fork.h"
#include <iostream>
#include <thread>

int main()
{
	auto f1 = std::make_shared<fork>(1);
	auto f2 = std::make_shared<fork>(2);
	auto f3 = std::make_shared<fork>(3);

	philosopher p1(1, f1, f2);
	philosopher p2(2, f2, f3);
	philosopher p3(3, f3, f1);


	std::thread t1(p1);
	std::thread t2(p2);
	std::thread t3(p3);

	t1.join();
	t2.join();
	t3.join();
  
}

