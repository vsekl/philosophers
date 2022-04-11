SRCS	=	srcs/time.c\
			srcs/init.c\
			srcs/main.c\
			srcs/states.c\
			srcs/utils.c

NAME	= philo

OBJS	= $(SRCS:.c=.o)

OBJS_D  = $(SRCS:.c=.d)

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

RM	=	rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS)   -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS)  -c $< -o $@ -MD

include $(wildcard $(OBJS_D))

clean:
	$(RM) $(OBJS) $(OBJS_D)

fclean:	clean
	$(RM) $(NAME)

re: 	fclean all
	
.PHONY: all clean fclean re bonus