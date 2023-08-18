#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <thread>
#include <vector>
#include "processors.h"
#include "getSum.h"
#include "resultBuilder.h"

int64_t sumByFlatThreads(const int32_t *arr, const size_t size, const size_t threadCounts)
{
	auto getStep = [size, threadCounts]()
	{
		if(size > threadCounts)
		{
			const size_t step = size / threadCounts;
			return  size % threadCounts ? step + 1 : step;
		}
		return static_cast<size_t>(1);
	};

	ResultBuilder builder;
	std::vector<std::thread> threads;
	const int32_t *end = arr + size + 1;
	const size_t step = getStep();

	for(const int32_t *b = arr; b < end; b += step)
	{
		const int32_t *e = b + step;

		if(e > end)
		{
			e = end;
		}
		threads.push_back(std::thread([b, e, &builder]()
		{
			builder.init(std::this_thread::get_id());
			builder.add(std::this_thread::get_id(), getSum(b, e));
		}));
	}

	std::for_each(threads.begin(), threads.end(), [](auto &it){it.join();});

	return builder.build();
}

void getRes(const int32_t *begin, const int32_t *end, const int32_t minSize, int64_t &dest)
{
	if(end - begin <= minSize)
	{
		dest = getSum(begin, end);
	}
	else
	{
		int64_t left, right;
		const int32_t *middle = begin + (end - begin) / 2;

		std::thread leftThread(getRes, begin, middle, minSize, std::ref(left));
		std::thread rightThread(getRes, middle, end, minSize, std::ref(right));
		leftThread.join();
		rightThread.join();

		dest = left + right;
	}
};

int64_t sumByThreadTree(const int32_t *arr, const size_t size, const size_t minSize)
{

	int64_t result;

	getRes(arr, arr + size, minSize, result);

	return result;
}
