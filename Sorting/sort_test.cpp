#include "sort_test.hpp"
#include <algorithm>
#include <iostream>
#include "vector_data.hpp"

namespace chm {
	auto is_sorted(const std::vector<int>& v) -> bool {
		return std::is_sorted(v.begin(), v.end());
	}

	auto run_all_algos(const size_t size) -> void {
		run_test(size, SortAlgoType::BUBBLE);
		run_test(size, SortAlgoType::HEAP);
		run_test(size, SortAlgoType::INSERTION);
		run_test(size, SortAlgoType::MERGE);
		run_test(size, SortAlgoType::SELECTION);
		std::cout << "[PASSED] " << "Test size: " << size << '\n';
	}

	auto run_test(const size_t size, const SortAlgoType type) -> void {
		auto vec = generate_int_vector(size, 0, 100);
		const auto vec_copy = vec;

		switch(type) {
		case SortAlgoType::BUBBLE:
			bubble_sort(vec);
			break;
		case SortAlgoType::HEAP:
			heap_sort(vec);
			break;
		case SortAlgoType::INSERTION:
			insertion_sort(vec);
			break;
		case SortAlgoType::MERGE:
			merge_sort(vec);
			break;
		case SortAlgoType::SELECTION:
			selection_sort(vec);
			break;
		}

		if(!is_sorted(vec))
			throw AppError("[FAILED] {vec: ") << vec_copy << ", " << "algo: " <<
				to_string(type) << '}';
	}

	auto run_with_sizes(const std::vector<int>& sizes) -> void {
		for(const auto& s : sizes)
			run_all_algos(s);
	}
}
