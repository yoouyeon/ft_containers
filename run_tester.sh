#!/bin/bash

# COLORS
BRED	=	"\033[31m"
BGREEN	=	"\033[32m"
BCYAN	=	"\e[96m"
BPURPLE	=	"\033[35m"
RESET	=	"\033[0m"

cd testers
echo -e "${BCYAN} ====== First tester ====== $(RESET)"
read input
cd containers_test
./do.sh
sleep 5
echo -e "$(BCYAN) ====== Second tester ===== $(RESET)"
read input
cd ../tester_ft_containers
./grademe.sh
sleep 10
echo -e "$(BCYAN) ====== Bench tester ====== $(RESET)"
read input
make bench
./bench_test
sleep 10
make fclean
cd ../
echo -e "$(BRED) ====== develop tester ====== $(RESET)"
cd FT_CONTAINERS_42_tester
cp ../../includes/*.hpp ./includes/your_headers_files
echo -e "$(BPURPLE)VECTOR TEST START$(RESET)"
read input
make vector
sleep 10
echo -e "$(BPURPLE)STACK TEST START$(RESET)"
read input
make stack
sleep 10
echo -e "$(BPURPLE)MAP TEST START$(RESET)"
read input
make stack
sleep 10
echo -e "$(BPURPLE)SET TEST START$(RESET)"
read input
make stack
sleep 10
make fclean
rm -rf *.hpp 
cd ../
echo -e $(BRED) ==== develop tester ends === $(RESET)