#ifndef STACK_HPP
# define STACK_HPP

#include "./vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack {
		public:
			typedef Container                                container_type;
			typedef typename container_type::value_type      value_type;
			typedef typename container_type::reference       reference;
			typedef typename container_type::const_reference const_reference;
			typedef typename container_type::size_type       size_type;
		protected:
			container_type c;
		public:
			// ANCHOR - construct/copy/destruct
			explicit stack(const container_type& container = container_type()) 
			: c(container) {};

			~stack(void) {};

			stack(const stack &other) : c(other.c) {};

			stack& operator=(const stack& other){
				if (*this != other) {
					c = other.c;
				}
				return *this;
			};

			// ANCHOR - Element access
			reference top() { return c.back(); };
			const_reference top() const { return c.back(); };

			// ANCHOR - Capacity
			bool empty() const { return c.empty(); };
			size_type size() const { return c.size(); };

			// ANCHOR - Modifiers
			void push( const value_type& value ) { c.push_back(value); };
			void pop() { c.pop_back(); };

			// ANCHOR - operators
			friend bool operator==( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs ) {
				return lhs.c == rhs.c;
			};
			friend bool operator!=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs ) {
				return lhs.c != rhs.c;
			};
			friend bool operator<( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs ) {
				return lhs.c < rhs.c;
			};
			friend bool operator<=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs ) {
				return lhs.c <= rhs.c;
			};
			friend bool operator>( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs ) {
				return lhs.c > rhs.c;
			};
			friend bool operator>=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs ) {
				return lhs.c >= rhs.c;
			};
	};
}
#endif