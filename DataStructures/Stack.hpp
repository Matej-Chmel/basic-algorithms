#pragma once

namespace chm {
	class Stack {
	public:
		auto pop() -> int;
		auto push(int element) -> void;
		auto size() -> size_t;
	};
}
