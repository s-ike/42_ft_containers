NAME		:= a.out
SRCS		:= main.cpp
OBJDIR		:= ./objs/
OBJS		:= $(addprefix $(OBJDIR), $(SRCS:.cpp=.o))
DEPENDS		:= $(addprefix $(OBJDIR), $(SRCS:.cpp=.d))

CXX			:= clang++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 -pedantic -MMD -MP
CXXFLAGS_2	:= -Wall -Wextra -Werror -std=c++98 -pedantic

RM			:= rm -f
C_GREEN		:= "\033[32m"
C_CYAN		:= "\033[36m"
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
			$(MAKE) -B CXXFLAGS="$(CXXFLAGS) -D NO_LEAKS=1"
			./$(NAME) > test_fd.txt 2> test_err_fd.txt
			$(MAKE) -B CXXFLAGS="$(CXXFLAGS) -D NO_LEAKS=1 -D TEST=1"
			./$(NAME) > test_stl.txt 2> test_err_stl.txt
			@echo $(C_CYAN)"=== diff ==="$(C_DEFAULT)$(C_REST)
			diff test_fd.txt test_stl.txt
			@echo $(C_CYAN)"=== ft error ==="$(C_DEFAULT)$(C_REST)
			@cat test_err_fd.txt
			@echo $(C_CYAN)"=== STL error ==="$(C_DEFAULT)$(C_REST)
			@cat test_err_stl.txt

.PHONY:		time
time:
			$(MAKE) -B CXXFLAGS="$(CXXFLAGS) -D NO_LEAKS=1 -D TIME=1"
			./$(NAME) > test_fd.txt 2> test_err_fd.txt
			$(MAKE) -B CXXFLAGS="$(CXXFLAGS) -D NO_LEAKS=1 -D TEST=1 -D TIME=1"
			./$(NAME) > test_stl.txt 2> test_err_stl.txt
			@echo $(C_CYAN)"=== diff ==="$(C_DEFAULT)$(C_REST)
			diff test_fd.txt test_stl.txt

.PHONY:		time2
time2:		main_time.cpp
			$(CXX) $(CXXFLAGS_2) $<
			./$(NAME)

.PHONY:		42
42:			main_42.cpp
			@echo $(C_GREEN)"=== ft ==="$(C_DEFAULT)$(C_REST)
			$(CXX) $(CXXFLAGS_2) $<
			./$(NAME) 1
			@echo $(C_GREEN)"=== STL ==="$(C_DEFAULT)$(C_REST)
			$(CXX) $(CXXFLAGS_2) -D TEST=1 $<
			./$(NAME) 1
