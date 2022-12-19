#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{
	template <class T1, class T2>
	struct pair {

	};

	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y) {
		return pair<T1,T2>(x,y);
	};
}

#endif