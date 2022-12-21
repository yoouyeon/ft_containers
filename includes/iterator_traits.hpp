#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

#include <iterator>

/**
 * NOTE - Iterator types
 * https://www.enseignement.polytechnique.fr/informatique/INF478/docs/Cpp/en/cpp/iterator/iterator.html
 * - difference_type : Distance(std::ptrdiff_t). iterator 사이의 거리를 표현하는 타입 
 * - value_type : T. Iterator로 참조할 수 있는 값의 type
 * - pointer : T*. Iterator로 참조할 수 있는 값의 pointer type
 * - reference : T&. Iterator로 참조할 수 있는 값의 reference type
 * - iterator_category : Iterator의 Category (https://www.enseignement.polytechnique.fr/informatique/INF478/docs/Cpp/en/cpp/iterator/iterator_tags.html)
 */

namespace ft
{
	template<class Iter>
	struct iterator_traits {
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template<class T>
	struct iterator_traits<T*> {
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};
	
	template<class T>
	struct iterator_traits<const T*> {
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};
}

#endif