#pragma once
#include <exception>
#include <sstream>
#include <string>
#include <vector>

namespace chm {
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

	/**
	 * Passes through the array multiple times and compares adjacent elements.
	 * Large numbers bubble to the end of the array.
	 *
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
	auto bubble_sort(std::vector<int>& v) -> void;
	/**
	 * Incremental approach. Best for almost-sorted arrays.
	 * Splits array into sorted and unsorted sections.
	 * Each iteration inserts next element into the sorted section.
	 *
	 * Time complexity: O(n^2)
	 * Derived from two nested loops.
	 *
	 * Space complexity: O(1)
	 * No new space tied to the size of the array is needed.
	*/
	auto insertion_sort(std::vector<int>& v) -> void;
	/**
	 * Recursive. Divide & conquer.
	 * Splits array into sub-arrays and merges it from the lowest level up.
	 *
	 * Time complexity: O(n * log n)
	 * The maximum height of a balanced tree is log(n) and in every level,
	 * a single pass is needed to merge two sub-arrays.
	 *
	 * Space complexity: O(n)
	 * In total, space for one extra array of the same size
	 * is needed to represent all the sub-arrays.
	*/
	auto merge_sort(std::vector<int>& v) -> void;
	/**
	 * In each iteration, finds minimum and replaces it with current index.
	 *
	 * Time complexity, all cases: O(n^2).
	 * Space complexity: O(1).
	*/
	auto selection_sort(std::vector<int>& v) -> void;
	auto to_string(SortAlgoType t) -> std::string;

	template<typename T> auto AppError::operator<<(const T& t) -> AppError {
		std::stringstream stream;
		stream << this->what() << t;
		return AppError(stream.str());
	}
}