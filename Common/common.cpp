#include "common.hpp"
#include <cstdlib>
#include <random>

namespace chm {
	AppError::AppError(const std::string& s) : exception(s.c_str()) {}

	auto operator<<(
		std::ostream& s,
		const std::vector<int>& v
	) -> std::ostream& {
		if(v.empty()) {
			s << "EMPTY";
			return s;
		}

		const auto last_idx = v.size() - 1;
		s << '[';

		for(size_t i = 0; i < last_idx; i++)
			s << v[i] << ", ";

		s << v[last_idx] << ']';
		return s;
	}

	auto generate_int(const int min, const int max) -> int {
		std::default_random_engine gen(std::random_device{}());
		const std::uniform_int_distribution dist(min, max);
		return dist(gen);
	}

	auto generate_int_vector(
		const size_t size,
		const int min,
		const int max
	) -> std::vector<int> {
		std::default_random_engine gen(std::random_device{}());
		const std::uniform_int_distribution dist(min, max);
		std::vector<int> res;
		res.reserve(size);

		for(size_t i = 0; i < size; i++)
			res.emplace_back(dist(gen));

		return res;
	}

	auto sorted(const std::vector<int>& v) -> std::vector<int> {
		auto copy = v;
		std::sort(copy.begin(), copy.end());
		return copy;
	}

	auto wrap_main(const std::function<void()>& f) -> int {
		try { f(); }
		catch(const AppError& e) {
			std::cerr << e.what() << '\n';
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
}
