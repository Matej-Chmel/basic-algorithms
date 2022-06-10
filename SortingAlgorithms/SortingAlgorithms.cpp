#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

class AppError final : public std::exception {
public:
	explicit AppError(const std::string& s);
	template<typename T> auto operator<<(const T& t) -> AppError;
};

enum class SortAlgoType {
	BUBBLE,
	INSERTION,
	MERGE,
	SELECTION
};

auto to_string(SortAlgoType t) -> std::string;

static auto operator<<(
	std::ostream& s,
	const std::vector<int>& v
) -> std::ostream&;
static auto bubble_sort(std::vector<int>& v) -> void;
static auto generate_int_vector(
	size_t size,
	int min,
	int max
) -> std::vector<int>;
static auto insertion_sort(std::vector<int>& v) -> void;
static auto is_sorted(const std::vector<int>& v) -> bool;
static auto merge(std::vector<int>& a, std::vector<int>& b) -> std::vector<int>;
static auto merge_sort(std::vector<int>& v) -> void;
static auto run_all_algos(size_t size) -> void;
static auto run_test(size_t size, SortAlgoType type) -> void;
static auto run_with_sizes(const std::vector<int>& sizes) -> void;
static auto selection_sort(std::vector<int>& v) -> void;

auto operator<<(std::ostream& s, const std::vector<int>& v) -> std::ostream& {
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

template<typename T> auto AppError::operator<<(const T& t) -> AppError {
	std::stringstream stream;
	stream << this->what() << t;
	return AppError(stream.str());
}

AppError::AppError(const std::string& s) : exception(s.c_str()) {}

/**
 * Time complexity.
 *
 * Best case: O(n)
 * When array is already sorted. Single pass.
 *
 * Average & worst case: O(n^2)
 * Derived from the two nested loops. Worst case if sorted the other way.
 *
 * Space complexity: O(1)
 * No new space tied to the size of the array is needed.
 */
auto bubble_sort(std::vector<int>& v) -> void {
	for(size_t i = 1; i < v.size(); i++) {
		auto swapped = false;

		for(size_t j = 0; j < v.size() - 1; j++) {
			const auto next_idx = j + 1;

			if(v[j] > v[next_idx]) {
				const auto temp = v[j];
				v[j] = v[next_idx];
				v[next_idx] = temp;
				swapped = true;
			}
		}

		if(!swapped)
			break;
	}
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

/**
 * Incremental approach. Best for almost-sorted arrays.
 *
 * Time complexity: O(n^2)
 * Derived from two nested loops.
 *
 * Space complexity: O(1)
 * No new space tied to the size of the array is needed.
 */
auto insertion_sort(std::vector<int>& v) -> void {
	if(v.size() < 2)
		return;

	for(auto i = 1; i < static_cast<int>(v.size()); i++) {
		auto j = i - 1;
		const auto val = v[i];

		for(; j > 0 && v[j] > val; j--)
			v[j + 1] = v[j];

		v[j] = val;
	}
}

auto is_sorted(const std::vector<int>& v) -> bool {
	if(v.size() < 2)
		return true;

	for(size_t i = 1; i < v.size() - 1; i++)
		if(v[i] < v[i - 1])
			return false;
	return true;
}

/**
 * Used by merge_sort to merge two sub-arrays
 * into an array of their combined length.
 */
auto merge(std::vector<int>& a, std::vector<int>& b) -> std::vector<int> {
	std::vector<int> res;

	size_t idx_a = 0, idx_b = 0;

	while(idx_a < a.size() && idx_b < b.size())
		if(a[idx_a] < b[idx_b]) {
			res.emplace_back(a[idx_a]);
			idx_a++;
		}
		else {
			res.emplace_back(b[idx_b]);
			idx_b++;
		}

	// Now, a or b is empty.

	while(idx_a < a.size()) {
		res.emplace_back(a[idx_a]);
		idx_a++;
	}

	while(idx_b < b.size()) {
		res.emplace_back(b[idx_b]);
		idx_b++;
	}

	return res;
}

/**
 * Recursive. Divide & conquer.
 *
 * Time complexity: O(n * log n)
 * The maximum height of a balanced tree is log(n) and in every level,
 * a single pass is needed to merge two sub-arrays.
 *
 * Space complexity: O(n)
 * In total, space for one extra array of the same size
 * is needed to represent all the sub-arrays.
 */
auto merge_sort(std::vector<int>& v) -> void {
	if(v.size() < 2)
		return;

	const auto half = v.begin() + static_cast<std::vector<
		int>::iterator::difference_type>(v.size() / 2);
	std::vector<int> left(v.begin(), half);
	std::vector<int> right(half + 1, v.end());

	merge_sort(left);
	merge_sort(right);
	v = merge(left, right);
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

/**
 * Time complexity, all cases: O(n^2).
 * Space complexity: O(1).
 */
auto selection_sort(std::vector<int>& v) -> void {
	if(v.size() < 2)
		return;

	for(size_t i = 0; i < v.size(); i++) {
		auto min_idx = i;

		for(auto j = i; j < v.size(); j++)
			if(v[j] < v[min_idx])
				min_idx = j;

		if(min_idx != i) {
			const auto temp = v[i];
			v[i] = v[min_idx];
			v[min_idx] = temp;
		}
	}
}

auto to_string(const SortAlgoType t) -> std::string {
	switch(t) {
	case SortAlgoType::BUBBLE:
		return "BUBBLE";
	case SortAlgoType::INSERTION:
		return "INSERTION";
	case SortAlgoType::MERGE:
		return "MERGE";
	case SortAlgoType::SELECTION:
		return "SELECTION";
	}
	throw AppError("[UNKNOWN VALUE] SortAlgoType = ") << static_cast<int>(t);
}

auto main() -> int {
	try { run_with_sizes({0, 1, 2, 10, 15, 25}); }
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
