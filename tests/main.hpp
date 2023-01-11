#ifndef MAIN_TEST_HPP
# define MAIN_TEST_HPP
#include <iostream>
#include <string>
#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	#include <set>
	namespace ft = std;
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
	#include "set.hpp"
#endif

# define RESET "\x1b[0m"
# define BLACK "\x1b[0;30m"
# define RED "\x1b[0;31m"
# define GREEN "\x1b[0;32m"
# define YELLOW "\x1b[0;33m"
# define BLUE "\x1b[0;34m"
# define PURPLE "\x1b[0;35m"
# define CYAN "\x1b[0;36m"

void print_title(std::string title);
void print_msg(std::string msg);

#endif