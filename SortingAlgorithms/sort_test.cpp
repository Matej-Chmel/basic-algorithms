#include "sort_test.hpp"

#include <iostream>
#include <random>

namespace chm {
	auto operator<<(
		std::ostream& s,
		const std::vector<int>& v
	) -> std::ostream& {
		if(v.empty()) {
			s << "EMPTY";
			return s;
		}

		const auto last_idx = v.size() - 1;
		s << '[';

		for(size_t i = 0; i < last_idx; i++)
			s << v[i] << ", ";

		s << v[last_idx] << ']';
		return s;
	}

	auto generate_int_vector(
		const size_t size,
		const int min,
		const int max
	) -> std::vector<int> {
		std::default_random_engine gen(std::random_device{}());
		const std::uniform_int_distribution<int> dist(min, max);
		std::vector<int> res;
		res.reserve(size);

		for(size_t i = 0; i < size; i++)
			res.emplace_back(dist(gen));

		return res;
	}

	auto is_sorted(const std::vector<int>& v) -> bool {
		if(v.size() < 2)
			return true;

		for(size_t i = 1; i < v.size() - 1; i++)
			if(v[i] < v[i - 1])
				return false;
		return true;
	}

	auto run_all_algos(const size_t size) -> void {
		run_test(size, SortAlgoType::BUBBLE);
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

		if(!is_sorted(vec)) {
			throw AppError("[FAILED] {vec: ") << vec_copy << ", " << "algo: " <<
				to_string(type) << '}';
		}
	}

	auto run_with_sizes(const std::vector<int>& sizes) -> void {
		for(const auto& s : sizes)
			run_all_algos(s);
	}
}
