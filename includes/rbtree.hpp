#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <algorithm>
#include <memory>
#include <iterator>

namespace ft
{
	// SECTION - treeNode
	/**
	 * @param T	
	 */
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
	// !SECTION

	// SECTION - tree iterator
	// TODO - 파일 분리 가능성 있음
	/**
	 * @param T	ft::pair
	 * @param U treeNode
	 */
	/*NOTE - reference
		map line 793
		_tree line 182
	*/
	template <class T, class U>
	class treeIterator {
		public :
			// ANCHOR - Member types
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef T								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef T&								reference;
			typedef T*								pointer;
			typedef U								node_type;
			typedef U&								node_reference;
			typedef U*								node_pointer;
		private :
			// ANCHOR - Member variables
			node_pointer _ptr;
		public :
			// SECTION - Member funcions
			// ANCHOR - construct/copy/destruct
			treeIterator(void) {};
			treeIterator(pointer ptr) : _ptr(ptr) {};
			treeIterator(const treeIterator &other) : _ptr(other.base()) {};
			treeIterator &operator=(const treeIterator &other) {
				if (this != &other) {
					_ptr = other.base();
				}
				return *this;
			}
			~treeIterator(void) {};
			// getter
			node_pointer base(void) const {
				return _ptr;
			}
			// ANCHOR - equality/inequality operators
			bool operator==(const treeIterator &other) {
				return _ptr == other.base()
			}
			bool operator!=(const treeIterator &other) {
				return _ptr != other.base();
			}
			// ANCHOR - Element access
			pointer operator*(void) const {
				return &(_ptr->_value);
			}
			reference operator->(void) const {
				return _ptr->_value;
			}
			// ANCHOR - increase, decrease
			treeIterator &operator++(void) {
				// 전위
			}
			treeIterator &operator--(void) {

			}
			treeIterator operator++(int) {
				// 후위
			}
			treeIterator operator--(int) {
				
			}
			// !SECTION

	};
	// !SECTION

	// SECTION - red-black tree
	/**
	 * @param T	
	 */
	template<typename T, typename Comp = std::less<T>, typename Alloc = std::allocator<T> >
	class rbTree {
		public :
			typedef treeNode<T> node;
			typedef node* node_pointer;
			typedef T value_type;
			typedef treeIterator<value_type, node> iterator;
			
			// TODO - 필요없으면 private으로 옮겨도 ㄱㅊ
			node_pointer	_begin;	// root
			node_pointer	_end;	// last (?)
			node_pointer	_nil; 	// unique leaf black node 
			Comp			_comp;
			Alloc			_alloc;
			size_t			_size;

			// ANCHOR - tree construct
			rbTree (const Comp &comp, const Alloc &alloc)
			: _comp(comp),
			_alloc(alloc),
			_size(0) {
				_nil = _alloc.allocate(1);
				_alloc.construct(&(_nil->_value), value_type());
				_nil->_is_black = true;
				_nil->_parent = NULL;
				_nil->_left = NULL;
				_nil->_right = NULL;
				_begin = NULL;
				_end = NULL;
			};
			rbTree (const rbTree &other)
			: _comp(other._comp),
			_alloc(other._alloc),
			_size(other._size) {
				_nil = _alloc.allocate(1);
				_alloc.construct(&(_nil->_value), value_type());
				_nil->_is_black = true;
				_nil->_parent = NULL;
				_nil->_left = NULL;
				_nil->_right = NULL;
				_begin = NULL;
				_end = NULL;
				this->insert(other.begin(), other.end());
			};
			rbTree& operator=( const rbTree& other ) {
				if (*this != other) {
					this->clear();
					_comp = other._comp;
					_alloc = other._alloc;
					_size = other._size;
					this->insert(other.begin(), other.end());
				}
				return *this;
			};
			~rbTree(void) {
				/*TODO - tree 소멸자
					- 완전히 삭제 (end부터 삭제해야 할 듯 ?)
					- nil 삭제
				*/
			};
			// ANCHOR - insert (map에서 그대로 호출 예정)
			ft::pair<iterator, bool> insert( const value_type& value ) {

			};
			iterator insert( iterator pos, const value_type& value ) {

			};
			template <class InputIt>
			void insert(InputIt first, InputIt last) {

			}
			// ANCHOR - iterator
			iterator begin(void) {
				// return _begin;
			};
			iterator end(void) {
				// return _end;
			};
			// ANCHOR - clear
			void clear(void) {

			};
		private :
			rbTree (void) {};
			node_pointer _construct_node (value_type &value) {
				node_pointer ret;
				_alloc.construct (&(ret->_value), value);
				ret->_is_black = false;
				ret->_parent = NULL;
				ret->_left = _nil;
				ret->_right = _nil;
				return (ret);
			}
	};
	// !SECTION
}

#endif