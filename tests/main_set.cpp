#include "./main.hpp"

template<typename set>
void print_set(set const &s) {
	std::cout << "==================\n";
	std::cout << "size : " << s.size() << std::endl;
	for(typename set::const_iterator iter = s.begin(); iter != s.end(); iter++)
		std::cout << *iter << std::endl;
	std::cout << "==================\n";
}

void test_set(void) {
	// ANCHOR - copy constructor
	{
		print_title("= copy constructor =");
		ft::set<std::string> ss;
		for(int i = 1; i <= 5; i++)
			ss.insert(std::string(i, 'a'));
		ft::set<std::string> ss2(ss);
		print_set(ss);
		print_set(ss2);
		print_msg("clear ss");
		ss.clear();
		print_set(ss);
		print_set(ss2);
	}
	// ANCHOR - const key
	{
		print_title("= const iterator =");
		ft::set<std::string> ss;
		for(int i = 1; i <= 5; i++)
			ss.insert(std::string(i, 'a'));
		ft::set<std::string>::iterator iter_0 = ss.begin();
		ft::set<std::string>::const_reverse_iterator iter_c0 = ss.rbegin();
		std::cout << "iter_0 : " << *iter_0 << std::endl;
		std::cout << "iter_c0 : " << *iter_c0 << std::endl;
		// compile error
		// *iter_0 = "b";
		// *iter_c0 = "b";
	}
}