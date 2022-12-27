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
			vector_iterator &operator=(const vector_iterator<const T> &other) {
				if (this != &other)
					_ptr = other.base();
				return *this;
			};
			~vector_iterator(void) {};
			// getter
			pointer base(void) const {
				return _ptr; 
			};

			operator vector_iterator<const T>(void) const { 
				return vector_iterator<const T>(this->_ptr);
			};
	protected:
		pointer _ptr;

	public:
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

		bool operator == (const vector_iterator<const T> &other) const {
			return _ptr == other.base();
		}

		bool operator != (const vector_iterator<const T> &other) const {
			return _ptr != other.base();
		}

		bool operator > (const vector_iterator<const T> &other) const {
			return _ptr > other.base();
		}

		bool operator >= (const vector_iterator<const T> &other) const {
			return (_ptr >= other.base());
		}

		bool operator < (const vector_iterator<const T> &other) const {
			return (_ptr < other.base());
		}

		bool operator <= (const vector_iterator<const T> &other) const {
			return (_ptr <= other.base());
		}

		value_type &operator * (void) {
			return (*_ptr);
		}

		value_type *operator -> (void) {
			return (_ptr);
		}

		vector_iterator operator + (int n) const {
			vector_iterator temp(*this);
			temp += n;
			return (temp);
		}

		vector_iterator operator - (int n) const {
			vector_iterator temp(*this);
			temp -= n;
			return (temp);
		}

		friend vector_iterator	operator + (std::ptrdiff_t n, vector_iterator it) {
            vector_iterator temp(it.base());
            temp += n;
            return (temp);
        }

		int		operator - (vector_iterator<const T> const &other) const {
			return _ptr - other.base();
		}

		vector_iterator &operator += (int n) {
			_ptr += n;
			return *this;
		}

		vector_iterator &operator -= (int n) {
			_ptr -= n;
			return *this;
		}

		value_type &operator [] (int n) const {
			return _ptr[n];
		}
	};

}

#endif