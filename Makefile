NAME	=	container
CXX	=	c++
SRCS	=	test/vector_test.cpp
OBJS	=	$(SRCS:.cpp=.o)

ifdef CPP11
	CXXFLAGS	=	-Wall -Wextra -Werror -std=c++11
else
	CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98
endif

# ======= Rules =======

all	:	$(NAME)

$(NAME)	: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)
	@printf "🤩 $(BGREEN)$(NAME) was created.$(RESET)\n"

11		:
				@make CPP11=1 all


%.o	:	%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean	:
	@rm -rf $(OBJS)
	@printf "🗑 $(NAME)'s object files were removed.\n"

fclean	:	clean
	@rm -rf $(NAME)
	@printf "🗑 $(NAME) was removed.\n"

re	:	
	@make fclean
	@make all

.PHONY : all clean fclean re 11

# ======= Color =======

BGREEN	=	\033[1;32m
BCYAN	=	\033[1;96m
BPURPLE	=	\033[1;35m
RESET	=	\033[0m