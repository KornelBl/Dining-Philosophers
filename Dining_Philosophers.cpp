// Dining_Philosophers.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "philosopher.h"
#include <iostream>
#include <thread>
#include <ncurses.h>

	void visualise(std::vector<std::shared_ptr<philosopher>> philos);
	

int main()
{
	int N = 5;

	std::vector<std::shared_ptr<fork>> forks;
	std::vector<std::shared_ptr<philosopher>> philos;
	std::vector<std::thread> threads;

	for(int i = 0; i < N; i++){
		auto f = std::make_shared<fork>();
		forks.push_back(f);
	}

	for(int i = 0; i < N; i++){
		auto philo = std::make_shared<philosopher>(i,forks[i],forks[(i+1)%N]);
		philos.push_back(philo);
	}

	for(int i = 0;i < N;i++){
		threads.push_back(std::thread(&philosopher::execute, philos[i]));
	}

	std::thread visualise_thread(&visualise, philos);

	for(int i = 0; i < N; i++){
		threads[i].join();
	}

	visualise_thread.join();
  

}

void visualise(std::vector<std::shared_ptr<philosopher>> philos)
{
	int N = philos.size();
	initscr();
	move(0,15);
	printw("Stan");
	
	
	move(0,25);
	printw("Czas");

	for(int i = 0; i < N; i++){
			move(i+1, 0);
			printw("Filozof nr ");
			printw(std::to_string(i+1).c_str());
		}
	
	while(true){
		
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		for(int i = 0; i < N; i++){
			move(i+1,15);
			printw(philos[i]->status.c_str());
			refresh();
		}

	}
    endwin();
	
}


