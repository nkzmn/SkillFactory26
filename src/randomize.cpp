#include <cstdint>
#include <cstdlib>
#include <ctime>

template<class T>
T randomize()
{
	static bool initiated = false;

	if(!initiated)
	{
		srand(time(nullptr));
		initiated = true;
	}

	size_t size = sizeof(size_t) / sizeof(int);

	int *ints = new int[size];

	for(size_t i = 0; i < size; ++i)
	{
		*(ints + i) = rand();
	}

	T result = *(reinterpret_cast<T*>(ints));

	delete[] ints;

	return rand() % 2 ? result : ~result;
}
