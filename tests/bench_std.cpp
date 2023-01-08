# define MAX_SIZE 20

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <set>

# define RESET "\x1b[0m"
# define BLUE "\x1b[0;34m"

void insert_test_vector_std(void) {
	std::vector<int> v;
	for(int i = 0; i < MAX_SIZE; i++) {
		v.push_back(i);
	}
	std::cout << BLUE << "🐋 insert_test_vector_std DONE" << RESET << std::endl;
}

void delete_test_vector_std(void) {
	std::vector<int> v;
	for(int i = 0; i < MAX_SIZE; i++) {
		v.push_back(i);
	}
	v.erase(v.begin() + MAX_SIZE / 2);
	v.erase(v.begin() + (MAX_SIZE / 3), v.end() - (MAX_SIZE / 3));
	while (!v.empty())
		v.pop_back();
	std::cout << BLUE << "🐋 delete_test_vector_std DONE" << RESET << std::endl;
}

void search_test_vector_std(void) {
	std::vector<int> v;
	for(int i = 0; i < MAX_SIZE; i++) {
		v.push_back(i);
	}
	for(int i = 0; i * 3 < (int)v.size(); i++) {
		v.at(i * 3);
	}
	for(int i = 0; i * 4 < (int)v.size(); i++) {
		v[i * 4];
	}
	std::cout << BLUE << "🐋 search_test_vector_std DONE" << RESET << std::endl;
}

void insert_test_stack_std(void) {
	std::stack<int> s;
	for(int i = 0; i < MAX_SIZE; i++) {
		s.push(i);
	}
	std::cout << BLUE << "🐋 insert_test_stack_std DONE" << RESET << std::endl;
}

void delete_test_stack_std(void) {
	std::stack<int> s;
	for(int i = 0; i < MAX_SIZE; i++) {
		s.push(i);
	}
	while (!s.empty()) {
		s.pop();
	}
	std::cout << BLUE << "🐋 delete_test_stack_std DONE" << RESET << std::endl;
}

void insert_test_map_std(void) {
	std::map<int, int>m;
	for(int i = 0; i < MAX_SIZE; i++) {
		m.insert(std::make_pair(i, i * 2));
	}
	for(int i = -1; i < (-1) * MAX_SIZE; i--) {
		m[i] = i * 2;
	}
	std::cout << BLUE << "🐋 insert_test_map_std DONE" << RESET << std::endl;
}

void delete_test_map_std(void) {
	std::map<int, int>m;
	for(int i = 0; i < MAX_SIZE; i++) {
		m.insert(std::make_pair(i, i * 2));
	}
	for(int i = 1; i * 4 < MAX_SIZE; i++) {
		m.erase(i * 4);
	}
	m.erase(m.begin());
	m.erase(--m.end());
	m.erase(++(++m.begin()));
	m.erase(--(--m.end()));
	m.erase(++(++m.begin()), --(--m.end()));
	std::cout << BLUE << "🐋 delete_test_map_std DONE" << RESET << std::endl;
}

void search_test_map_std(void) {
	std::map<int, int>m;
	for(int i = 0; i < MAX_SIZE; i++) {
		m.insert(std::make_pair(i, i * 2));
	}
	for(int i = 1; i * 2 < MAX_SIZE; i++) {
		m.find(i * 2);
	}
	m.equal_range(3);
	m.lower_bound(3);
	m.upper_bound(3);
	std::cout << BLUE << "🐋 search_test_map_std DONE" << RESET << std::endl;
}

void insert_test_set_std(void) {
	std::set<int>s;
	for(int i = 0; i * 2 < MAX_SIZE; i++) {
		s.insert(i);
		s.insert(-i);
	}
	std::cout << BLUE << "🐋 insert_test_set_std DONE" << RESET << std::endl;
}

void delete_test_set_std(void) {
	std::set<int>s;
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
	std::cout << BLUE << "🐋 delete_test_set_std DONE" << RESET << std::endl;
}

void search_test_set_std(void) {
	std::set<int>s;
	for(int i = 0; i < MAX_SIZE; i++) {
		s.insert(i);
	}
	for(int i = 1; i * 2 < MAX_SIZE; i++) {
		s.find(i * 2);
	}
	s.equal_range(3);
	s.lower_bound(3);
	s.upper_bound(3);
	std::cout << BLUE << "🐋 search_test_set_std DONE" << RESET << std::endl;
}