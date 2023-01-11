#include <deque>
#include <vector>
#include <list>
#include "./main.hpp"

template <typename stack>
void print_stack(stack &s) {
	std::cout << "==================\n";
	std::cout << "size : " << s.size() << std::endl;
	if (!s.empty())
		std::cout << "top : " << s.top() << std::endl;
	std::cout << std::boolalpha << "empty : " << s.empty() << std::endl;
	std::cout << "==================\n";
}

void test_stack(void){
	{
		print_title("= default stack =");
		ft::stack<std::string> s;
		s.push("happy");
		s.push("ft_container");
		print_stack(s);
		s.pop();
		print_stack(s);
		s.pop();
		print_stack(s);
	}
	{
		print_title("= deque stack =");
		ft::stack<std::string, std::deque<std::string> > s;
		s.push("happy");
		s.push("ft_container");
		print_stack(s);
		s.pop();
		print_stack(s);
		s.pop();
		print_stack(s);
	}
	{
		print_title("= vector stack =");
		ft::stack<std::string, std::vector<std::string> > s;
		s.push("happy");
		s.push("ft_container");
		print_stack(s);
		s.pop();
		print_stack(s);
		s.pop();
		print_stack(s);
	}
	{
		print_title("= list stack =");
		ft::stack<std::string, std::list<std::string> > s;
		s.push("happy");
		s.push("ft_container");
		print_stack(s);
		s.pop();
		print_stack(s);
		s.pop();
		print_stack(s);
	}
};