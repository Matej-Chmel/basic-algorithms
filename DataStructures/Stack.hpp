#pragma once

namespace chm {
	class Stack {
	public:
		~Stack();
		auto clear() -> void;
		auto operator=(const Stack& other) -> Stack& = default;
		auto operator=(Stack&& other) noexcept -> Stack& = default;
		auto pop() -> int;
		auto push(int element) -> void;
		[[nodiscard]] auto size() const -> size_t;
		explicit Stack(size_t capacity);
		Stack(const Stack& other) = default;
		Stack(Stack&& other) noexcept = default;
		static auto test_case() -> void;
		auto top() const -> int;

	private:
		size_t capacity;
		int* data;
		size_t data_size{0};
	};
}
