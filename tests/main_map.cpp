#include "./main.hpp"

template<typename Key, typename Value>
void print_map(ft::map<Key, Value> const &mmap) {
	std::cout << "==================\n";
	std::cout << "size : " << mmap.size() << std::endl;
	for(typename ft::map<Key, Value>::const_iterator iter = mmap.begin(); iter != mmap.end(); iter++)
		std::cout << "key : " << (*iter).first << ", value : " << (*iter).second << std::endl;
	std::cout << "==================\n";
}

void test_map(void) {
	// ANCHOR - copy constructor
	{
		print_title("= copy constructor =");
		ft::map<int, std::string> mm;
		for(int i = 1; i <= 5; i++) {
			mm.insert(ft::make_pair(i, std::string(i, 'a')));
		}
		ft::map<int, std::string> mm2(mm);
		print_map(mm);
		print_map(mm2);
		print_msg("clear mm");
		mm.clear();
		print_map(mm);
		print_map(mm2);
	}
	// ANCHOR - insert
	{
		print_title("= insert =");
		print_msg("basic insert");
		ft::map<char, int> mm;
		print_map(mm);
		mm.insert(ft::make_pair('a', 0));
		mm.insert(ft::make_pair('c', 2));
		ft::map<char, int>::iterator iter = mm.begin();
		print_map(mm);
		std::cout << "iter : (" << iter->first  << ", " << iter->second << ")" << std::endl;
		mm['b'] = 1;
		mm['d'] = 3;
		print_map(mm);
		std::cout << "iter : (" << iter->first  << ", " << iter->second << ")" << std::endl;
		++iter;
		std::cout << "++iter : (" << iter->first  << ", " << iter->second << ")" << std::endl;
		print_msg("duplicated key");
		ft::pair<ft::map<char, int>::iterator, bool> ret = mm.insert(ft::make_pair('a', 10));
		std::cout << "ret : (" << ret.first->first << ", " << ret.first->second << ") , " << std::boolalpha << ret.second << std::endl; 
	}
	// ANCHOR - erase
	{
		print_title("= erase =");
		ft::map<int, std::string> mm;
		for(int i = 1; i <= 5; i++) {
			mm.insert(ft::make_pair(i, std::string(i, 'a')));
		}
		print_map(mm);
		ft::map<int, std::string>::iterator iter = mm.begin();
		std::cout << "iter : (" << iter->first  << ", " << iter->second << ")" << std::endl;
		mm.erase(2);
		print_map(mm);
		std::cout << "iter : (" << iter->first  << ", " << iter->second << ")" << std::endl;
		++iter;
		std::cout << "++iter : (" << iter->first  << ", " << iter->second << ")" << std::endl;
	}
	// ANCHOR - swap
	{
		print_title("= swap =");
		ft::map<int, std::string> mm;
		for(int i = 1; i <= 5; i++) {
			mm.insert(ft::make_pair(i, std::string(i, 'a')));
		}
		ft::map<int, std::string> mm2;
		for(int i = 1; i <= 5; i++) {
			mm2.insert(ft::make_pair(i, std::string(i, 'b')));
		}
		print_map(mm);
		print_map(mm2);
		print_msg("swap");
		mm.swap(mm2);
		print_map(mm);
		print_map(mm2);
		print_msg("swap");
		ft::swap(mm, mm2);
		print_map(mm);
		print_map(mm2);
	}
}
