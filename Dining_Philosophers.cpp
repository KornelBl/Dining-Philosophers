// Dining_Philosophers.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "philosopher.h"
#include <iostream>
#include <thread>
#include <ncurses.h>

	void visualise();
	
	
	
	auto f1 = std::make_shared<fork>(1);
	auto f2 = std::make_shared<fork>(2);
	auto f3 = std::make_shared<fork>(3);


	philosopher p1(1, f1, f2);
	philosopher p2(2, f2, f3);
	philosopher p3(3, f3, f1);




int main()
{
	
	std::thread t1(&philosopher::execute, &p1);
	std::thread t2(&philosopher::execute, &p2);
	std::thread t3(&philosopher::execute, &p3);
	
	std::thread visualise_thread(&visualise);

	t1.join();
	t2.join();
	t3.join();
	visualise_thread.join();
  

}

void visualise()
{
	initscr();
	move(0,15);
	printw("Stan");
	
	
	move(0,25);
	printw("Czas");

	move(1,0);
	printw("Filozof nr 1 ");
	move(2,0);
	printw("Filozof nr 2 ");
	move(3,0);
	printw("Filozof nr 3 ");
	while(true){
		
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		move(1,15);
		printw(p1.status.c_str());
		refresh();
		move(2,15);
		printw(p2.status.c_str());
		refresh();
		move(3,15);
		printw(p3.status.c_str());
		refresh();
	}
    endwin();
	
}


