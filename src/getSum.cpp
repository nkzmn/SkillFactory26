#include <cstdint>
#include <numeric>
#include "getSum.h"

int64_t getSum(const int32_t *begin, const int32_t *end)
{
	return std::accumulate(begin, end, static_cast<int64_t>(0));
}
