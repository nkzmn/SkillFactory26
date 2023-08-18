#pragma once
#include <cstddef>
#include <cstdint>

int64_t sumByFlatThreads(const int32_t*, const size_t, const size_t);

int64_t sumByThreadTree(const int32_t*, const size_t, const size_t);
