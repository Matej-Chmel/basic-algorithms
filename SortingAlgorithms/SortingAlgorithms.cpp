#include <cstdlib>
#include <exception>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

class AppError : public std::exception {
public:
	explicit AppError(const std::string& s);
	template <typename T>
	AppError operator<<(const T& t);
};

enum class SortAlgoType {
	BUBBLE,
	INSERTION,
	SELECTION
};

std::string to_string(const SortAlgoType t);

static std::ostream& operator<<(std::ostream& s, const std::vector<int>& v);
static void bubble_sort(std::vector<int>& v);
static std::vector<int> generate_int_vector(const size_t size, const int min, const int max);
static void insertion_sort(std::vector<int>& v);
static bool is_sorted(const std::vector<int>& v);
static void run_all_algos(const size_t size);
static void run_test(const size_t size, const SortAlgoType type);
static void run_with_sizes(const std::vector<int>& sizes);
static void selection_sort(std::vector<int>& v);

std::ostream& operator<<(std::ostream& s, const std::vector<int>& v) {
	if (v.empty()) {
		s << "EMPTY";
		return s;
	}

	const auto last_idx = v.size() - 1;
	s << '[';

	for (size_t i = 0; i < last_idx; i++)
		s << v[i] << ", ";

	s << v[last_idx] << ']';
	return s;
}

template <typename T>
AppError AppError::operator<<(const T& t) {
	std::stringstream stream;
	stream << this->what() << t;
	return AppError(stream.str());
}

AppError::AppError(const std::string& s) : exception(s.c_str()) {}

/**
 * Time complexity.
 * Best case: O(n)
 * Average & worst case: O(n^2)
 *
 * Space complexity: O(1)
 */
void bubble_sort(std::vector<int>& v) {
	const auto size = v.size();
	const auto last_idx = size - 1;

	for (size_t i = 1; i < size; i++) {
		auto swapped = false;

		for (size_t j = 0; j < last_idx; j++) {
			const auto next_idx = j + 1;

			if (v[j] > v[next_idx]) {
				const auto temp = v[j];
				v[j] = v[next_idx];
				v[next_idx] = temp;
				swapped = true;
			}
		}

		if (!swapped)
			break;
	}
}

std::vector<int> generate_int_vector(const size_t size, const int min, const int max) {
	std::default_random_engine gen(std::random_device{}());
	const std::uniform_int_distribution<int> dist(min, max);
	std::vector<int> res;
	res.reserve(size);

	for (size_t i = 0; i < size; i++)
		res.emplace_back(dist(gen));

	return res;
}

/**
 * Time complexity: O(n^2)
 * Space complexity: O(1)
 */
void insertion_sort(std::vector<int>& v) {
	const auto size = static_cast<int>(v.size());

	if (size < 2)
		return;

	for (int i = 1; i < size; i++) {
		int j = i - 1;
		const auto val = v[i];
		
		for(;j > 0 && v[j] > val; j--)
			v[j + 1] = v[j];

		v[j] = val;
	}
}

bool is_sorted(const std::vector<int>& v) {
	if (v.size() < 2)
		return true;

	const auto last_idx = v.size() - 1;

	for (size_t i = 1; i < last_idx; i++)
		if (v[i] < v[i - 1])
			return false;
	return true;
}

void run_all_algos(const size_t size) {
	run_test(size, SortAlgoType::BUBBLE);
	run_test(size, SortAlgoType::INSERTION);
	run_test(size, SortAlgoType::SELECTION);
	std::cout << "[PASSED] " << "Test size: " << size << '\n';
}

void run_test(const size_t size, const SortAlgoType type) {
	auto vec = generate_int_vector(size, 0, 100);
	const auto vec_copy = vec;

	switch (type) {
	case SortAlgoType::BUBBLE:
		bubble_sort(vec);
		break;
	case SortAlgoType::INSERTION:
		insertion_sort(vec);
		break;
	case SortAlgoType::SELECTION:
		selection_sort(vec);
		break;
	}

	if (!is_sorted(vec))
		throw AppError("[FAILED] {vec: ") << vec_copy << ", " << "algo: " << to_string(type) << '}';
}

void run_with_sizes(const std::vector<int>& sizes) {
	for (const auto& s : sizes)
		run_all_algos(s);
}

/**
 * Time complexity, all cases: O(n^2).
 * Space complexity: O(1).
 */
void selection_sort(std::vector<int>& v) {
	const auto size = v.size();

	if (size < 2)
		return;

	for (size_t i = 0; i < size; i++) {
		auto min_idx = i;

		for (size_t j = i; j < size; j++)
			if (v[j] < v[min_idx])
				min_idx = j;

		if (min_idx != i) {
			const auto temp = v[i];
			v[i] = v[min_idx];
			v[min_idx] = temp;
		}
	}
}

std::string to_string(const SortAlgoType t) {
	switch (t) {
	case SortAlgoType::BUBBLE:
		return "BUBBLE";
	case SortAlgoType::INSERTION:
		return "INSERTION";
	case SortAlgoType::SELECTION:
		return "SELECTION";
	}
	throw AppError("[UNKNOWN VALUE] SortAlgoType = ") << static_cast<int>(t);
}

int main() {
	try { run_with_sizes({0, 1, 2, 10, 15, 25}); }
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
