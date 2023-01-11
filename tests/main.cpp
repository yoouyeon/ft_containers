#include <iostream>

# define RESET "\x1b[0m"
# define BLACK "\x1b[0;30m"
# define RED "\x1b[0;31m"
# define GREEN "\x1b[0;32m"
# define YELLOW "\x1b[0;33m"
# define BLUE "\x1b[0;34m"
# define PURPLE "\x1b[0;35m"
# define CYAN "\x1b[0;36m"

void test_vector(void);
void test_stack(void);
void test_map(void);
void test_set(void);

void print_title(std::string title) {
	std::cout << std::endl << PURPLE << title << RESET << std::endl;
}

void print_msg(std::string msg) {
	std::cout << "\n* " << msg << " *" << std::endl;
}

int main(void) {
	std::cout << YELLOW << "\n================ [ VECTOR ] ================\n" << RESET << std::endl;
	test_vector();
	std::cout << YELLOW << "\n================== [ MAP ] =================\n" << RESET << std::endl;
	test_map();
	std::cout << YELLOW << "\n================= [ STACK ] ================\n" << RESET << std::endl;
	test_stack();
	std::cout << YELLOW << "\n================== [ SET ] =================\n" << RESET << std::endl;
	test_set();

	std::cout << "MAIN_TEST_FINISHED!!" << std::endl;
	// system("leaks test_main");
	return 0;
}