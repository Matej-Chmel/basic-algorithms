#pragma once
#include <optional>

namespace chm {
	/**
	 * Linear data structure that allows dynamically quickly adding elements
	 * at any position without large memory allocations.
	 *
	 * Complexity of operations:
	 *
	 * Append element anywhere, time = O(1), space = O(1)
	 *
	 * Clear, time = O(n), space = O(1)
	 * Every node has to be deleted.
	 *
	 * Get size, time = O(n), space = O(1)
	 * Without storing this property,
	 * getting the size involves traversing the whole list.
	 *
	 * Linear search, time = O(n), space = O(1)
	 *
	 * Remove element
	 * Always, space = O(1)
	 * Best case, time = O(1), when removing the tail.
	 * Avg case, time = O(n),
	 * parent must be found to set its next field to the correct value.
	 */
	class SinglyLinkedList {
	public:
		class Node {
		public:
			~Node();
			auto append(int new_data) -> Node*;
			[[nodiscard]] auto find_parent() const -> Node*;
			[[nodiscard]] auto get_data() const -> int;
			[[nodiscard]] auto get_next() const -> Node*;
			explicit Node(int p_data, SinglyLinkedList* p_list);
			Node(const Node& other) = default;
			Node(Node&& other) noexcept = default;
			[[nodiscard]] auto operator!=(const Node* o) const -> bool;
			auto operator=(const Node& other) -> Node& = default;
			auto operator=(Node&& other) noexcept -> Node& = default;
			[[nodiscard]] auto operator==(const Node* o) const -> bool;
			auto remove() -> void;

		private:
			int data;
			SinglyLinkedList* list;
			Node* next{nullptr};
		};

		~SinglyLinkedList();
		auto append(int data) -> Node*;
		auto clear() -> void;
		[[nodiscard]] auto get_head() const -> Node*;
		[[nodiscard]] auto linear_search(
			int target
		) const -> std::optional<size_t>;
		auto operator=(
			const SinglyLinkedList& other
		) -> SinglyLinkedList& = delete;
		auto operator=(
			SinglyLinkedList&& other
		) noexcept -> SinglyLinkedList& = delete;
		[[nodiscard]] auto pop() const -> int;
		SinglyLinkedList() = default;
		SinglyLinkedList(const SinglyLinkedList& other) = delete;
		SinglyLinkedList(SinglyLinkedList&& other) noexcept = delete;
		[[nodiscard]] auto size() const -> size_t;
		static auto test_case() -> void;

	private:
		Node* head{nullptr},* tail{nullptr};
	};
}
