#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template<class Iter>
	class reverse_iterator {
		public :
			// ANCHOR - Member types
			typedef Iter											iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer				pointer;
			typedef typename ft::iterator_traits<Iter>::reference			reference;
			// ANCHOR - Member functions
			reverse_iterator() {
				// Default constructor. The underlying iterator is value-initialized.
			};
			explicit reverse_iterator(iterator_type x) : current(x) {
				// The underlying iterator is initialized with x.
			};
			template<class U>
			reverse_iterator(const reverse_iterator<U>& other) : current(other.base()) {
				// The underlying iterator is initialized with that of other. 
			};
			template< class U >
			reverse_iterator& operator=(const reverse_iterator<U>& other) {
				if (*this != other)
					current = other.base();
				return *this;
			};
			iterator_type base() const {
				// Returns the underlying base iterator.
				return current;
			};
			reference operator*() const {
				// Equivalent to Iter tmp = current; return *--tmp;
				iterator_type tmp = current;
				return *--tmp;
			};
			pointer operator->() const {
				// Equivalent to return std::addressof(operator*());.
				return &(operator*());
			};
			reference operator[](difference_type n) const {
				// 반환타입 unspecified ?
				return current[-n - 1];
			};
			reverse_iterator& operator++() {
				current--;
				return *this;
			};
			reverse_iterator& operator--() {
				current++;
				return *this;
			};
			reverse_iterator operator++(int) {
				reverse_iterator temp = *this;
				current--;
				return (temp);
			};
			reverse_iterator operator--(int) {
				reverse_iterator temp = *this;
				current++;
				return temp;
			};
			reverse_iterator operator+(difference_type n) const {
				return reverse_iterator(current - n);
			};
			reverse_iterator operator-(difference_type n) const {
				return reverse_iterator(current + n);
			};
			reverse_iterator& operator+=(difference_type n) {
				current -= n;
				return *this;
			};
			reverse_iterator& operator-=(difference_type n) {
				current += n;
				return *this;
			};
		protected :
			iterator_type current;
	};
	//ANCHOR - Non-member functions
	template< class Iterator1, class Iterator2 >
	bool operator==(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}
	template< class Iterator1, class Iterator2 >
	bool operator!=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() != rhs.base();
	}
	template< class Iterator1, class Iterator2 >
	bool operator<(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() > rhs.base();
	}
	template< class Iterator1, class Iterator2 >
	bool operator<=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() >= rhs.base();
	}
	template< class Iterator1, class Iterator2 >
	bool operator>(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() < rhs.base();
	}
	template< class Iterator1, class Iterator2 >
	bool operator>=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() <= rhs.base();
	}
	template< class Iter >
	reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it ) {
		return reverse_iterator<Iter>(it.base() - n);
	}
	template< class Iterator1, class Iterator2 >
	typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return rhs.base() - lhs.base();
	}
}

#endif
