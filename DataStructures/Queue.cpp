#include "Queue.hpp"
#include <utility>
#include "common.hpp"

namespace chm {
	Queue::~Queue() { delete[] data; }

	auto Queue::clear() -> void {
		head = -1;
		tail = -1;
	}

	auto Queue::dequeue() -> int {
		check_not_empty();
		const auto res = data[head];

		if(head == tail) {
			head = -1;
			tail = -1;
		}
		else if(++head >= capacity)
			head = 0;
		return res;
	}

	auto Queue::enqueue(const int element) -> void {
		auto new_tail = tail + 1;

		if(new_tail >= capacity)
			new_tail = 0;
		if(head == new_tail)
			throw AppError("Queue is full.");
		if(head <= 0)
			head = 0;

		tail = new_tail;
		data[tail] = element;
	}

	auto Queue::linear_search(const int target) -> std::optional<int> {
		Queue copy{capacity};
		const auto original_size = size();
		std::optional<int> res = std::nullopt;

		for(auto i = 0; i < original_size; i++) {
			if(top() == target) {
				res = i;
				break;
			}
			copy.enqueue(dequeue());
		}

		if(copy.size()) {
			while(size())
				copy.enqueue(dequeue());
			std::swap(copy.data, data);
			head = copy.head;
			tail = copy.tail;
		}
		return res;
	}

	Queue::Queue(const int capacity)
		: capacity{capacity}, data{new int[capacity]} {}

	auto Queue::size() const -> int { return head < 0 ? 0 : tail - head + 1; }

	auto Queue::test_case() -> void {
		std::cout << "Queue\n";
		Queue q{4};

		check_exception([&] { (void)q.dequeue(); });
		check_exception([&] { (void)q.top(); });

		q.enqueue(1);
		q.enqueue(2);
		q.enqueue(3);
		q.enqueue(4);

		check_exception([&] { q.enqueue(5); });
		check<std::optional<int>>(q.linear_search(1), 0);
		check<std::optional<int>>(q.linear_search(3), 2);
		check<std::optional<int>>(q.linear_search(5), std::nullopt);
		check(q.top(), 1);
		check(q.dequeue(), 1);
		check(q.dequeue(), 2);
		check(q.dequeue(), 3);
		check(q.dequeue(), 4);

		q.enqueue(1);
		q.enqueue(2);
		q.enqueue(3);
		q.enqueue(4);

		check<size_t>(q.size(), 4);
		q.clear();
		check<size_t>(q.size(), 0);
		std::cout << '\n';
	}

	auto Queue::top() const -> int {
		check_not_empty();
		return data[head];
	}

	auto Queue::check_not_empty() const -> void {
		if(head < 0)
			throw AppError("Queue is empty.");
	}
}
