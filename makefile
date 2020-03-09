all:
	g++ -pthread Dining_Philosophers.cpp fork.cpp fork.h philosopher.cpp philosopher.h -o dining_philosophers -lncurses
