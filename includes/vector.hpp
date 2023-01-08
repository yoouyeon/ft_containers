#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>		// allocator
#include <exception>	// exception
#include <algorithm>	// swap
#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include <iostream>

namespace ft
{
	template<class T, class Allocator = std::allocator<T> >
	class vector {
		public :
			// ANCHOR - Member types
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			// typedef pointer										iterator;		// 이게 맞나
			typedef ft::vector_iterator<value_type>			iterator;
			// typedef const_pointer								const_iterator;	// 이게 맞나
			typedef ft::vector_iterator<const value_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		protected :
			// ANCHOR - Member variables
			pointer			_start;		// null
			size_type		_size;		// 0
			size_type		_capacity;	// 0
			allocator_type	_alloc;		// Allocator()
		public :
			//ANCHOR - Member functions
			explicit vector() \
				: _start(NULL), \
				_size(0), \
				_capacity(0), \
				_alloc(Allocator()) {
				// (1) Default constructor. Constructs an empty container with a default-constructed allocator.
			};
			explicit vector(const Allocator& alloc) \
				: _start(NULL), \
				_size(0), \
				_capacity(0), \
				_alloc(Allocator(alloc)) {
				// (2) Constructs an empty container with the given allocator alloc.
			};
			explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) \
				: _size(count), \
				_capacity(count), \
				_alloc(Allocator(alloc)) {
				// (3) Constructs the container with count copies of elements with value value.
				if (_size < 0)
					throw std::length_error("vector (constructor)");
				_start = _alloc.allocate(_capacity);
				for (size_type i = 0; i < count; i++)
					_alloc.construct(&_start[i], value);
				/* TODO
					- capacity 결정 ✔️
					- 할당 ✔️
					- 값 넣어주기 ✔️
					- _start 결정 ✔️
				*/
			};
			template<class InputIt>
			vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type* = 0) \
				: _alloc(Allocator(alloc)) {
				// (5) Constructs the container with the contents of the range [first, last).
				_size = std::distance(first, last);
				if (_size < 0)
					throw std::length_error("vector (constructor)");
				_capacity = _size;
				_start = _alloc.allocate(_capacity);
				this->assign(first, last);
				/* TODO
					- capacity 결정 ✔️
					- 할당 ✔️
					- 값 넣어주기 ✔️
					- size ✔️
					- _start 결정 ✔️
				*/
			};
			vector(const vector& other) \
				: _size(other.size()), \
				_capacity(other.capacity()), \
				_alloc(other.get_allocator()) {
				// (6) Copy constructor. Constructs the container with the copy of the contents of other.
				_start = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++) {
					_alloc.construct(&_start[i], other[i]);
				}
				/* TODO
					- 할당 ✔️
					- 값 넣어주기 ✔️
					- size ✔️
					- _start 결정 ✔️
				*/
			};
			~vector() {
				this->clear();
				_alloc.deallocate(_start, _capacity);
			};
			vector& operator=(const vector& other) {
				// Copy assignment operator. Replaces the contents with a copy of the contents of other.
				if (*this == other)
					return *this;
				/*
					테스트 결과
					this->capacity() > other.capacity() 인 경우에도 this->capacity()가 그대로
						-> 필요하지 않으면 재할당 안함.
				*/
				this->assign(other.begin(), other.end());
				return *this;
			};
			void assign(size_type count, const T& value) {
				// Replaces the contents with count copies of value value
				if (count < 0)
					throw std::length_error("vector (assign)");
				this->clear();
				if (_capacity < count)
					this->reserve(count);
				for (size_type i = 0; i < count; i++)
					_alloc.construct(&_start[i], value);
				_size = count;
			};
			template<class InputIt>
			void assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type* = 0) {
				// Replaces the contents with copies of those in the range [first, last).
				// The behavior is undefined if either argument is an iterator into *this.
				size_type range = std::distance(first, last);
				if (range < 0)
					throw std::length_error("vector (assign)");
				this->clear();
				if (_capacity < range)
					this->reserve(range);
				// vector<bool> 의 경우에는 push_back을 반복하는 구조로 구현됨.
				for (size_type i = 0; i < range; i++, first++) {
					_alloc.construct(&_start[i], *first);
				}
				_size = range;
			};
			allocator_type get_allocator() const {
				// Returns the allocator associated with the container.
				return (_alloc);
			};
			// ANCHOR - Element access
			reference at(size_type pos) {
				// Returns a reference to the element at specified location pos
				// with bounds checking.
				if (pos >= _size)
					throw std::out_of_range("vector (at)");
				return _start[pos];
			};
			const_reference at(size_type pos) const {
				if (pos >= _size)
					throw std::out_of_range("vector (at)");
				return _start[pos];
			};
			reference operator[](size_type pos) {
				// Returns a reference to the element at specified location pos.
				// No bounds checking is performed.
				return _start[pos];
			};
			const_reference operator[](size_type pos) const {
				return _start[pos];
			};
			reference front() {
				// Returns a reference to the first element in the container.
				// Calling front on an empty container is undefined.
				return _start[0];
			};
			const_reference front() const {
				return _start[0];
			};
			reference back() {
				// Returns a reference to the last element in the container.
				// Calling back on an empty container causes undefined behavior.
				return _start[_size - 1];
			};
			const_reference back() const {
				return _start[_size - 1];
			};
			T* data() {
				// Returns pointer to the underlying array serving as element storage.
				// 첫 데이터의 주소값을 반환한다.
				return _start;
			};
			const T* data() const {
				return _start;
			};
			//ANCHOR - Iterators
			iterator begin() {
				// Returns an iterator to the first element of the vector.
				// If the vector is empty, the returned iterator will be equal to end().
				return iterator(_start);
			};
			const_iterator begin() const {
				return const_iterator(_start);
			};
			iterator end() {
				// Returns an iterator to the element following the last element of the vector.
				// attempting to access it results in undefined behavior.
				return iterator(_start + _size);
			};
			const_iterator end() const {
				return const_iterator(_start + _size);
			};
			reverse_iterator rbegin() {
				// Returns a reverse iterator to the first element of the reversed vector.
				// If the vector is empty, the returned iterator is equal to rend().
				return reverse_iterator(this->end());
			};
			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(this->end());
			};
			reverse_iterator rend() {
				// Returns a reverse iterator to the element following the last element of the reversed vector.
				// attempting to access it results in undefined behavior.
				return reverse_iterator(this->begin());
			};
			const_reverse_iterator rend() const {
				return const_reverse_iterator(this->begin());
			};
			//ANCHOR - Capacity
			bool empty() const {
				if (_size == 0)
					return true;
				return false;
			};
			size_type size() const {
				return _size;
			};
			size_type max_size() const {
				// Returns the maximum number of elements the container is able to hold due to system or library implementation limitations
				// TODO - 여전히 잘 모르겠따
				return std::min<size_type>(PTRDIFF_MAX, _alloc.max_size());
			};
			void reserve(size_type new_cap) {
				// Increase the capacity of the vector to a value that's greater or equal to new_cap.
				if (new_cap > _alloc.max_size())
					throw std::length_error("vector (reserve)");
				if (new_cap > 0 && new_cap > _capacity) {
					// 기존것 temp에 저장
					pointer temp = _start;
					// 새로운 _start
					_start = _alloc.allocate(new_cap);
					for (size_type i = 0; i < _size; i++) {
						_alloc.construct(&_start[i], temp[i]);
						_alloc.destroy(&temp[i]);
					}
					_alloc.deallocate(temp, _capacity);
					_capacity = new_cap;
				}
			};
			size_type capacity() const {
				// Returns the number of elements that the container has currently allocated space for.
				return _capacity;
			};
			//ANCHOR - Modifiers
			void clear() {
				// Erases all elements from the container. After this call, size() returns zero.
				for (size_type i = 0; i < _size; i++) {
					_alloc.destroy(&_start[i]);
				}
				_size = 0;
			};
			iterator insert(const_iterator pos, const T& value) {
				// inserts value before pos.
				return this->insert(pos, 1, value);
			};
			iterator insert(const_iterator pos, size_type count, const T& value) {
				// inserts count copies of the value before pos.
				difference_type pos_offset = pos - begin();
				size_type new_size = _size + count;
				if (_capacity < new_size)
					this->reserve(_new_capacity(new_size));
				for (size_type i = 0; i < count; i++)
					_alloc.construct(_start + _size + i, T());
				pointer new_pos = _start + pos_offset;
				std::copy_backward(new_pos, _start + _size, _start + new_size);
				for (size_type i = 0 ; i < count ; i++) {
					new_pos[i] = value;
				}
				_size = new_size;
				return iterator(new_pos);
				/* TODO
					- pos에 대한 iterator/pointer 결정 ✔️
					- 뒤에서부터 pos 전까지 복사 ✔️
						-> 값이 계속 변경되기 때문에 뒤에서부터 복사해야 함. => copy_backward
					- 복사한 앞에서부터 value 복사 ✔️
					- pos iterator 반환 ✔️
				*/
			};
			template< class InputIt >
			iterator insert(iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type* = 0) {
				// inserts elements from range [first, last) before pos.
				// This overload has the same effect as overload (3) if InputIt is an integral type.
				iterator old_start = iterator(_start);
				size_type new_size = _size + std::distance(first, last);
 				if (_capacity < new_size)
					this->reserve(_new_capacity(new_size));
				pointer ptr = _start + (pos - old_start);
				std::copy_backward(ptr, _start + _size, _start + new_size);
				std::copy(first, last, ptr);
				_size = new_size;
				return iterator(ptr);
				/* TODO
					- pos에 대한 iterator/pointer 결정 ✔️
					- 뒤에서부터 pos 전까지 복사 ✔️
						-> 값이 계속 변경되기 때문에 뒤에서부터 복사해야 함. => copy_backward
					- 복사한 앞에서부터 복사 (iterator 고려하기) ✔️
					- pos iterator 반환 ✔️
				*/
			};
			iterator erase(iterator pos) {
				// Removes the element at pos.
				pointer ptr = _start + (pos - _start);
				_alloc.destroy(ptr);
				std::copy(ptr + 1, _start + _size, ptr);
				_size--;
				return iterator(ptr);
				/* TODO
					- pos iterator 결정
					- pos destroy
					- pos 뒤의 것들 "한칸" 앞으로 construct, 기존 것 destroy
					- pos iterator 반환
				*/
			};
			iterator erase(iterator first, iterator last) {
				// Removes the elements in the range [first, last).
				iterator startIter = this->begin();
				iterator ptr = _start + (first - startIter);
				iterator lastIter = this->begin() + (last - startIter);
				for (iterator p = ptr; p != lastIter; p++) {
					_alloc.destroy(&(*p));
				}
				std::copy(lastIter, this->end(), ptr);
				_size -= last - first;
				return iterator(ptr);
				/* TODO
					- range, first, last iterator 결정
					- first 부터 range destroy
					- last 뒤의 것들 range 앞으로 construct, 기존 것 destroy
					- first iterator 반환
				*/
			};
			void push_back(const T& value) {
				// Appends the given element value to the end of the container.
				size_type new_size = _size + 1;
				if (_capacity < new_size)
					this->reserve(_new_capacity(new_size));
				_alloc.construct(&_start[_size], value);
				_size = new_size;
				/* TODO
					- 늘어나야 하는 capacity에 맞게 reserve
					- _size 위치에 construct
					- _size 증가
				*/
			};
			void pop_back() {
				// Removes the last element of the container.
				// Calling pop_back on an empty container results in undefined behavior.
				if (this->empty())
					return;
				_alloc.destroy(&_start[_size - 1]);
				_size--;
			};
			void resize(size_type count, T value = T()) {
				// Resizes the container to contain count elements.
				// If the current size is less than count, additional copies of value are appended.
				if (count < _size) {
					while (_size != count)
						this->pop_back();
				}
				else if (count > _size) {
					reserve(count);
					while (_size != count) {
						_alloc.construct(&_start[_size], value);
						_size++;
					}
				}
				/* TODO
					- count가 size보다 작은 경우 
						-> size가 동일해질때까지 pop (연속적인 호출보다 좋은 방법이 있을듯)
					- count가 size보다 큰 경우
						-> 늘어냐야 하는 capacity에 맞게 reserve
						-> _size가 동일해질 때까지 construct value
				*/
			};
			void swap(vector& other) {
				// Exchanges the contents of the container with those of other.
				// Does not invoke any move, copy, or swap operations on individual elements.
				// 멤버변수들만 바꿔주면 됨
				std::swap(_start, other._start);
				std::swap(_size, other._size);
				std::swap(_capacity, other._capacity);
				std::swap(_alloc, other._alloc);
			};

		// ANCHOR - private functions
		private:
			size_type _new_capacity(size_type size) {
				size_type new_capacity;
				if (_capacity == 0)
					new_capacity = 1;
				else
					new_capacity = _capacity;
				if (size > _capacity) {
					while (size > new_capacity)
						new_capacity *= 2;
					return new_capacity;
				}
				return new_capacity;
			}
	};
	//ANCHOR - Non-member functions
	template<class T, class Alloc>
	bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		if (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
			return true;
		return false;
	}
	template<class T, class Alloc>
	bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}
	template<class T, class Alloc>
	bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		if (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
			return true;
		return false;
	}
	template<class T, class Alloc>
	bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		if (lhs < rhs || lhs == rhs)
			return true;
		return false;
	}
	template<class T, class Alloc>
	bool operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		if (!(lhs <= rhs))
			return true;
		return false;
	}
	template<class T, class Alloc>
	bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		if (!(lhs < rhs))
			return true;
		return false;
	}
	template<class T, class Alloc>
	void swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs) {
		// Specializes the std::swap algorithm for ft::vector.
		// Swaps the contents of lhs and rhs. Calls lhs.swap(rhs).
		lhs.swap(rhs);
	}
}

#endif
