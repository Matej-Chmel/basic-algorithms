#pragma once
#include "sort_algos.hpp"

namespace chm {
	auto is_sorted(const std::vector<int>& v) -> bool;
	auto run_all_algos(size_t size) -> void;
	auto run_test(size_t size, SortAlgoType type) -> void;
	auto run_with_sizes(const std::vector<int>& sizes) -> void;
}
