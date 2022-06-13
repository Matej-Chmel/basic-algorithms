#include "Array.hpp"
#include "common.hpp"
#include "Queue.hpp"
#include "Stack.hpp"

auto main() -> int {
	return chm::wrap_main(
		[] {
			chm::Array::test_case();
			chm::Stack::test_case();
			chm::Queue::test_case();
		}
	);
}
