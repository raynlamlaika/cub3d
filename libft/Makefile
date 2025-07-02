
CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

AR =  ar rc

SRC = 	ft_putchar_fd.c ft_strmapi.c ft_atoi.c ft_putendl_fd.c ft_strncmp.c ft_bzero.c \
		ft_putnbr_fd.c ft_strnstr.c ft_calloc.c ft_putstr_fd.c ft_strrchr.c ft_isalnum.c \
		ft_split.c ft_strtrim.c ft_isalpha.c ft_strchr.c ft_substr.c ft_isascii.c \
		ft_strdup.c ft_tolower.c ft_isdigit.c ft_memchr.c ft_striteri.c ft_toupper.c \
		ft_isprint.c ft_memcmp.c ft_strjoin.c ft_itoa.c ft_memcpy.c ft_strlcat.c \
		ft_memmove.c ft_strlcpy.c ft_memset.c ft_strlen.c
OBJ = ${SRC:.c=.o}
HEADER = libft.h

BONUS_SRC =	ft_lstadd_back_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
			ft_lstsize_bonus.c ft_lstadd_front_bonus.c ft_lstdelone_bonus.c ft_lstlast_bonus.c \
			ft_lstnew_bonus.c

BONUS_OBJ=${BONUS_SRC:.c=.o}

all :${NAME}

${NAME} :${OBJ}

%.o:%.c ${HEADER}
	${CC} ${CFLAGS} -c $< -o $@
	${AR} ${NAME} $@

bonus:${BONUS_OBJ}

clean:
	rm -f ${OBJ} ${BONUS_OBJ}

fclean :clean   
	rm -f ${NAME}

re : fclean all
