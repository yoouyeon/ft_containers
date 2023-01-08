# define MAX_SIZE 20
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
	m.print_nodes_map();
	for(int i = 1; i * 4 < MAX_SIZE; i++) {
		std::cout << "- erase " << i * 4 <<std::endl;
		m.erase(i * 4);
		m.print_nodes_map();
	}
	std::cout << std::endl;
	m.print_nodes_map();
	m.erase(m.begin());
	std::cout << std::endl;
	m.print_nodes_map();
	m.erase(--m.end());
	std::cout << std::endl;
	m.print_nodes_map();
	m.erase(++(++m.begin()));
	m.erase(--(--m.end()));
	std::cout << std::endl;
	m.print_nodes_map();
	std::cout << (++(++m.begin()))->first << " : " << (++(++m.begin()))->second << std::endl;
	std::cout << (--(--m.end()))->first << " : " << (--(--m.end()))->second << std::endl;
	m.erase(++(++m.begin()), --(--m.end()));
	std::cout << std::endl;
	m.print_nodes_map();
	std::cout << "😇\n";
	std::cout << YELLOW << "✨ delete_test_map DONE" << RESET << std::endl;
}

void search_test_mapvoid() {

}

void insert_test_set(void) {

}

void delete_test_set(void) {

}

void search_test_set(void) {

}