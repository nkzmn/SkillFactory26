#include <unordered_map>
#include <thread>
#include <numeric>
#include "resultBuilder.h"

void ResultBuilder::init(const std::thread::id threadId)noexcept
{
	_tsums[threadId] = 0;
}

void ResultBuilder::add(const std::thread::id threadId, const int32_t x)noexcept
{
	if(_tsums.find(threadId) == _tsums.end())
	{
		init(threadId);
	}

	_tsums[threadId] += x;
}

int64_t ResultBuilder::build()const noexcept
{
	return std::accumulate(_tsums.begin(), _tsums.end(), 0, [](int64_t x, auto it){return x + it.second;});
}
