#pragma once
#include <optional>

namespace chm {
	constexpr size_t DEFAULT_CAPACITY = 4;

	/**
	 * Resizable array.
	 * Linear data structure based on random (direct) access.
	 * Common building block of other data structures.
	 *
	 * Complexity of operations:
	 *
	 * Read / modify element
	 * Always, time = O(1), space = O(1)
	 *
	 * Append element
	 * Avg case, capacity > number of elements, time = O(1), space = O(1)
	 * Worst case, capacity = number of elements,
	 * time = O(n), space = O(n)
	 *
	 * Clear all elements and keep the capacity
	 * Always time = O(1), space = O(1)
	 *
	 * Delete element
	 * Always, space = O(1)
	 * Best case, last element, time = O(1)
	 * Avg case, any other element, time = O(n)
	 *
	 * Linear search
	 * Always, space = O(1)
	 * Avg case, time = O(n)
	 */
	class Array {
	public:
		~Array();
		Array() = default;
		Array(const Array& other) = default;
		Array(Array&& other) noexcept = default;
		auto clear() -> void;
		[[nodiscard]] auto linear_search(int t) const -> std::optional<int>;
		auto operator=(const Array& other) -> Array& = default;
		auto operator=(Array&& other) noexcept -> Array& = default;
		auto operator[](size_t i) const -> int&;
		auto push_back(int element) -> void;
		auto remove(size_t i) -> void;
		[[nodiscard]] auto size() const -> size_t;
		static auto test_case() -> void;

	private:
		size_t capacity{DEFAULT_CAPACITY};
		int* data{new int[DEFAULT_CAPACITY]};
		size_t data_size{0};

		auto check_index(size_t i) const -> void;
	};
}
