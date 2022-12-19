#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP
/*
	- enable_if
	- is_integral
*/

namespace ft
{
	template< bool B, class T = void >
	struct enable_if {

	};
	template<class T>
	struct enable_if<true, T> {

	};

	template< class T >
	struct is_integral {
		
	};
}

#endif