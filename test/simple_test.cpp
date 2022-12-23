#include <vector>
#include <iostream>
int main(void) {
    try
    {
        std::vector<int> v1(1);
        std::vector<int> v2(10, 10);
        // auto first = v2.begin() + 2;
        // auto last = v2.begin();
        // std::vector<int> vector_error(-1); // throw std::length_error: vector
        // vector.assign(-1, 7);   // throw std::length_error: vector
        // vector.assign(first, last); // throw std::length_error: vector
        std::cout << v2.capacity() << std::endl;
        v2 = v1;
        std::cout << v2.capacity() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n'; 
    }
    

    return 0;
}