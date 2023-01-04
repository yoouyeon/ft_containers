#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{
	template <class T1, class T2>
	struct pair {
		public : 
			typedef T1 first_type;
			typedef T2 second_type;
			// ANCHOR - Member objects
			first_type first;
			second_type second;
			//ANCHOR - Construct
			pair(void) : first(first_type()), second(second_type()){};
			pair( const first_type& x, const second_type& y ) : first(x), second(y) {};
			template< class U1, class U2 >
			pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {};
			// ANCHOR - Assign
			pair& operator=( const pair& other ) {
				if (this != &other) {
					first = other.first;
					second = other.second;
				}
				return *this;
			};
	};

	// ANCHOR - Non-member functions
	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y) {
		return pair<T1,T2>(x, y);
	}

	template< class T1, class T2 >
	bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
		return (lhs.first == rhs.first) && (lhs.second == rhs.second);
	}

	template< class T1, class T2 >
	bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
		return !(lhs == rhs);
	}

	template< class T1, class T2 >
	bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template< class T1, class T2 >
	bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
		return !(rhs < lhs);
	}

	template< class T1, class T2 >
	bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
		return rhs < lhs;
	}

	template< class T1, class T2 >
	bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
		return !(lhs < rhs);
	}
}

#endif
