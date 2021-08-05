FLAGS = -Wall -Wextra -Werror -fsanitize=address -lpthread

CC = gcc -g

RM = rm -f

NAME = philo

SRC = 	main.c\

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
