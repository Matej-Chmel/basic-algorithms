#include "Stack.hpp"
#include "common.hpp"

namespace chm {
	Stack::~Stack() { delete[] data; }

	auto Stack::clear() -> void { data_size = 0; }

	auto Stack::pop() -> int {
		if(!data_size)
			throw AppError("No elements to pop.");
		return data[data_size-- - 1];
	}

	auto Stack::push(int element) -> void {}
	auto Stack::size() -> size_t {}
	Stack::Stack(size_t capacity) {}
}
