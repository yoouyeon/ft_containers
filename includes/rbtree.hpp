#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <algorithm>

namespace ft
{
	// ANCHOR - treeNode
	template <typename T>
	struct treeNode {
		typedef T value_type;

		bool _is_black;
		value_type _value;
		treeNode *_parent;
		treeNode *_left;
		treeNote *_right;

		treeNode (void)
			: _is_black(false),
			_value(value_type()),
			_parent(NULL),
			_left(NULL),
			_right(NULL) {};
		treeNode (const value_type &value)
			: _is_black(false),
			_value(value),
			_parent(NULL),
			_left(NULL),
			_right(NULL) {};
		treeNode (const treeNode &other)
			: _is_black(other._is_black),
			_value(other._value),
			_parent(other._parent),
			_left(other._left),
			_right(other._right) {};
		~treeNode (void) {};
		treeNode &operator=(const treeNode &other) {
			if (*this != other) {
				_is_black = other._is_black;
				_value = other._value;
				_parent = other._parent;
				_left = other._left;
				_right = other._right;
			}
			return *this;
		};
	};
	// ANCHOR - red-black tree
	template<typename T, typename Comp = std::less<T>, typename Alloc = std::allocator<T> >
	class rbTree {
		public :
			typedef treeNode<T> node;
			typedef node* node_pointer;
			typedef T value_type;
			
			// TODO - 필요없으면 private으로 옮겨도 ㄱㅊ
			node_pointer	_begin;
			node_pointer	_end;
			node_pointer	_nil;
			Comp			_comp;
			Alloc			_alloc;

			// ANCHOR - tree construct
			rbTree (const Comp &comp, const Alloc &alloc)
			: _comp(comp),
			_alloc(alloc) {
				
			};
			rbTree (const rbTree &other) 
			: _comp(other._comp),
			_alloc(other._comp) {

			};
			~rbTree(void) {};
		private :
			rbTree (void) {};
	};
}

#endif