#ifndef MAP_HPP
# define MAP_HPP

#include <algorithm>	// less
#include <memory>		// allocator
#include <exception>	// std::out_of_range
// #include <cstddef>	// std::ptrdiff_t
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "rbtree.hpp"
#include "pair.hpp"
// #include "map_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	class map {
		public :
			// ANCHOR - Member types
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef typename ft::pair<const Key, T>			value_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef Compare									key_compare;
			typedef Allocator								allocator_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef Allocator::pointer						pointer;
			typedef Allocator::const_pointer				const_pointer;
			typedef map_iterator<value_type>				iterator;
			typedef map_iterator<const value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			// typedef ft::treeNote<value_type>				node_type;
			// typedef node_type*								node_pointer;
			class value_compare {
				public : 
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;

				protected :
					key_compare comp;
					value_compare( Compare c ) : comp(c) {};
				
				public : 
					bool operator()( const value_type& lhs, const value_type& rhs ) const {
						comp(lhs.first, rhs.first);
					};
					// TODO - key 말고 value 비교는 안해도 되나?
			};
		
		protected :
			// ANCHOR - Member variables
			key_compare 	_comp;
			allocator_type	_alloc;
			ft::rbTree<value_type, value_compare, allocator_type> _tree;
		public:
			// SECTION - Member functions
			// ANCHOR - Constructor, Destructor, assign operator, getter
			explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) 
			: _comp(comp),
			_alloc(alloc),
			_tree(_comp, _alloc) {

			};
			template< class InputIt >
			map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() , typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0 ) 
			: _comp(comp),
			_alloc(alloc),
			_tree(_comp, _alloc) {
				_tree.insert(first, last);
			};
			map( const map& other ) 
			: _comp(other._comp),
			_alloc(other._alloc),
			_tree(other._tree) {
				_tree.insert(other.begin(), other.end());
			};
			map& operator=( const map& other ) {
				if (*this != other) {
					_comp = other._comp;
					_alloc = other._alloc;
					_tree = other._tree;
				}
				return *this;
			};
			allocator_type get_allocator() const {
				return _alloc;
			};
			//ANCHOR - Element access
			T& at( const Key& key ) {
				iterator iter = this->find(key);
				if (iter == this->end())
					throw std::out_of_range("map (at)");
				return iter->second;
			};
			T& operator[]( const Key& key ) {
				// TODO - 매커니즘 확인하기
				return insert(ft::make_pair(key, T())).first->second;
			};
			// ANCHOR - Iterators
			
			// !SECTION

	};
}

#endif