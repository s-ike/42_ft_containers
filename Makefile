NAME		:= a.out
SRCS		:= main.cpp
OBJDIR		:= ./objs/
OBJS		:= $(addprefix $(OBJDIR), $(SRCS:.cpp=.o))
DEPENDS		:= $(addprefix $(OBJDIR), $(SRCS:.cpp=.d))

CXX			:= clang++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 -pedantic -MMD -MP

RM			:= rm -f
C_GREEN		:= "\033[32m"
C_DEFAULT	:= "\033[39m"
C_RESET		:= "\033[m"

$(OBJDIR)%.o:	%.cpp
			@if [ ! -d $(OBJDIR) ]; then \
				echo "mkdir $(OBJDIR)"; mkdir $(OBJDIR); \
			fi
			$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY:		all
all:		$(NAME)

$(NAME):	$(OBJS)
			$(CXX) $(CXXFLAGS) $(OBJS) -o $@
			@echo $(C_GREEN)"=== Make Done ==="$(C_DEFAULT)$(C_REST)

.PHONY:		clean
clean:
			$(RM) $(OBJS)
			$(RM) $(DEPENDS)

.PHONY:		fclean
fclean:		clean
			$(RM) $(NAME)

.PHONY:		re
re:			fclean $(NAME)

-include	$(DEPENDS)

.PHONY:		test
test:
			$(MAKE) CXXFLAGS="$(CXXFLAGS) -D NO_LEAKS=1"
			./$(NAME) > test_fd.txt
			$(MAKE) -B CXXFLAGS="$(CXXFLAGS) -D NO_LEAKS=1 -D TEST=1"
			./$(NAME) > test_stl.txt
			diff test_fd.txt test_stl.txt
