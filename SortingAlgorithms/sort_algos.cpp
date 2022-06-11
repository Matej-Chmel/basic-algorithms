#include "sort_algos.hpp"

namespace chm {
	AppError::AppError(const std::string& s) : exception(s.c_str()) {}

	auto bubble_sort(std::vector<int>& v) -> void {
		for(size_t i = 1; i < v.size(); i++) {
			auto swapped = false;

			for(size_t j = 0; j < v.size() - 1; j++) {
				const auto next_idx = j + 1;

				if(v[j] > v[next_idx]) {
					const auto temp = v[j];
					v[j] = v[next_idx];
					v[next_idx] = temp;
					swapped = true;
				}
			}

			if(!swapped)
				break;
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
	* Used by merge_sort to merge two sub-arrays
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
		std::vector<int> left(v.begin(), half);
		std::vector<int> right(half + 1, v.end());

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

			if(min_idx != i) {
				const auto temp = v[i];
				v[i] = v[min_idx];
				v[min_idx] = temp;
			}
		}
	}

	auto to_string(const SortAlgoType t) -> std::string {
		switch(t) {
		case SortAlgoType::BUBBLE:
			return "BUBBLE";
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
