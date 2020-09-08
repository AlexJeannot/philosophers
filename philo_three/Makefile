NAME =	philo_three

SRCS =	main.c		\
		setup.c		\
		exec.c		\
		eat.c		\
		error.c		\
		display.c	\
		clean.c		\
		annexes.c	

OBJS =	$(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))
OBJS_DIR = objs/

INCL =	philo_three.h

CC =	gcc
FLAGS =	-Wall -Wextra -Werror

$(OBJS_DIR)%.o:	%.c
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

test:		re
			echo
			echo
			./$(NAME) 5 900 1000 1000



.PHONY :	all clean fclean re test
.SILENT: 