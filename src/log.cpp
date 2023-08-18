#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include "log.h"
#include "createRandomArray.h"
#include "processors.h"

const size_t THREAD_COUNTS[] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
const size_t SIZES_NOT_THREADING[] = {100000, 1000000};

void log(const std::string &logName, int64_t (*func)(const int32_t*, const size_t, const size_t), const int32_t *arr, const size_t size, const size_t secondSize)
{
	std::cout << "Starting test '" << logName << "'. Array's length is " << size << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	int64_t result = func(arr, size, secondSize);

	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;

	std::cout << "Test '" << logName << "' finished. It took " << elapsed.count() << " sec." << std::endl;
	std::cout << "The result is " << result << std::endl;
}

void doTests(size_t size)
{
	std::cout << "Creating array with size = " << size << std::endl;

	int32_t *arr = createRandomArray(size);

	std::cout << "Array created" << std::endl << std::endl;

	for(size_t i = 0; i < sizeof(THREAD_COUNTS) / sizeof(size_t); ++i)
	{
		std::string logName = "Count sum with " + std::to_string(THREAD_COUNTS[i]) + " thread";
		if(THREAD_COUNTS[i] > 1)
		{
			logName += "s";
		}

		log(logName, sumByFlatThreads, arr, size, THREAD_COUNTS[i]);
		std::cout << std::endl;
	}

	std::cout << std::endl;

	for(size_t i = 0; i < sizeof(SIZES_NOT_THREADING) / sizeof(size_t); ++i)
	{
		std::string logName = "Count sum with tree thredding, size without threading is " + std::to_string(SIZES_NOT_THREADING[i]);

		log(logName, sumByThreadTree, arr, size, SIZES_NOT_THREADING[i]);
		std::cout << std::endl;
	}

	std::cout << std::endl;

	delete[] arr;
}
