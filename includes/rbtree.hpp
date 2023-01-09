#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <algorithm>
#include <memory>
#include <iterator>
#include "pair.hpp"
#include <iostream>

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
			node_pointer _nil;
		public :
			// SECTION - Member funcions
			// ANCHOR - construct/copy/destruct
			treeIterator(void) : _ptr(NULL), _nil(NULL) {};
			treeIterator(node_pointer ptr, node_pointer nil) : _ptr(ptr), _nil(nil) {};
			treeIterator(const treeIterator &other) { *this = other; };
			operator treeIterator<const T, U>(void) const { 
				return treeIterator<const T, U>(this->_ptr, this->_nil);
			};
			treeIterator &operator=(const treeIterator &other) {
				if (this != &other) {
					_ptr = other._ptr;
					_nil = other._nil;
				}
				return *this;
			}
			~treeIterator(void) {};
			// getter
			node_pointer base(void) const {
				return _ptr;
			}
			// ANCHOR - equality/inequality operators
			bool operator==(const treeIterator &other) const {
				return _ptr == other.base();
			}
			bool operator!=(const treeIterator &other) const {
				return _ptr != other.base();
			}
			// ANCHOR - Element access
			reference operator*(void) const {
				return _ptr->_value;
			}
			pointer operator->(void) const {
				return &(_ptr->_value);
			}
			// ANCHOR - increase, decrease
			treeIterator &operator++(void) {
				// 전위
				// std::cout << "전위증가!!!!!!!!!\n";
				if (this->_ptr->_right != _nil)
					this->_ptr = this->_get_minimum_node(this->_ptr->_right);
				else
				{
					// node_pointer child = this->_ptr;
					// this->_ptr = this->_ptr->_parent;
					// while (this->_ptr != _nil && child == this->_ptr->_right) {
					// 	child = this->_ptr;
					// 	this->_ptr = this->_ptr->_parent;
					// }
					while (_ptr != _nil && _ptr != _ptr->_parent->_left) {
						_ptr = _ptr->_parent;
					}
					_ptr = _ptr->_parent;
				}
				return (*this);
			}
			treeIterator &operator--(void) {
				// std::cout << "전위감소!!!!!!!!!\n";
				if (this->_ptr->_left != _nil)
					this->_ptr = this->_get_maximum_node(this->_ptr->_left);
				else
				{
					// node_pointer child = this->_ptr;
					// this->_ptr = this->_ptr->_parent;
					// while (this->_ptr != _nil && child == this->_ptr->_left) {
					// 	child = this->_ptr;
					// 	this->_ptr = this->_ptr->_parent;
					// }
					while (_ptr != _nil && _ptr != _ptr->_parent->_right) {
						_ptr = _ptr->_parent;
					}
					_ptr = _ptr->_parent;
				}
				return (*this);
			}
			treeIterator operator++(int) {
				// 후위
				// std::cout << "후위증가!!!!!!!!!\n";
				treeIterator ret(*this);
				++(*this);
				return ret;
			}
			treeIterator operator--(int) {
				// std::cout << "후위감소!!!!!!!!!\n";
				treeIterator ret(*this);
				--(*this);
				return ret;
			}
			// !SECTION
		private:
			// ANCHOR - util functions
			node_pointer _get_minimum_node(node_pointer sub_root) {
				node_pointer ret = sub_root;
				while (ret->_left != _nil)
					ret = ret->_left;
				return ret;
			}
			node_pointer _get_maximum_node(node_pointer sub_root) {
				node_pointer ret = sub_root;
				while (ret->_right != _nil) {
					ret = ret->_right;
				}
				return ret;
			}
	};
	// !SECTION

	// SECTION - red-black tree
	template<typename T, typename Key, typename Comp = std::less<T>, typename Alloc = std::allocator<T> >
	class rbTree {
		public :
			typedef T value_type;
			typedef treeNode<value_type> node_type;
			typedef node_type* node_pointer;
			typedef Key key_type;
			typedef treeIterator<value_type, node_type> iterator;
			typedef treeIterator<const value_type, node_type> const_iterator;
			typedef std::size_t		size_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::template rebind<node_type>::other node_allocator;
			typedef Comp		key_compare;
			
			// TODO - 필요없으면 private으로 옮겨도 ㄱㅊ
			node_pointer	_begin;	// first (smallest)
			node_pointer	_end;	// last (?)
			node_pointer	_nil; 	// unique leaf black node 
			key_compare			_comp;
			node_allocator			_alloc;
			size_type		_size;

			// ANCHOR - tree construct
			rbTree (const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _comp(comp),
			_alloc(alloc),
			_size(0) {
				_nil = _alloc.allocate(1);
				_alloc.construct(_nil, value_type());
				_nil->_is_black = true;
				_nil->_parent = _nil;
				_nil->_left = _nil;
				_nil->_right = _nil;
				_begin = _construct_node(value_type());
				_end = _begin;
			};
			rbTree (const rbTree &other)
			: _comp(other._comp),
			_alloc(other._alloc),
			_size(0) {
				_nil = _alloc.allocate(1);
				_alloc.construct(_nil, value_type());
				_nil->_is_black = true;
				_nil->_parent = _nil;
				_nil->_left = _nil;
				_nil->_right = _nil;
				_begin = _construct_node(value_type());
				_end = _begin;
				this->insert(other.begin(), other.end());
			};
			rbTree& operator=( const rbTree& other ) {
				if (this != &other) {
					this->clear();
					_comp = other._comp;
					_alloc = other._alloc;
					// _size = other._size;
					this->insert(other.begin(), other.end());
				}
				return *this;
			};
			~rbTree(void) {
				this->clear();
				_destruct_node(_nil);
				_destruct_node(_end);
				// NOTE (end는 다음의 무언가를 가리키게 해 두었으므로 소멸자에서만 해제하는게 맞을 듯 하다.)
			};
			//SECTION - print
			void
			print_nodes_map(void) const
			{
				check2(this->_end->_left);
			};

			void
			check2(node_pointer node_) const
			{
				if (node_->_left != _nil)
					check2(node_->_left);
				if (node_->_parent != _end)
					std::cout << "key: " << node_->_value.first << "\tv: " << node_->_value.second << "\tparents: " << node_->_parent->_value.first << "\tv: " << node_->_parent->_value.second << "\tcolor: " << (node_->_is_black ? "black" : "red") << std::endl;
				else
					std::cout << "key: " << node_->_value.first << "\tv: " << node_->_value.second<< "\tparents: " << "ROOT" << " \tcolor: " << (node_->_is_black ? "black" : "red") << std::endl;
				if (node_->_right != _nil)
					check2(node_->_right);
			};
			//!SECTION

			// ANCHOR - iterator
			iterator begin(void) {
				// return _begin;
				return iterator(_begin, _nil);
			};
			iterator end(void) {
				// return _end;
				return iterator(_end, _nil);
			};
			const_iterator begin(void) const {
				// return _begin;
				return const_iterator(_begin, _nil);
			};
			const_iterator end(void) const {
				// return _end;
				return const_iterator(_end, _nil);
			};
			// ANCHOR - Modifiers
			void clear(void) {
				if (_size != 0)
					_clear_tree(_get_root());
				_size = 0;
				_end->_left = _nil;
				_begin = _end;
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
				if (_get_root() == _nil) {
					node_pointer new_root = _construct_node(value);
					_set_root(new_root);
					_insert_update(new_root);
					return ft::make_pair(iterator(new_root, _nil), true);
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
				if (_get_root() == _nil) {
					node_pointer new_root = _construct_node(value);
					this->_set_root(new_root);
					_insert_update(new_root);
					return iterator(new_root, _nil);
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

			iterator erase( iterator pos ) {
				/**
				 * TODO - 만약에 이상한 이터레이터가 들어왔을 때 (근데 이게 안에서 보기엔 유효함)
				 * std::map에서는 세그폴트가 남.
				 * ft::map에서도 세크폴트를 유발하는 것이 맞을지 모르겠다.
				 */
				if (_size == 0)
					return this->end();
				iterator temp(pos);	// backup (for iterator )
				temp++;
				if (pos == this->begin()) {
					// 만약 지우려는 값이 최솟값이었다면 새로운 최솟값으로 업데이트 해 줍니다.
					_begin = temp.base();
				}
				// pos에 해당하는 노드를 트리에서 떼어내기
				_delete_node(pos.base());
				// 노드 메모리 상에서 제거하기
				_destruct_node(pos.base());
				// 마지막에 사이즈 감소시키기
				_size--;
				// 이상해진 _nil의 내부 변수들 수정해주기
				_nil->_left = _nil;
				_nil->_right = _nil;
				_nil->_parent = _nil;
				return temp;
			};
			size_type erase( const value_type &key_value ) {
				iterator target = iterator(_find_node(key_value), _nil);
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
				// TODO - 확인 필요함.
				return std::min<size_type>(PTRDIFF_MAX, _alloc.max_size());
				// return _alloc.max_size();
			};

			// ANCHOR - Lookup
			iterator find( const value_type &key_value ) {
				return iterator(_find_node(key_value), _nil);
			};
			const_iterator find(  const value_type &key_value ) const {
				return const_iterator(_find_node(key_value), _nil);
			};
		// SECTION - private member functions
		private :
			rbTree (void) {};
			// ANCHOR - construct, destruct node
			node_pointer _construct_node (const value_type &value) {
				node_pointer ret = _alloc.allocate(1);
				// TODO - 왜 과거의 나는 이걸 동적할당 해줬을까?
				_alloc.construct(ret, value);
				// ret->_value = value;
				ret->_is_black = false;
				ret->_parent = _nil;
				ret->_left = _nil;
				ret->_right = _nil;
				return (ret);
			};

			void _destruct_node(node_pointer ptr) {
				// TODO - 생성시에 동적할당 해줬기 때문에 지워줌. 만약에 불필요하다면 없애버리자.
				_alloc.destroy(ptr);
				_alloc.deallocate(ptr, 1);
			}
			// ANCHOR - find
			node_pointer _find_node( const value_type &key_value ) const {
				if (this->empty())
					return _end;
				node_pointer ptr = _get_root();
				while(ptr != _nil) {
					if (_comp(ptr->_value, key_value))
						ptr = ptr->_right;
					else if (_comp(key_value, ptr->_value))
						ptr = ptr->_left;
					else
						return ptr;
				}
				return _end;
			};
			// ANCHOR - insert node
			ft::pair<iterator, bool> _insert_node(const value_type& value) {
				node_pointer node_ptr = _find_node(value);
				bool result;
				if (node_ptr != _end)
					result = false;
				else {
					result = true;
					node_ptr = _construct_node(value);
					// 삽입
					_insert_node_at(_get_root(), node_ptr);
					_insert_fix_up(node_ptr);
					_insert_update(node_ptr);
				}
				return ft::make_pair(iterator(node_ptr, _nil), result);
			};
			iterator _insert_hint_node(node_pointer pos, const value_type& value) {
				node_pointer node_ptr = _find_node(value);
				if (node_ptr == _end) {
					(void)pos; // TODO - pos를 이용해서 실제로 넣을 수 있는 위치를 효율적으로 찾는 작업이 필요함. (__find_equal(const_iterator __hint 을 참고하면 좋을 듯?)
					node_ptr = _construct_node(value);
					// _insert_node_at(pos, node_ptr);
					_insert_node_at(_get_root(), node_ptr);
					_insert_fix_up(node_ptr);
					_insert_update(node_ptr);
				}
				return iterator(node_ptr, _nil);
			};
			void _insert_node_at(node_pointer parent, node_pointer child) {
				// node_pointer new_node;
				if (_comp(parent->_value, child->_value)) {
					if (parent->_right == _nil) {
						parent->_right = child;
						child->_parent = parent;
					}
					else
						_insert_node_at(parent->_right, child);
				}
				else {
					if (parent->_left == _nil) {
						parent->_left = child;
						child->_parent = parent;
					}
					else
						_insert_node_at(parent->_left, child);
				}
			}
			void _insert_fix_up(node_pointer node) {
				node_pointer current = node;
				while (current != _get_root() && current->_parent->is_red() == true) {
					if (current->_parent == current->_parent->_parent->_left) {
						current = _insert_fix_up_left(current);
					}
					else {
						current = _insert_fix_up_right(current);
					}
				}
				_get_root()->_is_black = true;
			}

			node_pointer _insert_fix_up_left(node_pointer current) {
				node_pointer uncle;
				uncle = current->_parent->_parent->_right;
				if (uncle->is_red() == true) {
					_recolor(current->_parent, uncle, current->_parent->_parent);
					current = current->_parent->_parent;
				}
				else {
					if (current == current->_parent->_right) {
						current = current->_parent;
						_rotate_left(current);
					}
					current->_parent->_is_black = true;
					current->_parent->_parent->_is_black = false;
					_rotate_right(current->_parent->_parent);
				}
				return current;
			}

			node_pointer _insert_fix_up_right(node_pointer current) {
				node_pointer uncle;
				uncle = current->_parent->_parent->_left;
				if (uncle->is_red() == true) {
					_recolor(current->_parent, uncle, current->_parent->_parent);
					current = current->_parent->_parent;
				}
				else {
					if (current == current->_parent->_left) {
						current = current->_parent;
						_rotate_right(current);
					}
					current->_parent->_is_black = true;
					current->_parent->_parent->_is_black = false;
					_rotate_left(current->_parent->_parent);
				}
				return current;
			}

			void _insert_update(node_pointer new_node) {
				if(_size == 0 || _comp(new_node->_value, _begin->_value))
					_begin = new_node;
				_size++;
			}

			// ANCHOR - rotate
			void _rotate_left(node_pointer parent) {
				node_pointer right_child = parent->_right;
				parent->_right = right_child->_left; // 오른쪽 자식노드의 왼쪽 자식노드를 부모의 오른쪽 자식으로
				if (parent->_right != _nil) // 만약 자식이 존재한다면 자식의 부모 정보도 업데이트 해 준다.
					parent->_right->_parent = parent;
				right_child->_parent = parent->_parent; // 자식의 부모도 부모의 부모로 (...) 업데이트 해 준다.
				if (right_child->_parent == _end) {	// 만약 부모가 루트였을 경우에는 자식을 루트로 업데이트 해 준다.
					_set_root(right_child);
				}
				else {
					if (parent == parent->_parent->_right)
						parent->_parent->_right = right_child;
					else
						parent->_parent->_left = right_child;
				}
				right_child->_left = parent;
				parent->_parent = right_child;
			}

			void _rotate_right(node_pointer parent) {
				node_pointer left_child = parent->_left;

				parent->_left = left_child->_right;
				
				if (parent->_left != _nil)
					parent->_left->_parent = parent;

				left_child->_parent = parent->_parent;

				if (left_child->_parent == _end)
					_set_root(left_child);
				else
				{
					if (parent == parent->_parent->_left)
						parent->_parent->_left = left_child;
					else
						parent->_parent->_right = left_child;
				}
				left_child->_right = parent;
				parent->_parent = left_child;
			}
			// ANCHOR - recolor
			void _recolor(node_pointer parent, node_pointer uncle, node_pointer grand_parent) {
				parent->_is_black = true;
				uncle->_is_black = true;
				grand_parent->_is_black = false;
			}

			// ANCHOR - erase/delete
			void _delete_node(node_pointer target) {
				// TODO - 변수 네이밍 꼭 수정합시다 ^_^
				node_pointer y = target;
				node_pointer x;
				bool y_original_color_is_black = y->_is_black;

				if (target->_left == _nil) { // case 1)
					x = target->_right;
					_transplant(target, x);
				}
				else if (target->_right == _nil) { // case 2)
					x = target->_left;
					_transplant(target, x);
				}
				else {	// case 3)
					y = _get_minimum_node(target->_right);
					y_original_color_is_black = y->_is_black;
					x = y->_right;
					// ===
					if (y->_parent == target) {
						// NOTE - 일반적인 경우라면 필요없는 작업이지만 x가 Nil인 경우에는 따로 부모가 설정되어 있지 않으므로 설정해줘야 한다.
						x->_parent = y;
					}
					else {
						_transplant(y, x);
						y->_right = target->_right;
						y->_right->_parent = y;
					}
					_transplant(target, y);
					y->_left = target->_left;
					y->_left->_parent = y;
					y->_is_black = target->_is_black;
				}
				if (y_original_color_is_black == true)
					_delete_fix_up(x);
			}
			// SECTION
			void _delete_fix_up(node_pointer node) {
				while (node != _get_root() && node->is_black() == true) {
					// 대체된 노드의 새로운 자리가 왼쪽 자식 자리인 경우
					if (node == node->_parent->_left) {
						node = _delete_fix_up_left(node);
					}
					else {
						node = _delete_fix_up_right(node);
					}
				}
				node->_is_black = true; // TODO - 이거 뭐지
			}

			// NOTE - Doubly Black 처리
			node_pointer _delete_fix_up_left(node_pointer node) {
				node_pointer sibling = node->_parent->_right;	// 형제는 오른쪽
				if (sibling->is_red() == true) {		// doubly black의 형제(삼촌)가 red인 경우
					sibling->_is_black = true;		// 삼촌의 색을 조부모의 색으로 (삼촌이 red였으니 조부모는 black)
					node->_parent->_is_black = false;	// 조부모의 색을 삼촌의 색으로 바꾼다.
					_rotate_left(node->_parent);	// 조부모를 기준으로 좌회전
					sibling = node->_parent->_right;	// doubly black의 새로운 형제로 바꾸어서 상황에 맞게 처리한다.
				}
				if (sibling->_left->is_black() == true && sibling->_right->is_black() == true) {
					// 형제가 black, 자녀도 모두 black인 경우
					// 형제들의 black을 모아서 조부모에게로 넘김. 조부모가 알아서 extra black을 처리한다.
					// node는 doubly black이었으므로 색깔 변화가 없지만
					sibling->_is_black = false;	// 형제는 black이 하나였으므로 색깔이 변한다.
					node = node->_parent;	// 조부모에게로 extra black 처리 넘김
				}
				else {
					if (sibling->_right->is_black() == true) { // 형제의 방향과 다른 방향의 자녀는 red, 같은 방향의 자녀는 black인 경우 (case 3)
						// 형제의 왼쪽 자녀와 형제의 색깔을 바꿔준다.
						sibling->_left->_is_black = true;		// 원래 red였던 왼쪽 자녀의 색을 형제의 색인 black으로
						sibling->_is_black = false;			// 원래 black이었던 형제의 색을 왼쪽 자녀의 색인 red로 바꿔준다.
						_rotate_right(sibling);				// 형제를 기준으로 우회전한다.
						sibling = node->_parent->_right;		// 아래 작업을 거쳐야 하므로 sibling을 다시 원래 지점으로 돌려준다.
					}
					// 형제의 방향과 같은 방향의 자녀가 red인 경우
					sibling->_is_black = node->_parent->_is_black;	// 형제의 색을 부모의 색으로 바꿔준다.
					sibling->_right->_is_black = true;				// red였던 형제의 오른쪽 자녀의 색을 black으로 바꿔준다.
					node->_parent->_is_black = true;				// 부모의 색은 무조건 black으로 바꿔준다.(red-and-black 해결)
					_rotate_left(node->_parent);					// 부모를 기준으로 좌회전한다.
					node = _get_root();								// fix-up 이 끝났으므로 종료조건을 반환.
				}
				return node;
			}

			node_pointer _delete_fix_up_right(node_pointer node) {
				// doubly black이 오른쪽 노드
				node_pointer sibling = node->_parent->_left; // 형제는 왼쪽의 노드이다.
				if (sibling->is_red() == true) { // 형제 노드가 red일 경우 (Case 1)
					sibling->_is_black = true;	// 형제의 색을 부모의 색으로 (형제가 red이므로 부모는 black이다.)
					node->_parent->_is_black = false;	// 부모의 색을 형제의 색 black으로
					// _rotate_left(node->_parent);	// 부모를 기준으로 좌회전
					_rotate_right(node->_parent);	// 형제가 왼쪽의 노드이므로, 부모를 기준으로 우회전해야 한다.
					sibling = node->_parent->_left;	// 새로운 형제의 색으로 위치를 변경하여 다시 확인한다.
				}
				if (sibling->_right->is_black() == true && sibling->_left->is_black() == true) {
					// 만약의 형제의 두 자식들이 모두 black인 경우 (Case 2)
					// node와 sibling 두 형제의 black을 모아서 부모에게 전달
					// node는 doubly black이었으므로 색깔 변화가 없음
					sibling->_is_black = false;	// 형제는 black이었으므로 red로 바뀐다.
					node = node->_parent;		// 부모가 extra black을 받아 처리한다.
				}
				else {	// 형제의 자녀들 중에 적어도 하나가 red인 경우
					if (sibling->_left->is_black() == true) {	// 형제와 다른 방향의 자식이 red, 같은 방향의 자식은 black인 경우 (Case 3)
						// 형제와 같은 방향의 자식이 red가 되게 해서 Case 4를 적용시킨다.
						sibling->_right->_is_black = true;	// 형제와 다른 방향의 자녀를 black으로 바꿈 (형제의 색깔)
						sibling->_is_black = false;			// 형제의 색깔을 다른 방향의 자녀의 색깔로 바꿈 (Red)
						_rotate_left(sibling);				// 형제를 기준으로 좌회전 한다.
						sibling = node->_parent->_left;		// 아래 작업을 거쳐야 하므로 다시 형제 포인터를 원래의 값으로 돌린다.
					}
					// 형제와 같은 방향의 자식이 red인 경우 (Case 4)
					sibling->_is_black = node->_parent->_is_black;	// 형제의 색을 형제의 부모의 색으로 바꾼다. (형제의 색은 원래 Black)
					node->_parent->_is_black = true;	// 형제의 부모의 색은 무조건 Black으로 바꿔줌 (red-and-black 조치를 미리 한 것으로 이해하자)
					sibling->_left->_is_black = true;		// 형제와 같은 방향인 왼쪽의 자녀도 Red에서 Black으로 바꿔준다.
					_rotate_right(node->_parent);		// 부모를 기준으로 우회전한다.
					node = _get_root();					// fix-up이 끝났으므로 종료 조건을 준다.
				}
				return node;
			}

			node_pointer _get_replace_node(node_pointer target) {
				node_pointer replace_node;
				if (target->_right != _nil)
					replace_node = _get_minimum_node(target);
				else if (target->_left != _nil)
					replace_node = _get_maximum_node(target);
				else
					replace_node = _nil;
				return replace_node;
			}

			node_pointer _get_minimum_node(node_pointer root) {
				node_pointer ret = root;
				while (ret->_left != _nil)
					ret = ret->_left;
				return ret;
			}

			node_pointer _get_maximum_node(node_pointer root) {
				node_pointer ret = root;
				while (ret->_right != _nil)
					ret = ret->_right;
				return ret;
			}

			void _transplant(node_pointer target, node_pointer replace_node) {
				if (target == _get_root())
					_set_root(replace_node);
				else {
					if (target == target->_parent->_left)
						target->_parent->_left = replace_node;
					else
						target->_parent->_right = replace_node;
					if (replace_node != _nil)
						replace_node->_parent = target->_parent;
				}
			}

			// ANCHOR - util
			void _set_root(node_pointer new_root) {
				new_root->_is_black = true;
				_end->_left = new_root;
				new_root->_parent = _end;
			};
			node_pointer _get_root(void) const {
				return _end->_left;
			}
			void _clear_tree(node_pointer sub_root) {
				if (sub_root == _nil)
					return;
				this->_clear_tree(sub_root->_left);
				this->_clear_tree(sub_root->_right);
				_destruct_node(sub_root);
				// TODO - _end 노드가 지워지는지 확인할 것. (지워지면 안된다.)
			}
		// !SECTION
	};
	// !SECTION
}

#endif
