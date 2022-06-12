#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <optional>
#include "vector_data.hpp"

namespace chm {
	auto operator<<(
		std::ostream& s,
		const std::optional<size_t>& o
	) -> std::ostream&;
	/**
	 * Can be used ONLY on a sorted array.
	 *
	 * Each iteration halves the search area
	 * based on comparison of midpoint and the target.
	 *
	 * Time complexity: O(log n)
	 * Space complexity: O(1)
	 */
	auto binary_search(
		const std::vector<int>& v,
		int target
	) -> std::optional<size_t>;
	/**
	 * Iterates through all elements and breaks early if target is found.
	 *
	 * Time complexity: O(n)
	 * Space complexity: O(1)
	 */
	auto linear_search(
		const std::vector<int>& v,
		int target
	) -> std::optional<size_t>;
	auto run_all_algos(const std::vector<int>& v, int target) -> void;
	auto run_test(
		const std::vector<int>& v,
		int target,
		bool run_binary
	) -> void;
	auto run_with_sizes(const std::vector<size_t>& sizes) -> void;
	auto std_find(
		const std::vector<int>& v,
		int target
	) -> std::optional<size_t>;

	auto operator<<(
		std::ostream& s,
		const std::optional<size_t>& o
	) -> std::ostream& {
		if(o)
			s << *o;
		else
			s << "nullopt";
		return s;
	}

	auto binary_search(
		const std::vector<int>& v,
		const int target
	) -> std::optional<size_t> {
		auto left = 0;
		auto right = static_cast<int>(v.size()) - 1;

		while(left <= right)
			if(const auto mid = left + (right - left) / 2; v[mid] == target)
				return mid;
			else if(v[mid] < target)
				left = mid + 1;
			else
				right = mid - 1;

		return left < static_cast<int>(v.size()) && v[left] == target
					? std::optional{static_cast<size_t>(left)}
					: std::nullopt;
	}

	auto linear_search(
		const std::vector<int>& v,
		const int target
	) -> std::optional<size_t> {
		for(size_t i = 0; i < v.size(); i++)
			if(v[i] == target)
				return i;
		return std::nullopt;
	}

	auto run_all_algos(const std::vector<int>& v, const int target) -> void {
		run_test(v, target, false);
		run_test(v, target, true);
	}

	auto run_test(
		const std::vector<int>& v,
		const int target,
		const bool run_binary
	) -> void {
		const auto actual = run_binary
								? binary_search(v, target)
								: linear_search(v, target);
		const auto expected = std_find(v, target);

		const auto do_throw = [&] {
			throw AppError("[FAILED] {algo: ") << (
					run_binary ? "BINARY" : "LINEAR") << ", vec: " << v <<
				", target: " << target << ", actual: " << actual <<
				", expected: "
				<< expected << '}';
		};

		if(actual && expected) {
			if(v[*actual] != v[*expected])
				do_throw();
		}
		else if(actual != expected)
			do_throw();
	}

	auto run_with_sizes(const std::vector<size_t>& sizes) -> void {
		for(const auto& s : sizes) {
			run_all_algos(
				sorted(generate_int_vector(s, 0, static_cast<int>(s))),
				generate_int(0, static_cast<int>(s))
			);
			std::cout << "[PASSED] Test size: " << s << '\n';
		}
	}

	auto std_find(
		const std::vector<int>& v,
		const int target
	) -> std::optional<size_t> {
		if(const auto iter = std::find(v.begin(), v.end(), target); iter == v.
			end())
			return std::nullopt;
		else
			return iter - v.begin();
	}
}

auto main() -> int {
	try { chm::run_with_sizes({0, 1, 2, 5, 10, 15, 25}); }
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
