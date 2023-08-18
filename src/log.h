#pragma once
#include <cstddef>
#include <cstdint>
#include <string>

void log(const std::string&, int64_t (*func)(const int32_t*, const size_t, const size_t), const int32_t*, const size_t, const size_t);

void doTests(const size_t);
