#include <cstddef>
#include <cstdint>
#include "createRandomArray.h"
#include "randomize.h"

int32_t *createRandomArray(const size_t size)
{
	int32_t *res = new int32_t[size];

	for(size_t i = 0; i < size; ++i)
	{
		*(res + i) = randomize<int32_t>() / 1000000;
	}

	return res;
}
