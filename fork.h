#include <mutex>

class fork
{

public:

	std::mutex availability;

	fork();
	~fork();
};

