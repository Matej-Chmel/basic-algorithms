#include <cstdlib>
#include <iostream>
#include <optional>
#include "vector_data.hpp"
#include "../Sorting/sort_test.hpp"

namespace chm {
	auto run_test(const std::vector<int>& v, int target) -> void;
	auto sequential_search(
		const std::vector<int>& v,
		int target
	) -> std::optional<int>;
	auto std_find(const std::vector<int>& v, int target) -> std::optional<int>;

	auto run_test(const std::vector<int>& v, const int target) -> void {
		const auto actual = sequential_search(v, target);

		if(const auto expected = std_find(v, target); actual != expected)
			throw AppError("[FAILED] {vec: ") << v << ", target: " << target <<
				'}';

		std::cout << "[PASSED]\n";
	}

	auto sequential_search(
		const std::vector<int>& v,
		const int target
	) -> std::optional<int> {
		for(const auto& i : v)
			if(i == target)
				return i;
		return std::nullopt;
	}

	auto std_find(
		const std::vector<int>& v,
		const int target
	) -> std::optional<int> {
		if(const auto iter = std::find(v.begin(), v.end(), target); iter == v.
			end())
			return std::nullopt;
		else
			return *iter;
	}
}

auto main() -> int {
	try { chm::run_test(chm::generate_int_vector(10, 0, 10), 5); }
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
