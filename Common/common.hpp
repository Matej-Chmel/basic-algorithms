#pragma once
#include <functional>
#include <ostream>
#include <sstream>
#include <vector>

namespace chm {
	class AppError final : public std::exception {
	public:
		explicit AppError(const std::string& s);
		template<typename T> auto operator<<(const T& t) -> AppError;
	};

	auto operator<<(
		std::ostream& s,
		const std::vector<int>& v
	) -> std::ostream&;
	auto generate_int(int min, int max) -> int;
	auto generate_int_vector(size_t size, int min, int max) -> std::vector<int>;
	auto sorted(const std::vector<int>& v) -> std::vector<int>;
	auto wrap_main(const std::function<void()>& f) -> int;

	template<typename T> auto AppError::operator<<(const T& t) -> AppError {
		std::stringstream stream;
		stream << this->what() << t;
		return AppError(stream.str());
	}
}
