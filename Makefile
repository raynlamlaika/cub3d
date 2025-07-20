CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = check_args.c config_parser.c ft_split.c get_next_line.c \
       init.c main.c map_parser.c parse_map.c parser.c utils_2.c utils.c

OBJS = $(SRCS:.c=.o)

NAME = cub3d

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
