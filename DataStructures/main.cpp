#include "Array.hpp"
#include "common.hpp"
#include "Stack.hpp"

auto main() -> int {
	return chm::wrap_main(
		[] {
			chm::Array::test_case();
			chm::Stack::test_case();
		}
	);
}
