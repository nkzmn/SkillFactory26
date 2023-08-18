#include <cstddef>
#include "log.h"

const size_t SIZES[] = {1000, 2000, 10000, 1000000};

int main()
{
	for(size_t i = 0; i < sizeof(SIZES) / sizeof(size_t); ++i)
	{
		doTests(SIZES[i]);
	}

	return 0;
}
