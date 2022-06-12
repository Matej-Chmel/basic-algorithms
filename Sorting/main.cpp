#include "common.hpp"
#include "sort_test.hpp"

auto main() -> int {
	return chm::wrap_main([] { chm::run_with_sizes({0, 1, 2, 10, 15, 25}); });
}
