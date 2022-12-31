#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <algorithm>
#include <memory>
#include <iterator>
#include "pair.hpp"

namespace ft
{
	// SECTION - treeNode
	/**
	 * @param T	: ft::pair
	 */
	template <typename T>
	struct treeNode {
		typedef T value_type;

		bool _is_black;
		value_type _value;
		treeNode *_parent;
		treeNode *_left;
		treeNode *_right;

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
		// ANCHOR - check color
		bool is_black(void) {
			return _is_black;
		};
		bool is_red(void) {
			return !(_is_black);
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
	 * @param T	ft::pair<const Key, t>
	 * @param Key map key
	 */
	template<typename T, typename Key, typename Comp = std::less<T>, typename Alloc = std::allocator<T> >
	class rbTree {
		public :
			typedef treeNode<T> node;
			typedef node* node_pointer;
			typedef T value_type;
			typedef Key key_type;
			typedef treeIterator<value_type, node> iterator;
			typedef __tree_iterator<const value_type, node_type> const_iterator;
			typedef std::size_t		size_type;
			
			// TODO - 필요없으면 private으로 옮겨도 ㄱㅊ
			node_pointer	_begin;	// root
			node_pointer	_end;	// last (?)
			node_pointer	_nil; 	// unique leaf black node 
			Comp			_comp;
			Alloc			_alloc;
			size_type		_size;

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
			// ANCHOR - iterator
			node_pointer begin(void) const {
				return _begin;
			};
			node_pointer end(void) const {
				return _end;
			};
			// ANCHOR - Modifiers
			void clear(void) {

			};

			/** 
			 * NOTE
			 * ref : _tree 2090 __emplace_unique_key_args (value)
			 * ref : _tree 2190 __emplace_hint_unique_key_args (pos)
			 */
			ft::pair<iterator, bool> insert( const value_type& value ) {
				/** 
				 * NOTE
				 * bool의 의미 - true : 없는 key를 추가함 false : 존재하던 key의 값을 업데이트함.
				 * case 1) 빈 경우 : 루트로 설정해준다.
				 * case 2) 그 외 : _insert_node(const value_type& value) 함수 호출
				 * 	- 내부에서 _insert_node_at 함수 호출 예정...
				 */
				if (_begin == NULL) {
					return ft::make_pair(this->_set_root(value), true);
				}
				else {
					return this->_insert_node(value);
				}
			};
			iterator insert( iterator pos, const value_type& value ) {
				/**
				 * NOTE
				 * 여기서 말하는 pos는 insert할 정확한 위치가 아닌, 최대한 그 지점과 비슷한 곳에 삽입하라는 뜻이다.
				 * 일단 그 지점을 시작으로 삽입할 수 있는 곳을 찾아서, 넣어준다.
				 * 상황에 따라서 회전, 혹은 색상 변환을 해 주면 되겠다.
				 * 
				 * case 1) 빈 경우 : 루트로 설정해준다.
				 * case 2) 그 외 : _insert_hint_node(node_pointer pos, const value_type& value) 함수 호출
				 */
				if (_begin == NULL) {
					return this->_set_root(value);
				}
				else {
					return this->_insert_hint_node(pos.base(), value);
				}
			};
			template <class InputIt>
			void insert(InputIt first, InputIt last) {
				while (first != last) {
					this->insert(*first);
					first++;
				}
			}

			void erase( iterator pos ) {

			};
			size_type erase( const key_type& key ) {
				iterator target = this->find(key);
				if (target == this->end())
					return 0;
				else {
					this->erase(target);
					return 1;
				}
			};

			void swap(rbTree &other) {
				std::swap(_begin, other._begin);
				std::swap(_end, other._end);
				std::swap(_nil, other._nil);
				std::swap(_comp, other._comp);
				std::swap(_alloc, other._alloc);
				std::swap(_size, other._size);
			}
			// ANCHOR - Capacity
			bool empty() const {
				if (_size == 0)
					return true;
				else
					return false;
			};
			size_type size() const {
				return _size;
			};
			size_type max_size() const {
				return _alloc.max_size();
			};

			// ANCHOR - Lookup
			node_pointer find( const key_type &key ) const {
				
			};
			node_pointer lower_bound( const Key& key ) const {

			}
			node_pointer upper_bound( const Key& key ) const {

			}
		// SECTION - private member functions
		private :
			rbTree (void) {};
			// ANCHOR - set default node
			node_pointer _construct_node (value_type &value) {
				node_pointer ret;
				_alloc.construct (&(ret->_value), value);
				ret->_is_black = false;
				ret->_parent = NULL;
				ret->_left = _nil;
				ret->_right = _nil;
				return (ret);
			};
			iterator _set_root(const value_type& value) {
				_begin = _construct_node(value);
				_begin->_is_black = true;
				_begin = _end;
				return iterator(_begin);
			};
			// ANCHOR - insert node
			ft::pair<iterator, bool> _insert_node(const value_type& value) {
				node_pointer node_ptr = this->find(value.first);
				bool result;
				if (node_ptr != this->end()) {
					result = false;
					node_ptr->_value.second = value.second;
				}
				else {
					result = true;
					node_ptr = _construct_node(value);
					// 삽입
					_insert_node_at(_begin, node_ptr);
					// 필요에 따라 회전
					_rotate_if_needed(node_ptr);
					// 필요에 따라 색상 변환
					_recolor_if_needed(node_ptr);
				}
				return ft::make_pair(iterator(ret_ptr), result);
			};
			iterator _insert_hint_node(node_pointer pos, const value_type& value) {
				node_pointer node_ptr = this->find(value.first);
				if (node_ptr != this->end())
					node_ptr->_value.second = value.second;
				else {
					if (pos->_parent != NULL)
						pos = pos->_parent;
					node_ptr = _construct_node(value);
					// 삽입
					_insert_node_at(pos, node_ptr);
					// 필요에 따라 회전
					_rotate_if_needed(node_ptr);
					// 필요에 따라 색상 변환
					_recolor_if_needed(node_ptr);
				}
				return iterator(node_ptr);
			};
			void _insert_node_at(node_pointer parent, node_pointer child) {
				node_pointer new_node;
				if (_comp(parent->_value, child->_value)) {
					if (parent->_right == _nil) {
						parent->_right = child;
						child->_parent = parent->_right;
					}
					else
						_insert_node_at(parent->_right, child);
				}
				else {
					if (parent->_left == _nil) {
						parent->_left = child;
						child->_parent = parent->_right;
					}
					else
						_insert_node_at(parent->_left, child);
				}
			}
			// ANCHOR - rotate
			void _rotate_if_needed(node_pointer node) {
				// TODO - 회전 필요 여부 확인하는 함수 분리해야할지도
				if (node->_parent == NULL || node->_parent->is_black() == true)
					return;
				node_pointer uncle_ptr = _get_sibling_ptr(node->_parent);
				if (uncle_ptr != _nil && uncle_ptr->is_red() == true)
					return;
				// TODO - 회전 시작
			}
			// ANCHOR - recolor
			void _recolor_if_needed(node_pointer node) {
				// TODO - 색깔 변환 필요 여부 확인하는 함수 분리해야할지도
				if (node->_parent == NULL || node->_parent->is_black() == true)
					return;
				node_pointer uncle_ptr = _get_sibling_ptr(node->_parent);
				if (uncle_ptr == _nil || uncle_ptr->is_black() == true)
					return;
				// TODO - 색깔 변환 시작
			}

			// ANCHOR - util
			node_pointer _get_sibling_ptr(node_pointer node) {
				if (node->_parent == NULL)
					return _nil;
				else if (node->_parent->_left != node)
					return node->_parent->_left;
				else
					return node->_parent->_right;
			}

		// !SECTION
	};
	// !SECTION
}

#endif