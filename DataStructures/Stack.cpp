#include "Stack.hpp"
#include "common.hpp"

namespace chm {
	Stack::~Stack() { delete[] data; }

	auto Stack::clear() -> void { data_size = 0; }

	auto Stack::pop() -> int {
		if(!data_size)
			throw AppError("No elements to pop.");
		return data[--data_size];
	}

	auto Stack::push(const int element) -> void {
		if(data_size >= capacity)
			throw AppError("Stack is full.");
		data[data_size++] = element;
	}

	auto Stack::size() const -> size_t { return data_size; }

	Stack::Stack(const size_t capacity)
		: capacity{capacity}, data{new int[capacity]} {}

	auto Stack::test_case() -> void {
		Stack s{4};

		check_exception([&] { s.pop(); });
		check_exception([&] { (void)s.top(); });
		s.push(1);
		s.push(2);
		s.push(3);
		s.push(4);
		check_exception([&] { s.push(5); });
		check(s.top(), 4);
		check(s.pop(), 4);
		check(s.pop(), 3);
		check(s.pop(), 2);
		check(s.pop(), 1);
		s.push(1);
		s.push(2);
		s.push(3);
		s.push(4);
		check<size_t>(s.size(), 4);
		s.clear();
		check<size_t>(s.size(), 0);
	}

	auto Stack::top() const -> int {
		if(!data_size)
			throw AppError("Stack is empty.");
		return data[data_size - 1];
	}
}
