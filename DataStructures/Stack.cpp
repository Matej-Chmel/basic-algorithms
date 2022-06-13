#include "Stack.hpp"
#include "common.hpp"

namespace chm {
	Stack::~Stack() { delete[] data; }

	auto Stack::clear() -> void { data_size = 0; }

	auto Stack::linear_search(const int t) -> std::optional<size_t> {
		Stack copy{capacity};
		const auto original_size = size();
		std::optional<size_t> res = std::nullopt;

		for(size_t i = 0; i < original_size; i++) {
			if(top() == t) {
				res = i;
				break;
			}
			copy.push(pop());
		}

		while(copy.size())
			push(copy.pop());
		return res;
	}

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
		std::cout << "Stack\n";
		Stack s{4};

		check_exception([&] { s.pop(); });
		check_exception([&] { (void)s.top(); });

		s.push(1);
		s.push(2);
		s.push(3);
		s.push(4);

		check_exception([&] { s.push(5); });
		check<std::optional<size_t>>(s.linear_search(2), 2);
		check<std::optional<size_t>>(s.linear_search(3), 1);
		check<std::optional<size_t>>(s.linear_search(5), std::nullopt);

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
		std::cout << '\n';
	}

	auto Stack::top() const -> int {
		if(!data_size)
			throw AppError("Stack is empty.");
		return data[data_size - 1];
	}
}
