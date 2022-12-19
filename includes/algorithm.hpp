#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

/* ==============================================================================================
	- equal (기본 == or 사용자 정의 비교함수)
		- 첫번째 범위의 원소들과 두번째 범위의 원소들이 모두 같으면 true
		- 그 외엔 false
	- lexicographical_compare (기본 < or 사용자 정의 비교함수)
		- 첫번째 범위의 원소들이 두번째 범위의 원소들보다 모두 작으면 true
		- 그 외엔 false
   ============================================================================================== */

namespace ft
{
	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
		while (first1 != last1) {
			if (*first1 != *first2)
				return false;
			++first1; ++first2;
		}
		return true;
	};

	template<class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p) {
		while (first1 != last1) {
			if (!p(*first1, *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	};

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
		while (first1 != last1 && first2 != last2) {
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
			// 동일하면 계속 반복
			++first1; ++first2;
		}
		// 앞쪽만 끝났으면 true, 뒷쪽도 끝났거나 뒷쪽만 끝났으면 false
		return (first1 == last1) && (first2 != last2);
	};

	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp) {
		// Elements are compared using the given binary comparison function comp.
		while (first1 != last1 && first2 != last2) {
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
			// 동일하면 계속 반복
			++first1; ++first2;
		}
		// 앞쪽만 끝났으면 true, 뒷쪽도 끝났거나 뒷쪽만 끝났으면 false
		return (first1 == last1) && (first2 != last2);
	};
}

#endif