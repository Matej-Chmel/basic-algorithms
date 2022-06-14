#pragma once
#include <functional>
#include <iostream>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
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
	template<typename T> auto operator<<(
		std::ostream& s,
		const std::optional<T>& o
	) -> std::ostream&;
	template<typename T> auto check(T actual, T expected) -> void;
	auto check_exception(const std::function<void()>& f) -> void;
	auto generate_int(int min, int max) -> int;
	auto generate_int_vector(size_t size, int min, int max) -> std::vector<int>;
	auto sorted(const std::vector<int>& v) -> std::vector<int>;
	auto wrap_main(const std::function<void()>& f) -> int;

	template<typename T> auto AppError::operator<<(const T& t) -> AppError {
		std::stringstream stream;
		stream << this->what() << t;
		return AppError(stream.str());
	}

	template<typename T> auto operator<<(
		std::ostream& s,
		const std::optional<T>& o
	) -> std::ostream& {
		if(o)
			s << *o;
		else
			s << "nullopt";
		return s;
	}

	template<typename T> auto check(const T actual, const T expected) -> void {
		const auto equals = actual == expected;
		std::stringstream s;
		s << actual << (equals ? " == " : " != ") << expected << '\n';

		if(equals)
			std::cout << s.str();
		else
			throw AppError(s.str());
	}
}
