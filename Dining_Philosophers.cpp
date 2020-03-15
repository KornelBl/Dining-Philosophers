// Dining_Philosophers.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "philosopher.h"
#include <iostream>
#include <thread>
#include <ncurses.h>

void writeGUI(int N);
void visualise(const std::vector<std::shared_ptr<philosopher>> &philos);

static bool is_running = true;

void initialize_table(std::vector<std::shared_ptr<fork>> &forks,
					  std::vector<std::shared_ptr<philosopher>> &philos,
					  std::vector<std::thread> &threads, int N);

void clear_table(std::vector<std::shared_ptr<fork>> &forks,
				 std::vector<std::shared_ptr<philosopher>> &philos,
				 std::vector<std::thread> &threads);

int main()
{
	initscr();

	int N = 5;
	std::vector<std::shared_ptr<fork>> forks;
	std::vector<std::shared_ptr<philosopher>> philos;
	std::vector<std::thread> threads;

	initialize_table(forks, philos, threads, N);

	std::unique_ptr<std::thread> visualise_thread = std::make_unique<std::thread>(&visualise, philos);

	do
	{
		char h = getchar();

		switch (h)
		{
		case 'q':
			is_running = false;
			visualise_thread->join();
			clear_table(forks, philos, threads);
			break;
		case 'a':
			is_running = false;
			visualise_thread->join();
			clear_table(forks, philos, threads);
			N++;
			initialize_table(forks, philos, threads, N);
			is_running = true;
			visualise_thread = std::make_unique<std::thread>(&visualise, philos);
			break;
		case 'z':
			is_running = false;
			visualise_thread->join();
			clear_table(forks, philos, threads);
			N--;
			initialize_table(forks, philos, threads, N);
			is_running = true;
			visualise_thread = std::make_unique<std::thread>(&visualise, philos);
			break;
		default:
			break;
		}

	} while (is_running);
	endwin();
}

void initialize_table(std::vector<std::shared_ptr<fork>> &forks,
					  std::vector<std::shared_ptr<philosopher>> &philos,
					  std::vector<std::thread> &threads, int N)
{
	for (int i = 0; i < N; i++)
	{
		auto f = std::make_shared<fork>();
		forks.push_back(f);
	}

	for (int i = 0; i < N; i++)
	{
		auto philo = std::make_shared<philosopher>(i, forks[i], forks[(i + 1) % N]);
		philos.push_back(philo);
	}

	for (int i = 0; i < N; i++)
	{
		threads.push_back(std::thread(&philosopher::execute, philos[i]));
	}
}

void clear_table(std::vector<std::shared_ptr<fork>> &forks,
				 std::vector<std::shared_ptr<philosopher>> &philos,
				 std::vector<std::thread> &threads)
{
	for (auto philo : philos)
		philo->disactivate();
	for (auto &thread : threads)
		thread.detach();

	forks.clear();
	threads.clear();
	philos.clear();
}

void writeGUI(int N)
{
	move(0, 15);
	printw("Stan");

	move(0, 30);
	printw("exit: q");
	move(1, 30);
	printw("+1 philosopher: a");
	move(2, 30);
	printw("-1 philosopher: z");

	for (int i = 0; i < N; i++)
	{
		move(i + 1, 0);
		printw("Filozof nr ");
		printw(std::to_string(i + 1).c_str());
	}
}

void visualise(const std::vector<std::shared_ptr<philosopher>> &philos)
{
	int N = philos.size();

	writeGUI(N);

	while (is_running)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		for (auto philo : philos)
		{
			move(philo->getID() + 1, 15);
			printw(philo->status.c_str());
		}

		refresh();
	}

	clear();
}
