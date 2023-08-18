#pragma once
#include <unordered_map>
#include <thread>

class ResultBuilder final
{
	private:
	std::unordered_map<std::thread::id, int64_t> _tsums;

	public:
	void init(const std::thread::id)noexcept;
	void add(const std::thread::id, const int32_t)noexcept;
	int64_t build()const noexcept;
};
