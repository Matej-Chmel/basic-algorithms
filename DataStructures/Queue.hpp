#pragma once
#include <optional>

namespace chm {
	/**
	 * Linear data structure based on FIFO principle (First In, First Out).
	 *
	 * Complexity of operations:
	 *
	 * Clear, time = O(1), space = O(1)
	 *
	 * Linear search, time = O(n), space = O(n)
	 * Another queue is needed to traverse the original one.
	 *
	 * Dequeue, time = O(1), space = O(1)
	 * Enqueue, time = O(1), space = O(1)
	 * Top, time = O(1), space = O(1)
	 */
	class Queue {
	public:
		~Queue();
		auto clear() -> void;
		[[nodiscard]] auto dequeue() -> int;
		auto enqueue(int element) -> void;
		[[nodiscard]] auto linear_search(int target) -> std::optional<int>;
		auto operator=(const Queue& other) -> Queue& = default;
		auto operator=(Queue&& other) noexcept -> Queue& = default;
		explicit Queue(int capacity);
		Queue(const Queue& other) = default;
		Queue(Queue&& other) noexcept = default;
		[[nodiscard]] auto size() const -> int;
		static auto test_case() -> void;
		[[nodiscard]] auto top() const -> int;

	private:
		int capacity;
		int* data;
		int head{-1}, tail{-1};

		auto check_not_empty() const -> void;
	};
}
