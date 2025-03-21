NAME = get_next_line.a

SRCS =  get_next_line.c \
		get_next_line_utils.c 
		
CC = gcc

FLAGS = -c -Wall -Wextra -Werror

INCLUDES = -I.

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

all : $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
