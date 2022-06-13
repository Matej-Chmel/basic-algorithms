#include "Array.hpp"
#include "common.hpp"

namespace chm {
	Array::~Array() { delete[] data; }

	auto Array::clear() -> void { data_size = 0; }

	auto Array::linear_search(const int t) const -> std::optional<int> {
		for(size_t i = 0; i < size(); i++)
			if(operator[](i) == t)
				return static_cast<int>(i);
		return std::nullopt;
	}

	auto Array::operator[](const size_t i) const -> int& {
		check_index(i);
		return data[i];
	}

	auto Array::push_back(const int element) -> void {
		if(data_size >= capacity) {
			capacity *= 2;
			const auto new_data = new int[capacity];

			for(size_t i = 0; i < data_size; i++)
				new_data[i] = data[i];

			delete[] data;
			data = new_data;
		}

		data[data_size++] = element;
	}

	auto Array::remove(size_t i) -> void {
		check_index(i);
		data_size -= 1;

		for(; i < data_size; i++)
			data[i] = data[i + 1];
	}

	auto Array::size() const -> size_t { return data_size; }

	auto Array::test_case() -> void {
		std::cout << "Array\n";
		Array a{};

		a.push_back(1);
		a.push_back(2);
		a.push_back(3);
		a.push_back(4);
		a.push_back(5);

		check<std::optional<int>>(a.linear_search(3), 2);
		check<std::optional<int>>(a.linear_search(6), std::nullopt);
		check(a[0], 1);
		check(a[1], 2);
		check(a[2], 3);
		check(a[3], 4);
		check(a[4], 5);
		check<size_t>(a.size(), 5);

		a[0] = 5;
		check(a[0], 5);
		check_exception([&] { a[5] = 6; });

		a.remove(0);
		check(a[0], 2);
		check_exception([&] { a.remove(6); });

		a.clear();
		check<size_t>(a.size(), 0);
		check_exception([&] { a[0]++; });
		std::cout << '\n';
	}

	auto Array::check_index(const size_t i) const -> void {
		if(i >= data_size)
			throw AppError("Index(") << i << ") >= data_size(" << data_size <<
				").";
	}
}
