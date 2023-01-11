#include <iostream>
#include <ctime>
#include <fstream>

# define RESET "\x1b[0m"
# define BLACK "\x1b[0;30m"
# define RED "\x1b[0;31m"
# define GREEN "\x1b[0;32m"
# define YELLOW "\x1b[0;33m"
# define BLUE "\x1b[0;34m"
# define PURPLE "\x1b[0;35m"
# define CYAN "\x1b[0;36m"

void insert_test_vector(void);
void delete_test_vector(void);
void search_test_vector(void);
void insert_test_stack(void);
void delete_test_stack(void);
void insert_test_map(void);
void delete_test_map(void);
void search_test_map(void);
void insert_test_set(void);
void delete_test_set(void);
void search_test_set(void);

void insert_test_vector_std(void);
void delete_test_vector_std(void);
void search_test_vector_std(void);
void insert_test_stack_std(void);
void delete_test_stack_std(void);
void insert_test_map_std(void);
void delete_test_map_std(void);
void search_test_map_std(void);
void insert_test_set_std(void);
void delete_test_set_std(void);
void search_test_set_std(void);

float time_to_msec(clock_t time) {
	return time / (float)CLOCKS_PER_SEC * 1000;
}

void show_time(clock_t std_time, clock_t ft_time) {
	std::cout << "⏱ std_time : " << time_to_msec(std_time) << "\t⏱ ft_time : " << time_to_msec(ft_time);
	if (std_time * 20 < ft_time) {
		std::cout << RED << "\t❌ x" << ft_time / (float)std_time << RESET << std::endl;
	}
	else {
		std::cout << GREEN << "\t✅ x" << ft_time / (float)std_time << RESET << std::endl;
	}
}

void bench_test_box(void ft_test(void), void std_test(void)) {
	clock_t ft_time, std_time;

	std_time = clock();
	std_test();
	std_time = clock() - std_time;
	ft_time = clock();
	ft_test();
	ft_time = clock() - ft_time;
	show_time(std_time, ft_time);
}

int main(void) {
	std::cout << std::endl << CYAN << "-------------------- insert_test_vector --------------------" << RESET << std::endl;
	bench_test_box(insert_test_vector, insert_test_vector_std);

	std::cout << std::endl << CYAN << "-------------------- delete_test_vector --------------------" << RESET << std::endl;
	bench_test_box(delete_test_vector, delete_test_vector_std);

	std::cout << std::endl << CYAN << "-------------------- search_test_vector --------------------" << RESET << std::endl;
	bench_test_box(search_test_vector, search_test_vector_std);

	std::cout << std::endl << CYAN << "--------------------- insert_test_stack --------------------" << RESET << std::endl;
	bench_test_box(insert_test_stack, insert_test_stack_std);

	std::cout << std::endl << CYAN << "-------------------- delete_test_stack ---------------------" << RESET << std::endl;
	bench_test_box(delete_test_stack, delete_test_stack_std);

	std::cout << std::endl << CYAN << "--------------------- insert_test_map ----------------------" << RESET << std::endl;
	bench_test_box(insert_test_map, insert_test_map_std);

	std::cout << std::endl << CYAN << "--------------------- delete_test_map ----------------------" << RESET << std::endl;
	bench_test_box(delete_test_map, delete_test_map_std);

	std::cout << std::endl << CYAN << "--------------------- search_test_map ----------------------" << RESET << std::endl;
	bench_test_box(search_test_map, search_test_map_std);

	std::cout << std::endl << CYAN << "--------------------- insert_test_set ----------------------" << RESET << std::endl;
	bench_test_box(insert_test_set, insert_test_set_std);

	std::cout << std::endl << CYAN << "--------------------- delete_test_set ----------------------" << RESET << std::endl;
	bench_test_box(delete_test_set, delete_test_set_std);

	std::cout << std::endl << CYAN << "--------------------- search_test_set ----------------------" << RESET << std::endl;
	bench_test_box(search_test_set, search_test_set_std);

	std::cout << std::endl << PURPLE << "BENCH_TEST_FINISHED!!" << RESET << std::endl;

	system("leaks test_bench");
	return 0;
}