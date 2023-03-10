# define MAX_SIZE 100000
#include <iostream>
#include "map.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include "set.hpp"

# define RESET "\x1b[0m"
# define YELLOW "\x1b[0;33m"

void insert_test_vector(void) {
	ft::vector<int> v;
	for(int i = 0; i < MAX_SIZE; i++) {
		v.push_back(i);
	}
	// for(int i = 0; i < MAX_SIZE; i++) {
	// 	for(int k = 0; k < MAX_SIZE; k++) {

	// 	}
	// }
	std::cout << YELLOW << "✨ insert_test_vector DONE" << RESET << std::endl;
}

void delete_test_vector(void) {
	ft::vector<int> v;
	for(int i = 0; i < MAX_SIZE; i++) {
		v.push_back(i);
	}
	v.erase(v.begin() + MAX_SIZE / 2);
	v.erase(v.begin() + (MAX_SIZE / 3), v.end() - (MAX_SIZE / 3));
	while (!v.empty())
		v.pop_back();
	std::cout << YELLOW << "✨ delete_test_vector DONE" << RESET << std::endl;
}

void search_test_vector(void) {
	ft::vector<int> v;
	for(int i = 0; i < MAX_SIZE; i++) {
		v.push_back(i);
	}
	for(int i = 0; i * 3 < (int)v.size(); i++) {
		v.at(i * 3);
	}
	for(int i = 0; i * 4 < (int)v.size(); i++) {
		v[i * 4];
	}
	std::cout << YELLOW << "✨ search_test_vector DONE" << RESET << std::endl;
}

void insert_test_stack(void) {
	ft::stack<int> s;
	for(int i = 0; i < MAX_SIZE; i++) {
		s.push(i);
	}
	std::cout << YELLOW << "✨ insert_test_stack DONE" << RESET << std::endl;
}

void delete_test_stack(void) {
	ft::stack<int> s;
	for(int i = 0; i < MAX_SIZE; i++) {
		s.push(i);
	}
	while (!s.empty()) {
		s.pop();
	}
	std::cout << YELLOW << "✨ delete_test_stack DONE" << RESET << std::endl;
}

void insert_test_map(void) {
	ft::map<int, int>m;
	for(int i = 0; i < MAX_SIZE; i++) {
		m.insert(ft::make_pair(i, i * 2));
	}
	for(int i = -1; i < (-1) * MAX_SIZE; i--) {
		m[i] = i * 2;
	}
	std::cout << YELLOW << "✨ insert_test_map DONE" << RESET << std::endl;
}

void delete_test_map(void) {
	ft::map<int, int>m;
	for(int i = 0; i < MAX_SIZE; i++) {
		m.insert(ft::make_pair(i, i * 2));
	}
	for(int i = 1; i * 4 < MAX_SIZE; i++)
		m.erase(i * 4);
	m.erase(m.begin());
	m.erase(--m.end());
	m.erase(++(++m.begin()));
	m.erase(--(--m.end()));
	m.erase(++(++m.begin()), --(--m.end()));
	std::cout << YELLOW << "✨ delete_test_map DONE" << RESET << std::endl;
}

void search_test_map(void) {
	ft::map<int, int>m;
	for(int i = 0; i < MAX_SIZE; i++) {
		m.insert(ft::make_pair(i, i * 2));
	}
	for(int i = 1; i * 2 < MAX_SIZE; i++) {
		m.find(i * 2);
	}
	m.equal_range(3);
	m.lower_bound(3);
	m.upper_bound(3);
	std::cout << YELLOW << "✨ search_test_map DONE" << RESET << std::endl;
}

void insert_test_set(void) {
	ft::set<int>s;
	for(int i = 0; i * 2 < MAX_SIZE; i++) {
		s.insert(i);
		s.insert(-i);
	}
	std::cout << YELLOW << "✨ insert_test_set DONE" << RESET << std::endl;
}

void delete_test_set(void) {
	ft::set<int>s;
	for(int i = 0; i < MAX_SIZE; i++) {
		s.insert(i);
	}
	for(int i = 1; i * 4 < MAX_SIZE; i++) {
		s.erase(i * 4);
	}
	s.erase(s.begin());
	s.erase(--s.end());
	s.erase(++(++s.begin()));
	s.erase(--(--s.end()));
	s.erase(++(++s.begin()), --(--s.end()));
	std::cout << YELLOW << "✨ delete_test_set DONE" << RESET << std::endl;
}

void search_test_set(void) {
	ft::set<int>s;
	for(int i = 0; i < MAX_SIZE; i++) {
		s.insert(i);
	}
	for(int i = 1; i * 2 < MAX_SIZE; i++) {
		s.find(i * 2);
	}
	s.equal_range(3);
	s.lower_bound(3);
	s.upper_bound(3);
	std::cout << YELLOW << "✨ search_test_set DONE" << RESET << std::endl;
}