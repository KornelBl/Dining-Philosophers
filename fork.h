#include <mutex>

class fork
{
	int id;

public:

	std::mutex availability;

	int getId();
	fork(int id);
	~fork();
};

