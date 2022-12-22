#include <vector>
#include <iostream>
int main(void) {
    try
    {
        std::vector<int> vector(1);
        std::vector<int> arr(10, 10);
        auto first = arr.begin() + 2;
        auto last = arr.begin();
        // std::vector<int> vector_error(-1); // throw std::length_error: vector
        // vector.assign(-1, 7);   // throw std::length_error: vector
        vector.assign(first, last); // throw std::length_error: vector
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n'; 
    }
    

    return 0;
}