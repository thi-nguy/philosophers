NAME = philo_two
SRC = eat_sleep_repeat.c \
		errors.c \
		ft_atoi.c \
		ft_isdigit.c \
		ft_itoa.c \
		ft_putstr_fd.c \
		ft_strdup.c \
		ft_strlcat.c \
		ft_strlen.c \
		get_time.c \
		init.c \
		message.c \
		parse.c \
		philo_two.c

OBJ = $(SRC:.c=.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror

%.o : %.c
	gcc $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
