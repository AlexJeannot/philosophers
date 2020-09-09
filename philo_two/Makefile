NAME =	philo_two

SRCS =	srcs/main.c		\
		srcs/setup.c	\
		srcs/exec.c		\
		srcs/eat.c		\
		srcs/error.c	\
		srcs/display.c	\
		srcs/clean.c	\
		annexes.c	

OBJS =	$(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))
OBJS_DIR = objs/

INCL =	includes/philo_two.h

CC =	gcc
FLAGS =	-Wall -Wextra -Werror

$(OBJS_DIR)%.o:	*/%.c
						if [ -d "objs" ]; then : ; else mkdir objs; fi
						$(CC) $(FLAGS) -c $< -o $@
						echo $(notdir $@) "\033[0;32mcreated\033[0m"

all :		$(NAME)

$(NAME) :	$(OBJS) $(INCL)
			echo "\033[0;35mLinking files\033[0m"
			$(CC) $(FLAGS) $(OBJS) -o $@
			echo $(NAME) "\033[0;32mdone\033[0m"

clean :
			rm -rf $(OBJS)
			echo object files "\033[0;31mdeleted\033[0m"
			rm -rf $(OBJS_DIR)
			echo object directory "\033[0;31mdeleted\033[0m"

fclean :	clean
			rm -rf $(NAME)

re :		fclean all

.PHONY :	all clean fclean re test
.SILENT: 