CC	= gcc

RM	= rm -f

SRCDIR	= ./src

CFLAGS	+= -W -Wall -Wextra -g3

CFLAGS	+= -I./includes

NAME	= trie

SRCS	= $(SRCDIR)/main.c \


OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all


.PHONY: all clean fclean re
