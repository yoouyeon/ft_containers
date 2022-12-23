#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>		// allocator
#include <exception>	// exception
#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"
#include "algorithm.hpp"

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
			typedef typename vector_iterator<value_type>			iterator;
			// typedef const_pointer								const_iterator;	// 이게 맞나
			typedef typename vector_iterator<const value_type>		const_iterator;
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
				: _begin(NULL), \
				_size(0), \
				_capacity(0), \
				_alloc(Allocator()) {
				// (1) Default constructor. Constructs an empty container with a default-constructed allocator.
			};
			explicit vector(const Allocator& alloc) \
				: _begin(NULL), \
				_size(0), \
				_capacity(0), \
				_alloc(Allocator(alloc)) {
				// (2) Constructs an empty container with the given allocator alloc.
			};
			explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) \
				: _size(count), \
				_alloc(Allocator(alloc)) {
				// (3) Constructs the container with count copies of elements with value value.
				if (_size < 0)
					throw std::length_error("vector (constructor)");
				// _capacity = /* ? */;
				_start = _alloc.allocate(_capacity);
				for (size_type i = 0; i < count; i++)
					_alloc.construct(&_start[i], value);
				/* TODO
					- capacity 결정
					- 할당 ✔️
					- 값 넣어주기 ✔️
					- _begin 결정 ✔️
				*/
			};
			template<class InputIt>
			explicit vector(InputIt first, InputIt last, const Allocator& alloc = Allocator()) \
				: _alloc(Allocator(alloc)) {
				// (5) Constructs the container with the contents of the range [first, last).
				_size = std::distance(last, first);
				if (_size < 0)
					throw std::length_error("vector (constructor)");
				// _capacity = /* ? */;
				_start = _alloc.allocate(_capacity);
				this->assign(first, last);
				/* TODO
					- capacity 결정
					- 할당 ✔️
					- 값 넣어주기 ✔️
					- size ✔️
					- _begin 결정 ✔️
				*/
			};
			explicit vector(const vector& other) \
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
					- _begin 결정 ✔️
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
				// push_back을 반복하는 방식으로 구현되어있음.
			};
			template<class InputIt>
			void assign(InputIt first, InputIt last) {
				// Replaces the contents with copies of those in the range [first, last).
				// The behavior is undefined if either argument is an iterator into *this.
				size_type range = std::distance(first, last);
				if (range < 0)
					throw std::length_error("vector (assign)");
			};
			allocator_type get_allocator() const {
				// Returns the allocator associated with the container.
				return (_alloc);
			};
			// ANCHOR - Element access
			reference at(size_type pos) {
				// Returns a reference to the element at specified location pos
				// with bounds checking.
			};
			const_reference at(size_type pos) const {
				if (pos >= _size)
					throw std::length_error("vector (at)");
			};
			reference operator[](size_type pos) {
				// Returns a reference to the element at specified location pos.
				// No bounds checking is performed.
				if (pos >= _size)
					throw std::length_error("vector (at)");
			};
			const_reference operator[](size_type pos) const {

			};
			reference front() {
				// Returns a reference to the first element in the container.
				// Calling front on an empty container is undefined.

			};
			const_reference front() const {

			};
			reference back() {
				// Returns a reference to the last element in the container.
				// Calling back on an empty container causes undefined behavior.
			};
			const_reference back() const {

			};
			T* data() {
				// Returns pointer to the underlying array serving as element storage.
			};
			const T* data() const {

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
				return _alloc.max_size();
			};
			void reserve(size_type new_cap) {
				// Increase the capacity of the vector to a value that's greater or equal to new_cap.
				if (new_cap > _alloc.max_size())
					throw std::length_error("vector (reserve)");
			};
			size_type capacity() const {
				// Returns the number of elements that the container has currently allocated space for.
				return _capacity;
			};
			//ANCHOR - Modifiers
			void clear() {
				// Erases all elements from the container. After this call, size() returns zero.

			};
			iterator insert(const_iterator pos, const T& value) {
				// inserts value before pos.
			};
			iterator insert(const_iterator pos, size_type count, const T& value) {
				// inserts count copies of the value before pos.
			};
			template< class InputIt >
			iterator insert(const_iterator pos, InputIt first, InputIt last) {
				// inserts elements from range [first, last) before pos.
				// This overload has the same effect as overload (3) if InputIt is an integral type.
			};
			iterator erase(iterator pos) {
				// Removes the element at pos.
			};
			iterator erase(iterator first, iterator last) {
				// Removes the elements in the range [first, last).
			};
			void push_back(const T& value) {
				// Appends the given element value to the end of the container.
			};
			void pop_back() {
				// Removes the last element of the container.
				// Calling pop_back on an empty container results in undefined behavior.
			};
			void resize(size_type count, T value = T()) {
				// Resizes the container to contain count elements.
				// If the current size is less than count, additional copies of value are appended.

			};
			void swap(vector& other) {
				// Exchanges the contents of the container with those of other.
				// Does not invoke any move, copy, or swap operations on individual elements.
			};

			// SECTION - Private
			void _destruct_at_end(pointer to) {
				// 끝부터 to까지의 메모리 해제
			}
	};
	//ANCHOR - Non-member functions
	template<class T, class Alloc>
	bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		if (ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
			return true;
		return false;
	};
	template<class T, class Alloc>
	bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		if (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
			return true;
		return false;
	};
	template<class T, class Alloc>
	bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		if (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
			return true;
		return false;
	};
	template<class T, class Alloc>
	bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		if (lhs < rhs || lhs == rhs)
			return true;
		return false;
	};
	template<class T, class Alloc>
	bool operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		if (!(lhs <= rhs))
			return true;
		return false;
	};
	template<class T, class Alloc>
	bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		if (!(lhs < rhs))
			return true;
		return false;
	};
	template<class T, class Alloc>
	void swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs) {
		// Specializes the std::swap algorithm for ft::vector.
		// Swaps the contents of lhs and rhs. Calls lhs.swap(rhs).
	};
}

#endif