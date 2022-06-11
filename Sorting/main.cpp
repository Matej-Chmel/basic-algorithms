#include <iostream>
#include "sort_test.hpp"

auto main() -> int {
	try { chm::run_with_sizes({0, 1, 2, 10, 15, 25}); }
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
