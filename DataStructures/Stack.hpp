#pragma once
#include <optional>

namespace chm {
	/**
	 * Linear data structure based on LIFO (Last In, First Out) principle.
	 *
	 * Complexity of operations:
	 *
	 * Clear, time = O(1), space = O(1)
	 *
	 * Linear search, time = O(n), space = O(n)
	 * Another stack is needed to traverse the original one.
	 *
	 * Pop, time = O(1), space = O(1)
	 * Push, time = O(1), space = O(1)
	 * Top, time = O(1), space = O(1)
	 */
	class Stack {
	public:
		~Stack();
		auto clear() -> void;
		[[nodiscard]] auto linear_search(int t) -> std::optional<int>;
		auto operator=(const Stack& other) -> Stack& = default;
		auto operator=(Stack&& other) noexcept -> Stack& = default;
		auto pop() -> int;
		auto push(int element) -> void;
		[[nodiscard]] auto size() const -> size_t;
		explicit Stack(size_t capacity);
		Stack(const Stack& other) = default;
		Stack(Stack&& other) noexcept = default;
		static auto test_case() -> void;
		[[nodiscard]] auto top() const -> int;

	private:
		size_t capacity;
		int* data;
		size_t data_size{0};
	};
}
