#ifndef MAP_HPP
# define MAP_HPP

#include <algorithm>
#include <memory>
#include <exception>
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "rbtree.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	class map {
		public :
			// ANCHOR - Member types
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef typename ft::pair<const Key, T>				value_type;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef Compare										key_compare;
			typedef Allocator									allocator_type;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;
			typedef ft::treeNode<value_type>					node_type;
			typedef node_type*									node_pointer;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			class value_compare {
				friend class map;
				public : 
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
				protected :
					key_compare comp;
					value_compare( Compare c ) : comp(c) {};
				public :
					bool operator()( const value_type& lhs, const value_type& rhs ) const {
						return comp(lhs.first, rhs.first);
					};
			};
			typedef typename ft::rbTree<value_type, key_type, value_compare, allocator_type>::iterator			iterator;
			typedef typename ft::rbTree<value_type, key_type, value_compare, allocator_type>::const_iterator	const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		
		protected :
			// ANCHOR - Member variables
			key_compare 	_comp;
			allocator_type	_alloc;
			ft::rbTree<value_type, key_type, value_compare, allocator_type> _tree;
		public:
			// SECTION - Member functions
			// ANCHOR - Constructor, Destructor, assign operator, getter
			explicit map( const Compare& comp = key_compare(), const Allocator& alloc = Allocator() ) 
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
			_tree(other._tree) {};
			map& operator=( const map& other ) {
				if (*this != other) {
					_comp = other._comp;
					_tree = other._tree;
				}
				return *this;
			};
			~map() {};
			allocator_type get_allocator() const {
				return _alloc;
			};
			// SECTION
			void print_nodes_map() const {
				_tree.print_nodes_map();
			}
			//!SECTION
			// ANCHOR - Element access
			T& at( const Key& key ) {
				iterator iter = this->find(key);
				if (iter == this->end())
					throw std::out_of_range("map (at)");
				return iter->second;
			};
			T& operator[]( const Key& key ) {
				return insert(_make_key_value(key)).first->second;
			};
			// ANCHOR - Iterators
			iterator begin() {
				return _tree.begin();
			};
			const_iterator begin() const {
				return _tree.begin();
			};
			iterator end() {
				return _tree.end();
			};
			const_iterator end() const {
				return _tree.end();
			};
			reverse_iterator rbegin() {
				return reverse_iterator(this->end());
			};
			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(this->end());
			};
			reverse_iterator rend() {
				return reverse_iterator(this->begin());
			};
			const_reverse_iterator rend() const {
				return const_reverse_iterator(this->begin());
			};
			// ANCHOR - Capacity
			bool empty() const {
				return _tree.empty();
			};
			size_type size() const {
				return _tree.size();
			};
			size_type max_size() const {
				return _tree.max_size();
			};
			// ANCHOR - Modifiers
			void clear() {
				_tree.clear();
			};

			ft::pair<iterator, bool> insert( const value_type& value ) {
				return _tree.insert(value);
			};
			iterator insert( iterator pos, const value_type& value ) {
				return _tree.insert(pos, value);
			};
			template< class InputIt >
			void insert( InputIt first, InputIt last ) {
				_tree.insert(first, last);
			};

			void erase( iterator pos ) {
				_tree.erase(pos);
			};

			size_type erase( const Key& key ) {
				return _tree.erase(ft::make_pair(key, mapped_type()));
			};
			void erase (iterator first, iterator last) {
				iterator next_delete = first;
				while (next_delete != last)
					next_delete = _tree.erase(next_delete);
			};
			void swap( map& other ) {
				_tree.swap(other._tree);
			};

			// ANCHOR - Lookup
			size_type count( const Key& key ) const {
				if (_tree.find(_make_key_value(key)) == _tree.end())
					return 0;
				else
					return 1;
			};

			iterator find( const key_type& key ) {
				return iterator(_tree.find(_make_key_value(key)));
			};
			const_iterator find( const key_type& key ) const {
				return const_iterator(_tree.find(_make_key_value(key)));
			};

			ft::pair<iterator,iterator> equal_range( const key_type& key ) {
				return _tree.equal_range(_make_key_value(key));
			};
			ft::pair<const_iterator,const_iterator> equal_range( const key_type& key ) const {
				return _tree.equal_range(_make_key_value(key));
			};

			iterator lower_bound( const key_type& key ) {
				return _tree.lower_bound(_make_key_value(key));
			};
			const_iterator lower_bound( const key_type& key ) const {
				return _tree.lower_bound(_make_key_value(key));
			};

			iterator upper_bound( const key_type& key ) {
				return _tree.upper_bound(_make_key_value(key));
			};
			const_iterator upper_bound( const key_type& key ) const {
				return _tree.upper_bound(_make_key_value(key));	
			};

			// ANCHOR - Observers
			key_compare key_comp() const {
				return _comp;
			};
			value_compare value_comp() const {
				return value_compare(_comp);
			};

		private:
			// ANCHOR - util
			value_type _make_key_value(const key_type& key) const {
				return ft::make_pair(key, mapped_type());
			}
			// !SECTION
	};
	// SECTION - Non-member functions
	// ANCHOR - operators
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ) {
		if (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
			return true;
		else
			return false;
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ) {
		return !(lhs == rhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ) {
		if (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
			return true;
		return false;
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ) {
		if (lhs < rhs || lhs == rhs)
			return true;
		return false;
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ) {
		if (!(lhs <= rhs))
			return true;
		return false;
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ) {
		if (!(lhs < rhs))
			return true;
		return false;
	}
	// ANCHOR - swap
	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs ) {
		lhs.swap(rhs);
	}
	// !SECTION
}

#endif
