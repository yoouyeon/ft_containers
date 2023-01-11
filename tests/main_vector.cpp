#include "./main.hpp"

template<typename T>
void print_vector(ft::vector<T> const &vec) {
	std::cout << "==================\n";
	std::cout << "size : " << vec.size() << " | capacity : " << vec.capacity() << std::endl;
	for(typename ft::vector<T>::const_iterator iter = vec.begin(); iter != vec.end(); iter++)
		std::cout << *iter << std::endl;
	std::cout << "==================\n";
}

void test_vector(void) {
	//ANCHOR - iterator
	{
		print_title("= iterator =");
		int arr[] = {1, 5, 9, 7, 3};
		{
			print_msg("test const_iterator compare");
			ft::vector<int> const const_vec(arr, arr + sizeof(arr) / sizeof(int));
			print_vector(const_vec);
			ft::vector<int>::const_iterator iter_c0 = const_vec.begin();
			ft::vector<int>::const_iterator iter_c1 = const_vec.begin();
			std::cout << "iter_c0 : " << *iter_c0 << ", " << "iter_c1 : " << *iter_c1 << std::endl;
			std::cout << std::boolalpha << "iter_c0 == iter_c1 : " << (iter_c0 == iter_c1) << std::endl;
			std::cout << std::boolalpha << "iter_c0 != iter_c1 : " << (iter_c0 != iter_c1) << std::endl;
			iter_c1 += 2;
			std::cout << "iter_c0 : " << *iter_c0 << ", " << "iter_c1 : " << *iter_c1 << std::endl;
			std::cout << std::boolalpha << "iter_c0 == iter_c1 : " << (iter_c0 == iter_c1) << std::endl;
			std::cout << std::boolalpha << "iter_c0 != iter_c1 : " << (iter_c0 != iter_c1) << std::endl;
			std::cout << std::boolalpha << "iter_c0 > iter_c1 : " << (iter_c0 > iter_c1) << std::endl;
			std::cout << std::boolalpha << "iter_c0 >= iter_c1 : " << (iter_c0 >= iter_c1) << std::endl;
			std::cout << std::boolalpha << "iter_c0 < iter_c1 : " << (iter_c0 < iter_c1) << std::endl;
			std::cout << std::boolalpha << "iter_c0 <= iter_c1 : " << (iter_c0 <= iter_c1) << std::endl;
		}
		{
			print_msg("test iterator compare");
			ft::vector<int> vec(arr, arr + sizeof(arr) / sizeof(int));
			print_vector(vec);
			ft::vector<int>::const_iterator iter_c0 = vec.begin();
			ft::vector<int>::iterator iter_0 = vec.begin();
			std::cout << "iter_c0 : " << *iter_c0 << ", " << "iter_0 : " << *iter_0 << std::endl;
			std::cout << std::boolalpha << "iter_c0 == iter_0 : " << (iter_c0 == iter_0) << std::endl;
			std::cout << std::boolalpha << "iter_c0 != iter_0 : " << (iter_c0 != iter_0) << std::endl;
			iter_0 += 2;
			std::cout << "iter_c0 : " << *iter_c0 << ", " << "iter_c1 : " << *iter_0 << std::endl;
			std::cout << std::boolalpha << "iter_c0 == iter_0 : " << (iter_c0 == iter_0) << std::endl;
			std::cout << std::boolalpha << "iter_c0 != iter_0 : " << (iter_c0 != iter_0) << std::endl;
			std::cout << std::boolalpha << "iter_c0 > iter_0 : " << (iter_c0 > iter_0) << std::endl;
			std::cout << std::boolalpha << "iter_c0 >= iter_0 : " << (iter_c0 >= iter_0) << std::endl;
			std::cout << std::boolalpha << "iter_c0 < iter_0 : " << (iter_c0 < iter_0) << std::endl;
			std::cout << std::boolalpha << "iter_c0 <= iter_0 : " << (iter_c0 <= iter_0) << std::endl;
		}
	}
	//ANCHOR - swap
	{
		print_title("= swap =");
		ft::vector<std::string> vec1(5, "aaa");
		ft::vector<std::string> vec2(3, "bbb");
		ft::vector<std::string>::iterator iter_a = vec1.begin();
		ft::vector<std::string>::iterator iter_b = vec2.begin();
		print_vector(vec1);
		print_vector(vec2);
		std::cout << "iter_a : " << *iter_a << ", iter_b : " << *iter_b << std::endl;
		print_msg("swap");
		ft::swap(vec1, vec2);
		print_vector(vec1);
		print_vector(vec2);
		std::cout << "iter_a : " << *iter_a << ", iter_b : " << *iter_b << std::endl;
		std::cout << "++iter_a : " << *(++iter_a) << ", ++iter_b : " << *(++iter_b) << std::endl;
		print_msg("swap");
		vec1.swap(vec2);
		print_vector(vec1);
		print_vector(vec2);
	}
}