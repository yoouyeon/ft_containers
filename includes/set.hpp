#ifndef SET_HPP
# define SET_HPP

#include <functional>
#include <algorithm>
#include <memory>
#include <exception>

#include "algorithm.hpp"
#include "pair.hpp"
#include "type_traits.hpp"
#include "rbtree.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template< class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set {
		public :
			// ANCHOR - Member types
			typedef Key                                      key_type;
			typedef key_type                                 value_type;
			typedef Compare                                  key_compare;
			typedef key_compare                              value_compare;
			typedef Allocator                                allocator_type;
			typedef typename allocator_type::reference       reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::size_type       size_type;
			typedef typename allocator_type::difference_type difference_type;
			typedef typename allocator_type::pointer         pointer;
			typedef typename allocator_type::const_pointer   const_pointer;
			typedef typename ft::rbTree<const value_type, key_type, value_compare, allocator_type>::iterator iterator;			
			typedef typename ft::rbTree<const value_type, key_type, value_compare, allocator_type>::const_iterator const_iterator;
			typedef std::reverse_iterator<iterator>          reverse_iterator;
			typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;
		private :
			// ANCHOR - Member variables
			key_compare _comp;
			allocator_type _alloc;
			ft::rbTree<const value_type, key_type, value_compare, allocator_type> _tree;
		public :
			// SECTION - Member functions
			// ANCHOR - Constructor, Destructor, assign operator, getter
			explicit set( const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
			: _comp(comp),
			_alloc(alloc),
			_tree(_comp, _alloc) {};

			template< class InputIt >
			set( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() , typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0 )
			: _comp(comp),
			_alloc(alloc),
			_tree(_comp, _alloc) {
				_tree.insert(first, last);
			};

			set( const set& other )
			: _comp(other._comp),
			_alloc(other._alloc),
			_tree(other._tree) {};

			~set() {};

			set& operator=( const set& other ){
				if (this != &other) {
					_comp = other._comp;
					_alloc = other._alloc;
					_tree = other._tree;
				}
				return *this;
			};

			allocator_type get_allocator() const {
				return _alloc;
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
			}

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

			void erase( iterator first, iterator last ) {
				iterator next_delete = first;
				while (next_delete != last)
					next_delete = _tree.erase(next_delete);
			};

			size_type erase( const Key& key ) {
				return _tree.erase(key);
			};

			void swap( set& other ) {
				_tree.swap(other._tree);
			};

			// ANCHOR - Lookup
			size_type count( const Key& key ) const {
				if (_tree.find(key) == _tree.end())
					return 0;
				else
					return 1;
			};

			iterator find( const Key& key ) {
				return iterator(_tree.find(key));
			};

			const_iterator find( const Key& key ) const {
				return const_iterator(_tree.find(key));
			};

			ft::pair<iterator,iterator> equal_range( const Key& key ) {
				return _tree.equal_range(key);
			};

			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
				return _tree.equal_range(key);
			};

			iterator lower_bound( const Key& key ) {
				return _tree.lower_bound(key);
			};

			const_iterator lower_bound( const Key& key ) const {
				return _tree.lower_bound(key);
			};

			iterator upper_bound( const Key& key ) {
				return _tree.upper_bound(key);
			};

			const_iterator upper_bound( const Key& key ) const {
				return _tree.upper_bound(key);
			};

			// ANCHOR - Observers

			key_compare key_comp() const {
				return _comp;
			};

			value_compare value_comp() const {
				return _comp;
			};

			// !SECTION
	};

	// ANCHOR - Non-member functions
	template< class Key, class Compare, class Alloc >
	bool operator==( const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs ) {
		if (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
			return true;
		else
			return false;
	}
	template< class Key, class Compare, class Alloc >
	bool operator!=( const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs ) {
		return !(lhs == rhs);
	}
	template< class Key, class Compare, class Alloc >
	bool operator<( const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs ) {
		if (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
			return true;
		return false;
	}
	template< class Key, class Compare, class Alloc >
	bool operator<=( const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs ) {
		if (lhs < rhs || lhs == rhs)
			return true;
		return false;
	}
	template< class Key, class Compare, class Alloc >
	bool operator>( const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs ) {
		if (!(lhs <= rhs))
			return true;
		return false;
	}
	template< class Key, class Compare, class Alloc >
	bool operator>=( const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs ) {
		if (!(lhs < rhs))
			return true;
		return false;
	}
	template< class Key, class Compare, class Alloc >
	void swap( ft::set<Key, Compare, Alloc>& lhs, ft::set<Key, Compare, Alloc>& rhs ) {
		lhs.swap(rhs);
	}
}

#endif
