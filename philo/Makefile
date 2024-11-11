NAME=philo
CC=gcc
CFLAGS= -Wall -Wextra -Werror -g
RM= rm -rf
SRCS= philo.c\
	  utils.c\
	  arg_control.c\
	  init.c\
	  thread.c\
	  destroy.c\
	  check_thread.c\

OBJS=$(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean : 
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re