FLAGS = -Wall -Wextra -Werror -lpthread

CC = gcc

RM = rm -f

NAME = philo

SRC = 	main.c utils.c check_arguments.c init.c execute_threads.c routines.c routine_utils.c\

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
