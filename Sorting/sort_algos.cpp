#include "sort_algos.hpp"
#include "common.hpp"

namespace chm {
	auto build_max_heap(std::vector<int>& v) -> void;
	auto heapify(std::vector<int>& v, size_t i, size_t n) -> void;
	auto merge(std::vector<int>& a, std::vector<int>& b) -> std::vector<int>;
	auto swap(int& a, int& b) noexcept -> void;

	auto bubble_sort(std::vector<int>& v) -> void {
		for(size_t i = 1; i < v.size(); i++) {
			auto swapped = false;

			for(size_t j = 0; j < v.size() - 1; j++)
				if(const auto next_idx = j + 1; v[j] > v[next_idx]) {
					swap(v[j], v[next_idx]);
					swapped = true;
				}

			if(!swapped)
				break;
		}
	}

	/**
	 * Called by heap_sort.
	 */
	auto build_max_heap(std::vector<int>& v) -> void {
		for(auto i = static_cast<int>(v.size() / 2 - 1); i >= 0; i--)
			heapify(v, static_cast<size_t>(i), v.size());
	}

	auto heap_sort(std::vector<int>& v) -> void {
		if(v.empty())
			return;

		build_max_heap(v);

		for(auto i = v.size() - 1; i > 0; i--) {
			swap(v[0], v[i]);
			heapify(v, 0, i);
		}
	}

	/**
	 * Called by heap_sort.
	 */
	auto heapify(std::vector<int>& v, const size_t i, const size_t n) -> void {
		const auto left = 2 * i + 1;
		auto max_idx = left < n && v[left] > v[i] ? left : i;

		if(const auto right = left + 1; right < n && v[right] > v[max_idx])
			max_idx = right;

		if(max_idx != i) {
			swap(v[i], v[max_idx]);
			heapify(v, max_idx, n);
		}
	}

	auto insertion_sort(std::vector<int>& v) -> void {
		if(v.size() < 2)
			return;

		for(auto i = 1; i < static_cast<int>(v.size()); i++) {
			auto j = i - 1;
			const auto val = v[i];

			for(; j > 0 && v[j] > val; j--)
				v[j + 1] = v[j];

			v[j] = val;
		}
	}

	/**
	* Called by merge_sort to merge two sub-arrays
	* into an array of their combined length.
	*/
	auto merge(std::vector<int>& a, std::vector<int>& b) -> std::vector<int> {
		std::vector<int> res;

		size_t idx_a = 0, idx_b = 0;

		while(idx_a < a.size() && idx_b < b.size())
			if(a[idx_a] < b[idx_b]) {
				res.emplace_back(a[idx_a]);
				idx_a++;
			}
			else {
				res.emplace_back(b[idx_b]);
				idx_b++;
			}

		// Now, a or b is empty.

		while(idx_a < a.size()) {
			res.emplace_back(a[idx_a]);
			idx_a++;
		}

		while(idx_b < b.size()) {
			res.emplace_back(b[idx_b]);
			idx_b++;
		}

		return res;
	}

	auto merge_sort(std::vector<int>& v) -> void {
		if(v.size() < 2)
			return;

		const auto half = v.begin() + static_cast<std::vector<
			int>::iterator::difference_type>(v.size() / 2);
		std::vector left(v.begin(), half);
		std::vector right(half + 1, v.end());

		merge_sort(left);
		merge_sort(right);
		v = merge(left, right);
	}

	auto selection_sort(std::vector<int>& v) -> void {
		if(v.size() < 2)
			return;

		for(size_t i = 0; i < v.size(); i++) {
			auto min_idx = i;

			for(auto j = i; j < v.size(); j++)
				if(v[j] < v[min_idx])
					min_idx = j;

			if(min_idx != i)
				swap(v[i], v[min_idx]);
		}
	}

	auto swap(int& a, int& b) noexcept -> void {
		const auto temp = a;
		a = b;
		b = temp;
	}

	auto to_string(const SortAlgoType t) -> std::string {
		switch(t) {
		case SortAlgoType::BUBBLE:
			return "BUBBLE";
		case SortAlgoType::HEAP:
			return "HEAP";
		case SortAlgoType::INSERTION:
			return "INSERTION";
		case SortAlgoType::MERGE:
			return "MERGE";
		case SortAlgoType::SELECTION:
			return "SELECTION";
		}
		throw AppError("[UNKNOWN VALUE] SortAlgoType = ") << static_cast<int>(
			t);
	}
}
