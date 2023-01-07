#include <vector>
#include <list>
#include <iostream>
#include "../includes/vector.hpp"

void print_vector(ft::vector<int> &v) {
    std::cout << "---------\n";
    for(unsigned long i = 0; i < v.size(); i++) {
        std::cout << " - " << v[i] << "\n";
    }
    std::cout << "---------\n";
}

void test_test() {
    try
    {
        std::list<int> lst;
        ft::vector<int> v1(5, 100);
        //std::vector<int> v2(10, 100);
        // auto first = v2.begin() + 2;
        // auto last = v2.begin();
        // std::vector<int> vector_error(-1); // throw std::length_error: vector
        // vector.assign(-1, 7);   // throw std::length_error: vector
        // vector.assign(first, last); // throw std::length_error: vector

        for(int i = 1; i <= 5; i++) {
            lst.push_back(i * 3);
        }
        std::list<int> lst2;
        for(int i = 1; i <= 5; i++) {
            lst2.push_back(i * 2);
        }
        v1.assign(lst.begin(), lst.end());
        print_vector(v1);
        // std::cout << *(v1.end() - 1) << "\n";
        v1.insert(v1.end(), lst.begin(), lst.end());
        print_vector(v1);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n'; 
    }
}

void pop_back_empty() {
    std::cout << "------- pop_back_empty -------\n";
    std::vector<int> ft;
    ft.pop_back();
    std::cout << ft.size() << "\n";
}

int main(void) {
    // test_test();
    pop_back_empty();
    system("leaks container");

    return 0;
}