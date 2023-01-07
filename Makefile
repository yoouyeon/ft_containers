# ======= Name =======
NAME	=	ft_container
TEST	=	test_main
BENCH	=	test_bench
INTRA	=	test_intra

# ======= Compile =======
CXX	=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -g -std=c++98
CXXFLAGS	+=	-I$(INCS_DIR)

# ======= Files =======
INCS_DIR	=	./includes/
INCS	=	$(addprefix $(INCS_DIR), $(INCS_LIST))
SRCS_TEST	=	./tests/main.cpp
SRCS_BENCH	=	./tests/bench_main.cpp
SRCS_INTRA	=	./tests/intra_main.cpp
OBJS_TEST	=	$(patsubst %.cpp, %.o, $(SRCS_TEST))
OBJS_BENCH	=	$(patsubst %.cpp, %.o, $(SRCS_BENCH))
OBJS_INTRA	=	$(patsubst %.cpp, %.o, $(SRCS_INTRA))
OBJS	=	$(OBJS_TEST) $(OBJS_BENCH) $(OBJS_INTRA)

# ======= Rules =======
all	:	$(NAME)

$(NAME) : $(TEST) $(BENCH) $(INTRA)

%.o	:	%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST)	:	$(OBJS_TEST)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_TEST)
	@printf "🤩 $(BGREEN)$@ was created.$(RESET)\n"

$(BENCH)	:	$(OBJS_BENCH)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_BENCH)
	@printf "🤩 $(BGREEN)$@ was created.$(RESET)\n"

$(INTRA)	:	$(OBJS_INTRA)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_INTRA)
	@printf "🤩 $(BGREEN)$@ was created.$(RESET)\n"

clean	:
	@rm -rf $(OBJS)
	@printf "🗑 $(NAME)'s object files were removed.\n"

fclean	:	clean
	@rm -rf $(TEST)
	@printf "🗑 $(TEST) was removed.\n"
	@rm -rf $(BENCH)
	@printf "🗑 $(BENCH) was removed.\n"
	@rm -rf $(INTRA)
	@printf "🗑 $(INTRA) was removed.\n"

re	:	
	@make fclean
	@make all

.PHONY : all clean fclean re

# ======= Color =======

BGREEN	=	\033[1;32m
BCYAN	=	\033[1;96m
BPURPLE	=	\033[1;35m
RESET	=	\033[0m