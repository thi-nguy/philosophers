FLAGS = -Wall -Wextra -Werror -fsanitize=address -lpthread

CC = gcc -g

RM = rm -f

NAME = philo

SRC = 	main.c utils.c routine.c execute_threads.c check_arguments.c eat_sleep.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	-@echo "Compiling..."
	$(CC) -o $(NAME) $(OBJ) $(FLAGS)

clean:
	-@echo "Removing object files..."
	$(RM) $(OBJ)

fclean : clean
	-@echo "Removing executive file..."
	$(RM) $(NAME)

re: fclean all
