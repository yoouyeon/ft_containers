#ifndef VECTOR_ITERATOR_HPP
# define VECTPR_ITERATPR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template <class T, class Category = std::random_access_iterator_tag, \
		class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class vector_iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
		public:
			vector_iterator(void) {};
			vector_iterator(pointer ptr) : _ptr(ptr) {};
			vector_iterator(const vector_iterator &other) : _ptr(other.base()) {};
			vector_iterator &operator=(const vector_iterator &other) {
				if (this != &other)
					_ptr = other.base();
				return *this;
			}
			~vector_iterator(void) {};
			// getter
			pointer base() const {
				return _ptr;
			}

		protected:
			pointer _ptr;

		public:
			// increase, decrease
			vector_iterator& operator++(void) {
				_ptr++;
				return *this;
			};
			vector_iterator operator++(int) {
				vector_iterator temp = *this;
				_ptr++;
				return temp;
			};
			vector_iterator &operator--(void) {
				_ptr--;
				return *this
			};
			vector_iterator operator--(int) {
				vector_iterator temp = *this;
				_ptr--;
				return temp;
			};

			// arithmetic
			vector_iterator operator+(difference_type n) const {
				return vector_iterator(_ptr + n);
			}
			vector_iterator operator-(difference_type n) const {
				return vector_iterator(_ptr - n);
			}
			vector_iterator &operator+=(differece_type n) {
				_ptr += n;
				return *this;
			}
			vector_iterator &operator-=(difference_type n) {
				_ptr -= n;
				return *this;
			}
			// comparison
			bool operator==(const vector_iterator &other) {
				return (_ptr == other.base());
			};
			bool operator!=(const vector_iterator &other) {
				return (_ptr != other.base());
			};
			bool operator<(const vector_iterator &other) {
				return (_ptr < other.base());
			};
			bool operator<=(const vector_iterator &other) {
				return (_ptr <= other.base());
			};
			bool operator>(const vector_iterator &other) {
				return (_ptr > other.base());
			};
			bool operator>=(const vector_iterator &other) {
				return (_ptr >= other.base());
			};
			// etc
			reference operator*(void) const {
				return (*_ptr);
			}
			pointer operator->(void) const {
				return (_ptr);
			}
			reference operator[](difference_type n ) {
				return _ptr[n];
			}
	};

	template< class Iterator1, class Iterator2 >
	bool operator==(const ft::vector_iterator<Iterator1>& lhs, const ft::vector_iterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	};
	template< class Iterator1, class Iterator2 >
	bool operator!=(const ft::vector_iterator<Iterator1>& lhs, const ft::vector_iterator<Iterator2>& rhs) {
		return lhs.base() != rhs.base();
	};
	template< class Iterator1, class Iterator2 >
	bool operator<(const ft::vector_iterator<Iterator1>& lhs, const ft::vector_iterator<Iterator2>& rhs) {
		return lhs.base() < rhs.base();
	};
	template< class Iterator1, class Iterator2 >
	bool operator<=(const ft::vector_iterator<Iterator1>& lhs, const ft::vector_iterator<Iterator2>& rhs) {
		return lhs.base() <= rhs.base();
	};
	template< class Iterator1, class Iterator2 >
	bool operator>(const ft::vector_iterator<Iterator1>& lhs, const ft::vector_iterator<Iterator2>& rhs) {
		return lhs.base() > rhs.base();
	};
	template< class Iterator1, class Iterator2 >
	bool operator>=(const ft::vector_iterator<Iterator1>& lhs, const ft::vector_iterator<Iterator2>& rhs) {
		return lhs.base() >= rhs.base();
	};
	template< class Iter >
	vector_iterator<Iter> operator+( typename vector_iterator<Iter>::difference_type n, const vector_iterator<Iter>& it ) {
		return (vector_iterator<Iter>(it.base() + n));
	};
	template< class Iterator1, class Iterator2 >
	typename vector_iterator<Iterator1>::difference_type operator-(const vector_iterator<Iterator1>& lhs, const vector_iterator<Iterator2>& rhs) {
		return (vector_iterator<Iter>(it.))
	};
}

#endif