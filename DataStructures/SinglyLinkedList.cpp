#include "SinglyLinkedList.hpp"
#include "common.hpp"

namespace chm {
	SinglyLinkedList::Node::~Node() { delete next; }

	auto SinglyLinkedList::Node::append(const int new_data) -> Node* {
		const auto new_node = new Node(new_data, list);
		new_node->next = next;
		next = new_node;

		if(list->tail == this)
			list->tail = new_node;
		return new_node;
	}

	auto SinglyLinkedList::Node::find_parent() const -> Node* {
		auto node = list->get_head();
		Node* parent{nullptr};

		while(node) {
			if(node == this)
				break;
			parent = node;
			node = node->get_next();
		}
		return parent;
	}

	auto SinglyLinkedList::Node::get_data() const -> int { return data; }
	auto SinglyLinkedList::Node::get_next() const -> Node* { return next; }

	SinglyLinkedList::Node::Node(
		const int p_data,
		SinglyLinkedList* const p_list
	) : data(p_data), list(p_list) {}

	auto SinglyLinkedList::Node::operator!=(const Node* const o) const -> bool {
		return !operator==(o);
	}

	auto SinglyLinkedList::Node::operator==(const Node* const o) const -> bool {
		return o == this;
	}

	auto SinglyLinkedList::Node::remove() -> void {
		const auto parent = find_parent();

		if(parent)
			parent->next = next;
		if(list->head == this)
			list->head = nullptr;
		if(list->tail == this)
			list->tail = parent;

		next = nullptr;
		delete this;
	}

	SinglyLinkedList::~SinglyLinkedList() { delete head; }

	auto SinglyLinkedList::append(const int data) -> Node* {
		if(tail)
			return tail->append(data);

		const auto new_node = new Node(data, this);
		head = new_node;
		tail = new_node;
		return new_node;
	}

	auto SinglyLinkedList::clear() -> void {
		delete head;
		head = nullptr;
		tail = nullptr;
	}

	auto SinglyLinkedList::get_head() const -> Node* { return head; }

	auto SinglyLinkedList::linear_search(
		const int target
	) const -> std::optional<size_t> {
		auto current = get_head();

		for(size_t i = 0; current; current = current->get_next(), ++i)
			if(current->get_data() == target)
				return i;
		return std::nullopt;
	}

	auto SinglyLinkedList::pop() const -> int {
		if(!tail)
			throw AppError("List is empty.");
		const auto res = tail->get_data();
		tail->remove();
		return res;
	}

	auto SinglyLinkedList::size() const -> size_t {
		auto node = head;
		size_t res{0};

		while(node) {
			++res;
			node = node->get_next();
		}
		return res;
	}

	auto SinglyLinkedList::test_case() -> void {
		SinglyLinkedList list{};

		check<size_t>(list.size(), 0);
		list.append(1);
		list.append(2);
		list.append(3);
		list.append(4);
		check<size_t>(list.size(), 4);

		check(list.get_head()->get_data(), 1);
		check<std::optional<size_t>>(list.linear_search(2), 1);
		check<std::optional<size_t>>(list.linear_search(4), 3);

		list.get_head()->get_next()->get_next()->remove();
		check<std::optional<size_t>>(list.linear_search(4), 2);

		check(list.pop(), 4);
		check<std::optional<size_t>>(list.linear_search(4), std::nullopt);

		const auto print = [](const SinglyLinkedList& p_list) -> std::string {
			auto node = p_list.get_head();
			std::string res;

			while(node) {
				res += std::to_string(node->get_data());
				node = node->get_next();
			}
			return res;
		};

		check<std::string>(print(list), "12");

		check<size_t>(list.size(), 2);
		list.clear();
		check<size_t>(list.size(), 0);
		std::cout << '\n';
	}
}
