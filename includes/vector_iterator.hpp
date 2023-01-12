#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template <class T, class Category = std::random_access_iterator_tag, class Distance = ptrdiff_t,
    	    class Pointer = T*, class Reference = T&>
	class vector_iterator {
		public:
			typedef T         value_type;
			typedef Distance  difference_type;
			typedef Pointer   pointer;
			typedef Reference reference;
			typedef Category  iterator_category;
		public:
			vector_iterator(void) {};
			vector_iterator(pointer ptr) : _ptr(ptr) {};
			vector_iterator(const vector_iterator &other) : _ptr(other.base()) {};
			// const iterator
			operator vector_iterator<const T>(void) const { 
				return vector_iterator<const T>(this->_ptr);
			};
			vector_iterator &operator=(const vector_iterator<const T> &other) {
				if (this != &other)
					_ptr = other.base();
				return *this;
			};
			~vector_iterator(void) {};
			pointer base(void) const {
				return _ptr; 
			};
		protected:
			pointer _ptr;

		public:
			value_type &operator * (void) {
				return (*_ptr);
			}

			value_type *operator -> (void) {
				return (_ptr);
			}

			value_type &operator [] (int n) const {
				return _ptr[n];
			}

			vector_iterator &operator++(void) {
				_ptr++; 
				return *this;
			};

			vector_iterator &operator--(void) {
				_ptr--;
				return *this;
			};

			vector_iterator operator++(int) {
				vector_iterator temp(*this);
				_ptr++;
				return temp;
			};

			vector_iterator operator--(int) {
				vector_iterator temp(*this);
				_ptr--;
				return temp;
			};

			vector_iterator operator + (difference_type n) const {
				vector_iterator temp(*this);
				temp += n;
				return (temp);
			}

			vector_iterator operator - (difference_type n) const {
				vector_iterator temp(*this);
				temp -= n;
				return (temp);
			}

			vector_iterator &operator += (int n) {
				_ptr += n;
				return *this;
			}

			vector_iterator &operator -= (int n) {
				_ptr -= n;
				return *this;
			}
	};

	template <typename T1, typename T2>
	bool operator==(const vector_iterator<T1>& x, const vector_iterator<T2>& y) {
		return x.base() == y.base();
	}

	template <typename T1, typename T2>
	bool operator!=(const vector_iterator<T1>& x, const vector_iterator<T2>& y) {
		return x.base() != y.base();
	}

	template <typename T1, typename T2>
	bool operator<(const vector_iterator<T1>& x, const vector_iterator<T2>& y) {
		return x.base() < y.base();
	}

	template <typename T1, typename T2>
	bool operator<=(const vector_iterator<T1>& x, const vector_iterator<T2>& y) {
		return x.base() <= y.base();
	}

	template <typename T1, typename T2>
	bool operator>(const vector_iterator<T1>& x, const vector_iterator<T2>& y) {
		return x.base() > y.base();
	}

	template <typename T1, typename T2>
	bool operator>=(const vector_iterator<T1>& x, const vector_iterator<T2>& y) {
		return x.base() >= y.base();
	}

	template <typename T>
	vector_iterator<T> operator + (typename vector_iterator<T>::difference_type n, const vector_iterator<T> &iter) {
		return vector_iterator<T>(iter.base() + n);
	}

	template <typename T>
	vector_iterator<T> operator - (typename vector_iterator<T>::difference_type n, const vector_iterator<T> &iter) {
		return vector_iterator<T>(iter.base() - n);
	}

	template <typename T1, typename T2>
	typename vector_iterator<T1>::difference_type operator - (const vector_iterator<T1> &x, const vector_iterator<T2> &y) {
		return x.base() - y.base();
	}
}

#endif
